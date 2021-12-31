cpp-starter-kit
==================

This repository is a skeleton for cpp project using Qt5 and OpenGL.

Default folder structure. The name of the project* is defined by the variable META_PROJECT_NAME on the root CMakeLists.txt file. It when modified, for instance, the "sample-project" name and  "sample-project.config.cmake.in" will be update accordingly.

```bash
cpp-starter-kit
├── build
├── cmake
├── files
├── libs (Third Party Libraries)
│   ├── glad
│   ├── glm
│   └── tinyobjloader
└── src
    └── smaple-project*
        ├── cmake
        │   └── sample-project.config.cmake.in*
        ├── gui
        └── CMakeLists.txt (Project Itself)
.gitignore
CMakeLists.txt (Meta Project Information)
README.md
```
