<h1 align="center">SPR1D-GAME</h1>

<p align="center">
  <em>University Project</em>
</p>

<p align="center">
  <strong>Built with:</strong>
</p>

<p align="center">
<img src="https://img.shields.io/badge/C-A8B9CC?style=for-the-badge&logo=c&logoColor=white" alt="C">
  <img src="https://img.shields.io/badge/Make-FFD43B?style=for-the-badge&logo=gnu&logoColor=white" alt="Make">
  <img src="https://img.shields.io/badge/CMake-064F8C?style=for-the-badge&logo=cmake&logoColor=white" alt="CMake">
</p>

---

## Table of Contents

- [About the Project](#about-the-project)
- [Requirements](#requirements)
- [Usage](#usage)

## About the Project

SPR1D-GAME is a project developed for the University of Cagliari. The game simulates a competitive elimination-style challenge where at least 16 players compete in multiple mini-games, with only one winner standing. Players can be controlled by users or the CPU, and each round consists of different challenges requiring skill and/or luck.

The project is implemented in C using CMake for build automation. It focuses on efficient memory management, structured game logic, and a dynamic player system that allows interaction through both user input and AI-driven decisions.

Disclaimer: this project has been developed mainly for Linux x86/x64 systems. 

### Game Structure
1. **Selection Phase**: The initial number of players is reduced through a number-guessing game.
2. **Game Phase**: Players compete in various mini-games such as Rock-Paper-Scissors, Dice, Tic-Tac-Toe, and others. Winners proceed to the next round, while losers are eliminated.
3. **Final Phase**: The last two remaining players compete in a game of Blackjack to determine the ultimate winner.

## Requirements

SPR1D-GAME requires the following dependencies:

- **Make**
- **CMake**
- **GCC (GNU Compiler Collection)**
- **Ncurses library**

### Installation

#### Ubuntu/Debian:
```sh
sudo apt update && sudo apt install -y build-essential cmake gcc libncurses-dev libncursesw-dev
```

#### Fedora:
```sh
sudo dnf install -y make cmake gcc ncurses-devel
```

#### macOS (using Homebrew):
```sh
brew install make cmake gcc ncurses
```

## Usage

### Building the Project
To compile the project, run the following commands:
```sh
cmake . && make
```
This will generate the executable file in the project directory.

### Running the Game
Once compiled, you can start the game by executing:
```sh
./SPR1DGAME
```

### Cleaning the Build
To remove compiled files and reset the build directory, run:
```sh
make clean
```
