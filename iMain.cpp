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
//

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
		// PLAY
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


		// LEVEL SELECT
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


		// STORY
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


		// EXIT
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
		// LEVEL 1
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


		// LEVEL 2
		else if (
			mx >= 367 &&
			mx <= 645 &&
			my >= 121 &&
			my <= 438
			)
		{
			startLevel2();
		}


		// BACK
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
	// ATTACK
	// LEVEL 1 + LEVEL 2
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
	// BACK TO MENU
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
		1000,
		600,
		"The Last Jade Marquis"
		);


	// ========================================================
	// MENU / STORY / WIN / GAME OVER
	// ========================================================

	menuImage =
		iLoadImage(
		"Images//menu.png"
		);

	levelSelectImage =
		iLoadImage(
		"Images//level_select.png"
		);

	storyImage =
		iLoadImage(
		"Images//story.png"
		);

	winImage =
		iLoadImage(
		"Images//win.png"
		);

	gameoverImage =
		iLoadImage(
		"Images//gameover.png"
		);


	// ========================================================
	// LEVEL 1 BACKGROUNDS
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
	// LEVEL 2 BACKGROUNDS
	// ========================================================

	level2BackgroundImage1 =
		iLoadImage(
		"Images//level2_background1.png"
		);

	level2BackgroundImage2 =
		iLoadImage(
		"Images//level2_background2.png"
		);

	level2BackgroundImage3 =
		iLoadImage(
		"Images//level2_background3.png"
		);


	// ========================================================
	// PLAYER
	// ========================================================

	playerImage =
		iLoadImage(
		"Images//player.png"
		);


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
	// LEVEL 1 ENEMY
	// ========================================================

	enemyImage =
		iLoadImage(
		"Images//enemy.png"
		);

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

	enemyAttackImage[0] =
		iLoadImage(
		"Images//enemy_attack_1.png"
		);

	enemyAttackImage[1] =
		iLoadImage(
		"Images//enemy_attack_2.png"
		);


	// ========================================================
	// LEVEL 2 - FIRST ENEMY TYPE
	// ========================================================

	level2EnemyImage =
		iLoadImage(
		"Images//level2_enemy.png"
		);

	level2EnemyRunImage[0] =
		iLoadImage(
		"Images//level2_enemy_run1.png"
		);

	level2EnemyRunImage[1] =
		iLoadImage(
		"Images//level2_enemy_run2.png"
		);

	level2EnemyRunImage[2] =
		iLoadImage(
		"Images//level2_enemy_run3.png"
		);

	level2EnemyAttackImage[0] =
		iLoadImage(
		"Images//level2_enemy_attack1.png"
		);

	level2EnemyAttackImage[1] =
		iLoadImage(
		"Images//level2_enemy_attack2.png"
		);

	level2EnemyAttackImage[2] =
		iLoadImage(
		"Images//level2_enemy_attack3.png"
		);


	// ========================================================
	// LEVEL 2 - SECOND ENEMY TYPE
	// ========================================================

	level2Enemy1Image =
		iLoadImage(
		"Images//level2_enemy1_idle.png"
		);

	level2Enemy1RunImage[0] =
		iLoadImage(
		"Images//level2_enemy1_run1.png"
		);

	level2Enemy1RunImage[1] =
		iLoadImage(
		"Images//level2_enemy1_run2.png"
		);

	level2Enemy1RunImage[2] =
		iLoadImage(
		"Images//level2_enemy1_run3.png"
		);

	level2Enemy1AttackImage[0] =
		iLoadImage(
		"Images//level2_enemy1_attack1.png"
		);

	level2Enemy1AttackImage[1] =
		iLoadImage(
		"Images//level2_enemy1_attack2.png"
		);

	level2Enemy1AttackImage[2] =
		iLoadImage(
		"Images//level2_enemy1_attack3.png"
		);


	// ========================================================
	// HUD
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
		"open \"Audios//attack.wav\" alias attacksound",
		NULL,
		0,
		NULL
		);

	mciSendString(
		"open \"Audios//enemy_hit.wav\" alias enemyhitsound",
		NULL,
		0,
		NULL
		);

	mciSendString(
		"open \"Audios//victory.wav\" alias victorysound",
		NULL,
		0,
		NULL
		);

	mciSendString(
		"open \"Audios//win.wav\" alias winsound",
		NULL,
		0,
		NULL
		);


	// Game over sound
	mciSendString(
		"open \"Audios//gameover.mp3\" alias ggsong",
		NULL,
		0,
		NULL
		);


	mciSendString(
		"play bgsong repeat",
		NULL,
		0,
		NULL
		);


	// ========================================================
	// TIMERS
	// ========================================================

	iSetTimer(
		20,
		fixedUpdate
		);

	iSetTimer(
		1000,
		enemyAttackUpdate
		);

	iSetTimer(
		120,
		updatePlayerAnimation
		);

	iSetTimer(
		100,
		updateAttackAnimation
		);

	iSetTimer(
		120,
		updateEnemyAnimation
		);

	iSetTimer(
		150,
		updateEnemyAttackAnimation
		);

	iSetTimer(
		30,
		updateMenuAction
		);


	iStart();

	return 0;
}