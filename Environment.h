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

int instructionImage;

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
// SCREEN SIZE
// ============================================================

const int screenWidth = 1000;

const int screenHeight = 600;


// ============================================================
// LEVEL 1 CAMERA
// ============================================================

int cameraX = 0;

const int level1WorldWidth = 3000;

int backgroundImage2;
int backgroundImage3;


// ============================================================
// LEVEL 2 CAMERA
// ============================================================

int level2CameraX = 0;

const int level2ScreenWidth = 1000;

const int level2WorldWidth = 4000;


// Camera starts following player after this position

const int cameraFollowX = 400;
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


// Door position in Level 1 world
const int level1DoorX = 1800;


// Jade position in Level 1 world
const int jadeX = 2500;


// Jade image
int jadeImage;


// Jade collected
bool jadeCollected = false;

// ============================================================
// MENU
// ============================================================

int selectedMenuButton = 0;

int instructionTimer = 0;

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
	// --------------------------------------------------------
	// PLAYER
	// --------------------------------------------------------

	playerX = 150;

	playerY = groundY;

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
	// LEVEL 1 PROGRESSION
	level1Stage = 0;
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
// INSTRUCTION PAGE
// ============================================================

void drawInstruction()
{
	iShowImage(
		0,
		0,
		screenWidth,
		screenHeight,
		instructionImage
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

	// ========================================================
	// START GAME
	// ========================================================

	if (selectedMenuButton == 1)
	{
		selectedMenuButton = 0;

		resetLevel();

		gameState = 7;

		instructionTimer = 3000;
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
// INSTRUCTION TIMER
// 3 SECONDS
// ============================================================

void updateInstruction()
{
	if (gameState != 7)
	{
		return;
	}

	instructionTimer -= 20;

	if (instructionTimer <= 0)
	{
		instructionTimer = 0;

		gameState = 2;
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
	// Heart icon

	iShowImage(
		20,
		545,
		35,
		35,
		heartImage
		);


	// Health number

	char healthText[20];

	sprintf_s(
		healthText,
		"%d",
		playerHealth
		);

	iSetColor(255, 255, 255);

	iText(
		65,
		555,
		healthText,
		GLUT_BITMAP_HELVETICA_18
		);


	// --------------------------------------------------------
	// HEALTH BAR BACKGROUND
	// --------------------------------------------------------

	iSetColor(80, 0, 0);

	iFilledRectangle(
		20,
		520,
		200,
		15
		);


	// --------------------------------------------------------
	// HEALTH BAR
	// --------------------------------------------------------

	iSetColor(0, 255, 0);

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
// NEW ENEMY
// ============================================================

void drawEnemyLevel2()
{
	if (!enemyAlive)
	{
		return;
	}

	int drawX = enemyX - level2CameraX;


	// --------------------------------------------------------
	// ATTACK
	// --------------------------------------------------------

	if (enemyAttacking)
	{
		iShowImage(
			drawX,
			enemyY,
			enemyWidth,
			enemyHeight,
			enemy2AttackImage[enemyAttackFrame]
			);
	}


	// --------------------------------------------------------
	// RUN
	// --------------------------------------------------------

	else if (abs(enemyX - playerX) > 100)
	{
		iShowImage(
			drawX,
			enemyY,
			enemyWidth,
			enemyHeight,
			enemy2RunImage[enemyRunFrame]
			);
	}


	// --------------------------------------------------------
	// IDLE
	// --------------------------------------------------------

	else
	{
		iShowImage(
			drawX,
			enemyY,
			enemyWidth,
			enemyHeight,
			enemy2Image
			);
	}
}

// ============================================================
// DRAW SCORE
// ============================================================

void drawScoreUI()
{
	// Coin icon moved to top-right

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


	iSetColor(255, 255, 255);

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

void drawLevel1()
{
	// --------------------------------------------------------
	// LEVEL 1 BACKGROUND

	// --------------------------------------------------------

	int backgroundX = -cameraX;


	// --------------------------------------------------------
	// FIRST BACKGROUND
	// --------------------------------------------------------

	iShowImage(
		backgroundX,
		0,
		screenWidth,
		screenHeight,
		backgroundImage
		);


	// --------------------------------------------------------
	// SECOND BACKGROUND
	// --------------------------------------------------------

	iShowImage(
		backgroundX + screenWidth,
		0,
		screenWidth,
		screenHeight,
		backgroundImage2
		);


	// --------------------------------------------------------
	// THIRD BACKGROUND
	// --------------------------------------------------------

	iShowImage(
		backgroundX + (screenWidth * 2),
		0,
		screenWidth,
		screenHeight,
		backgroundImage3
		);


	// --------------------------------------------------------
	// PLAYER
	// --------------------------------------------------------

	drawPlayerLevel1();


	// --------------------------------------------------------
	// ENEMY
	// --------------------------------------------------------

	drawEnemyLevel1();


	// --------------------------------------------------------
	// HEALTH UI
	// --------------------------------------------------------

	drawHealthUI();


	// --------------------------------------------------------
	// SCORE UI
	// --------------------------------------------------------

	drawScoreUI();


	// --------------------------------------------------------
	// ENEMY COUNT
	// --------------------------------------------------------

	char enemyText[50];

	sprintf_s(
		enemyText,
		"Enemy: %d / %d",
		enemiesDefeated,
		totalEnemies
		);

	iSetColor(255, 255, 255);

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
		currentEnemy
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


	// --------------------------------------------------------
	// DAMAGE ENEMY
	// --------------------------------------------------------

	enemyHealth -= attackDamage;

	attackHit = true;


	// --------------------------------------------------------
	// ENEMY STILL ALIVE
	// --------------------------------------------------------

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


	// --------------------------------------------------------
	// LEVEL 1 COMPLETE
	// --------------------------------------------------------

	if (enemiesDefeated >= totalEnemies)
	{
		startLevel2();

		return;
	}


	// --------------------------------------------------------
	// NEXT ENEMY
	// --------------------------------------------------------

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


	// --------------------------------------------------------
	// DAMAGE ENEMY
	// --------------------------------------------------------

	enemyHealth -= attackDamage;

	attackHit = true;


	// --------------------------------------------------------
	// ENEMY STILL ALIVE
	// --------------------------------------------------------

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


	level2EnemiesDefeated++;

	score += scorePerEnemy;


	// --------------------------------------------------------
	// ALL 10 ENEMIES KILLED
	// --------------------------------------------------------

	if (level2EnemiesDefeated >= level2TotalEnemies)
	{
		gameState = 4;

		return;
	}


	// --------------------------------------------------------
	// NEXT WAVE
	// --------------------------------------------------------

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
		level1WorldWidth - playerWidth)
	{
		playerX =
			level1WorldWidth - playerWidth;
	}


	// --------------------------------------------------------
	// ATTACK COOLDOWN
	// --------------------------------------------------------

	if (attackTimer > 0)
	{
		attackTimer--;
	}


	// --------------------------------------------------------
	// PLAYER ATTACK
	// --------------------------------------------------------

	updateLevel1PlayerAttack();


	// --------------------------------------------------------
	// ENEMY MOVEMENT
	// --------------------------------------------------------

	updateEnemyMovement();


	// --------------------------------------------------------
	// CAMERA
	// --------------------------------------------------------

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


void fixedUpdate()
{
	if (gameState == 7)
	{
		updateInstruction();
	}

	else if (gameState == 2)
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


	iSetColor(255, 255, 255);

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
