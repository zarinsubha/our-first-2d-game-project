#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

// ============================================================
// FORWARD DECLARATIONS
// ============================================================

void startLevel2();

void updateLevel1PlayerAttack();

void updateLevel2PlayerAttack();

void fixedUpdateLevel1();

void fixedUpdateLevel2();


// ============================================================
// IMAGES
// ============================================================

int menuImage;

int storyImage;

int backgroundImage;

int backgroundImage2;

int backgroundImage3;

int level2BackgroundImage;

int winImage;

int gameoverImage;

int heartImage;

int coinImage;

int levelSelectImage;


// ============================================================
// SCORE
// ============================================================

int score = 0;

const int scorePerEnemy = 5;


// ============================================================
// SCREEN SIZE
// ============================================================

const int screenWidth = 1000;

const int screenHeight = 600;


// ============================================================
// LEVEL 1 CAMERA
// ============================================================

int cameraX = 0;

const int level1WorldWidth = 3000;


// ============================================================
// LEVEL 2 CAMERA
// ============================================================

int level2CameraX = 0;

const int level2ScreenWidth = 1000;

const int level2WorldWidth = 4000;

const int cameraFollowX = 400;


// ============================================================
// LEVEL 1 PLATFORM POSITIONS
// ============================================================
//
// IMPORTANT:
//
// iShowImage() uses the BOTTOM-LEFT corner.
//
// Therefore playerY is the player's FEET position.
//
// Do NOT subtract playerHeight.
//
// ============================================================

const int level1PlatformY1 = 135;

const int level1PlatformY2 = 135;

const int level1PlatformY3 = 135;


// ============================================================
// LEVEL 1 PROGRESSION
// ============================================================
//
// 0 = FIGHTING 10 ENEMIES
// 1 = GO TO DOOR
// 2 = GO TO JADE
// 3 = JADE COLLECTED
//
// ============================================================

int level1Stage = 0;


// ============================================================
// LEVEL 1 DOOR
// ============================================================

const int level1DoorX = 500;


// ============================================================
// LEVEL 1 JADE
// ============================================================

const int jadeX = 800;

bool jadeCollected = false;


// ============================================================
// MENU
// ============================================================

int selectedMenuButton = 0;

int menuActionTimer = 0;


// ============================================================
// MOUSE
// ============================================================

int mouseX = 0;

int mouseY = 0;


// ============================================================
// LEVEL 2 ENEMY SYSTEM
// ============================================================

const int level2TotalEnemies = 10;

int level2EnemiesDefeated = 0;

int level2CurrentWave = 1;


// ============================================================
// LEVEL 1 PLATFORM HELPER
// ============================================================
//
// This function puts the player's FEET exactly on the
// correct platform for the current Level 1 stage.
//
// ============================================================

void setLevel1PlayerOnPlatform()
{
	if (level1Stage == 0)
	{
		playerY = level1PlatformY1;
	}
	else if (level1Stage == 1)
	{
		playerY = level1PlatformY2;
	}
	else if (level1Stage == 2)
	{
		playerY = level1PlatformY3;
	}
}


// ============================================================
// RESET LEVEL 1
// ============================================================

void resetLevel()
{
	// --------------------------------------------------------
	// PLAYER
	// --------------------------------------------------------

	playerX = 150;

	level1Stage = 0;

	setLevel1PlayerOnPlatform();

	playerHealth = playerMaxHealth;

	faceRight = true;

	playerMoving = false;

	runFrame = 0;


	// --------------------------------------------------------
	// ATTACK
	// --------------------------------------------------------

	isAttacking = false;

	attackFrame = 0;

	attackHit = false;

	attackTimer = 0;


	// --------------------------------------------------------
	// JUMP
	// --------------------------------------------------------

	isJumping = false;

	velocityY = 0;


	// --------------------------------------------------------
	// CAMERA
	// --------------------------------------------------------

	cameraX = 0;


	// --------------------------------------------------------
	// LEVEL 1 PROGRESSION
	// --------------------------------------------------------

	jadeCollected = false;


	// --------------------------------------------------------
	// SCORE
	// --------------------------------------------------------

	score = 0;


	// --------------------------------------------------------
	// ENEMY SYSTEM
	// --------------------------------------------------------

	enemiesDefeated = 0;

	currentEnemy = 1;


	// --------------------------------------------------------
	// SPAWN FIRST ENEMY
	// --------------------------------------------------------

	spawnEnemy();
}


