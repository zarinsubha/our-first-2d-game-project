#include "iGraphics.h"


// ============================================================
// GAME STATE
// ============================================================
//
// 0 = MENU
// 1 = STORY
// 2 = LEVEL 1
// 3 = GAME OVER
// 4 = WIN
// 5 = LEVEL 2
// 6 = LEVEL SELECT
// 7 = INSTRUCTION
// ============================================================

int gameState = 0;


// ============================================================
// HEADER FILES
// ============================================================

#include "Player.h"

#include "Enemy.h"

#include "Environment.h"


// ============================================================
// DRAW
// ============================================================

void iDraw()
{
	iClear();


	// ========================================================
	// MENU
	// ========================================================

	if (gameState == 0)
	{
		drawMenu();
	}


	// ========================================================
	// STORY
	// ========================================================

	else if (gameState == 1)
	{
		drawStory();
	}


	// ========================================================
	// LEVEL 1
	// ========================================================

	else if (gameState == 2)
	{
		drawLevel1();
	}


	// ========================================================
	// GAME OVER
	// ========================================================

	else if (gameState == 3)
	{
		drawGameOver();
	}


	// ========================================================
	// WIN
	// ========================================================

	else if (gameState == 4)
	{
		drawWin();
	}


	// ========================================================
	// LEVEL 2
	// ========================================================

	else if (gameState == 5)
	{
		drawLevel2();
	}


	// ========================================================
	// LEVEL SELECT
	// ========================================================

	else if (gameState == 6)
	{
		drawLevelSelect();
	}

	else if (gameState == 7)
	{
		drawInstruction();
	}
}


// ============================================================
// MOUSE MOVE
// ============================================================

void iMouseMove(int mx, int my)
{
	mouseX = mx;

	mouseY = my;
}


void iPassiveMouseMove(int mx, int my)
{
	mouseX = mx;

	mouseY = my;
}


// ============================================================
// MOUSE CLICK
// ============================================================

void iMouse(
	int button,
	int state,
	int mx,
	int my
	)
{
	// Only react to LEFT mouse button press
	if (
		button != GLUT_LEFT_BUTTON ||
		state != GLUT_DOWN
		)
	{
		return;
	}


	// ========================================================
	// MENU
	// ========================================================

	if (gameState == 0)
	{
		// ----------------------------------------------------
		// START GAME
		// Original: 110-485, 355-420
		// Resized: 86-379, 296-350
		// ----------------------------------------------------

		if (
			mx >= 86 &&
			mx <= 379 &&
			my >= 296 &&
			my <= 350
			)
		{
			selectedMenuButton = 1;

			menuActionTimer = 20;
		}


		// ----------------------------------------------------
		// LEVEL SELECT
		// Original: 110-485, 280-350
		// Resized: 86-379, 233-292
		// ----------------------------------------------------

		else if (
			mx >= 86 &&
			mx <= 379 &&
			my >= 233 &&
			my <= 292
			)
		{
			selectedMenuButton = 2;

			gameState = 6;
		}


		// ----------------------------------------------------
		// STORY
		// Original: 110-485, 130-200
		// Resized: 86-379, 108-167
		// ----------------------------------------------------

		else if (
			mx >= 86 &&
			mx <= 379 &&
			my >= 108 &&
			my <= 167
			)
		{
			selectedMenuButton = 4;

			gameState = 1;
		}


		// ----------------------------------------------------
		// EXIT
		// Original: 110-485, 60-130
		// Resized: 86-379, 50-108
		// ----------------------------------------------------

		else if (
			mx >= 86 &&
			mx <= 379 &&
			my >= 50 &&
			my <= 108
			)
		{
			selectedMenuButton = 5;

			menuActionTimer = 20;
		}
	}


	// ========================================================
	// LEVEL SELECT
	// ========================================================

	else if (gameState == 6)
	{
		// ----------------------------------------------------
		// LEVEL 1
		// Original: 95-435, 145-525
		// Resized: 74-340, 121-438
		// ----------------------------------------------------

		if (
			mx >= 74 &&
			mx <= 340 &&
			my >= 121 &&
			my <= 438
			)
		{
			resetLevel();

			gameState = 2;
		}


		// ----------------------------------------------------
		// LEVEL 2
		// Original: 470-825, 145-525
		// Resized: 367-645, 121-438
		// ----------------------------------------------------

		else if (
			mx >= 367 &&
			mx <= 645 &&
			my >= 121 &&
			my <= 438
			)
		{
			startLevel2();
		}


		// ----------------------------------------------------
		// BACK TO MENU
		// Original: 990-1215, 40-105
		// Resized: 773-949, 33-88
		// ----------------------------------------------------

		else if (
			mx >= 773 &&
			mx <= 949 &&
			my >= 33 &&
			my <= 88
			)
		{
			gameState = 0;

			selectedMenuButton = 0;
		}
	}


	// ========================================================
	// PLAYER ATTACK
	// LEVEL 1 AND LEVEL 2
	// ========================================================

	else if (
		gameState == 2 ||
		gameState == 5
		)
	{
		if (
			!isAttacking &&
			attackTimer == 0
			)
		{
			isAttacking = true;

			attackFrame = 0;

			attackHit = false;

			attackTimer = 20;
		}
	}
}


