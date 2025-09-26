# Build-Rush
Build Rush is a causal arcade-style construction game designed for both single player and multiplayer gameplay

##  Game Description
**Build Rush** is a 2D block-stacking arcade game inspired by classic mobile stacking titles.  
Players drop moving blocks to create the tallest, most stable tower possible. Precise timing and streaks of accuracy are rewarded with a **repeating point-based scoring system**.  

The game supports both **single-player** and **multiplayer** modes for competitive fun.  


## Features
 **Single Player** with progressive difficulty.  
 **Multiplayer Mode** (two players on the same PC).  
 **Point System (repeats every 3 placements):**  
  - 1st block in a row → **+1 point**  
  - 2nd consecutive block → **+3 points**  
  - 3rd consecutive block → **+5 points**  
  - Then resets and repeats.  
  - Increasing block speed as towers grow taller.  
 -Tower physics: misaligned blocks reduce stability or collapse the tower.  
  -Scoreboards and high-score tracking.  



##  Project Details
-**IDE:** Visual Studio 2010 / 2013 (or later)  
-**Language:** C / C++  
- **Graphics Library:** iGraphics  
- **Platform:** Windows PC  
- **Genre:** 2D Arcade  


##  How to Build & Run

### Prerequisites
- Visual Studio (2013 or later recommended)  
- iGraphics library (included in the project folder)  
- Optional: MinGW compiler  

### Steps
1. Open the project in **Visual Studio**.  
2. Go to **File → Open → Project/Solution** and select the `.sln` file.  
3. Configure iGraphics include & library paths (Project → Properties → C/C++ → Additional Include Directories).  
4. Build the solution (**Build → Build Solution**).  
5. Run using **Debug → Start Without Debugging** or execute the compiled `.exe`.  



##  How to Play

### Controls
| Mode / Player | Action | Key |
|---------------|----------------|------------|
| Single Player | Drop Block | Space |
| Player 1 (MP) | Drop Block | S |
| Player 2 (MP) | Drop Block | Page Down |

## Game Rules
- Players drop blocks using their assigned keys:  
  - Single Player → Space  
  - Player 1 (Multiplayer) → S  
  - Player 2 (Multiplayer) → Page Down  
- Points are awarded based on the scoring sequence:  
  - 1st successful placement → 1 point  
  - 2nd consecutive → 3 points  
  - 3rd consecutive → 5 points  
  - After the 3rd placement, the cycle resets and repeats.  
- Blocks must be stacked accurately to avoid collapse.  
- The game ends if the tower collapses.  
- In multiplayer mode, the player with the higher score when a tower collapses wins.





## Project Contributors

1.Talha Jubeir
2.Sammyo Chakroborty
3.Tanveer Shahriar


## Screenshots
 

### **Main Menu**  
 <img src="https://github.com/sammyochak1050-max/Build-Rush/blob/06200bc3c87b803e9831e302c1bc6c0408824d3a/1000027823.jpg" width="200" height="200">

### **Single Player Gameplay**  
 <img src="https://github.com/sammyochak1050-max/Build-Rush/blob/3937039a5d9daaf5f12552d978c8cc9920bc1ac5/1000027822.jpg" width="200" height="200">   

###**Multiplayer Match**  
  <img src="https://github.com/sammyochak1050-max/Build-Rush/blob/89c8872fe11c90c1add239bf4e0fda2ab9b34fe4/1000027824.jpg" width="200" height="200">  




  ## YouTube Link
  [Build Rush Project:](https://youtu.be/OrEk-fGueaY/)
  
 ##Project Report
 [Project Report:Build Rush](https://docs.google.com/document/d/15pYN6JJF-TT0dzb1jL4aj-inb4q5mPXM/edit?usp=drive_link&ouid=106212286006993300162&rtpof=true&sd=true)



