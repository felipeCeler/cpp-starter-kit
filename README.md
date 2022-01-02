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
│   ├── libs (_Third Party Libraries_)/
│   │   ├── glad
│   │   ├── glm
│   │   └── tinyobjloader
│   └── src/
│       └── smaple-project*/
│           ├── cmake/
│           │   └── sample-project.config.cmake.in*
│           ├── gui
│           └── CMakeLists.txt (_Project Itself_)
├── .gitignore
├── CMakeLists.txt (_Meta Project Information_)
└── README.md
```

### Reference
- Tree code -  https://tree.nathanfriend.io/ and Markdown bash code - https://newbedev.com/is-there-a-way-to-represent-a-directory-tree-in-a-github-readme-md
