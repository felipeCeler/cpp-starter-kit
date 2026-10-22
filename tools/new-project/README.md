# Project Skeleton Generators (`tools/new-project`)

This directory provides three equivalent, cross-platform generators to bootstrap a new project from `cpp-starter-kit` without requiring Python:

1. **[`new-project.cmake`](new-project.cmake)** — CMake 4.0+ Script Mode (`cmake -P`), zero additional dependencies.
2. **[`new_project.cpp`](new_project.cpp)** — Modern C++23 standalone CLI tool (`<print>`, `<format>`, `<expected>`, `<filesystem>`).
3. **[`new_project.go`](new_project.go)** — Go standalone CLI script/binary using only the Go standard library.

---

## What Each Generator Does

Given a project name `<name>` and an optional destination path `<out>` (defaults to `../<name>`):

1. **Copies** the starter kit skeleton (`.gitignore`, `CMakeLists.txt`, `CMakePresets.json`, `CMakeUserPresets.json.example.md`, `README.md`, `cmake/`, `libs/`, `src/`) into `<out>`, excluding `.git/`, `build/`, and `tools/`.
2. **Renames** `src/sample-project` to `src/<name>`.
3. **Cleans** any cached `*-config.cmake` and `*-config-version.cmake` files and **renames** `sample-project-*-config.cmake.in` to `<name>-*-config.cmake.in`.
4. **Updates** `set(META_PROJECT_NAME "sample-project")` to `set(META_PROJECT_NAME "<name>")` in the root `CMakeLists.txt`.
5. **Initializes** a fresh Git repository (`git init`) in `<out>`.

---

## 1. Using CMake (`new-project.cmake`)

Runs anywhere CMake 4.0+ is installed (Windows, Linux, macOS):

```bash
# Create ../my-app
cmake -DNAME="my-app" -P tools/new-project/new-project.cmake

# Or specify a custom destination directory
cmake -DNAME="my-app" -DOUT="/path/to/my-app" -P tools/new-project/new-project.cmake
```

---

## 2. Using Modern C++23 (`new_project.cpp`)

### Compile

**Linux / macOS (GCC 14+ or Clang 18+):**
```bash
g++ -std=c++23 -O2 tools/new-project/new_project.cpp -o build/new-project
```

**Windows (MSVC 2022 17.10+ / MSVC 2026 Developer Command Prompt):**
```powershell
cl /std:c++latest /O2 /EHsc tools\new-project\new_project.cpp /Fe:build\new-project.exe
```

### Run

```bash
# Create ../my-app
./build/new-project --name my-app

# Or specify a custom destination directory
./build/new-project --name my-app --out /path/to/my-app
```

---

## 3. Using Go (`new_project.go`)

### Run Directly

```bash
# Create ../my-app
go run tools/new-project/new_project.go -name my-app

# Or specify a custom destination directory
go run tools/new-project/new_project.go -name my-app -out /path/to/my-app
```

### Or Build a Static Binary

```bash
go build -o build/new-project tools/new-project/new_project.go
./build/new-project -name my-app -out /path/to/my-app
```

