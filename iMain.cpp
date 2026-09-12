#include "iGraphics.h"


// ============================================================
// GAME STATE
//
// 0 = MENU
// 1 = STORY
// 2 = LEVEL 1
// 3 = GAME OVER
// 4 = WIN
// 5 = LEVEL 2
// 6 = LEVEL SELECT
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


	if (gameState == 0)
	{
		drawMenu();
	}


	else if (gameState == 1)
	{
		drawStory();
	}


	else if (gameState == 2)
	{
		drawLevel1();
	}


	else if (gameState == 3)
	{
		drawGameOver();
	}


	else if (gameState == 4)
	{
		drawWin();
	}


	else if (gameState == 5)
	{
		drawLevel2();
	}


	else if (gameState == 6)
	{
		drawLevelSelect();
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
		// START GAME

		if (
			mx >= 110 &&
			mx <= 485 &&
			my >= 355 &&
			my <= 420
			)
		{
			selectedMenuButton = 1;

			menuActionTimer = 20;
		}


		// LEVEL SELECT

		else if (
			mx >= 110 &&
			mx <= 485 &&
			my >= 280 &&
			my <= 350
			)
		{
			selectedMenuButton = 2;

			gameState = 6;
		}


		// STORY

		else if (
			mx >= 110 &&
			mx <= 485 &&
			my >= 130 &&
			my <= 200
			)
		{
			selectedMenuButton = 4;

			gameState = 1;
		}


		// EXIT

		else if (
			mx >= 110 &&
			mx <= 485 &&
			my >= 60 &&
			my <= 130
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
		// LEVEL 1

		if (
			mx >= 95 &&
			mx <= 435 &&
			my >= 145 &&
			my <= 525
			)
		{
			resetLevel();

			gameState = 2;
		}


		// LEVEL 2

		else if (
			mx >= 470 &&
			mx <= 825 &&
			my >= 145 &&
			my <= 525
			)
		{
			startLevel2();
		}


		// BACK TO MENU

		else if (
			mx >= 990 &&
			mx <= 1215 &&
			my >= 40 &&
			my <= 105
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
	iInitialize(
		1280,
		720,
		"The Last Jade Marquis"
		);


	// ========================================================
	// MENU
	// ========================================================

	menuImage =
		iLoadImage(
		"Images//menu.png"
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
	// START
	// ========================================================

	iStart();


	return 0;
}