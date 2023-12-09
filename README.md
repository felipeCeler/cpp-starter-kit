cpp-starter-kit
==================

This repository is a skeleton for cpp project using Qt5 and OpenGL.

The name of the project* is defined by the variable META_PROJECT_NAME on the root CMakeLists.txt file. When modified, the "_sample-project_" name and  "_sample-project.config.cmake.in_" will be update accordingly.

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
│   └── src/
│       └── smaple-project*/
│           ├── cmake/
│           │   └── sample-project.config.cmake.in*
│           ├── gui
│           └── CMakeLists.txt (For each gui type project itself)
├── .gitignore
├── CMakeLists.txt (Meta Project Information)
└── README.md
```

# Build without preset
Debug or Release
cmake -B build/Debug -GNinja -DCMAKE_BUILD_TYPE=Debug && cmake --build .\build\Debug

# Build with preset

You can use:
<code>git archive --format zip --output /full/path/to/zipfile.zip master</code>
to create a zip file of the project.

### Reference
- Tree code -  https://tree.nathanfriend.io/ and Markdown bash code - https://newbedev.com/is-there-a-way-to-represent-a-directory-tree-in-a-github-readme-md
- cmake-init - https://github.com/cginternals/cmake-init