// ============================================================
// MENU DRAW
// ============================================================

void drawMenu()
{
	iShowImage(
		0,
		0,
		screenWidth,
		screenHeight,
		menuImage
		);
}


// ============================================================
// MENU ACTION
// ============================================================

void updateMenuAction()
{
	if (menuActionTimer <= 0)
	{
		return;
	}

	menuActionTimer--;

	if (menuActionTimer != 0)
	{
		return;
	}


	// --------------------------------------------------------
	// START GAME
	// --------------------------------------------------------

	if (selectedMenuButton == 1)
	{
		selectedMenuButton = 0;

		resetLevel();

		gameState = 2;
	}


	// --------------------------------------------------------
	// EXIT
	// --------------------------------------------------------

	else if (selectedMenuButton == 5)
	{
		exit(0);
	}
}


// ============================================================
// STORY
// ============================================================

void drawStory()
{
	iShowImage(
		0,
		0,
		screenWidth,
		screenHeight,
		storyImage
		);
}


// ============================================================
// GAME OVER
// ============================================================

void drawGameOver()
{
	iShowImage(
		0,
		0,
		screenWidth,
		screenHeight,
		gameoverImage
		);
}


// ============================================================
// WIN
// ============================================================

void drawWin()
{
	iShowImage(
		0,
		0,
		screenWidth,
		screenHeight,
		winImage
		);
}


// ============================================================
// LEVEL SELECT
// ============================================================

void drawLevelSelect()
{
	iShowImage(
		0,
		0,
		screenWidth,
		screenHeight,
		levelSelectImage
		);
}


// ============================================================
// HEALTH UI
// ============================================================

void drawHealthUI()
{
	iShowImage(
		20,
		545,
		35,
		35,
		heartImage
		);


	char healthText[20];

	sprintf_s(
		healthText,
		"%d",
		playerHealth
		);


	iSetColor(
		255,
		255,
		255
		);


	iText(
		65,
		555,
		healthText,
		GLUT_BITMAP_HELVETICA_18
		);


	iSetColor(
		80,
		0,
		0
		);


	iFilledRectangle(
		20,
		520,
		200,
		15
		);


	iSetColor(
		0,
		255,
		0
		);


	int healthBarWidth =
		(playerHealth * 200) / playerMaxHealth;


	iFilledRectangle(
		20,
		520,
		healthBarWidth,
		15
		);
}


// ============================================================
// DRAW PLAYER LEVEL 1
// ============================================================

void drawPlayerLevel1()
{
	int drawX = playerX - cameraX;


	if (isAttacking)
	{
		iShowImage(
			drawX,
			playerY,
			playerWidth,
			playerHeight,
			attackImage[attackFrame]
			);
	}
	else if (playerMoving && !isJumping)
	{
		iShowImage(
			drawX,
			playerY,
			playerWidth,
			playerHeight,
			runImage[runFrame]
			);
	}
	else
	{
		iShowImage(
			drawX,
			playerY,
			playerWidth,
			playerHeight,
			playerImage
			);
	}
}


// ============================================================
// DRAW PLAYER LEVEL 2
// ============================================================

void drawPlayerLevel2()
{
	int drawX = playerX - level2CameraX;


	if (isAttacking)
	{
		iShowImage(
			drawX,
			playerY,
			playerWidth,
			playerHeight,
			attackImage[attackFrame]
			);
	}
	else if (playerMoving && !isJumping)
	{
		iShowImage(
			drawX,
			playerY,
			playerWidth,
			playerHeight,
			runImage[runFrame]
			);
	}
	else
	{
		iShowImage(
			drawX,
			playerY,
			playerWidth,
			playerHeight,
			playerImage
			);
	}
}


// ============================================================
// DRAW ENEMY LEVEL 1
// ============================================================

