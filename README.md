# 🐿️ Hungry Squirrel  
*A fun terminal arcade game written in C*

Hungry Squirrel is a fast-paced ASCII terminal game where you control a squirrel on a mission to collect nuts while avoiding danger. As your score increases, the difficulty increases too. Simple idea, addictive gameplay.

---

# 🎮 Game Versions

## 🟢 Version 1 – Classic Edition (Windows Only)

### 📌 Overview
The original release of Hungry Squirrel.  
A lightweight terminal game built using Windows-specific libraries.

### 🎯 Gameplay
- Control the squirrel `Q`
- Collect nuts `@`
- Avoid hitting walls `X`
- Each nut gives **+5 points**
- Speed increases as score increases
- High score saved locally

### 💻 Platform
- Windows only  
- Uses `conio.h` and `windows.h`

### ▶️ Compile & Run (Windows – MinGW)
```

gcc hungrySquirrelV1.c -o game.exe
game.exe

```

---

## 🔵 Version 2 – Enhanced Cross-Platform Edition (Windows + Ubuntu)

### 📌 Overview
A fully improved and optimized version with better performance, additional gameplay mechanics, and cross-platform compatibility.

### 🚀 New Features
- 🐍 Tail system (snake-style growth)
- 💥 Self-collision detection
- 📈 Level progression
- ⭐ Power-up nuts
- ⚡ Smoother rendering using ANSI escape codes
- 🛡 Safer high score handling
- 🖥 Cross-platform keyboard input
- 🚀 Improved performance (no system calls for clearing screen)

### 🎯 Gameplay
- Squirrel head: `Q`
- Tail: `o`
- Regular nut: `@` (+5 points)
- Power nut: `$` (+15 points)
- Walls: `#`
- Speed increases with levels
- High score persists across sessions

### 💻 Platform Support
- Windows
- Ubuntu / Linux
- Any ANSI-compatible terminal

### ▶️ Compile & Run

#### Windows
```

gcc hungrySquirrelV2.c -o game.exe
game.exe

```

#### Ubuntu / Linux
```

gcc hungrySquirrelV2.c -o game
./game

```

---

# 🎮 Controls

| Action       | Key |
|--------------|-----|
| Move Up      | W |
| Move Down    | S |
| Move Left    | A |
| Move Right   | D |
| Start Game   | SPACE |
| Restart      | R |
| Exit         | X |

---

# 🧠 Concepts Used

- C programming fundamentals  
- File handling  
- Random number generation  
- ANSI escape codes  
- Non-blocking keyboard input  
- Conditional compilation  
- Game loop design  
- Collision detection  
- Dynamic difficulty scaling  

---

# 🏆 Why This Project Stands Out

- Runs completely inside terminal  
- No external libraries required  
- Demonstrates system-level programming  
- Shows progression from basic to advanced version  
- Lightweight, fast, and portable  

---

Enjoy the game and try to beat your high score! 🥜🐿️🏆
