#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H


// ============================================================
// FUNCTION DECLARATIONS
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


// LEVEL 2 BACKGROUNDS

int level2BackgroundImage1;

int level2BackgroundImage2;

int level2BackgroundImage3;


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
// SCREEN
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

const int level2WorldWidth = 3000;

const int cameraFollowX = 400;


// ============================================================
// LEVEL 1 PLATFORM
// ============================================================

const int level1PlatformY1 = 135;

const int level1PlatformY2 = 135;

const int level1PlatformY3 = 135;


// ============================================================
// LEVEL 2 PLATFORM
// ============================================================

const int level2PlatformY = 105;


// ============================================================
// LEVEL 1 STAGE
// ============================================================

// 0 = Fight
// 1 = Door
// 2 = Jade

int level1Stage = 0;


// ============================================================
// LEVEL 1 DOOR + JADE
// ============================================================

const int level1DoorX = 500;

const int jadeX = 800;

bool jadeCollected = false;


// ============================================================
// LEVEL 2 STAGE
// ============================================================

// 0 = First 5 enemies
// 1 = Second 5 enemies
// 2 = Background 2 + Gate
// 3 = Background 3 + Jade

int level2Stage = 0;


// ============================================================
// LEVEL 2 GATE + JADE
// ============================================================

const int level2DoorX = 330;

const int level2JadeX = 500;


// ============================================================
// LEVEL 2 ENEMY COUNT
// ============================================================

int level2CurrentWave = 1;


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
// LEVEL 1 PLATFORM POSITION
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
	playerX = 150;

	level1Stage = 0;

	setLevel1PlayerOnPlatform();

	playerHealth = playerMaxHealth;

	faceRight = true;

	playerMoving = false;

	runFrame = 0;


	isAttacking = false;

	attackFrame = 0;

	attackHit = false;

	attackTimer = 0;


	isJumping = false;

	velocityY = 0;


	cameraX = 0;


	jadeCollected = false;


	score = 0;


	enemiesDefeated = 0;

	currentEnemy = 1;


	spawnEnemy();
}


// ============================================================
// MENU
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


	if (selectedMenuButton == 1)
	{
		selectedMenuButton = 0;

		resetLevel();

		gameState = 2;
	}
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
		(playerHealth * 200) /
		playerMaxHealth;


	iFilledRectangle(
		20,
		520,
		healthBarWidth,
		15
		);
}


// ============================================================
// PLAYER LEVEL 1
// ============================================================