// ============================================================
// KEYBOARD
// ============================================================

void iKeyboard(unsigned char key)
{
	// ========================================================
	// B = BACK TO MAIN MENU
	//
	// STORY
	// GAME OVER
	// WIN
	// ========================================================

	if (key == 'b' || key == 'B')
	{
		if (
			gameState == 1 ||
			gameState == 3 ||
			gameState == 4
			)
		{
			gameState = 0;

			selectedMenuButton = 0;

			menuActionTimer = 0;

			return;
		}
	}


	// ========================================================
	// LEVEL 2 JUMP
	// ========================================================

	if (gameState == 5)
	{
		if (
			(key == 'w' || key == 'W') &&
			!isJumping &&
			!isAttacking
			)
		{
			velocityY = jumpPower;

			isJumping = true;
		}
	}
}


// ============================================================
// SPECIAL KEYBOARD
// ============================================================

void iSpecialKeyboard(unsigned char key)
{
}


// ============================================================
// MAIN
// ============================================================

int main()
{
	// ========================================================
	// INITIALIZE GAME WINDOW
	// ========================================================
	//
	// New screen size:
	// Width  = 1000
	// Height = 600
	//
	// ========================================================

	iInitialize(
		1000,
		600,
		"The Last Jade Marquis"
		);


	// ========================================================
	// MENU
	// ========================================================

	menuImage =
		iLoadImage(
		"Images//menu.png"
		);
	// ============================================================
	// INSTRUCTION
	// ============================================================

	instructionImage =
		iLoadImage(
		"Images//instruction.png"
		);

	// ========================================================
	// LEVEL SELECT
	// ========================================================

	levelSelectImage =
		iLoadImage(
		"Images//level_select.png"
		);


	// ========================================================
	// STORY
	// ========================================================

	storyImage =
		iLoadImage(
		"Images//story.png"
		);


	// ========================================================
	// WIN
	// ========================================================

	winImage =
		iLoadImage(
		"Images//win.png"
		);


	// ========================================================
	// GAME OVER
	// ========================================================

	gameoverImage =
		iLoadImage(
		"Images//gameover.png"
		);


	// ========================================================
	// LEVEL 1 BACKGROUND
	// ========================================================

	backgroundImage =
		iLoadImage(
		"Images//background.png"
		);
	backgroundImage2 =
		iLoadImage(
		"Images//background2.png"
		);

	backgroundImage3 =
		iLoadImage(
		"Images//background3.png"
		);

	// ========================================================
	// LEVEL 2 BACKGROUND
	// ========================================================

	level2BackgroundImage =
		iLoadImage(
		"Images//level2_background.png"
		);


	// ========================================================
	// PLAYER IDLE
	// ========================================================

	playerImage =
		iLoadImage(
		"Images//player.png"
		);
	

	// ========================================================
	// PLAYER RUN
	// ========================================================

	runImage[0] =
		iLoadImage(
		"Images//run_1.png"
		);

	runImage[1] =
		iLoadImage(
		"Images//run_2.png"
		);

	runImage[2] =
		iLoadImage(
		"Images//run_3.png"
		);


	// ========================================================
	// PLAYER ATTACK
	// ========================================================

	attackImage[0] =
		iLoadImage(
		"Images//attack_1.png"
		);

	attackImage[1] =
		iLoadImage(
		"Images//attack_2.png"
		);

	attackImage[2] =
		iLoadImage(
		"Images//attack_3.png"
		);

	attackImage[3] =
		iLoadImage(
		"Images//attack_4.png"
		);


	// ========================================================
	// ENEMY IDLE
	// SAME ENEMY FOR BOTH LEVELS
	// ========================================================

	enemyImage =
		iLoadImage(
		"Images//enemy.png"
		);


	// ========================================================
	// ENEMY RUN
	// ========================================================

	enemyRunImage[0] =
		iLoadImage(
		"Images//enemy_run1.png"
		);

	enemyRunImage[1] =
		iLoadImage(
		"Images//enemy_run2.png"
		);

	enemyRunImage[2] =
		iLoadImage(
		"Images//enemy_run3.png"
		);


	// ========================================================
	// ENEMY ATTACK
	// ========================================================

	enemyAttackImage[0] =
		iLoadImage(
		"Images//enemy_attack_1.png"
		);

	enemyAttackImage[1] =
		iLoadImage(
		"Images//enemy_attack_2.png"
		);
	// ============================================================
	// LEVEL 2 ENEMY IDLE
	// ============================================================

	enemy2Image =
		iLoadImage(
		"Images//enemy2_idle.png"
		);


	// ============================================================
	// LEVEL 2 ENEMY RUN
	// ============================================================

	enemy2RunImage[0] =
		iLoadImage(
		"Images//enemy2_run1.png"
		);

	enemy2RunImage[1] =
		iLoadImage(
		"Images//enemy2_run2.png"
		);

	enemy2RunImage[2] =
		iLoadImage(
		"Images//enemy2_run3.png"
		);


	// ============================================================
	// LEVEL 2 ENEMY ATTACK
	// ============================================================

	enemy2AttackImage[0] =
		iLoadImage(
		"Images//enemy2_attack1.png"
		);

	enemy2AttackImage[1] =
		iLoadImage(
		"Images//enemy2_attack2.png"
		);

	enemy2AttackImage[2] =
		iLoadImage(
		"Images//enemy2_attack3.png"
		);

	// ========================================================
	// UI
	// ========================================================

	heartImage =
		iLoadImage(
		"Images//heart.png"
		);

	coinImage =
		iLoadImage(
		"Images//coin.png"
		);


	// ========================================================
	// AUDIO
	// ========================================================

	mciSendString(
		"open \"Audios//background.mp3\" alias bgsong",
		NULL,
		0,
		NULL
		);


	mciSendString(
		"open \"Audios//gameover.mp3\" alias ggsong",
		NULL,
		0,
		NULL
		);


	// ========================================================
	// BACKGROUND MUSIC
	// ========================================================

	mciSendString(
		"play bgsong repeat",
		NULL,
		0,
		NULL
		);


	// ========================================================
	// GAME UPDATE
	// ========================================================

	iSetTimer(
		20,
		fixedUpdate
		);


	// ========================================================
	// ENEMY DAMAGE
	// ========================================================

	iSetTimer(
		1000,
		enemyAttackUpdate
		);


	// ========================================================
	// PLAYER RUN ANIMATION
	// ========================================================

	iSetTimer(
		120,
		updatePlayerAnimation
		);


	// ========================================================
	// PLAYER ATTACK ANIMATION
	// ========================================================

	iSetTimer(
		100,
		updateAttackAnimation
		);


	// ========================================================
	// ENEMY RUN ANIMATION
	// ========================================================

	iSetTimer(
		120,
		updateEnemyAnimation
		);


	// ========================================================
	// ENEMY ATTACK ANIMATION
	// ========================================================

	iSetTimer(
		150,
		updateEnemyAttackAnimation
		);


	// ========================================================
	// MENU TIMER
	// ========================================================

	iSetTimer(
		30,
		updateMenuAction
		);


	// ========================================================
	// START GAME
	// ========================================================

	iStart();


	return 0;
}