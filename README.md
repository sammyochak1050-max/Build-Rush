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
| Mode / Player | Move Left | Move Right | Drop Block | Pause | Restart |
|---------------|-----------|------------|------------|-------|---------|
| **Single Player** | ← | → | Space | P | R |
| **Player 1 (Multiplayer)** | S | – | Space | P | R |
| **Player 2 (Multiplayer)** | Page Down | – | Space | P | R |


###  **Game Rules**
- Each player controls a block dropper on their side of the screen.  
- In **Single Player**, blocks are dropped using the **Space key**.  
- In **Multiplayer**,  
  - **Player 1 (Left Side)** drops blocks using the **S key**.  
  - **Player 2 (Right Side)** drops blocks using the **Page Down key**.  
- Points are awarded based on the special scoring sequence:  
  - 1st correctly placed block → **1 point**  
  - 2nd consecutive block → **3 points**  
  - 3rd consecutive block → **5 points**  
  - After the 3rd, the cycle resets back to 1 point.  
- The tower must remain stable — misaligned drops shorten blocks and may cause collapse.  
- The game ends when the tower collapses.  
- In **Multiplayer mode**, the player with the higher score when one tower collapses is declared the winner.






## Contributors

1.Talha Jubeir
2.Sammyo Chakroborty
3.Tanveer Shahriar


## Screenshots
> Replace placeholders with actual images.  

### **Main Menu**  

 

- **Single Player Gameplay**  
  ![Single Player](./screenshots/single.png)  

- **Multiplayer Match**  
  ![Multiplayer](./screenshots/multiplayer.png)  




  ## YouTube Link
  Build Rush Project: 
  
 ##Project Report
 Project Report:



