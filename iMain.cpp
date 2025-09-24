#include "iGraphics.h"
#include <cmath>
#include <string>

// screen size
int baseWidth = 350;                      // width of one game page
int screenHeight = 700;
int dividerWidth = 20;                    
int screenWidth = baseWidth * 2 + dividerWidth; 
int middleStart = (screenWidth - baseWidth) / 2;

// images
int imgHook, imgBlock, imgRope, imgBackground, imgMenu,imgBrick,imgBBuilding;

// block
float blockWidth = 80, blockHeight = 60;
float hookLength = 150;
float hookWidth = 14;
float ropeWidthBase = blockWidth - 20;
float ropeLengthBase = 20;
float baseGround = 330; // fixed ground for each page

// ------------- Game modes -------------
bool Menu = true;
bool HistoryMenu = false;
bool Multiplayer = false; // MP mode on/off

// ------------- History storage -------------
struct Match {
	int blocks;
	int score;
};
Match history[5];
int historyCount = 0;

// =============== Parameterized game state ===============
struct GameState {
	// state
	bool BlockFalling = false;
	bool gameOver = false;

	// hooks swing
	float centerX = baseWidth / 2.0f;
	float centerY = screenHeight;
	float hookAngle = 0;
	float angleSpeed = 2;
	float maxSwingAngle = 70;

	// rope positions
	float ropeX = 0, ropeY = 0;
	float ropeWidth = ropeWidthBase;
	float ropeLength = ropeLengthBase;

	// hook position
	float hookX = 0, hookY = 0;

	// falling block
	float fallX = 0.0f, fallY = 0.0f;
	float fallSpeed = 5.0;

	// ground and stack
	float ground = baseGround;
	float blockX[1000];
	float blockY[1000];
	int   blockCount = 0;

	// camera move
	float screenMove = 0;

	// block swing
	float angle = 0;
	float swingSpeed = 0.1 * 0.4;
	float s = 0;
	float maxAngle = 0;
	float avgX = 0;
	float totalX = 0;

	// score
	int totalBlocks = 0;
	int score = 0;
	int streak = 0;

	// label for messages
	const char* label = "Single";
};

// Single player
GameState single;
// Multiplayer
GameState leftGS;
GameState rightGS;

// =============== Generic game logic ===============
void updateHook(GameState &g) {
	if (g.gameOver) return;
	g.hookAngle += g.angleSpeed;
	if (g.hookAngle > g.maxSwingAngle || g.hookAngle < -g.maxSwingAngle) {
		g.angleSpeed *= -1;
	}

	g.hookX = g.centerX + hookLength * sin(g.hookAngle * 3.1416f / 180);
	g.hookY = g.centerY - hookLength * cos(g.hookAngle * 3.1416f / 180);

	if (!g.BlockFalling) {
		g.ropeX = g.hookX - g.ropeWidth / 2;
		g.ropeY = g.hookY - g.ropeLength;
		g.fallX = g.hookX - blockWidth / 2;
		g.fallY = g.hookY - g.ropeLength - blockHeight;
	}
}

void swing(GameState &g) {
	if (g.blockCount >= 5) {
		g.s = (g.avgX - blockWidth / 2) / 2 + (g.blockX[g.blockCount - 1] - g.avgX);
		g.maxAngle = atan2(g.blockY[g.blockCount - 1] + blockHeight, g.s);
		if (g.s < 0) {
			g.swingSpeed *= -1;
		}
	}
}

void gravity(GameState &g) {
	if (g.blockCount >= 6) {
		g.angle += g.swingSpeed;
		if (g.maxAngle >= 35 || g.maxAngle <= -35) {
			g.gameOver = true;
		}
		if (g.angle >= g.maxAngle || g.angle <= -g.maxAngle) {
			g.swingSpeed *= -1;
		}
	}
}

// Rotation distance
void iRotatePoint(float fallX_, float fallY_, float centerX_, float screenMove_, float angle, float &localX, float &localY) {
	float rad = (-angle) * 3.1416f / 180.0f;
	float dx = fallX_ - centerX_;
	float dy = fallY_ - screenMove_;
	localX = centerX_ + dx * cos(rad) - dy * sin(rad);
	localY = screenMove_ + dx * sin(rad) + dy * cos(rad);
}


void updateBlockFall(GameState &g) {
	if (!g.BlockFalling || g.gameOver) return;

	g.fallY -= g.fallSpeed;
	g.ropeY = -200;

	if (g.blockCount > 0) {
		g.ground = g.blockY[g.blockCount - 1] + blockHeight;
	}
	else {
		g.ground = baseGround;
	}

	float localFallX, localFallY;
	iRotatePoint(g.fallX, g.fallY, g.centerX, g.screenMove, g.angle, localFallX, localFallY);

	if (localFallY <= g.ground + g.screenMove) {
		g.BlockFalling = false;

		if (g.blockCount > 0) {
			float localFallCenterX = localFallX + blockWidth / 2.0f;
			float localTopCenterX = g.blockX[g.blockCount - 1] + blockWidth / 2.0f;

			if (fabs(localFallCenterX - localTopCenterX) < blockWidth * 0.8f) {
				g.gameOver = false;
			}
			else {
				g.gameOver = true;
				return;
			}
			g.totalX += localFallX;
			g.avgX = g.totalX / g.blockCount;
		}

		g.blockX[g.blockCount] = localFallX;
		g.blockY[g.blockCount] = g.ground;
		g.blockCount++;

		g.totalBlocks++;
		if (g.blockCount == 1){
			g.score++;
			g.streak++;
		}
		else if (g.streak == 1) {
			g.score += 1;
			if (g.blockX[g.blockCount - 1] - g.fallX < 8 && g.fallX - g.blockX[g.blockCount - 1] < 8) {
				g.streak++;
			}
			else {
				g.streak = 1;
			}
		}
		else if (g.streak == 2) {
			g.score += 2;
			if (g.blockX[g.blockCount - 1] - g.fallX < 8 && g.fallX - g.blockX[g.blockCount - 1] < 8) {
				g.streak++;
			}
			else {
				g.streak = 1;
			}
		}
		else if (g.streak == 3) {
			g.score += 3;
			if (g.blockX[g.blockCount - 1] - g.fallX < 8 && g.fallX - g.blockX[g.blockCount - 1] < 8) {
				g.streak++;
			}
			else {
				g.streak = 1;
			}
		}
		else if (g.streak == 4) {
			g.score += 5;
			g.streak = 1;
		}

		g.screenMove -= blockHeight;

		g.fallX = g.hookX - blockWidth / 2;
		g.fallY = g.hookY - g.ropeLength - blockHeight;
	}
}

// Drawing
void drawGame(GameState &g, int offsetX) {
	// background per page
	iShowImage(offsetX + 0, -120 + g.screenMove, baseWidth, screenHeight, imgBackground);

	// placed blocks
	iRotate(offsetX + g.centerX, g.screenMove, g.angle);
	for (int i = 0; i < g.blockCount; i++) {
		iShowImage(offsetX + g.blockX[i], g.blockY[i] + g.screenMove, blockWidth, blockHeight, imgBlock);
	}
	iUnRotate();

	// hook
	iRotate(offsetX + g.centerX, g.centerY, g.hookAngle);
	iShowImage(offsetX + g.centerX - hookWidth / 2, g.centerY - hookLength - 5, hookWidth, hookLength, imgHook);
	iUnRotate();

	// rope & falling block
	iShowImage(offsetX + g.ropeX, g.ropeY, g.ropeWidth, g.ropeLength, imgRope);
	iShowImage(offsetX + g.fallX, g.fallY, blockWidth, blockHeight, imgBlock);

	// point
	char point[64];
	iSetColor(255, 0, 0);
	sprintf_s(point, sizeof(point), "Blocks: %d", g.totalBlocks);
	iText(offsetX + 10, screenHeight - 30,point, GLUT_BITMAP_TIMES_ROMAN_24);

	sprintf_s(point, sizeof(point), "Score: %d", g.score);
	iText(offsetX + 10, screenHeight - 60, point, GLUT_BITMAP_TIMES_ROMAN_24);

	// Per-page game over message
	if (g.gameOver) {
		/*iSetColor(255, 0, 0);
		iText(screenWidth / 2 - 80, screenHeight / 2, "GAME OVER ", GLUT_BITMAP_TIMES_ROMAN_24);

		char str[50];
		sprintf_s(str, "Total Blocks: %d", g.totalBlocks);
		iText(screenWidth / 2 - 80, screenHeight / 2 - 50, str, GLUT_BITMAP_HELVETICA_18);

		sprintf_s(str, "Total Score: %d", g.score);
		iText(screenWidth / 2 - 80, screenHeight / 2 - 80, str, GLUT_BITMAP_HELVETICA_18);*/
		iSetColor(0, 255, 255);
		iFilledRectangle(0, 0, screenWidth, screenHeight);
		char msg[64];
		sprintf_s(msg, sizeof(msg), "%s Player Game Over", g.label);
		iSetColor(255, 0, 0);
		iText(offsetX + baseWidth / 2 - 110, screenHeight / 2 -40, msg, GLUT_BITMAP_TIMES_ROMAN_24);
		iText(offsetX + baseWidth / 2 - 110, screenHeight / 2 - 80, "Press SPACE to return", GLUT_BITMAP_TIMES_ROMAN_24);
	}
}

