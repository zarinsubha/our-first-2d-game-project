#include "iGraphics.h"
#include <cstdlib>
#include <cstdio>
#include <cstddef>


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
// 7 = LEVEL 3
//

// ============================================================
// HEADER FILES
// ============================================================

#include "Player.h"
#include "Enemy.h"
#include "Environment.h"


// ============================================================
// GAME STATE
// ============================================================

int gameState = 0;


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
	else if (gameState == 7)
	{
		drawLevel3();
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
	// Only respond to left mouse button
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
		// ----------------------------------------------------
		if (
			mx >= 390 &&
			mx <= 610 &&
			my >= 345 &&
			my <= 400
			)
		{
			selectedMenuButton = 1;

			// Start directly from Level 1
			resetLevel();

			gameState = 2;

			return;
		}


		// ----------------------------------------------------
		// LEVELS
		// ----------------------------------------------------
		else if (
			mx >= 390 &&
			mx <= 610 &&
			my >= 295 &&
			my <= 345
			)
		{
			selectedMenuButton = 2;

			// Go to Level Select page
			gameState = 6;

			return;
		}


		// ----------------------------------------------------
		// SCORES
		// ----------------------------------------------------
		else if (
			mx >= 390 &&
			mx <= 610 &&
			my >= 240 &&
			my <= 295
			)
		{
			selectedMenuButton = 3;

			// No score screen implemented yet
			return;
		}


		// ----------------------------------------------------
		// CREDITS
		// ----------------------------------------------------
		else if (
			mx >= 390 &&
			mx <= 610 &&
			my >= 185 &&
			my <= 240
			)
		{
			selectedMenuButton = 4;

			// No credits screen implemented yet
			return;
		}


		// ----------------------------------------------------
		// EXIT
		// ----------------------------------------------------
		else if (
			mx >= 390 &&
			mx <= 610 &&
			my >= 135 &&
			my <= 185
			)
		{
			selectedMenuButton = 5;

			// Exit immediately
			exit(0);

			return;
		}
	}


	// ========================================================
	// LEVEL SELECT
	// ========================================================

	else if (gameState == 6)
	{
		// ----------------------------------------------------
		// LEVEL 1
		// ----------------------------------------------------
		if (
			mx >= 120 &&
			mx <= 350 &&
			my >= 160 &&
			my <= 395
			)
		{
			resetLevel();

			gameState = 2;

			return;
		}


		// ----------------------------------------------------
		// LEVEL 2
		// ----------------------------------------------------
		else if (
			mx >= 380 &&
			mx <= 620 &&
			my >= 160 &&
			my <= 395
			)
		{
			startLevel2();

			return;
		}


		// ----------------------------------------------------
		// LEVEL 3
		// ----------------------------------------------------
		else if (
			mx >= 650 &&
			mx <= 880 &&
			my >= 160 &&
			my <= 395
			)
		{
			startLevel3();

			return;
		}
	}


	// ========================================================
	// ATTACK
	// LEVEL 1 + LEVEL 2 + LEVEL 3
	// ========================================================

	else if (
		gameState == 2 ||
		gameState == 5 ||
		gameState == 7
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

			// PLAY ATTACK SOUND
			mciSendString(
				"play attacksound from 0",
				NULL,
				0,
				NULL
				);
		}
	}
}


// ============================================================
// KEYBOARD
// ============================================================

