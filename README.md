# CHIP-8 interpreter
## Description
CHIP-8 interpretor to run CHIP-8 games, written in C.
Cross-platform compilation (see *How-To compile*).
### Compilation
```shell script
mkdir build && cd build           // create build directory
conan install .. --build=missing  // install project dependencies
cmake .. && cmake --build .       // compile project
```
### Usage
```shell script
CHIP-8 -f <path_to_rom> [options]

options:
  -r, --ratio: pixel size ratio
  -l, --log: log file path
```
### Upcoming improvements
- Keyboard management in pure C (No dependence to the graphic library)
- Clock based game loop frequency

### Upcoming features
- Command line arguments parsing (options like screen-size, super-mode...)
