# Snake-SFML

A custom implementation of the classic Snake game written in C++ using SFML and ImGui. 

This project features sprite-sheet based 2D rendering and an integrated GUI that allows you to dynamically adjust the game board size and restart state in real-time.

## Technical Overview
* **Graphics:** Renders using a single texture atlas (`Textures.png`), cutting out specific `IntRect` regions for the snake head, body segments, fruit, and randomized grid background.
* **Settings UI:** Integrates `imgui-SFML` to provide an in-game settings panel. Players can modify the grid boundaries (`velicina.x` and `velicina.y`) and hit a custom Restart button without closing the application.
* **Game Loop:** Relies on a fixed window framerate limit (12 FPS) to dictate game speed and movement logic. Tail tracking is handled via standard 2D vector arrays.
* **SFML 3 API:** Built using modern SFML conventions, utilizing `std::optional` for event polling.

## Dependencies
To compile this project, your environment must be linked against:
* C++17 (or newer)
* [SFML 3.x](https://www.sfml-dev.org/)
* [ImGui-SFML](https://github.com/SFML/imgui-sfml)

Ensure `Textures.png` is placed in the same working directory as your compiled executable, or the sprites will fail to load.*

## Controls
* **Spacebar** - Start the game
* **W, A, S, D** - Change snake direction
* **ImGui Window** - Adjust grid size manually and trigger game restarts
