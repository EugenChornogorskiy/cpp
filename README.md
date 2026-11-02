# Living World (C++)

A turn-based ecosystem simulation written in C++17 with a native Windows (Win32/GDI) window. Sheep, wolves and several kinds of plants live on a grid: they move, eat, reproduce, age and die. The world can be saved to a binary file and loaded back while the simulation is running.

The project is an exercise in object-oriented design: an abstract class hierarchy, polymorphism through virtual methods, smart pointers and binary serialization.

## Species

| Symbol | Species | Behaviour |
|--------|---------|-----------|
| `S` | Sheep (`Sheep`) | Moves randomly, eats grass and gains its power, reproduces with another sheep when both are strong enough, dies when it runs into a wolf |
| `W` | Wolf (`Wilk`) | Stronger predator: eats sheep, reproduces with another wolf, lives longer than a sheep |
| `G` | Grass (`Grass`) | Plant that spreads to free neighbouring cells |
| `D` | Dandelion (`Mlecz`) | Plant that spreads to free neighbouring cells |
| `T` | Toadstool (`Muchomor`) | Longer-living plant that spreads more slowly |

When two animals of other species meet, the one with more power wins.

## Features

- **Class hierarchy with polymorphism**: abstract `Organism`, abstract `Animal` and `Plant` branches, and concrete species. Behaviour (`action`, `onCollision`, `reproduce`, `isDead`) is overridden through virtual methods.
- **Turn engine** (`World::makeTurn`): organisms act in order of initiative. Dead organisms are marked during the turn and removed at its end, so no object is deleted while it is still being used.
- **Life cycle**: every organism has an age, a lifespan, a power level that grows each turn and a threshold that allows reproduction.
- **Ancestry tracking**: an organism records the birth and death turns of its ancestors, and children inherit that history.
- **Binary save and load** (`writeWorld`, `readWorld`): world size, turn counter and every organism, using virtual `serialize` / `deserialize` methods. `OrganismFactory` recreates the right class from the species symbol stored in the file.
- **Modern memory management**: organisms are owned by `std::unique_ptr`, and the base classes implement the rule of five.
- **Real-time window**: the board is drawn with GDI and advances automatically on a timer.

## Controls

| Key | Action |
|-----|--------|
| `Space` | Pause / resume automatic turns |
| `→` | Advance one turn manually |
| `S` | Save the world to `world.bin` |
| `L` | Load the world from `world.bin` |
| `Esc` | Quit |

## Project structure

| File | Purpose |
|------|---------|
| `Position.h/.cpp` | 2D coordinates, distance and movement |
| `Organism.h/.cpp` | Abstract base class: power, age, lifespan, ancestry, serialization |
| `Animal.h/.cpp` | Abstract animal: movement and default collision rules |
| `Plant.h/.cpp` | Abstract plant: stationary organism |
| `Sheep`, `Wilk` | Animals |
| `Grass`, `Mlecz`, `Muchomor` | Plants |
| `OrganismFactory.h` | Creates organisms from their species symbol when loading |
| `World.h/.cpp` | Board, turn logic, neighbour search, save and load |
| `MainWindow.cpp` | Win32 window, drawing, timer and keyboard input |

## Build and run

Requires Windows and a C++17 compiler such as MinGW-w64 or Visual Studio.

```bash
g++ -std=c++17 *.cpp -o program.exe -mwindows -lgdi32
program.exe
```

The simulation core (everything except `MainWindow.cpp`) uses only standard C++ and builds on any platform.

## Tech

C++17 · OOP (inheritance, polymorphism, abstract classes) · smart pointers · rule of five · binary file I/O · Win32 API (GDI)

## Author

Yewhenii Chornohorskyi, Applied Computer Science, University of Gdańsk.
