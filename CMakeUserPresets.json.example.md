# `CMakeUserPresets.json` Explanation & Guide

`CMakeUserPresets.json` is used for **developer-specific, machine-local configuration** (custom SDK paths, local compilers, and parallel job counts). It is excluded from version control (`.gitignore`) so individual developers can customize their environment without modifying the shared `CMakePresets.json`.

---

## 1. Complete Example (`CMakeUserPresets.json`)

```json
{
  "version": 8,
  "cmakeMinimumRequired": {
    "major": 3,
    "minor": 30,
    "patch": 0
  },
  "configurePresets": [
    {
      "name": "common-cache-qt6-install-path",
      "hidden": true,
      "cacheVariables": {
        "CMAKE_PREFIX_PATH": "$env{Qt6_DIR}",
        "CMAKE_INSTALL_PREFIX": "${sourceDir}/build/${presetName}/install"
      }
    },
    {
      "name": "common-cache-qt6-install-path-linux",
      "hidden": true,
      "cacheVariables": {
        "CMAKE_INSTALL_PREFIX": "${sourceDir}/build/${presetName}/install"
      }
    },
    {
      "name": "local-debug-msvc2022-x64-ninja-generator",
      "inherits": [
        "debug-msvc2022-x64-ninja-generator",
        "common-cache-qt6-install-path"
      ]
    },
    {
      "name": "local-release-msvc2022-x64-ninja-generator",
      "inherits": [
        "release-msvc2022-x64-ninja-generator",
        "common-cache-qt6-install-path"
      ]
    },
    {
      "name": "local-debug-msvc2026-x64-ninja-generator",
      "inherits": [
        "debug-msvc2026-x64-ninja-generator",
        "common-cache-qt6-install-path"
      ]
    },
    {
      "name": "local-release-msvc2026-x64-ninja-generator",
      "inherits": [
        "release-msvc2026-x64-ninja-generator",
        "common-cache-qt6-install-path"
      ]
    },
    {
      "name": "local-debug-gcc-x64-ninja-generator",
      "inherits": [
        "debug-gcc-x64-ninja-generator",
        "common-cache-qt6-install-path-linux"
      ]
    }
  ],
  "buildPresets": [
    {
      "name": "local-build-debug-msvc2026-x64-ninja-generator",
      "displayName": "Local Build Debug (MSVC 2026)",
      "configurePreset": "local-debug-msvc2026-x64-ninja-generator",
      "jobs": 20
    },
    {
      "name": "local-install-debug-msvc2026-x64-ninja-generator",
      "displayName": "Local Install Debug (MSVC 2026)",
      "configurePreset": "local-debug-msvc2026-x64-ninja-generator",
      "targets": ["install"]
    },
    {
      "name": "local-build-release-msvc2026",
      "displayName": "Local Build Release (MSVC 2026)",
      "configurePreset": "local-release-msvc2026-x64-ninja-generator",
      "jobs": 20
    },
    {
      "name": "local-install-release-msvc2026",
      "displayName": "Local Install Release (MSVC 2026)",
      "configurePreset": "local-release-msvc2026-x64-ninja-generator",
      "targets": ["install"]
    },
    {
      "name": "local-build-debug-gcc-x64-ninja-generator",
      "displayName": "Local Build Debug (GCC)",
      "configurePreset": "local-debug-gcc-x64-ninja-generator",
      "jobs": 20
    }
  ]
}
```

---

## 2. Section Breakdown

### A. Schema & Minimum Required Version

```json
"version": 8,
"cmakeMinimumRequired": {
    "major": 3,
    "minor": 30,
    "patch": 0
}
```

- **`version: 8`**: Specifies the CMake presets format version (introduced with CMake 3.30).
- **`cmakeMinimumRequired`**: Ensures CMake versions older than 3.30 reject the file upfront rather than failing with cryptic parsing errors.

---

