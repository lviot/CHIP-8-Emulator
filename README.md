# CHIP-8 interpreter
## Description
CHIP-8 interpretor to run CHIP-8 games, written in C.
Compile exclusively on macOS for now.
### Compilation
```shell script
make
```
### Usage
```shell script
./CHIP-8 ./path/to/rom/file
```
### Upcoming improvements
- Keyboard management in pure C (No dependence to the graphic library)
- Clock based game loop frequency

### Upcoming features
- Cross platform compilation with CMake
- Command line arguments parsing (options like screen-size, super-mode...)