void drawEnemyLevel1()
{
	if (!enemyAlive)
	{
		return;
	}


	int drawX = enemyX - cameraX;


	if (enemyAttacking)
	{
		iShowImage(
			drawX,
			enemyY,
			enemyWidth,
			enemyHeight,
			enemyAttackImage[enemyAttackFrame]
			);
	}
	else if (abs(enemyX - playerX) > 100)
	{
		iShowImage(
			drawX,
			enemyY,
			enemyWidth,
			enemyHeight,
			enemyRunImage[enemyRunFrame]
			);
	}
	else
	{
		iShowImage(
			drawX,
			enemyY,
			enemyWidth,
			enemyHeight,
			enemyImage
			);
	}
}


// ============================================================
// DRAW ENEMY LEVEL 2
// ============================================================

void drawEnemyLevel2()
{
	if (!enemyAlive)
	{
		return;
	}


	int drawX = enemyX - level2CameraX;


	if (enemyAttacking)
	{
		iShowImage(
			drawX,
			enemyY,
			enemyWidth,
			enemyHeight,
			enemyAttackImage[enemyAttackFrame]
			);
	}
	else if (abs(enemyX - playerX) > 100)
	{
		iShowImage(
			drawX,
			enemyY,
			enemyWidth,
			enemyHeight,
			enemyRunImage[enemyRunFrame]
			);
	}
	else
	{
		iShowImage(
			drawX,
			enemyY,
			enemyWidth,
			enemyHeight,
			enemyImage
			);
	}
}


// ============================================================
// DRAW SCORE
// ============================================================

void drawScoreUI()
{
	iShowImage(
		850,
		545,
		35,
		35,
		coinImage
		);


	char scoreText[20];

	sprintf_s(
		scoreText,
		"%d",
		score
		);


	iSetColor(
		255,
		255,
		255
		);


	iText(
		895,
		555,
		scoreText,
		GLUT_BITMAP_HELVETICA_18
		);
}


// ============================================================
// DRAW LEVEL 1
// ============================================================
//
// STAGE 0 = background1 scrolling
// STAGE 1 = background2 static
// STAGE 2 = background3 static
//
// ============================================================

void drawLevel1()
{
	// ========================================================
	// STAGE 0
	// BACKGROUND 1
	// SCROLLING
	// ========================================================

	if (level1Stage == 0)
	{
		int backgroundX = -cameraX;


		iShowImage(
			backgroundX,
			0,
			screenWidth,
			screenHeight,
			backgroundImage
			);


		iShowImage(
			backgroundX + screenWidth,
			0,
			screenWidth,
			screenHeight,
			backgroundImage
			);


		iShowImage(
			backgroundX + (screenWidth * 2),
			0,
			screenWidth,
			screenHeight,
			backgroundImage
			);
	}


	// ========================================================
	// STAGE 1
	// BACKGROUND 2
	// STATIC
	// ========================================================

	else if (level1Stage == 1)
	{
		cameraX = 0;


		iShowImage(
			0,
			0,
			screenWidth,
			screenHeight,
			backgroundImage2
			);
	}


	// ========================================================
	// STAGE 2
	// BACKGROUND 3
	// STATIC
	// ========================================================

	else if (level1Stage == 2)
	{
		cameraX = 0;


		iShowImage(
			0,
			0,
			screenWidth,
			screenHeight,
			backgroundImage3
			);
	}


	// ========================================================
	// PLAYER
	// ========================================================

	drawPlayerLevel1();


	// ========================================================
	// ENEMY
	// ONLY STAGE 0
	// ========================================================

	if (level1Stage == 0)
	{
		drawEnemyLevel1();
	}


	// ========================================================
	// HEALTH
	// ========================================================

	drawHealthUI();


	// ========================================================
	// SCORE
	// ========================================================

	drawScoreUI();


	// ========================================================
	// ENEMY COUNT
	// ========================================================

	char enemyText[50];

	sprintf_s(
		enemyText,
		"Enemy: %d / %d",
		enemiesDefeated,
		totalEnemies
		);


	iSetColor(
		255,
		255,
		255
		);


	iText(
		390,
		555,
		enemyText,
		GLUT_BITMAP_HELVETICA_18
		);


	// ========================================================
	// STAGE MESSAGE
	// ========================================================

	if (level1Stage == 0)
	{
		iText(
			450,
			515,
			"FIGHT!",
			GLUT_BITMAP_HELVETICA_18
			);
	}
	else if (level1Stage == 1)
	{
		iText(
			420,
			515,
			"GO TO THE DOOR",
			GLUT_BITMAP_HELVETICA_18
			);
	}
	else if (level1Stage == 2)
	{
		iText(
			430,
			515,
			"GET THE JADE",
			GLUT_BITMAP_HELVETICA_18
			);
	}


	// ========================================================
	// LEVEL
	// ========================================================

	iText(
		460,
		580,
		"LEVEL 1",
		GLUT_BITMAP_HELVETICA_18
		);
}