// Winner check (multiplayer)
bool bothOver() {
	return leftGS.gameOver && rightGS.gameOver;
}

int computeWinner() {
	// return: 0 left, 1 right, 2 draw
	if (leftGS.score > rightGS.score) return 0;
	if (rightGS.score > leftGS.score) return 1;
	// tie -> fewer blocks wins
	if (leftGS.totalBlocks < rightGS.totalBlocks) return 0;
	if (rightGS.totalBlocks < leftGS.totalBlocks) return 1;
	return 2;
}

// iDraw
void iDraw() {
	iClear();
	iShowImage(0, 0, screenWidth, screenHeight, imgBrick);

	if (Menu) {
		iShowImage(middleStart, 0, baseWidth, screenHeight, imgMenu);
	}
	else if (HistoryMenu) {
		iSetColor(255,255,255);
		iFilledRectangle(0, 0, screenWidth, screenHeight);
		iSetColor(0, 0, 0);
		iText(20, 650, "Last 5 Matches", GLUT_BITMAP_HELVETICA_18);
		for (int i = 0; i < historyCount; i++){
			char str[100];
			sprintf_s(str, sizeof(str), "Match %d - Blocks: %d  Score: %d", i + 1, history[i].blocks, history[i].score);
			iText(20, 600 - i * 40, str, GLUT_BITMAP_HELVETICA_12);
		}
		iText(250, 100, "Press SPACE to return", GLUT_BITMAP_HELVETICA_18);
		iShowImage(screenWidth - 250, 150, 250, 700 - 150, imgBBuilding);
	}
	else if (Multiplayer) {
		iSetColor(0, 255, 255);
		iFilledRectangle(0, 0, baseWidth, screenHeight);
		// Left page
		drawGame(leftGS, 0);
		// Barrier
		iSetColor(50, 50, 50);
		iFilledRectangle(baseWidth, 0, dividerWidth, screenHeight);

		iSetColor(0, 255, 255);
		iFilledRectangle(baseWidth+dividerWidth, 0, baseWidth, screenHeight);
		// Right page with offset
		drawGame(rightGS, baseWidth + dividerWidth);

		// Winner display if both are over
		if (bothOver()) {
			int w = computeWinner();
			char msg[64];
			if (w == 0) sprintf_s(msg, sizeof(msg), "Left Player Wins");
			else if (w == 1) sprintf_s(msg, sizeof(msg), "Right Player Wins");
			else sprintf_s(msg, sizeof(msg), "Draw");
			iSetColor(150,150, 150);
			iFilledRectangle(0, 0, screenWidth, screenHeight);

			iSetColor(0, 0, 0);
			int midX = baseWidth + dividerWidth / 2;
			iText(midX - 90, screenHeight / 2, msg, GLUT_BITMAP_TIMES_ROMAN_24);
			iText(midX - 100, screenHeight / 2 - 40, "Press SPACE to return", GLUT_BITMAP_HELVETICA_18);
		}
	}
	else {
		iSetColor(0, 255, 255);
		iFilledRectangle(middleStart, 0, baseWidth, screenHeight);
		
		drawGame(single, middleStart);

		// Single-player extra info (center)
		if (single.gameOver) {
			char str[64];
			sprintf_s(str, sizeof(str), "Total Blocks: %d", single.totalBlocks);
			iText(middleStart + baseWidth / 2 - 80, screenHeight / 2 + 40, str, GLUT_BITMAP_HELVETICA_18);

			sprintf_s(str, sizeof(str), "Total Score: %d", single.score);
			iText(middleStart + baseWidth / 2 - 80, screenHeight / 2 + 10, str, GLUT_BITMAP_HELVETICA_18);
		}
	}
}

void resetSingle() {
	// Reset single player
	single = GameState();
	single.centerX = baseWidth / 2.0f;
	single.centerY = (float)screenHeight;
	single.label = "Single";
}

void resetMultiplayer() {
	// Reset left page
	leftGS = GameState();
	leftGS.centerX = baseWidth / 2.0f;
	leftGS.centerY = (float)screenHeight;
	leftGS.label = "Left";

	// Reset right page
	rightGS = GameState();
	rightGS.centerX = baseWidth / 2.0f; // local to its page; drawGame adds offset
	rightGS.centerY = (float)screenHeight;
	rightGS.label = "Right";
}