### B. Common Reusable Fragments (`hidden: true`)

These presets are base fragments (mixins) used to share common cache variables among multiple presets. Because `"hidden": true` is set, they do not appear in the IDE or command-line preset list.

#### 1. Qt6 Search Path + Demo Install Destination

```json
{
  "name": "common-cache-qt6-install-path",
  "hidden": true,
  "cacheVariables": {
    "CMAKE_PREFIX_PATH": "$env{Qt6_DIR}",
    "CMAKE_INSTALL_PREFIX": "${sourceDir}/build/${presetName}/install"
  }
}
```

- **`CMAKE_PREFIX_PATH: "$env{Qt6_DIR}"`**: Reads the local environment variable `Qt6_DIR` (e.g. `C:\Qt\6.8.0\msvc2022_64`) so `find_package(Qt6)` locates the Qt installation on the developer machine.
- **`CMAKE_INSTALL_PREFIX`**: Designates where the compiled sample/demo binaries, dependencies, and assets are installed when running the `install` target. By using `${sourceDir}/build/${presetName}/install`, each preset installs neatly inside its own build tree.

#### 2. Demo Install Destination Only

```json
{
  "name": "common-cache-qt6-install-path-linux",
  "hidden": true,
  "cacheVariables": {
    "CMAKE_INSTALL_PREFIX": "${sourceDir}/build/${presetName}/install"
  }
}
```

- Defines **only** `CMAKE_INSTALL_PREFIX` without overriding `CMAKE_PREFIX_PATH`.
- Used when Qt is already in system PATH / standard library locations (such as system package manager installs), or for builds where manual Qt paths are not required.

---

### C. Concrete Configure Presets (`local-*`)

These are the runnable presets that appear in your IDE (VS Code / Visual Studio) and `cmake --list-presets`.

```json
{
  "name": "local-debug-msvc2026-x64-ninja-generator",
  "inherits": [
    "debug-msvc2026-x64-ninja-generator",
    "common-cache-qt6-install-path"
  ]
}
```

- **Multiple Inheritance (`inherits`)**:
  1. **Shared Project Settings** (`debug-msvc2026-x64-ninja-generator` from `CMakePresets.json`): Inherits compiler flags, MSVC environment, generator (`Ninja`), and build type (`Debug`).
  2. **Local Machine Settings** (`common-cache-qt6-install-path`): Injects the developer's local `Qt6_DIR` and demo install directory.

---

### D. Build Presets (`buildPresets`)

Build presets automate invoking the build tool (`Ninja`) with predefined options, targets, and parallel execution jobs.

#### 1. Compile Preset

```json
{
  "name": "local-build-debug-msvc2026-x64-ninja-generator",
  "displayName": "Local Build Debug (MSVC 2026)",
  "configurePreset": "local-debug-msvc2026-x64-ninja-generator",
  "jobs": 20
}
```

- **`configurePreset`**: Associates this build preset with its corresponding configuration.
- **`jobs: 20`**: Runs compilation across 20 parallel threads (equivalent to `ninja -j 20`).

#### 2. Install Preset

```json
{
  "name": "local-install-debug-msvc2026-x64-ninja-generator",
  "displayName": "Local Install Debug (MSVC 2026)",
  "configurePreset": "local-debug-msvc2026-x64-ninja-generator",
  "targets": ["install"]
}
```

- **`targets: ["install"]`**: Builds the `install` target directly, placing the output demo executable and assets into `build/<presetName>/install`.

---

## 3. Quick CLI Reference

```bash
# 1. View all configured presets
cmake --list-presets

# 2. Configure the project using a user preset
cmake --preset local-debug-msvc2026-x64-ninja-generator

# 3. Build the sample/demo project
cmake --build --preset local-build-debug-msvc2026-x64-ninja-generator

# 4. Install the sample/demo project
cmake --build --preset local-install-debug-msvc2026-x64-ninja-generator
```
