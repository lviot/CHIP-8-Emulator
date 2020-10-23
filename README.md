# CHIP-8 interpreter
## Description
CHIP-8 interpretor to run CHIP-8 games, written in C.
Cross-platform compilation (see section *compilation*).
**Work in progress**, please be indulgent 🙏 there are still a lot of bugs.
### 🤖 Compilation
```shell script
mkdir build && cd build           // create build directory
conan install .. --build=missing  // install project dependencies
cmake .. && cmake --build .       // compile project
```
### 💡 Usage
```shell script
CHIP-8 -f <path_to_rom> [options]

options:
  -r, --ratio: pixel size ratio
  -l, --log: log file path
```

### 🛠 Tests
Made with criterion, and so not cross-platform. In progress.

Upcoming improvements! 🥳
