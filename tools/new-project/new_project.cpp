// =============================================================================
// Modern C++23 Project Skeleton Generator
//
// Build:
//   g++ -std=c++23 -O2 tools/new-project/new_project.cpp -o build/new-project
//   (or cl /std:c++latest /EHsc tools\new-project\new_project.cpp)
//
// Usage:
//   ./build/new-project --name my-project --out ../my-project
// =============================================================================

#include <algorithm>
#include <cstdlib>
#include <expected>
#include <filesystem>
#include <format>
#include <fstream>
#include <print>
#include <ranges>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>

namespace fs = std::filesystem;

struct Config {
    std::string name;
    fs::path repo_root;
    fs::path dest_dir;
};

[[nodiscard]] auto is_valid_project_name(std::string_view name) noexcept -> bool {
    if (name.empty()) {
        return false;
    }
    return std::ranges::all_of(name, [](unsigned char ch) {
        return std::isalnum(ch) || ch == '-' || ch == '_';
    });
}

[[nodiscard]] auto parse_args(int argc, char* argv[]) -> std::expected<Config, std::string> {
    std::string name;
    fs::path out_dir;

    for (int i = 1; i < argc; ++i) {
        std::string_view arg{argv[i]};
        if ((arg == "--name" || arg == "-n") && i + 1 < argc) {
            name = argv[++i];
        } else if ((arg == "--out" || arg == "-o") && i + 1 < argc) {
            out_dir = argv[++i];
        } else if (arg == "--help" || arg == "-h") {
            return std::unexpected(
                "Usage: new-project --name <project-name> [--out <output-dir>]");
        } else {
            return std::unexpected(std::format("Unknown argument: {}", arg));
        }
    }

    if (!is_valid_project_name(name)) {
        return std::unexpected(
            "Invalid or missing --name (use only letters, digits, '-' or '_').\n"
            "Usage: new-project --name <project-name> [--out <output-dir>]");
    }

    std::error_code ec;
    fs::path repo_root = fs::current_path(ec);
    if (ec) {
        return std::unexpected(std::format("Failed to resolve current path: {}", ec.message()));
    }

    fs::path dest_dir = out_dir.empty()
                            ? (repo_root.parent_path() / name)
                            : fs::absolute(out_dir, ec);

    return Config{
        .name = std::move(name),
        .repo_root = std::move(repo_root),
        .dest_dir = std::move(dest_dir),
    };
}

[[nodiscard]] auto replace_all(std::string str, std::string_view from, std::string_view to)
    -> std::string {
    std::size_t pos = 0;
    while ((pos = str.find(from, pos)) != std::string::npos) {
        str.replace(pos, from.length(), to);
        pos += to.length();
    }
    return str;
}

[[nodiscard]] auto generate_project(const Config& cfg) -> std::expected<void, std::string> {
    std::error_code ec;

    if (fs::exists(cfg.dest_dir, ec)) {
        return std::unexpected(
            std::format("Destination directory already exists: {}", cfg.dest_dir.string()));
    }

    std::println("-- Creating new project '{}' at '{}'...", cfg.name, cfg.dest_dir.string());
    fs::create_directories(cfg.dest_dir, ec);
    if (ec) {
        return std::unexpected(
            std::format("Failed to create destination directory: {}", ec.message()));
    }

    constexpr std::string_view items_to_copy[] = {
        ".gitignore",
        "CMakeLists.txt",
        "CMakePresets.json",
        "CMakeUserPresets.json.example.md",
        "README.md",
        "cmake",
        "libs",
        "src",
    };

    for (std::string_view item : items_to_copy) {
        const fs::path src_path = cfg.repo_root / item;
        const fs::path dst_path = cfg.dest_dir / item;
        if (fs::exists(src_path, ec)) {
            fs::copy(src_path, dst_path,
                     fs::copy_options::recursive | fs::copy_options::overwrite_existing, ec);
            if (ec) {
                return std::unexpected(
                    std::format("Failed to copy '{}': {}", item, ec.message()));
            }
        }
    }

    // Rename src/sample-project -> src/<name>
    const fs::path old_src = cfg.dest_dir / "src" / "sample-project";
    const fs::path new_src = cfg.dest_dir / "src" / cfg.name;
    if (cfg.name != "sample-project" && fs::exists(old_src, ec)) {
        fs::rename(old_src, new_src, ec);
        if (ec) {
            return std::unexpected(
                std::format("Failed to rename source directory: {}", ec.message()));
        }
    }

    // Collect generated *-config.cmake files to delete and *-config.cmake.in files to rename
    std::vector<fs::path> to_remove;
    std::vector<fs::path> to_rename;

    for (const auto& entry : fs::recursive_directory_iterator(new_src, ec)) {
        if (!entry.is_regular_file()) {
            continue;
        }
        const std::string filename = entry.path().filename().string();
        if (filename.ends_with("-config.cmake") || filename.ends_with("-config-version.cmake")) {
            to_remove.push_back(entry.path());
        } else if (filename.contains("sample-project") && filename.ends_with("-config.cmake.in")) {
            to_rename.push_back(entry.path());
        }
    }

    for (const auto& p : to_remove) {
        fs::remove(p, ec);
    }

    for (const auto& p : to_rename) {
        const std::string new_filename =
            replace_all(p.filename().string(), "sample-project", cfg.name);
        fs::rename(p, p.parent_path() / new_filename, ec);
        if (ec) {
            return std::unexpected(
                std::format("Failed to rename template '{}': {}", p.string(), ec.message()));
        }
    }

    // Update META_PROJECT_NAME in root CMakeLists.txt
    const fs::path root_cmake = cfg.dest_dir / "CMakeLists.txt";
    std::ifstream in(root_cmake, std::ios::binary);
    if (!in) {
        return std::unexpected(std::format("Failed to read '{}'", root_cmake.string()));
    }
    std::ostringstream buffer;
    buffer << in.rdbuf();
    in.close();

    const std::string updated_cmake = replace_all(
        buffer.str(),
        R"(set(META_PROJECT_NAME "sample-project"))",
        std::format(R"(set(META_PROJECT_NAME "{}"))", cfg.name));

    std::ofstream out(root_cmake, std::ios::binary | std::ios::trunc);
    if (!out) {
        return std::unexpected(std::format("Failed to write '{}'", root_cmake.string()));
    }
    out << updated_cmake;
    out.close();

    // Initialize empty Git repository
    const std::string git_cmd = std::format("git -C \"{}\" init -q", cfg.dest_dir.string());
    if (std::system(git_cmd.c_str()) == 0) {
        std::println("-- Initialized empty Git repository in '{}'", cfg.dest_dir.string());
    }

    std::println("-- Done! Next steps:\n   cd {}", cfg.dest_dir.string());
    return {};
}

auto main(int argc, char* argv[]) -> int {
    const auto cfg = parse_args(argc, argv);
    if (!cfg) {
        std::println(stderr, "Error: {}", cfg.error());
        return EXIT_FAILURE;
    }

    if (const auto res = generate_project(*cfg); !res) {
        std::println(stderr, "Error: {}", res.error());
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