void iKeyboard(unsigned char key)
{
	// ========================================================
	// B = BACK
	// ========================================================

	if (key == 'b' || key == 'B')
	{
		// ----------------------------------------------------
		// LEVEL SELECT -> MENU
		// ----------------------------------------------------
		if (gameState == 6)
		{
			gameState = 0;

			selectedMenuButton = 0;

			menuActionTimer = 0;

			return;
		}


		// ----------------------------------------------------
		// STORY / GAME OVER / WIN -> MENU
		// ----------------------------------------------------
		if (
			gameState == 1 ||
			gameState == 3 ||
			gameState == 4
			)
		{
			// STOP VICTORY / GAME OVER SOUND
			mciSendString(
				"stop victorysound",
				NULL,
				0,
				NULL
				);


			mciSendString(
				"stop ggsong",
				NULL,
				0,
				NULL
				);


			// RESTART BACKGROUND MUSIC
			mciSendString(
				"play bgsong repeat",
				NULL,
				0,
				NULL
				);


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


	// ========================================================
	// LEVEL 3 JUMP
	// ========================================================

	if (gameState == 7)
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
	// LEVEL 3 BACKGROUNDS
	// ========================================================

	level3BackgroundImage1 =
		iLoadImage(
		"Images//level3_background1.png"
		);

	level3BackgroundImage2 =
		iLoadImage(
		"Images//level3_background2.png"
		);

	level3BackgroundImage3 =
		iLoadImage(
		"Images//level3_background3.png"
		);

	level3BackgroundImage4 =
		iLoadImage(
		"Images//level3_background4.png"
		);

	level3BackgroundImage5 =
		iLoadImage(
		"Images//level3_background5.png"
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
	// LEVEL 3 - FIRST ENEMY TYPE
	// ========================================================

	level3Enemy1Image =
		iLoadImage(
		"Images//level3_enemy1_idle.png"
		);

	level3Enemy1RunImage[0] =
		iLoadImage(
		"Images//level3_enemy1_run1.png"
		);

	level3Enemy1RunImage[1] =
		iLoadImage(
		"Images//level3_enemy1_run2.png"
		);

	level3Enemy1RunImage[2] =
		iLoadImage(
		"Images//level3_enemy1_run3.png"
		);

	level3Enemy1AttackImage[0] =
		iLoadImage(
		"Images//level3_enemy1_attack1.png"
		);

	level3Enemy1AttackImage[1] =
		iLoadImage(
		"Images//level3_enemy1_attack2.png"
		);


	// ========================================================
	// LEVEL 3 - SECOND ENEMY TYPE
	// ========================================================

	level3Enemy2Image =
		iLoadImage(
		"Images//level3_enemy2_idle.png"
		);

	level3Enemy2RunImage[0] =
		iLoadImage(
		"Images//level3_enemy2_run1.png"
		);

	level3Enemy2RunImage[1] =
		iLoadImage(
		"Images//level3_enemy2_run2.png"
		);

	level3Enemy2RunImage[2] =
		iLoadImage(
		"Images//level3_enemy2_run3.png"
		);

	level3Enemy2AttackImage[0] =
		iLoadImage(
		"Images//level3_enemy2_attack1.png"
		);

	level3Enemy2AttackImage[1] =
		iLoadImage(
		"Images//level3_enemy2_attack2.png"
		);


	// ========================================================
	// HUD
	// ========================================================

	healthbarImage = iLoadImage(
		"Images//healthbar.png"
		);


	coinImage =
		iLoadImage(
		"Images//coin.png"
		);


	// ========================================================
	// AUDIO
	// ========================================================

	// BACKGROUND MUSIC
	mciSendString(
		"open \"Audios//background.mp3\" alias bgsong",
		NULL,
		0,
		NULL
		);


	// PLAYER ATTACK SOUND
	mciSendString(
		"open \"Audios//attack.wav\" alias attacksound",
		NULL,
		0,
		NULL
		);


	// ENEMY HIT SOUND
	mciSendString(
		"open \"Audios//enemy_hit.wav\" alias enemyhitsound",
		NULL,
		0,
		NULL
		);


	// VICTORY SOUND
	mciSendString(
		"open \"Audios//victory.wav\" alias victorysound",
		NULL,
		0,
		NULL
		);


	// GAME OVER SOUND
	mciSendString(
		"open \"Audios//gameover.mp3\" alias ggsong",
		NULL,
		0,
		NULL
		);


	// START BACKGROUND MUSIC
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