// ============================================================
// ENEMY MOVEMENT
// ============================================================

void updateEnemyMovement()
{
	if (!enemyAlive)
	{
		return;
	}


	int distance =
		abs(enemyX - playerX);


	if (distance > 100)
	{
		enemyAttacking = false;


		if (enemyX > playerX)
		{
			enemyX -= enemySpeed;
		}
		else if (enemyX < playerX)
		{
			enemyX += enemySpeed;
		}
	}
	else
	{
		enemyAttacking = true;
	}
}


// ============================================================
// LEVEL 1 PLAYER ATTACK
// ============================================================

void updateLevel1PlayerAttack()
{
	if (level1Stage != 0)
	{
		return;
	}


	if (
		!isAttacking ||
		attackHit ||
		!enemyAlive
		)
	{
		return;
	}


	int distance =
		abs(
		(enemyX + enemyWidth / 2) -
		(playerX + playerWidth / 2)
		);


	if (distance >= 180)
	{
		return;
	}


	// --------------------------------------------------------
	// DAMAGE
	// --------------------------------------------------------

	enemyHealth -= attackDamage;

	attackHit = true;


	if (enemyHealth > 0)
	{
		return;
	}


	// --------------------------------------------------------
	// ENEMY DEAD
	// --------------------------------------------------------

	enemyHealth = 0;

	enemyAlive = false;

	enemyAttacking = false;

	enemiesDefeated++;

	score += scorePerEnemy;


	// ========================================================
	// ALL 10 ENEMIES KILLED
	// ========================================================

	if (enemiesDefeated >= totalEnemies)
	{
		enemiesDefeated = totalEnemies;


		// ----------------------------------------------------
		// GO TO BACKGROUND 2
		// ----------------------------------------------------

		level1Stage = 1;

		cameraX = 0;


		// ----------------------------------------------------
		// PLAYER START POSITION
		// ----------------------------------------------------

		playerX = 100;

		setLevel1PlayerOnPlatform();


		// ----------------------------------------------------
		// PLAYER STATE
		// ----------------------------------------------------

		playerMoving = false;

		isAttacking = false;

		attackHit = false;

		attackTimer = 0;

		faceRight = true;

		isJumping = false;

		velocityY = 0;


		// ----------------------------------------------------
		// NO ENEMY
		// ----------------------------------------------------

		enemyAlive = false;

		enemyAttacking = false;


		return;
	}


	// ========================================================
	// NEXT ENEMY
	// ========================================================

	spawnNextWave();
}


// ============================================================
// LEVEL 2 PLAYER ATTACK
// ORIGINAL LEVEL 2 SYSTEM
// ============================================================

void updateLevel2PlayerAttack()
{
	if (
		!isAttacking ||
		attackHit ||
		!enemyAlive
		)
	{
		return;
	}


	int distance =
		abs(
		(enemyX + enemyWidth / 2) -
		(playerX + playerWidth / 2)
		);


	if (distance >= 180)
	{
		return;
	}


	enemyHealth -= attackDamage;

	attackHit = true;


	if (enemyHealth > 0)
	{
		return;
	}


	enemyHealth = 0;

	enemyAlive = false;

	enemyAttacking = false;


	level2EnemiesDefeated++;

	score += scorePerEnemy;


	if (level2EnemiesDefeated >= level2TotalEnemies)
	{
		gameState = 4;

		return;
	}


	level2CurrentWave++;

	spawnEnemy();
}


