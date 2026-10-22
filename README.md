# cpp-starter-kit

This repository is a skeleton for cpp project using Qt, glfw and OpenGL.

The name of the project\* is defined by the variable META*PROJECT_NAME on the root CMakeLists.txt file. When modified, the "\_sample-project*" name and "_sample-project.config.cmake.in_" will be update accordingly.

```bash
.
├── cpp-starter-kit/
│   ├── build
│   ├── cmake
│   ├── files
│   ├── libs (Third Party Libraries)/
│   │   ├── glad
│   │   ├── glm
│   │   └── tinyobjloader
│   ├── src/
│   │   └── sample-project*/
│   │       ├── cmake/
│   │       │   └── sample-project.config.cmake.in*
│   │       ├── gui
│   │       └── CMakeLists.txt (For each gui type project itself)
│   └── tools/
│       └── new-project/
├── .gitignore
├── CMakeLists.txt (Meta Project Information)
└── README.md
```

# Build with preset

See [CMakeUserPresets.json.example.md](CMakeUserPresets.json.example.md) to configure your local user preset before building.
List available presets:

```bash
cmake --list-presets
```

# Starting a new project

You can generate a new project skeleton (automatically renaming `sample-project`, updating `META_PROJECT_NAME`, and initializing a fresh Git repository) using any of the generators in [`tools/new-project/`](tools/new-project/README.md):

**Option 1 — CMake Script Mode (Zero extra dependencies):**
```bash
cmake -DNAME="my-project" -DOUT="../my-project" -P tools/new-project/new-project.cmake
```

**Option 2 — C++23 CLI Tool:**
```bash
g++ -std=c++23 -O2 tools/new-project/new_project.cpp -o build/new-project
./build/new-project --name my-project --out ../my-project
```

**Option 3 — Go CLI Tool:**
```bash
go run tools/new-project/new_project.go -name my-project -out ../my-project
```

See [tools/new-project/README.md](tools/new-project/README.md) for full details.

Alternatively, you can export a raw zip archive of the repository with:
<code>git archive --format zip --output /full/path/to/zipfile.zip master</code>

### Reference

- Tree code - https://tree.nathanfriend.io/ and Markdown bash code - https://newbedev.com/is-there-a-way-to-represent-a-directory-tree-in-a-github-readme-md
- cmake-init - https://github.com/cginternals/cmake-init
- Find WindowsToolchain - https://github.com/MarkSchofield/WindowsToolchain
- WinQtDeploy Script - https://github.com/nitroshare/nitroshare-desktop
