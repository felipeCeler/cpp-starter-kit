# `CMakeUserPresets.json` Explanation & Guide

`CMakeUserPresets.json` is used for **developer-specific, machine-local configuration** (custom SDK paths, local compilers, and parallel job counts). It is excluded from version control (`.gitignore`) so individual developers can customize their environment without modifying the shared `CMakePresets.json`.

---

## 1. Complete Example (`CMakeUserPresets.json`)

```json
{
  "version": 10,
  "cmakeMinimumRequired": {
    "major": 4,
    "minor": 0,
    "patch": 0
  },
  "configurePresets": [
    {
      "name": "common-qt6-path",
      "hidden": true,
      "cacheVariables": {
        "CMAKE_PREFIX_PATH": "$env{Qt6_DIR}"
      }
    },
    {
      "name": "local-debug-msvc2022-x64-ninja-generator",
      "displayName": "Local Debug (MSVC 2022 x64 Ninja)",
      "inherits": [
        "debug-msvc2022-x64-ninja-generator",
        "common-qt6-path"
      ]
    },
    {
      "name": "local-release-msvc2022-x64-ninja-generator",
      "displayName": "Local Release (MSVC 2022 x64 Ninja)",
      "inherits": [
        "release-msvc2022-x64-ninja-generator",
        "common-qt6-path"
      ]
    },
    {
      "name": "local-debug-msvc2026-x64-ninja-generator",
      "displayName": "Local Debug (MSVC 2026 x64 Ninja)",
      "inherits": [
        "debug-msvc2026-x64-ninja-generator",
        "common-qt6-path"
      ]
    },
    {
      "name": "local-release-msvc2026-x64-ninja-generator",
      "displayName": "Local Release (MSVC 2026 x64 Ninja)",
      "inherits": [
        "release-msvc2026-x64-ninja-generator",
        "common-qt6-path"
      ]
    },
    {
      "name": "local-debug-gcc-x64-ninja-generator",
      "displayName": "Local Debug (GCC x64 Ninja)",
      "inherits": [
        "debug-gcc-x64-ninja-generator"
      ]
    },
    {
      "name": "local-release-gcc-x64-ninja-generator",
      "displayName": "Local Release (GCC x64 Ninja)",
      "inherits": [
        "release-gcc-x64-ninja-generator"
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
      "name": "local-build-release-msvc2026-x64-ninja-generator",
      "displayName": "Local Build Release (MSVC 2026)",
      "configurePreset": "local-release-msvc2026-x64-ninja-generator",
      "jobs": 20
    },
    {
      "name": "local-install-release-msvc2026-x64-ninja-generator",
      "displayName": "Local Install Release (MSVC 2026)",
      "configurePreset": "local-release-msvc2026-x64-ninja-generator",
      "targets": ["install"]
    },
    {
      "name": "local-build-debug-gcc-x64-ninja-generator",
      "displayName": "Local Build Debug (GCC)",
      "configurePreset": "local-debug-gcc-x64-ninja-generator",
      "jobs": 20
    },
    {
      "name": "local-install-debug-gcc-x64-ninja-generator",
      "displayName": "Local Install Debug (GCC)",
      "configurePreset": "local-debug-gcc-x64-ninja-generator",
      "targets": ["install"]
    },
    {
      "name": "local-build-release-gcc-x64-ninja-generator",
      "displayName": "Local Build Release (GCC)",
      "configurePreset": "local-release-gcc-x64-ninja-generator",
      "jobs": 20
    },
    {
      "name": "local-install-release-gcc-x64-ninja-generator",
      "displayName": "Local Install Release (GCC)",
      "configurePreset": "local-release-gcc-x64-ninja-generator",
      "targets": ["install"]
    }
  ]
}
```

---

## 2. Section Breakdown

### A. Schema & Minimum Required Version

```json
"version": 10,
"cmakeMinimumRequired": {
    "major": 4,
    "minor": 0,
    "patch": 0
}
```