// ============================================================
// LEVEL 1 UPDATE
// ============================================================

void fixedUpdateLevel1()
{
	if (gameState != 2)
	{
		return;
	}


	playerMoving = false;


	// ========================================================
	// STAGE 0
	// FIGHT
	// ========================================================

	if (level1Stage == 0)
	{
		// ----------------------------------------------------
		// MOVE RIGHT
		// ----------------------------------------------------

		if (isKeyPressed('d') || isKeyPressed('D'))
		{
			if (!isAttacking)
			{
				playerX += playerSpeed;

				playerMoving = true;

				faceRight = true;
			}
		}


		// ----------------------------------------------------
		// MOVE LEFT
		// ----------------------------------------------------

		if (isKeyPressed('a') || isKeyPressed('A'))
		{
			if (!isAttacking)
			{
				playerX -= playerSpeed;

				playerMoving = true;

				faceRight = false;
			}
		}


		// ----------------------------------------------------
		// WORLD LIMIT
		// ----------------------------------------------------

		if (playerX < 0)
		{
			playerX = 0;
		}


		if (playerX >
			level1WorldWidth - playerWidth)
		{
			playerX =
				level1WorldWidth - playerWidth;
		}


		// ----------------------------------------------------
		// PLATFORM
		// ----------------------------------------------------

		setLevel1PlayerOnPlatform();


		// ----------------------------------------------------
		// ATTACK COOLDOWN
		// ----------------------------------------------------

		if (attackTimer > 0)
		{
			attackTimer--;
		}


		// ----------------------------------------------------
		// ATTACK
		// ----------------------------------------------------

		updateLevel1PlayerAttack();


		if (level1Stage != 0)
		{
			return;
		}


		// ----------------------------------------------------
		// ENEMY
		// ----------------------------------------------------

		updateEnemyMovement();


		// ----------------------------------------------------
		// CAMERA
		// ----------------------------------------------------

		if (playerX > cameraFollowX)
		{
			cameraX =
				playerX - cameraFollowX;
		}
		else
		{
			cameraX = 0;
		}


		if (cameraX < 0)
		{
			cameraX = 0;
		}


		if (cameraX >
			level1WorldWidth - screenWidth)
		{
			cameraX =
				level1WorldWidth - screenWidth;
		}


		return;
	}


	// ========================================================
	// STAGE 1
	// BACKGROUND 2
	// GO TO DOOR
	// ========================================================

	if (level1Stage == 1)
	{
		cameraX = 0;


		// ----------------------------------------------------
		// MOVE RIGHT
		// ----------------------------------------------------

		if (isKeyPressed('d') || isKeyPressed('D'))
		{
			if (!isAttacking)
			{
				playerX += playerSpeed;

				playerMoving = true;

				faceRight = true;
			}
		}


		// ----------------------------------------------------
		// MOVE LEFT
		// ----------------------------------------------------

		if (isKeyPressed('a') || isKeyPressed('A'))
		{
			if (!isAttacking)
			{
				playerX -= playerSpeed;

				playerMoving = true;

				faceRight = false;
			}
		}


		// ----------------------------------------------------
		// SCREEN LIMIT
		// ----------------------------------------------------

		if (playerX < 0)
		{
			playerX = 0;
		}


		if (playerX >
			screenWidth - playerWidth)
		{
			playerX =
				screenWidth - playerWidth;
		}


		// ----------------------------------------------------
		// PLAYER ON BACKGROUND 2 PLATFORM
		// ----------------------------------------------------

		playerY = level1PlatformY2;


		// ----------------------------------------------------
		// DOOR COLLISION
		// ----------------------------------------------------

		int playerCenter =
			playerX + (playerWidth / 2);


		int doorDistance =
			abs(
			playerCenter -
			level1DoorX
			);


		if (doorDistance <= 80)
		{
			// ------------------------------------------------
			// GO TO BACKGROUND 3
			// ------------------------------------------------

			level1Stage = 2;

			cameraX = 0;


			// ------------------------------------------------
			// PLAYER START
			// ------------------------------------------------

			playerX = 100;

			playerY = level1PlatformY3;


			// ------------------------------------------------
			// PLAYER STATE
			// ------------------------------------------------

			playerMoving = false;

			isAttacking = false;

			attackHit = false;

			attackTimer = 0;

			faceRight = true;

			isJumping = false;

			velocityY = 0;
		}


		return;
	}


	// ========================================================
	// STAGE 2
	// BACKGROUND 3
	// GET JADE
	// ========================================================

	if (level1Stage == 2)
	{
		cameraX = 0;


		// ----------------------------------------------------
		// MOVE RIGHT
		// ----------------------------------------------------

		if (isKeyPressed('d') || isKeyPressed('D'))
		{
			if (!isAttacking)
			{
				playerX += playerSpeed;

				playerMoving = true;

				faceRight = true;
			}
		}


		// ----------------------------------------------------
		// MOVE LEFT
		// ----------------------------------------------------

		if (isKeyPressed('a') || isKeyPressed('A'))
		{
			if (!isAttacking)
			{
				playerX -= playerSpeed;

				playerMoving = true;

				faceRight = false;
			}
		}


		// ----------------------------------------------------
		// SCREEN LIMIT
		// ----------------------------------------------------

		if (playerX < 0)
		{
			playerX = 0;
		}


		if (playerX >
			screenWidth - playerWidth)
		{
			playerX =
				screenWidth - playerWidth;
		}


		// ----------------------------------------------------
		// PLAYER ON BACKGROUND 3 PLATFORM
		// ----------------------------------------------------

		playerY = level1PlatformY3;


		// ----------------------------------------------------
		// JADE COLLISION
		// ----------------------------------------------------

		int playerCenter =
			playerX + (playerWidth / 2);


		int jadeDistance =
			abs(
			playerCenter -
			jadeX
			);


		if (jadeDistance <= 80)
		{
			jadeCollected = true;

			level1Stage = 3;


			// ------------------------------------------------
			// WIN
			// ------------------------------------------------

			gameState = 4;


			playerMoving = false;

			isAttacking = false;

			attackHit = false;

			attackTimer = 0;


			return;
		}


		return;
	}
}


