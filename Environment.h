#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H


// ============================================================
// FORWARD DECLARATION
// ============================================================

void startLevel2();


// ============================================================
// IMAGES
// ============================================================

int menuImage;

int storyImage;

int backgroundImage;

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
// LEVEL 1 CAMERA
// ============================================================

int cameraX = 0;

const int screenWidth = 800;

const int level1WorldWidth = 3000;


// ============================================================
// LEVEL 2 CAMERA
// ============================================================

int level2CameraX = 0;

const int level2ScreenWidth = 800;

const int level2WorldWidth = 4000;

const int cameraFollowX = 500;


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
// RESET LEVEL 1
// ============================================================

void resetLevel()
{
	// Player

	playerX = 150;
	playerY = groundY;

	playerHealth = playerMaxHealth;

	faceRight = true;

	playerMoving = false;

	runFrame = 0;


	// Attack

	isAttacking = false;

	attackFrame = 0;

	attackHit = false;

	attackTimer = 0;


	// Jump

	isJumping = false;

	velocityY = 0;


	// Camera

	cameraX = 0;


	// Score

	score = 0;


	// Enemy system

	enemiesDefeated = 0;

	currentEnemy = 1;


	// Spawn first enemy

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
		800,
		600,
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


	// Start game

	if (selectedMenuButton == 1)
	{
		selectedMenuButton = 0;

		resetLevel();

		gameState = 2;
	}


	// Exit

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
		800,
		600,
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
		800,
		600,
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
		800,
		600,
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
		800,
		600,
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
		540,
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


	iSetColor(255, 255, 255);

	iText(
		65,
		550,
		healthText,
		GLUT_BITMAP_HELVETICA_18
		);


	// Health bar background

	iSetColor(80, 0, 0);

	iFilledRectangle(
		20,
		515,
		200,
		15
		);


	// Health bar

	iSetColor(0, 255, 0);

	int healthBarWidth =
		(playerHealth * 200) / playerMaxHealth;


	iFilledRectangle(
		20,
		625,
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
// SAME ENEMY AS LEVEL 1
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
		700,
		540,
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


	iSetColor(255, 255, 255);

	iText(
		745,
		550,
		scoreText
		);
}


// ============================================================
// DRAW LEVEL 1
// ============================================================

void drawLevel1()
{
	int backgroundX =
		-(cameraX % screenWidth);


	iShowImage(
		backgroundX,
		0,
		screenWidth,
		600,
		backgroundImage
		);


	iShowImage(
		backgroundX + screenWidth,
		0,
		screenWidth,
		600,
		backgroundImage
		);


	drawPlayerLevel1();

	drawEnemyLevel1();

	drawHealthUI();

	drawScoreUI();


	// Enemy killed

	char enemyText[50];

	sprintf_s(
		enemyText,
		"Enemy: %d / %d",
		enemiesDefeated,
		totalEnemies
		);


	iSetColor(255, 255, 255);

	iText(
		520,
		680,
		enemyText,
		GLUT_BITMAP_HELVETICA_18
		);


	// Wave

	char waveText[50];

	sprintf_s(
		waveText,
		"Wave: %d",
		currentEnemy
		);


	iText(
		580,
		630,
		waveText
		);


	// Level

	iText(
		365,
		580,
		"LEVEL 1",
		GLUT_BITMAP_HELVETICA_18
		);
}


// ============================================================
// ENEMY MOVEMENT
// WORKS IN BOTH LEVELS
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


	// Damage enemy

	enemyHealth -= attackDamage;

	attackHit = true;


	// Enemy still alive

	if (enemyHealth > 0)
	{
		return;
	}


	// Enemy dead

	enemyHealth = 0;

	enemyAlive = false;

	enemyAttacking = false;


	enemiesDefeated++;

	score += scorePerEnemy;


	// Level 1 complete

	if (enemiesDefeated >= totalEnemies)
	{
		startLevel2();

		return;
	}


	// Next enemy

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


	// Damage enemy

	enemyHealth -= attackDamage;

	attackHit = true;


	// Enemy still alive

	if (enemyHealth > 0)
	{
		return;
	}


	// Enemy dead

	enemyHealth = 0;

	enemyAlive = false;

	enemyAttacking = false;


	// Level 2 enemy count

	level2EnemiesDefeated++;

	score += scorePerEnemy;


	// All 10 enemies killed

	if (level2EnemiesDefeated >= level2TotalEnemies)
	{
		gameState = 4;

		return;
	}


	// Next wave

	level2CurrentWave++;


	// Spawn same enemy again

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


	// Move right

	if (isKeyPressed('d') || isKeyPressed('D'))
	{
		if (!isAttacking)
		{
			playerX += playerSpeed;

			playerMoving = true;

			faceRight = true;
		}
	}


	// Move left

	if (isKeyPressed('a') || isKeyPressed('A'))
	{
		if (!isAttacking)
		{
			playerX -= playerSpeed;

			playerMoving = true;

			faceRight = false;
		}
	}


	// World limit

	if (playerX < 0)
	{
		playerX = 0;
	}

	if (playerX > level1WorldWidth - playerWidth)
	{
		playerX =
			level1WorldWidth - playerWidth;
	}


	// Attack cooldown

	if (attackTimer > 0)
	{
		attackTimer--;
	}


	// Attack enemy

	updateLevel1PlayerAttack();


	// Enemy movement

	updateEnemyMovement();


	// Camera

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


	// Move right

	if (isKeyPressed('d') || isKeyPressed('D'))
	{
		if (!isAttacking)
		{
			playerX += playerSpeed;

			playerMoving = true;

			faceRight = true;
		}
	}


	// Move left

	if (isKeyPressed('a') || isKeyPressed('A'))
	{
		if (!isAttacking)
		{
			playerX -= playerSpeed;

			playerMoving = true;

			faceRight = false;
		}
	}


	// World limit

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


	// Attack cooldown

	if (attackTimer > 0)
	{
		attackTimer--;
	}


	// Jump physics

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


	// Player attack

	updateLevel2PlayerAttack();


	if (gameState != 5)
	{
		return;
	}


	// Enemy movement

	updateEnemyMovement();


	// Camera

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


	// Player

	playerX = 150;

	playerY = groundY;

	playerHealth = playerMaxHealth;


	// Movement

	velocityY = 0;

	isJumping = false;

	playerMoving = false;

	faceRight = true;


	// Attack

	isAttacking = false;

	attackFrame = 0;

	attackHit = false;

	attackTimer = 0;


	// Camera

	level2CameraX = 0;


	// Level 2 enemy UI

	level2EnemiesDefeated = 0;

	level2CurrentWave = 1;


	// Spawn first enemy

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
// ============================================================

void drawLevel2()
{
	int backgroundX =
		-(level2CameraX % level2ScreenWidth);


	iShowImage(
		backgroundX,
		0,
		level2ScreenWidth,
		600,
		level2BackgroundImage
		);


	iShowImage(
		backgroundX + level2ScreenWidth,
		0,
		level2ScreenWidth,
		600,
		level2BackgroundImage
		);


	drawPlayerLevel2();

	drawEnemyLevel2();

	drawHealthUI();

	drawScoreUI();


	// Enemy killed

	char enemyText[50];

	sprintf_s(
		enemyText,
		"Enemy: %d / %d",
		level2EnemiesDefeated,
		level2TotalEnemies
		);


	iSetColor(255, 255, 255);

	iText(
		520,
		680,
		enemyText,
		GLUT_BITMAP_HELVETICA_18
		);


	// Wave

	char waveText[50];

	sprintf_s(
		waveText,
		"Wave: %d",
		level2CurrentWave
		);


	iText(
		580,
		630,
		waveText
		);


	// Level

	iText(
		365,
		580,
		"LEVEL 2",
		GLUT_BITMAP_HELVETICA_18
		);
}

#endif