void iMouse(int button, int state, int mx, int my) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {

		// --- Menu interactions ---
		if (Menu) {
			// Single Player button: x = [26,146], y = [432,532]
			if (mx >= 26+middleStart && mx <= 146+middleStart && my >= 432 && my <= 532) {
				Menu = false;
				HistoryMenu = false;
				Multiplayer = false;
				resetSingle();
				return;
			}

			// Multiplayer button: x = [26,146], y = [306,412]
			if (mx >= 26+middleStart && mx <= 146+middleStart && my >= 306 && my <= 412) {
				Menu = false;
				HistoryMenu = false;
				Multiplayer = true;
				resetMultiplayer();
				return;
			}

			// History button: x = [26,146], y = [226,290]
			if (mx >= 26+middleStart && mx <= 146+middleStart && my >= 226 && my <= 290) {
				HistoryMenu = true;
				Menu = false;
				Multiplayer = false;
				return;
			}
		}
	}
}

void iMouseMove(int mx, int my) {}
void iPassiveMouseMove(int mx, int my) {}

void iKeyboard(unsigned char key) {
	// Single player drop
	if (!Menu && !HistoryMenu && !Multiplayer && !single.gameOver && key == ' ') {
		if (!single.BlockFalling) single.BlockFalling = true;
	}

	// Multiplayer: left player drop with 'S' or 's'
	if (Multiplayer && !Menu && !HistoryMenu && !bothOver()) {
		if ((key == 's' || key == 'S') && !leftGS.gameOver && !leftGS.BlockFalling) {
			leftGS.BlockFalling = true;
		}
	}

	// SINGLE: Game Over -> save to history and return to menu
	if (!Multiplayer && single.gameOver && key == ' ') {
		// save match result into history
		if (historyCount < 5) {
			history[historyCount].blocks = single.totalBlocks;
			history[historyCount].score = single.score;
			historyCount++;
		}
		else {
			// shift and append
			for (int i = 1; i < 5; i++) history[i - 1] = history[i];
			history[4].blocks = single.totalBlocks;
			history[4].score = single.score;
		}

		// back to menu
		Menu = true;
		HistoryMenu = false;
		Multiplayer = false;
		resetSingle();
	}

	// History screen exit
	if (HistoryMenu && key == ' ') {
		HistoryMenu = false;
		Menu = true;
		Multiplayer = false;
		resetSingle();
	}

	// Multiplayer end: return to menu when both over
	if (Multiplayer && bothOver() && key == ' ') {
		Menu = true;
		HistoryMenu = false;
		Multiplayer = false;
		resetSingle(); // continue using middle single page within the same large window
	}
}

void iSpecialKeyboard(unsigned char key) {
	// Multiplayer: right player drop with DOWN key
	if (Multiplayer && !Menu && !HistoryMenu && !bothOver()) {
		if (key == GLUT_KEY_DOWN && !rightGS.gameOver && !rightGS.BlockFalling) {
			rightGS.BlockFalling = true;
		}
	}
}

// =============== Timers ===============
void timer_update() {
	if (Menu || HistoryMenu) return;
	if (Multiplayer) {
		updateHook(leftGS);
		updateHook(rightGS);
	}
	else {
		updateHook(single);
	}
}
void timer_fall() {
	if (Menu || HistoryMenu) return;
	if (Multiplayer) {
		updateBlockFall(leftGS);
		updateBlockFall(rightGS);
	}
	else {
		updateBlockFall(single);
	}
}
void timer_gravity() {
	if (Menu || HistoryMenu) return;
	if (Multiplayer) {
		gravity(leftGS);
		gravity(rightGS);
	}
	else {
		gravity(single);
	}
}
void timer_swing() {
	if (Menu || HistoryMenu) return;
	if (Multiplayer) {
		swing(leftGS);
		swing(rightGS);
	}
	else {
		swing(single);
	}
}

// =============== Main ===============
int main() {
	// Initialize the window to double-width so we can always fit two pages and a divider
	iInitialize(screenWidth, screenHeight, "Build Rush");

	imgHook = iLoadImage("assets//hook.png");
	imgBlock = iLoadImage("assets//block.png");
	imgRope = iLoadImage("assets//rope.png");
	imgBackground = iLoadImage("assets//background.png");
	imgMenu = iLoadImage("assets//menu.png");
	imgBrick = iLoadImage("assets//brick.png");
	imgBBuilding = iLoadImage("assets//bbuilding.png");

	// initialize labels
	single.label = "Single";
	leftGS.label = "Left";
	rightGS.label = "Right";

	iSetTimer(10, timer_update);
	iSetTimer(10, timer_fall);
	iSetTimer(10, timer_gravity);
	iSetTimer(10, timer_swing);

	iStart();
	return 0;
}
