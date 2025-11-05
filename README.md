# Snake-Game-CLI
This is a simple console based game. It can be played on windows machine only using arrow or WSAD keys. It comprises of three levels and few obstacles on road. Any further changes are truly appreciated. This code is extensible, i.e. new obstacles, levels can be added.

----------------------------------------------------------------------------------------------------------------------

**A. For Developers (Who wants to further extend the functionality of this code)**
For Developers: Architecture & Extension Guide
Overview
Classic Snake in C++ (Windows Console)

Multi-level difficulty, special food, obstacles, scoring

Tech Stack
Language: C++11+
Platform: Windows (Console API)

Dependencies: windows.h (console), conio.h (input), standard C++ libs

Core Components
Position struct: 2D coordinates, collision checks
Snake class: Controls movement, growth, collision (efficient head/tail ops using deque)
Food struct: Regular/special items, timed expiry, collision-free spawn
Game class: Controls game loop, rendering, input, scoring, difficulty, obstacles

Difficulty
| Mode   | Speed(ms) | Start Obstacles | Obstacles per 30 pts |
| ------ | --------- | --------------- | -------------------- |
| Easy   | 200       | 4               | +1                   |
| Medium | 100       | 6               | +2                   |
| Hard   | 80        | 12              | +3                   |

Rendering
Uses Windows Console color codes for snake, food, obstacles, score display
Board: 40x20, origin (0,0) top-left, cursor hidden for smoothness

Input
Arrow keys/WASD for movement, Q to quit
Prevents reversing direction to avoid instant self-collision

Building
Requires Windows + C++11 or later
Visual Studio: cl /EHsc /std:c++14 snake_game.cpp
MinGW: g++ -std=c++11 snake_game.cpp -o snake.exe

Possible Extensions
Speed/pause controls, save scores, larger boards, power-ups, multiplayer, improved rendering, file-based configs, and cross-platform support

For more details, see comments in code.
Feel free to modify/extend—this is an educational project!


--------------------------------------------------------------------------------------------------------------------------------

**B. For Users (who wants to run this game on their machine)**

Welcome!
Enjoy the classic Snake game with multiple difficulty levels, special foods, and obstacles!

System Requirements
- OS: Windows 7 or later (Windows 10/11 recommended)
- Console: Command Prompt/PowerShell with 42x24+ characters
- Keyboard: Standard

How to Run
1. Download snake.exe
2. Double-click or run from console:
      cd path\to\folder
      snake.exe
3. Choose difficulty and start playing!

Controls
- Arrow Keys or WASD to move
- Q to quit
- R to restart after game over

Gameplay
- Eat food (*) to grow and score 10 points
- Eat special food (@) worth 30 points; appears randomly, disappears after 5 seconds
- Avoid walls, your tail, and obstacles (#)
- Obstacles increase in number every 50 points

Difficulty Levels - 

| Level  | Speed           | Start Obstacles | Obstacles/50 pts |
| ------ | --------------- | --------------- | ---------------- |
| Easy   | Slow (200 ms)   | 4               | +1               |
| Medium | Medium (100 ms) | 6               | +2               |
| Hard   | Fast (80 ms)    | 12              | +3               |

Tips 
- Start on Easy to learn controls
- Focus on planning movements to avoid crashes
- Chase special food when safe for bonus points
- Use the full board to avoid trapping yourself

Game Over
Ends when you hit a wall, obstacle, or your own body. Try again to beat your high score!

Screen Layout

+----------------------------------------+
|                                        |
|          (Game Board Area)             |
|                                        |
+----------------------------------------+

Score: XXX    High Score: XXX    Level: Easy/Medium/Hard


-------------------------------------------------------------------------------------------------------------------------------------