// ============================================================
// LEVEL 2 UPDATE
// ORIGINAL LEVEL 2 SYSTEM
// ============================================================

void fixedUpdateLevel2()
{
	if (gameState != 5)
	{
		return;
	}


	playerMoving = false;


	// --------------------------------------------------------
	// MOVE RIGHT
	// --------------------------------------------------------

	if (isKeyPressed('d') || isKeyPressed('D'))
	{
		if (!isAttacking)
		{
			playerX += playerSpeed;

			playerMoving = true;

			faceRight = true;
		}
	}


	// --------------------------------------------------------
	// MOVE LEFT
	// --------------------------------------------------------

	if (isKeyPressed('a') || isKeyPressed('A'))
	{
		if (!isAttacking)
		{
			playerX -= playerSpeed;

			playerMoving = true;

			faceRight = false;
		}
	}


	// --------------------------------------------------------
	// WORLD LIMIT
	// --------------------------------------------------------

	if (playerX < 0)
	{
		playerX = 0;
	}


	if (playerX >
		level2WorldWidth - playerWidth)
	{
		playerX =
			level2WorldWidth - playerWidth;
	}


	// --------------------------------------------------------
	// ATTACK COOLDOWN
	// --------------------------------------------------------

	if (attackTimer > 0)
	{
		attackTimer--;
	}


	// --------------------------------------------------------
	// JUMP PHYSICS
	// --------------------------------------------------------

	if (isJumping)
	{
		velocityY -= gravity;

		playerY += velocityY;


		if (playerY <= groundY)
		{
			playerY = groundY;

			velocityY = 0;

			isJumping = false;
		}
	}


	// --------------------------------------------------------
	// PLAYER ATTACK
	// --------------------------------------------------------

	updateLevel2PlayerAttack();


	if (gameState != 5)
	{
		return;
	}


	// --------------------------------------------------------
	// ENEMY MOVEMENT
	// --------------------------------------------------------

	updateEnemyMovement();


	// --------------------------------------------------------
	// CAMERA
	// --------------------------------------------------------

	if (playerX > cameraFollowX)
	{
		level2CameraX =
			playerX - cameraFollowX;
	}
	else
	{
		level2CameraX = 0;
	}


	if (level2CameraX < 0)
	{
		level2CameraX = 0;
	}


	if (level2CameraX >
		level2WorldWidth - level2ScreenWidth)
	{
		level2CameraX =
			level2WorldWidth - level2ScreenWidth;
	}
}