void drawPlayerLevel1()
{
	int drawX =
		playerX - cameraX;


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
	else if (
		playerMoving &&
		!isJumping
		)
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
// PLAYER LEVEL 2
// ============================================================

void drawPlayerLevel2()
{
	int drawX =
		playerX - level2CameraX;


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
	else if (
		playerMoving &&
		!isJumping
		)
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
// LEVEL 1 ENEMY DRAW
// ============================================================

void drawEnemyLevel1()
{
	if (!enemyAlive)
	{
		return;
	}


	int drawX =
		enemyX - cameraX;


	if (enemyAttacking)
	{
		iShowImage(
			drawX,
			enemyY,
			enemyWidth,
			enemyHeight,
			enemyAttackImage[
				enemyAttackFrame
			]
			);
	}
	else if (
		abs(enemyX - playerX) > 100
		)
	{
		iShowImage(
			drawX,
			enemyY,
			enemyWidth,
			enemyHeight,
			enemyRunImage[
				enemyRunFrame
			]
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
// LEVEL 2 ENEMY DRAW
// ============================================================

void drawEnemyLevel2()
{
	if (!enemyAlive)
	{
		return;
	}


	int drawX =
		enemyX - level2CameraX;


	// ========================================================
	// FIRST ENEMY TYPE
	// ========================================================

	if (level2EnemyType == 0)
	{
		if (enemyAttacking)
		{
			iShowImage(
				drawX,
				enemyY,
				enemyWidth,
				enemyHeight,
				level2EnemyAttackImage[
					enemyAttackFrame
				]
				);
		}
		else if (
			abs(enemyX - playerX) > 100
			)
		{
			iShowImage(
				drawX,
				enemyY,
				enemyWidth,
				enemyHeight,
				level2EnemyRunImage[
					enemyRunFrame
				]
				);
		}
		else
		{
			iShowImage(
				drawX,
				enemyY,
				enemyWidth,
				enemyHeight,
				level2EnemyImage
				);
		}
	}


	// ========================================================
	// SECOND ENEMY TYPE
	// ========================================================

	else
	{
		if (enemyAttacking)
		{
			iShowImage(
				drawX,
				enemyY,
				enemyWidth,
				enemyHeight,
				level2Enemy1AttackImage[
					enemyAttackFrame
				]
				);
		}
		else if (
			abs(enemyX - playerX) > 100
			)
		{
			iShowImage(
				drawX,
				enemyY,
				enemyWidth,
				enemyHeight,
				level2Enemy1RunImage[
					enemyRunFrame
				]
				);
		}
		else
		{
			iShowImage(
				drawX,
				enemyY,
				enemyWidth,
				enemyHeight,
				level2Enemy1Image
				);
		}
	}
}


// ============================================================
// SCORE UI
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
// LEVEL 1 DRAW
// ============================================================

void drawLevel1()
{
	if (level1Stage == 0)
	{
		int backgroundX =
			-cameraX;


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
			backgroundX +
			(screenWidth * 2),
			0,
			screenWidth,
			screenHeight,
			backgroundImage
			);
	}
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


	drawPlayerLevel1();


	if (level1Stage == 0)
	{
		drawEnemyLevel1();
	}


	drawHealthUI();

	drawScoreUI();


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


	enemyHealth -= attackDamage;

	attackHit = true;


	if (enemyHealth > 0)
	{
		return;
	}


	enemyHealth = 0;

	enemyAlive = false;

	enemyAttacking = false;

	enemiesDefeated++;

	score += scorePerEnemy;


	// ========================================================
	// ALL 10 ENEMIES DEFEATED
	// ========================================================

	if (enemiesDefeated >= totalEnemies)
	{
		enemiesDefeated = totalEnemies;

		level1Stage = 1;

		cameraX = 0;

		playerX = 100;

		setLevel1PlayerOnPlatform();

		playerMoving = false;

		isAttacking = false;

		attackHit = false;

		attackTimer = 0;

		faceRight = true;

		isJumping = false;

		velocityY = 0;

		enemyAlive = false;

		enemyAttacking = false;

		return;
	}


	spawnNextWave();
}


// ============================================================
// LEVEL 2 PLAYER ATTACK
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


	// ========================================================
	// AFTER FIRST 5 ENEMIES
	// SECOND ENEMY TYPE STARTS
	// ========================================================

	if (
		level2EnemiesDefeated ==
		level2FirstEnemyCount
		)
	{
		level2Stage = 1;

		level2EnemyType = 1;

		level2CurrentWave = 6;

		spawnLevel2Enemy1();

		return;
	}


	// ========================================================
	// AFTER TOTAL 10 ENEMIES
	// GO TO BACKGROUND 2
	// ========================================================

	if (
		level2EnemiesDefeated >=
		level2TotalEnemies
		)
	{
		level2EnemiesDefeated =
			level2TotalEnemies;


		level2Stage = 2;

		enemyAlive = false;

		level2CameraX = 0;

		playerX = 100;

		playerY = level2PlatformY;

		playerMoving = false;

		isAttacking = false;

		attackHit = false;

		attackTimer = 0;

		faceRight = true;

		isJumping = false;

		velocityY = 0;

		return;
	}


	// ========================================================
	// NEXT ENEMY
	// ========================================================

	if (level2EnemyType == 0)
	{
		level2CurrentWave++;

		spawnLevel2Enemy();
	}
	else
	{
		level2CurrentWave++;

		spawnLevel2Enemy1();
	}
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
	// FIGHT STAGE
	// ========================================================

	if (level1Stage == 0)
	{
		if (
			isKeyPressed('d') ||
			isKeyPressed('D')
			)
		{
			if (!isAttacking)
			{
				playerX += playerSpeed;

				playerMoving = true;

				faceRight = true;
			}
		}


		if (
			isKeyPressed('a') ||
			isKeyPressed('A')
			)
		{
			if (!isAttacking)
			{
				playerX -= playerSpeed;

				playerMoving = true;

				faceRight = false;
			}
		}


		if (playerX < 0)
		{
			playerX = 0;
		}


		if (
			playerX >
			level1WorldWidth -
			playerWidth
			)
		{
			playerX =
				level1WorldWidth -
				playerWidth;
		}


		setLevel1PlayerOnPlatform();


		if (attackTimer > 0)
		{
			attackTimer--;
		}


		updateLevel1PlayerAttack();


		if (level1Stage != 0)
		{
			return;
		}


		updateEnemyMovement();


		if (playerX > cameraFollowX)
		{
			cameraX =
				playerX -
				cameraFollowX;
		}
		else
		{
			cameraX = 0;
		}


		if (cameraX < 0)
		{
			cameraX = 0;
		}


		if (
			cameraX >
			level1WorldWidth -
			screenWidth
			)
		{
			cameraX =
				level1WorldWidth -
				screenWidth;
		}


		return;
	}


	// ========================================================
	// LEVEL 1 DOOR
	// ========================================================

	if (level1Stage == 1)
	{
		cameraX = 0;


		if (
			isKeyPressed('d') ||
			isKeyPressed('D')
			)
		{
			if (!isAttacking)
			{
				playerX += playerSpeed;

				playerMoving = true;

				faceRight = true;
			}
		}


		if (
			isKeyPressed('a') ||
			isKeyPressed('A')
			)
		{
			if (!isAttacking)
			{
				playerX -= playerSpeed;

				playerMoving = true;

				faceRight = false;
			}
		}


		if (playerX < 0)
		{
			playerX = 0;
		}


		if (
			playerX >
			screenWidth -
			playerWidth
			)
		{
			playerX =
				screenWidth -
				playerWidth;
		}


		playerY =
			level1PlatformY2;


		int playerCenter =
			playerX +
			(playerWidth / 2);


		int doorDistance =
			abs(
			playerCenter -
			level1DoorX
			);


		if (doorDistance <= 80)
		{
			level1Stage = 2;

			cameraX = 0;

			playerX = 100;

			playerY =
				level1PlatformY3;

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
	// LEVEL 1 JADE
	// ========================================================

	if (level1Stage == 2)
	{
		cameraX = 0;


		if (
			isKeyPressed('d') ||
			isKeyPressed('D')
			)
		{
			if (!isAttacking)
			{
				playerX += playerSpeed;

				playerMoving = true;

				faceRight = true;
			}
		}


		if (
			isKeyPressed('a') ||
			isKeyPressed('A')
			)
		{
			if (!isAttacking)
			{
				playerX -= playerSpeed;

				playerMoving = true;

				faceRight = false;
			}
		}


		if (playerX < 0)
		{
			playerX = 0;
		}


		if (
			playerX >
			screenWidth -
			playerWidth
			)
		{
			playerX =
				screenWidth -
				playerWidth;
		}


		playerY =
			level1PlatformY3;


		int playerCenter =
			playerX +
			(playerWidth / 2);


		int jadeDistance =
			abs(
			playerCenter -
			jadeX
			);


		if (jadeDistance <= 80)
		{
			jadeCollected = true;

			level1Stage = 3;

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
// ============================================================

void fixedUpdateLevel2()
{
	if (gameState != 5)
	{
		return;
	}


	playerMoving = false;


	// ========================================================
	// STAGE 0 + STAGE 1
	// FIRST 5 + SECOND 5 ENEMIES
	// ========================================================

	if (
		level2Stage == 0 ||
		level2Stage == 1
		)
	{
		// RIGHT
		if (
			isKeyPressed('d') ||
			isKeyPressed('D')
			)
		{
			if (!isAttacking)
			{
				playerX += playerSpeed;

				playerMoving = true;

				faceRight = true;
			}
		}


		// LEFT
		if (
			isKeyPressed('a') ||
			isKeyPressed('A')
			)
		{
			if (!isAttacking)
			{
				playerX -= playerSpeed;

				playerMoving = true;

				faceRight = false;
			}
		}


		if (playerX < 0)
		{
			playerX = 0;
		}


		if (
			playerX >
			level2WorldWidth -
			playerWidth
			)
		{
			playerX =
				level2WorldWidth -
				playerWidth;
		}


		// ====================================================
		// JUMP
		// ====================================================

		if (isJumping)
		{
			velocityY -= gravity;

			playerY += velocityY;


			if (
				playerY <=
				level2PlatformY
				)
			{
				playerY =
					level2PlatformY;

				velocityY = 0;

				isJumping = false;
			}
		}
		else
		{
			playerY =
				level2PlatformY;
		}


		// ====================================================
		// ATTACK TIMER
		// ====================================================

		if (attackTimer > 0)
		{
			attackTimer--;
		}


		// ====================================================
		// PLAYER ATTACK
		// ====================================================

		updateLevel2PlayerAttack();


		if (gameState != 5)
		{
			return;
		}


		// ====================================================
		// ENEMY PLATFORM
		// ====================================================

		if (enemyAlive)
		{
			enemyY =
				level2PlatformY;
		}


		// ====================================================
		// ENEMY MOVEMENT
		// ====================================================

		updateEnemyMovement();


		// ====================================================
		// CAMERA
		// ====================================================

		if (playerX > cameraFollowX)
		{
			level2CameraX =
				playerX -
				cameraFollowX;
		}
		else
		{
			level2CameraX = 0;
		}


		if (level2CameraX < 0)
		{
			level2CameraX = 0;
		}


		if (
			level2CameraX >
			level2WorldWidth -
			level2ScreenWidth
			)
		{
			level2CameraX =
				level2WorldWidth -
				level2ScreenWidth;
		}


		return;
	}


	// ========================================================
	// STAGE 2
	// BACKGROUND 2 + GATE
	// ========================================================

	if (level2Stage == 2)
	{
		level2CameraX = 0;

		enemyAlive = false;


		// RIGHT
		if (
			isKeyPressed('d') ||
			isKeyPressed('D')
			)
		{
			if (!isAttacking)
			{
				playerX += playerSpeed;

				playerMoving = true;

				faceRight = true;
			}
		}


		// LEFT
		if (
			isKeyPressed('a') ||
			isKeyPressed('A')
			)
		{
			if (!isAttacking)
			{
				playerX -= playerSpeed;

				playerMoving = true;

				faceRight = false;
			}
		}


		if (playerX < 0)
		{
			playerX = 0;
		}


		if (
			playerX >
			screenWidth -
			playerWidth
			)
		{
			playerX =
				screenWidth -
				playerWidth;
		}


		playerY =
			level2PlatformY;


		int playerCenter =
			playerX +
			(playerWidth / 2);


		int doorDistance =
			abs(
			playerCenter -
			level2DoorX
			);


		if (doorDistance <= 80)
		{
			level2Stage = 3;

			level2CameraX = 0;

			playerX = 100;

			playerY =
				level2PlatformY;

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
	// STAGE 3
	// BACKGROUND 3 + JADE
	// ========================================================

	if (level2Stage == 3)
	{
		level2CameraX = 0;

		enemyAlive = false;


		// RIGHT
		if (
			isKeyPressed('d') ||
			isKeyPressed('D')
			)
		{
			if (!isAttacking)
			{
				playerX += playerSpeed;

				playerMoving = true;

				faceRight = true;
			}
		}


		// LEFT
		if (
			isKeyPressed('a') ||
			isKeyPressed('A')
			)
		{
			if (!isAttacking)
			{
				playerX -= playerSpeed;

				playerMoving = true;

				faceRight = false;
			}
		}


		if (playerX < 0)
		{
			playerX = 0;
		}


		if (
			playerX >
			screenWidth -
			playerWidth
			)
		{
			playerX =
				screenWidth -
				playerWidth;
		}


		playerY =
			level2PlatformY;


		int playerCenter =
			playerX +
			(playerWidth / 2);


		int jadeDistance =
			abs(
			playerCenter -
			level2JadeX
			);


		if (jadeDistance <= 90)
		{
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
// START LEVEL 2
// ============================================================

void startLevel2()
{
	gameState = 5;


	playerX = 150;

	playerY =
		level2PlatformY;


	playerHealth =
		playerMaxHealth;


	velocityY = 0;

	isJumping = false;

	playerMoving = false;

	faceRight = true;


	isAttacking = false;

	attackFrame = 0;

	attackHit = false;

	attackTimer = 0;


	level2CameraX = 0;


	// ========================================================
	// RESET LEVEL 2
	// ========================================================

	level2EnemiesDefeated = 0;

	level2CurrentWave = 1;

	level2Stage = 0;

	level2EnemyType = 0;


	score = 0;


	// ========================================================
	// FIRST ENEMY TYPE
	// ========================================================

	spawnLevel2Enemy();
}


// ============================================================
// FIXED UPDATE
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
// ============================================================

void drawLevel2()
{
	// ========================================================
	// STAGE 0 + STAGE 1
	// BACKGROUND 1
	// ========================================================

	if (
		level2Stage == 0 ||
		level2Stage == 1
		)
	{
		int backgroundX =
			-(level2CameraX %
			level2ScreenWidth);


		iShowImage(
			backgroundX,
			0,
			level2ScreenWidth,
			screenHeight,
			level2BackgroundImage1
			);


		iShowImage(
			backgroundX +
			level2ScreenWidth,
			0,
			level2ScreenWidth,
			screenHeight,
			level2BackgroundImage1
			);


		drawPlayerLevel2();

		drawEnemyLevel2();
	}


	// ========================================================
	// STAGE 2
	// BACKGROUND 2 + GATE
	// ========================================================

	else if (level2Stage == 2)
	{
		iShowImage(
			0,
			0,
			screenWidth,
			screenHeight,
			level2BackgroundImage2
			);


		drawPlayerLevel2();
	}


	// ========================================================
	// STAGE 3
	// BACKGROUND 3 + JADE
	// ========================================================

	else if (level2Stage == 3)
	{
		iShowImage(
			0,
			0,
			screenWidth,
			screenHeight,
			level2BackgroundImage3
			);


		drawPlayerLevel2();
	}


	// ========================================================
	// HUD
	// ========================================================

	drawHealthUI();

	drawScoreUI();


	// Enemy count
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


	// ========================================================
	// ENEMY TYPE TEXT
	// ========================================================

	char typeText[50];


	if (level2Stage == 0)
	{
		sprintf_s(
			typeText,
			"Enemy Type: 1"
			);
	}
	else if (level2Stage == 1)
	{
		sprintf_s(
			typeText,
			"Enemy Type: 2"
			);
	}
	else
	{
		sprintf_s(
			typeText,
			""
			);
	}


	iText(
		430,
		515,
		typeText,
		GLUT_BITMAP_HELVETICA_18
		);


	// ========================================================
	// LEVEL NAME
	// ========================================================

	iText(
		460,
		580,
		"LEVEL 2",
		GLUT_BITMAP_HELVETICA_18
		);
}


#endif