- **`version: 10`**: Specifies the CMake presets format version (supported in CMake 4.0+, adding `$comment` and `graphviz` fields).
- **`cmakeMinimumRequired`**: Ensures CMake versions older than 4.0.0 reject the file upfront rather than failing with cryptic parsing errors.

---

### B. Common Reusable Fragment (`hidden: true`)

This preset is a base fragment (mixin) used to share the local Qt6 search path among multiple presets. Because `"hidden": true` is set, it does not appear in the IDE or command-line preset list.

```json
{
  "name": "common-qt6-path",
  "hidden": true,
  "cacheVariables": {
    "CMAKE_PREFIX_PATH": "$env{Qt6_DIR}"
  }
}
```

- **`CMAKE_PREFIX_PATH: "$env{Qt6_DIR}"`**: Reads the local environment variable `Qt6_DIR` (e.g. `C:\Qt\6.8.0\msvc2022_64`) so `find_package(Qt6)` locates the Qt installation on the developer machine.
- *(Note: The install destination `"installDir": "${sourceDir}/build/${presetName}/install"` is already defined project-wide in `cmake/presets/generators.json`).*

---

### C. Concrete Configure Presets (`local-*`)

These are the runnable presets that appear in your IDE (VS Code / Visual Studio) and `cmake --list-presets`.

```json
{
  "name": "local-debug-msvc2026-x64-ninja-generator",
  "displayName": "Local Debug (MSVC 2026 x64 Ninja)",
  "inherits": [
    "debug-msvc2026-x64-ninja-generator",
    "common-qt6-path"
  ]
}
```

- **Multiple Inheritance (`inherits`)**:
  1. **Shared Project Settings** (`debug-msvc2026-x64-ninja-generator` from `CMakePresets.json`): Inherits compiler flags, MSVC environment, generator (`Ninja`), `binaryDir`, `installDir`, and build type (`Debug`).
  2. **Local Machine Settings** (`common-qt6-path`): Injects the developer's local `Qt6_DIR`.

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

## 3. Minimal Example: Quick-Start (MSVC & Linux GCC)

If you only want a minimal `CMakeUserPresets.json` with just the essential Debug presets for Windows (MSVC) and Linux (GCC):

```json
{
  "version": 10,
  "cmakeMinimumRequired": {
    "major": 4,
    "minor": 0,
    "patch": 0
  },
  "configurePresets": [
    {
      "name": "common-qt6-path",
      "hidden": true,
      "cacheVariables": {
        "CMAKE_PREFIX_PATH": "$env{Qt6_DIR}"
      }
    },
    {
      "name": "local-debug-msvc2026-x64-ninja-generator",
      "displayName": "Local Debug (MSVC 2026 x64 Ninja)",
      "inherits": [
        "debug-msvc2026-x64-ninja-generator",
        "common-qt6-path"
      ]
    },
    {
      "name": "local-debug-gcc-x64-ninja-generator",
      "displayName": "Local Debug (GCC x64 Ninja)",
      "inherits": [
        "debug-gcc-x64-ninja-generator"
      ]
    }
  ],
  "buildPresets": [
    {
      "name": "local-build-debug-msvc2026-x64-ninja-generator",
      "displayName": "Build Local Debug (MSVC 2026 x64 Ninja)",
      "configurePreset": "local-debug-msvc2026-x64-ninja-generator",
      "jobs": 20
    },
    {
      "name": "local-build-debug-gcc-x64-ninja-generator",
      "displayName": "Build Local Debug (GCC x64 Ninja)",
      "configurePreset": "local-debug-gcc-x64-ninja-generator",
      "jobs": 20
    }
  ]
}
```

### CLI commands for the minimal setup:

**Windows (MSVC):**

```bash
# Configure
cmake --preset local-debug-msvc2026-x64-ninja-generator

# Build
cmake --build --preset local-build-debug-msvc2026-x64-ninja-generator
```

**Linux (GCC):**

```bash
# Configure
cmake --preset local-debug-gcc-x64-ninja-generator

# Build
cmake --build --preset local-build-debug-gcc-x64-ninja-generator
```
