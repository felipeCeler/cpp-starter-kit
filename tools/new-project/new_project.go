// =============================================================================
// Go Project Skeleton Generator
//
// Usage:
//   go run tools/new-project/new_project.go -name my-project -out ../my-project
// =============================================================================
package main

import (
	"flag"
	"fmt"
	"io"
	"io/fs"
	"os"
	"os/exec"
	"path/filepath"
	"regexp"
	"strings"
)

var validNameRe = regexp.MustCompile(`^[A-Za-z0-9_-]+$`)

func main() {
	name := flag.String("name", "", "New project name (required)")
	out := flag.String("out", "", "Destination directory (defaults to ../<name>)")
	flag.Parse()

	if *name == "" {
		fmt.Fprintln(os.Stderr, "Error: -name is required.\nUsage: go run tools/new-project/new_project.go -name <project-name> [-out <output-dir>]")
		os.Exit(1)
	}
	if !validNameRe.MatchString(*name) {
		fmt.Fprintf(os.Stderr, "Error: invalid project name %q (use letters, digits, '-' or '_').\n", *name)
		os.Exit(1)
	}

	repoRoot, err := filepath.Abs(".")
	if err != nil {
		fatal(err)
	}

	destDir := *out
	if destDir == "" {
		destDir = filepath.Join(filepath.Dir(repoRoot), *name)
	}
	destDir, err = filepath.Abs(destDir)
	if err != nil {
		fatal(err)
	}

	if _, err := os.Stat(destDir); err == nil {
		fatal(fmt.Errorf("destination directory already exists: %s", destDir))
	}

	fmt.Printf("-- Creating new project %q at %s...\n", *name, destDir)

	itemsToCopy := []string{
		".gitignore",
		"CMakeLists.txt",
		"CMakePresets.json",
		"CMakeUserPresets.json.example.md",
		"README.md",
		"cmake",
		"libs",
		"src",
	}

	for _, item := range itemsToCopy {
		srcPath := filepath.Join(repoRoot, item)
		dstPath := filepath.Join(destDir, item)
		if _, err := os.Stat(srcPath); err == nil {
			if err := copyPath(srcPath, dstPath); err != nil {
				fatal(err)
			}
		}
	}

	// Rename src/sample-project -> src/<name>
	oldSrc := filepath.Join(destDir, "src", "sample-project")
	newSrc := filepath.Join(destDir, "src", *name)
	if *name != "sample-project" {
		if err := os.Rename(oldSrc, newSrc); err != nil {
			fatal(err)
		}
	}

	// Remove generated *-config.cmake files and rename *-config.cmake.in templates
	err = filepath.WalkDir(newSrc, func(path string, d fs.DirEntry, err error) error {
		if err != nil || d.IsDir() {
			return err
		}
		base := d.Name()
		if strings.HasSuffix(base, "-config.cmake") || strings.HasSuffix(base, "-config-version.cmake") {
			return os.Remove(path)
		}
		if strings.Contains(base, "sample-project") && strings.HasSuffix(base, "-config.cmake.in") {
			newBase := strings.ReplaceAll(base, "sample-project", *name)
			return os.Rename(path, filepath.Join(filepath.Dir(path), newBase))
		}
		return nil
	})
	if err != nil {
		fatal(err)
	}

	// Update META_PROJECT_NAME in root CMakeLists.txt
	cmakeListsPath := filepath.Join(destDir, "CMakeLists.txt")
	content, err := os.ReadFile(cmakeListsPath)
	if err != nil {
		fatal(err)
	}
	updated := strings.ReplaceAll(
		string(content),
		`set(META_PROJECT_NAME "sample-project")`,
		fmt.Sprintf(`set(META_PROJECT_NAME %q)`, *name),
	)
	if err := os.WriteFile(cmakeListsPath, []byte(updated), 0o644); err != nil {
		fatal(err)
	}

	// Initialize Git repository
	if _, err := exec.LookPath("git"); err == nil {
		cmd := exec.Command("git", "init", "-q")
		cmd.Dir = destDir
		if err := cmd.Run(); err == nil {
			fmt.Printf("-- Initialized empty Git repository in %s\n", destDir)
		}
	}

	fmt.Printf("-- Done! Next steps:\n   cd %s\n", destDir)
}

func copyPath(src, dst string) error {
	info, err := os.Stat(src)
	if err != nil {
		return err
	}
	if !info.IsDir() {
		return copyFile(src, dst, info.Mode())
	}
	return filepath.WalkDir(src, func(path string, d fs.DirEntry, err error) error {
		if err != nil {
			return err
		}
		rel, err := filepath.Rel(src, path)
		if err != nil {
			return err
		}
		target := filepath.Join(dst, rel)
		if d.IsDir() {
			return os.MkdirAll(target, 0o755)
		}
		fInfo, err := d.Info()
		if err != nil {
			return err
		}
		return copyFile(path, target, fInfo.Mode())
	})
}

func copyFile(src, dst string, mode fs.FileMode) error {
	if err := os.MkdirAll(filepath.Dir(dst), 0o755); err != nil {
		return err
	}
	in, err := os.Open(src)
	if err != nil {
		return err
	}
	defer in.Close()

	out, err := os.OpenFile(dst, os.O_CREATE|os.O_WRONLY|os.O_TRUNC, mode)
	if err != nil {
		return err
	}
	defer out.Close()

	_, err = io.Copy(out, in)
	return err
}

func fatal(err error) {
	fmt.Fprintf(os.Stderr, "Error: %v\n", err)
	os.Exit(1)
}