// ============================================================
// START LEVEL 2
// ============================================================

void startLevel2()
{
	gameState = 5;


	// --------------------------------------------------------
	// PLAYER
	// --------------------------------------------------------

	playerX = 150;

	playerY = groundY;

	playerHealth = playerMaxHealth;


	// --------------------------------------------------------
	// MOVEMENT
	// --------------------------------------------------------

	velocityY = 0;

	isJumping = false;

	playerMoving = false;

	faceRight = true;


	// --------------------------------------------------------
	// ATTACK
	// --------------------------------------------------------

	isAttacking = false;

	attackFrame = 0;

	attackHit = false;

	attackTimer = 0;


	// --------------------------------------------------------
	// CAMERA
	// --------------------------------------------------------

	level2CameraX = 0;


	// --------------------------------------------------------
	// LEVEL 2 ENEMY UI
	// --------------------------------------------------------

	level2EnemiesDefeated = 0;

	level2CurrentWave = 1;


	// --------------------------------------------------------
	// SPAWN FIRST ENEMY
	// --------------------------------------------------------

	spawnEnemy();
}


// ============================================================
// MAIN FIXED UPDATE
// ============================================================

void fixedUpdate()
{
	if (gameState == 2)
	{
		fixedUpdateLevel1();
	}
	else if (gameState == 5)
	{
		fixedUpdateLevel2();
	}
}


// ============================================================
// DRAW LEVEL 2
// ORIGINAL LEVEL 2 SYSTEM
// ============================================================

void drawLevel2()
{
	int backgroundX =
		-(level2CameraX % level2ScreenWidth);


	// --------------------------------------------------------
	// BACKGROUND
	// --------------------------------------------------------

	iShowImage(
		backgroundX,
		0,
		level2ScreenWidth,
		screenHeight,
		level2BackgroundImage
		);


	iShowImage(
		backgroundX + level2ScreenWidth,
		0,
		level2ScreenWidth,
		screenHeight,
		level2BackgroundImage
		);


	// --------------------------------------------------------
	// PLAYER
	// --------------------------------------------------------

	drawPlayerLevel2();


	// --------------------------------------------------------
	// ENEMY
	// --------------------------------------------------------

	drawEnemyLevel2();


	// --------------------------------------------------------
	// UI
	// --------------------------------------------------------

	drawHealthUI();

	drawScoreUI();


	// --------------------------------------------------------
	// ENEMY COUNT
	// --------------------------------------------------------

	char enemyText[50];

	sprintf_s(
		enemyText,
		"Enemy: %d / %d",
		level2EnemiesDefeated,
		level2TotalEnemies
		);


	iSetColor(
		255,
		255,
		255
		);


	iText(
		390,
		555,
		enemyText,
		GLUT_BITMAP_HELVETICA_18
		);


	// --------------------------------------------------------
	// WAVE
	// --------------------------------------------------------

	char waveText[50];

	sprintf_s(
		waveText,
		"Wave: %d",
		level2CurrentWave
		);


	iText(
		450,
		515,
		waveText,
		GLUT_BITMAP_HELVETICA_18
		);


	// --------------------------------------------------------
	// LEVEL
	// --------------------------------------------------------

	iText(
		460,
		580,
		"LEVEL 2",
		GLUT_BITMAP_HELVETICA_18
		);
}


#endif