# 2048

Welcome to the 2048 game written in C++. This repository contains the source code for a console-based implementation of the popular 2048 game.

<p align="center">
    <img align="center" width=512 alt="2048 game demo" src="2048/assets/demo.gif">
</p>

## Game controls

- Use the `W`, `S`, `A`, `D` keys or arrow keys (`↑`, `↓`, `←`, `→`) to move tiles in the respective directions.
- Press `Q` anytime to quit the game.
- After game over, press `R` to play again.

## Compilation

To compile the project, follow these steps:

```
cd pcc-nejedly/2048/

cmake -Bcmake-build-debug -H. -DCMAKE_BUILD_TYPE=Debug
cmake --build cmake-build-debug
```

## Run

Navigate to the build directory and run the executable:

```
cd cmake-build-debug

./2048
```

### Run with parameters

You can customize the game board size using the `-s` or `--size` parameter. The valid range for size is 3 to 5, and the default size is 4. To use these parameters, run:

```
./2048 -s 3
./2048 -s 4
./2048 -s 5
```

To view additional program options, use the `--help` parameter:

```
./2048 --help
```

### Run tests

All the tests can be found in the `tests` folder. To run these tests, run:

```
./2048Tests
```
