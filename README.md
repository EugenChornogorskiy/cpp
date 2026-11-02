# Living World (C++)

A turn-based simulation of a living world on a 2D grid, written in modern C++ as an exercise in object-oriented design. Organisms live on the board, act in order of initiative, age, gain power, reproduce and die. The world can be saved to and loaded from a binary file.

## Features

- **Class hierarchy with polymorphism**: an abstract `Organism` base class, abstract `Animal` and `Plant` branches, and concrete species `Sheep` and `Grass`. Behaviour (`action`, `onCollision`, `reproduce`, `isDead`) is overridden through virtual methods.
- **Turn engine** (`World::makeTurn`): organisms are sorted by initiative and act one by one. Dead organisms are removed at the end of each turn.
- **Life cycle**: every organism has an age, a lifespan, a power level that grows every turn and a power threshold that allows reproduction.
- **Reproduction** into a free neighbouring cell, which halves the parent's power.
- **Binary serialization**: `writeWorld` and `readWorld` save and restore the whole world (size, turn counter and every organism with its species and state) using virtual `serialize` / `deserialize` methods.
- **Modern memory management**: organisms are owned by `std::unique_ptr` inside the world, and the base class implements the rule of five (copy and move constructors and assignment operators).
- **Text rendering**: the board is printed every turn (`S` for sheep, `G` for grass, `.` for empty cells).

## Project structure

| File | Purpose |
|------|---------|
| `Position.h/.cpp` | 2D coordinates, distance and movement |
| `Organism.h/.cpp` | Abstract base class: power, age, lifespan, ancestors history, serialization |
| `Animal.h/.cpp` | Abstract animal: movement and collision rules |
| `Plant.h/.cpp` | Abstract plant: stationary organism |
| `Grass.h/.cpp` | Grass: grows and spreads to free neighbouring cells |
| `Sheep.h/.cpp` | Sheep: moves, eats grass, reproduces |
| `World.h/.cpp` | Board, turn logic, free-cell search, save and load |
| `LivingWorld.cpp` | Demo `main`: sets up a 6×6 world and runs 20+ turns |

## Build and run

Requires a C++17 compiler.

```bash
g++ -std=c++17 -Wall -Wextra *.cpp -o livingworld
./livingworld
```

With AddressSanitizer, which is useful while debugging memory handling:

```bash
g++ -std=c++17 -g -fsanitize=address,undefined *.cpp -o livingworld
```

## Example output

```
turn: 5
......
.SS...
....G.
..SGGG
.SGGGG
..GGGG
```

## Tech

C++17 · OOP (inheritance, polymorphism, abstract classes) · smart pointers · rule of five · binary file I/O

## Author

Yewhenii Chornohorskyi, Applied Computer Science, University of Gdańsk.
