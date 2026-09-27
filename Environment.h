#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H


// ============================================================
// FUNCTION DECLARATIONS
// ============================================================

void startLevel2();

void startLevel3();

void updateLevel1PlayerAttack();

void updateLevel2PlayerAttack();

void updateLevel3PlayerAttack();

void fixedUpdateLevel1();

void fixedUpdateLevel2();

void fixedUpdateLevel3();


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


// LEVEL 3 BACKGROUNDS

int level3BackgroundImage1;

int level3BackgroundImage2;

int level3BackgroundImage3;

int level3BackgroundImage4;

int level3BackgroundImage5;


int winImage;

int gameoverImage;
int heartImage;

int coinImage;

int levelSelectImage;
int healthbarImage;

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

const int level2WorldWidth = 4000;

const int cameraFollowX = 400;


// ============================================================
// LEVEL 3 CAMERA
// ============================================================

int level3CameraX = 0;

const int level3ScreenWidth = 1000;

const int level3WorldWidth = 3000;

const int level3CameraFollowX = 400;


// ============================================================
// LEVEL 1 PLATFORM
// ============================================================

const int level1PlatformY1 = 135;

const int level1PlatformY2 = 135;

const int level1PlatformY3 = 135;


// ============================================================
// LEVEL 2 PLATFORM
// ============================================================

const int level2PlatformY = 235;

// ============================================================
// LEVEL 2 ONLY - WORLD / CAMERA / PLATFORM SETTINGS
// ============================================================
// level2BackgroundImage1 is a 4000 x 600 image, so it is drawn
// at its real size and the camera crops the visible 1000 x 600 area.
const int level2RealWorldWidth = 4000;
const int level2ViewportWidth = 1000;
const int level2ViewportHeight = 600;

// Level 2 uses smaller visual sprites so they match the background.
const int level2PlayerDrawWidth = 130;
const int level2PlayerDrawHeight = 125;
const int level2EnemyDrawWidth = 130;
const int level2EnemyDrawHeight = 125;
const int level2CoinDrawSize = 38;

// Platform top Y values are world coordinates measured from the bottom.
// These are Level 2 only; Level 1 and Level 3 are untouched.
struct Level2Platform
{
	int x;
	int y;
	int width;
};

Level2Platform level2Platforms[] =
{
	{ 0, 235, 780 },   // starting ground
	{ 780, 235, 330 },   // after first spike
	{ 1110, 235, 420 },   // enemy area
	{ 1530, 235, 300 },
	{ 1830, 235, 420 },
	{ 2250, 235, 300 },
	{ 2550, 235, 450 },
	{ 3000, 235, 500 },
	{ 3500, 235, 500 },

	// upper platforms
	{ 360, 330, 170 },
	{ 560, 390, 170 },
	{ 1220, 330, 180 },
	{ 1420, 385, 170 },
	{ 1980, 325, 190 },
	{ 2210, 385, 170 },
	{ 2700, 330, 180 },
	{ 2920, 390, 170 }
};

const int level2PlatformCount =
sizeof(level2Platforms) / sizeof(level2Platforms[0]);

// First spike section from the Level 2 reference.
const int level2FirstSpikeX = 820;
const int level2FirstSpikeWidth = 170;

// The first enemy is unlocked only after the player crosses the first spike.
const int level2FirstEnemySpawnX = 1190;

// Coins replace the jade locations in Level 2.
const int level2CoinCount = 3;
int level2CoinX[level2CoinCount] = { 650, 2050, 2850 };
int level2CoinY[level2CoinCount] = { 395, 385, 390 };
bool level2CoinCollected[level2CoinCount] = { false, false, false };

bool level2FirstSpikeCrossed = false;
int level2SpikeDamageCooldown = 0;

// ============================================================
// LEVEL 2 HELPERS
// ============================================================

int getLevel2PlatformY(int x, int currentY)
{
	// Prefer the platform directly below the player's feet.
	int bestY = -10000;

	for (int i = 0; i < level2PlatformCount; i++)
	{
		Level2Platform p = level2Platforms[i];

		if (x + level2PlayerDrawWidth > p.x &&
			x < p.x + p.width)
		{
			if (p.y <= currentY && p.y > bestY)
			{
				bestY = p.y;
			}
		}
	}

	return bestY;
}

bool level2IsOnPlatform(int x, int y)
{
	for (int i = 0; i < level2PlatformCount; i++)
	{
		Level2Platform p = level2Platforms[i];

		if (x + level2PlayerDrawWidth > p.x &&
			x < p.x + p.width &&
			abs(y - p.y) <= 3)
		{
			return true;
		}
	}

	return false;
}

void level2ClampAgainstEnemy()
{
	if (!enemyAlive)
	{
		return;
	}

	if (playerX < enemyX)
	{
		if (playerX + level2PlayerDrawWidth > enemyX)
		{
			playerX = enemyX - level2PlayerDrawWidth;
		}
	}
	else
	{
		if (playerX < enemyX + level2EnemyDrawWidth)
		{
			playerX = enemyX + level2EnemyDrawWidth;
		}
	}
}

void level2CheckCoins()
{
	int playerCenter = playerX + level2PlayerDrawWidth / 2;

	for (int i = 0; i < level2CoinCount; i++)
	{
		if (level2CoinCollected[i])
		{
			continue;
		}

		if (abs(playerCenter - level2CoinX[i]) <= 55 &&
			abs((playerY + level2PlayerDrawHeight / 2) - level2CoinY[i]) <= 70)
		{
			level2CoinCollected[i] = true;
			score += 1;
		}
	}
}

void level2DrawCoins()
{
	for (int i = 0; i < level2CoinCount; i++)
	{
		if (level2CoinCollected[i])
		{
			continue;
		}

		iShowImage(
			level2CoinX[i] - level2CameraX - level2CoinDrawSize / 2,
			level2CoinY[i] - level2CoinDrawSize / 2,
			level2CoinDrawSize,
			level2CoinDrawSize,
			coinImage
			);
	}
}


// ============================================================
// LEVEL 3 PLATFORM
// ============================================================

const int level3PlatformY = 105;


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
// LEVEL 3 STAGE
// ============================================================

// 0 = Background 1 + First Gate
// 1 = Background 2 + First 5 Enemies
// 2 = Background 3 + Second Gate
// 3 = Background 4 + Second 5 Enemies
// 4 = Background 5 + Jade

int level3Stage = 0;


// ============================================================
// LEVEL 3 GATES + JADE
// ============================================================

const int level3Gate1X = 450;

const int level3Gate2X = 450;

const int level3JadeX = 800;


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
	// STOP PREVIOUS VICTORY SOUND
	mciSendString(
		"stop victorysound",
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
	int x = 20;
	int y = 545;
	int width = 260;
	int height = 30;

	// Draw healthbar image
	iShowImage(
		x,
		y,
		width,
		height,
		healthbarImage
		);

	// Calculate health percentage
	float healthPercent = 0.0f;

	if (playerMaxHealth > 0)
	{
		healthPercent =
			(float)playerHealth /
			(float)playerMaxHealth;
	}

	if (healthPercent < 0.0f)
	{
		healthPercent = 0.0f;
	}

	if (healthPercent > 1.0f)
	{
		healthPercent = 1.0f;
	}

	// Empty part of the health bar
	int fillX = x + 65;
	int fillY = y + 7;
	int fillWidth = 175;
	int fillHeight = 16;

	int currentFillWidth =
		(int)(fillWidth * healthPercent);

	if (currentFillWidth < fillWidth)
	{
		iSetColor(20, 30, 20);

		iFilledRectangle(
			fillX + currentFillWidth,
			fillY,
			fillWidth - currentFillWidth,
			fillHeight
			);
	}

	// Health number
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
		x + 95,
		y + 8,
		healthText,
		GLUT_BITMAP_HELVETICA_18
		);
}
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
	int drawX = playerX - level2CameraX;

	if (isAttacking)
	{
		iShowImage(
			drawX,
			playerY,
			level2PlayerDrawWidth,
			level2PlayerDrawHeight,
			attackImage[attackFrame]
			);
	}
	else if (playerMoving && !isJumping)
	{
		iShowImage(
			drawX,
			playerY,
			level2PlayerDrawWidth,
			level2PlayerDrawHeight,
			runImage[runFrame]
			);
	}
	else
	{
		iShowImage(
			drawX,
			playerY,
			level2PlayerDrawWidth,
			level2PlayerDrawHeight,
			playerImage
			);
	}
}


// ============================================================
// PLAYER LEVEL 3
// ============================================================

void drawPlayerLevel3()
{
	int drawX =
		playerX - level3CameraX;


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

	int drawX = enemyX - level2CameraX;

	if (level2EnemyType == 0)
	{
		if (enemyAttacking)
		{
			iShowImage(drawX, enemyY,
				level2EnemyDrawWidth, level2EnemyDrawHeight,
				level2EnemyAttackImage[enemyAttackFrame]);
		}
		else if (abs(enemyX - playerX) > 100)
		{
			iShowImage(drawX, enemyY,
				level2EnemyDrawWidth, level2EnemyDrawHeight,
				level2EnemyRunImage[enemyRunFrame]);
		}
		else
		{
			iShowImage(drawX, enemyY,
				level2EnemyDrawWidth, level2EnemyDrawHeight,
				level2EnemyImage);
		}
	}
	else
	{
		if (enemyAttacking)
		{
			iShowImage(drawX, enemyY,
				level2EnemyDrawWidth, level2EnemyDrawHeight,
				level2Enemy1AttackImage[enemyAttackFrame]);
		}
		else if (abs(enemyX - playerX) > 100)
		{
			iShowImage(drawX, enemyY,
				level2EnemyDrawWidth, level2EnemyDrawHeight,
				level2Enemy1RunImage[enemyRunFrame]);
		}
		else
		{
			iShowImage(drawX, enemyY,
				level2EnemyDrawWidth, level2EnemyDrawHeight,
				level2Enemy1Image);
		}
	}
}


// ============================================================
// LEVEL 3 ENEMY DRAW
// ============================================================

void drawEnemyLevel3()
{
	if (!enemyAlive)
	{
		return;
	}


	int drawX =
		enemyX - level3CameraX;


	// ========================================================
	// FIRST ENEMY TYPE
	// ========================================================

	if (level3EnemyType == 0)
	{
		if (enemyAttacking)
		{
			iShowImage(
				drawX,
				enemyY,
				enemyWidth,
				enemyHeight,
				level3Enemy1AttackImage[
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
				level3Enemy1RunImage[
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
				level3Enemy1Image
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
				level3Enemy2AttackImage[
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
				level3Enemy2RunImage[
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
				level3Enemy2Image
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
	// PLAY ENEMY HIT SOUND
	mciSendString(
		"play enemyhitsound from 0",
		NULL,
		0,
		NULL
		);

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
	if (!isAttacking || attackHit || !enemyAlive)
	{
		return;
	}

	int distance = abs(
		(enemyX + level2EnemyDrawWidth / 2) -
		(playerX + level2PlayerDrawWidth / 2)
		);

	if (distance >= 165)
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
		level2EnemiesDefeated = level2TotalEnemies;
		level2Stage = 2;
		level2CameraX = 0;
		playerX = 100;
		playerY = 235;
		playerMoving = false;
		isAttacking = false;
		attackHit = false;
		attackTimer = 0;
		faceRight = true;
		isJumping = false;
		velocityY = 0;
		return;
	}

	if (level2EnemiesDefeated >= level2FirstEnemyCount)
	{
		level2Stage = 1;
		level2EnemyType = 1;
	}
	else
	{
		level2EnemyType = 0;
	}

	level2CurrentWave++;
	enemyHealth = 100;
	enemyAlive = true;
	enemyAttacking = false;
	enemyRunFrame = 0;
	enemyAttackFrame = 0;
	enemyX = playerX + 300;
	if (enemyX < 1250) enemyX = 1250;
	enemyY = 235;

}


// ============================================================
// LEVEL 3 PLAYER ATTACK
// ============================================================

void updateLevel3PlayerAttack()
{
	// Only fight during stage 1 and stage 3.

	if (
		level3Stage != 1 &&
		level3Stage != 3
		)
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


	level3EnemiesDefeated++;

	score += scorePerEnemy;


	// ========================================================
	// FIRST 5 ENEMIES COMPLETE
	// GO TO BACKGROUND 3
	// ========================================================

	if (
		level3Stage == 1 &&
		level3EnemiesDefeated >= 5
		)
	{
		level3EnemiesDefeated = 5;

		level3Stage = 2;

		level3EnemyType = 1;

		level3CameraX = 0;

		playerX = 100;

		playerY = level3PlatformY;

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


	// ========================================================
	// SECOND 5 ENEMIES COMPLETE
	// GO TO BACKGROUND 5 + JADE
	// ========================================================

	if (
		level3Stage == 3 &&
		level3EnemiesDefeated >= level3TotalEnemies
		)
	{
		level3EnemiesDefeated =
			level3TotalEnemies;

		level3Stage = 4;

		level3CameraX = 0;

		playerX = 100;

		playerY = level3PlatformY;

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


	// ========================================================
	// NEXT LEVEL 3 ENEMY
	// ========================================================

	if (level3EnemyType == 0)
	{
		spawnLevel3Enemy1();
	}
	else
	{
		spawnLevel3Enemy2();
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
			// STOP BACKGROUND MUSIC
			mciSendString(
				"stop bgsong",
				NULL,
				0,
				NULL
				);


			// PLAY VICTORY SOUND
			mciSendString(
				"play victorysound from 0",
				NULL,
				0,
				NULL
				);
			// LEVEL 1 COMPLETE -> LEVEL SELECT
			gameState = 6;

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

	// --------------------------------------------------------
	// MOVEMENT
	// --------------------------------------------------------
	int oldX = playerX;
	int oldY = playerY;

	if (isKeyPressed('d') || isKeyPressed('D'))
	{
		if (!isAttacking)
		{
			playerX += playerSpeed;
			playerMoving = true;
			faceRight = true;
		}
	}

	if (isKeyPressed('a') || isKeyPressed('A'))
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

	if (playerX > level2RealWorldWidth - level2PlayerDrawWidth)
	{
		playerX = level2RealWorldWidth - level2PlayerDrawWidth;
	}

	// --------------------------------------------------------
	// JUMP
	// --------------------------------------------------------
	if (!isJumping && (isKeyPressed('w') || isKeyPressed('W')))
	{
		isJumping = true;
		velocityY = jumpPower;
	}

	if (isJumping)
	{
		playerY += velocityY;
		velocityY -= gravity;

		// Landing: only land while falling.
		if (velocityY <= 0)
		{
			int previousFeet = oldY;
			int currentFeet = playerY;

			for (int i = 0; i < level2PlatformCount; i++)
			{
				Level2Platform p = level2Platforms[i];

				bool horizontalHit =
					playerX + level2PlayerDrawWidth > p.x &&
					playerX < p.x + p.width;

				bool crossedTop =
					previousFeet >= p.y &&
					currentFeet <= p.y;

				if (horizontalHit && crossedTop)
				{
					playerY = p.y;
					velocityY = 0;
					isJumping = false;
					break;
				}
			}
		}
	}
	else
	{
		// If the player walks off a platform, gravity starts.
		int platformY = getLevel2PlatformY(playerX, playerY);

		if (platformY >= 0 && abs(platformY - playerY) <= 3)
		{
			playerY = platformY;
		}
		else
		{
			isJumping = true;
			velocityY = 0;
		}
	}

	// --------------------------------------------------------
	// SPIKE DAMAGE
	// --------------------------------------------------------
	if (level2SpikeDamageCooldown > 0)
	{
		level2SpikeDamageCooldown--;
	}

	int playerCenter = playerX + level2PlayerDrawWidth / 2;

	bool touchingFirstSpike =
		playerCenter >= level2FirstSpikeX &&
		playerCenter <= level2FirstSpikeX + level2FirstSpikeWidth &&
		playerY <= 235;

	if (touchingFirstSpike && level2SpikeDamageCooldown == 0)
	{
		playerHealth--;
		level2SpikeDamageCooldown = 45;

		if (playerHealth <= 0)
		{
			playerHealth = 0;
			gameState = 3;
			return;
		}
	}

	// First enemy becomes available only after crossing the spike.
	if (!level2FirstSpikeCrossed &&
		playerX > level2FirstSpikeX + level2FirstSpikeWidth)
	{
		level2FirstSpikeCrossed = true;

		if (!enemyAlive && level2EnemiesDefeated < level2TotalEnemies)
		{
			enemyX = level2FirstEnemySpawnX;
			enemyY = 235;
			enemyHealth = 100;
			enemyAlive = true;
			enemyAttacking = false;
			enemyRunFrame = 0;
			enemyAttackFrame = 0;
		}
	}

	// --------------------------------------------------------
	// ENEMY / PROGRESSION
	// --------------------------------------------------------
	if (enemyAlive)
	{
		// Enemy stays on the main ground in this first Level 2 section.
		enemyY = 235;

		updateEnemyMovement();
		level2ClampAgainstEnemy();
	}

	if (attackTimer > 0)
	{
		attackTimer--;
	}

	updateLevel2PlayerAttack();

	if (gameState != 5)
	{
		return;
	}

	// --------------------------------------------------------
	// COINS
	// --------------------------------------------------------
	level2CheckCoins();

	// --------------------------------------------------------
	// CAMERA - REAL 4000px BACKGROUND
	// --------------------------------------------------------
	if (playerX > cameraFollowX)
	{
		level2CameraX = playerX - cameraFollowX;
	}
	else
	{
		level2CameraX = 0;
	}

	int maxCamera = level2RealWorldWidth - level2ViewportWidth;

	if (level2CameraX < 0)
	{
		level2CameraX = 0;
	}

	if (level2CameraX > maxCamera)
	{
		level2CameraX = maxCamera;
	}
}


// ============================================================
// LEVEL 3 UPDATE
// ============================================================

void fixedUpdateLevel3()
{
	if (gameState != 7)
	{
		return;
	}


	playerMoving = false;


	// ========================================================
	// STAGE 0
	// BACKGROUND 1 + FIRST GATE
	// ========================================================

	if (level3Stage == 0)
	{
		level3CameraX = 0;

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


		playerY = level3PlatformY;


		int playerCenter =
			playerX +
			(playerWidth / 2);


		int gateDistance =
			abs(
			playerCenter -
			level3Gate1X
			);


		if (gateDistance <= 80)
		{
			// Start first enemy area.

			level3Stage = 1;

			level3EnemyType = 0;

			level3CameraX = 0;

			playerX = 100;

			playerY = level3PlatformY;

			playerMoving = false;

			isAttacking = false;

			attackHit = false;

			attackTimer = 0;

			faceRight = true;

			isJumping = false;

			velocityY = 0;

			spawnLevel3Enemy1();
		}


		return;
	}


	// ========================================================
	// STAGE 1
	// BACKGROUND 2 + FIRST 5 ENEMIES
	// ========================================================

	if (level3Stage == 1)
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
			level3WorldWidth -
			playerWidth
			)
		{
			playerX =
				level3WorldWidth -
				playerWidth;
		}


		playerY = level3PlatformY;


		if (attackTimer > 0)
		{
			attackTimer--;
		}


		updateLevel3PlayerAttack();


		if (gameState != 7)
		{
			return;
		}


		if (enemyAlive)
		{
			enemyY = level3PlatformY;
		}


		updateEnemyMovement();


		// ====================================================
		// CAMERA
		// ====================================================

		if (playerX > level3CameraFollowX)
		{
			level3CameraX =
				playerX -
				level3CameraFollowX;
		}
		else
		{
			level3CameraX = 0;
		}


		if (level3CameraX < 0)
		{
			level3CameraX = 0;
		}


		if (
			level3CameraX >
			level3WorldWidth -
			level3ScreenWidth
			)
		{
			level3CameraX =
				level3WorldWidth -
				level3ScreenWidth;
		}


		return;
	}


	// ========================================================
	// STAGE 2
	// BACKGROUND 3 + SECOND GATE
	// ========================================================

	if (level3Stage == 2)
	{
		level3CameraX = 0;

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


		playerY = level3PlatformY;


		int playerCenter =
			playerX +
			(playerWidth / 2);


		int gateDistance =
			abs(
			playerCenter -
			level3Gate2X
			);


		if (gateDistance <= 80)
		{
			// Start second enemy area.

			level3Stage = 3;

			level3EnemyType = 1;

			level3CameraX = 0;

			playerX = 100;

			playerY = level3PlatformY;

			playerMoving = false;

			isAttacking = false;

			attackHit = false;

			attackTimer = 0;

			faceRight = true;

			isJumping = false;

			velocityY = 0;

			spawnLevel3Enemy2();
		}


		return;
	}


	// ========================================================
	// STAGE 3
	// BACKGROUND 4 + SECOND 5 ENEMIES
	// ========================================================

	if (level3Stage == 3)
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
			level3WorldWidth -
			playerWidth
			)
		{
			playerX =
				level3WorldWidth -
				playerWidth;
		}


		playerY = level3PlatformY;


		if (attackTimer > 0)
		{
			attackTimer--;
		}


		updateLevel3PlayerAttack();


		if (gameState != 7)
		{
			return;
		}


		if (enemyAlive)
		{
			enemyY = level3PlatformY;
		}


		updateEnemyMovement();


		// ====================================================
		// CAMERA
		// ====================================================

		if (playerX > level3CameraFollowX)
		{
			level3CameraX =
				playerX -
				level3CameraFollowX;
		}
		else
		{
			level3CameraX = 0;
		}


		if (level3CameraX < 0)
		{
			level3CameraX = 0;
		}


		if (
			level3CameraX >
			level3WorldWidth -
			level3ScreenWidth
			)
		{
			level3CameraX =
				level3WorldWidth -
				level3ScreenWidth;
		}


		return;
	}


	// ========================================================
	// STAGE 4
	// BACKGROUND 5 + JADE
	// ========================================================

	if (level3Stage == 4)
	{
		level3CameraX = 0;

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


		playerY = level3PlatformY;


		int playerCenter =
			playerX +
			(playerWidth / 2);


		int jadeDistance =
			abs(
			playerCenter -
			level3JadeX
			);


		if (jadeDistance <= 90)
		{
			// ==================================================
			// LEVEL 3 COMPLETE
			// ==================================================
			// STOP BACKGROUND MUSIC
			mciSendString(
				"stop bgsong",
				NULL,
				0,
				NULL
				);


			// PLAY VICTORY SOUND
			mciSendString(
				"play victorysound from 0",
				NULL,
				0,
				NULL
				);
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
	mciSendString("stop victorysound", NULL, 0, NULL);
	mciSendString("play bgsong repeat", NULL, 0, NULL);

	gameState = 5;

	playerX = 150;
	playerY = 235;
	playerHealth = playerMaxHealth;
	velocityY = 0;
	isJumping = false;
	playerMoving = false;
	faceRight = true;

	isAttacking = false;
	attackFrame = 0;
	attackHit = false;
	attackTimer = 0;

	level2CameraX = 0;
	level2EnemiesDefeated = 0;
	level2CurrentWave = 0;
	level2Stage = 0;
	level2EnemyType = 0;

	level2FirstSpikeCrossed = false;
	level2SpikeDamageCooldown = 0;

	for (int i = 0; i < level2CoinCount; i++)
	{
		level2CoinCollected[i] = false;
	}

	// IMPORTANT: no enemy at the start.
	// The first enemy appears only after the first spike is crossed.
	enemyAlive = false;
	enemyAttacking = false;
	enemyHealth = 100;
	enemyRunFrame = 0;
	enemyAttackFrame = 0;
}


// ============================================================
// START LEVEL 3
// ============================================================

void startLevel3()
{
	// STOP PREVIOUS VICTORY SOUND
	mciSendString(
		"stop victorysound",
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

	gameState = 7;


	// ========================================================
	// PLAYER RESET
	// ========================================================

	playerX = 100;

	playerY = level3PlatformY;


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


	// ========================================================
	// LEVEL 3 RESET
	// ========================================================

	level3CameraX = 0;

	level3Stage = 0;

	level3EnemyType = 0;

	level3EnemiesDefeated = 0;


	// Do NOT reset score here.
	// Score continues from Level 2.


	enemyAlive = false;

	enemyAttacking = false;

	enemyRunFrame = 0;

	enemyAttackFrame = 0;
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
	else if (gameState == 7)
	{
		fixedUpdateLevel3();
	}
}


// ============================================================
// DRAW LEVEL 2
// ============================================================

void drawLevel2()
{
	// ========================================================
	// LEVEL 2 BACKGROUND 1
	// Draw the real 4000 x 600 image at 1:1 size.
	// The camera crops the visible 1000 x 600 section.
	// ========================================================
	if (level2Stage == 0 || level2Stage == 1)
	{
		iShowImage(
			-level2CameraX,
			0,
			level2RealWorldWidth,
			level2ViewportHeight,
			level2BackgroundImage1
			);

		level2DrawCoins();
		drawPlayerLevel2();
		drawEnemyLevel2();
	}
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

	drawHealthUI();
	drawScoreUI();

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

	char typeText[50];

	if (level2Stage == 0)
	{
		sprintf_s(typeText, "JUMP OVER THE SPIKES");
	}
	else if (level2Stage == 1)
	{
		sprintf_s(typeText, "ENEMY TYPE: 2");
	}
	else
	{
		sprintf_s(typeText, "");
	}

	iText(
		430,
		515,
		typeText,
		GLUT_BITMAP_HELVETICA_18
		);

	iText(
		460,
		580,
		"LEVEL 2",
		GLUT_BITMAP_HELVETICA_18
		);
}


// ============================================================
// DRAW LEVEL 3
// ============================================================

void drawLevel3()
{
	// ========================================================
	// STAGE 0
	// BACKGROUND 1 + GATE
	// ========================================================

	if (level3Stage == 0)
	{
		level3CameraX = 0;


		iShowImage(
			0,
			0,
			screenWidth,
			screenHeight,
			level3BackgroundImage1
			);


		drawPlayerLevel3();
	}


	// ========================================================
	// STAGE 1
	// BACKGROUND 2 + FIRST ENEMY TYPE
	// ========================================================

	else if (level3Stage == 1)
	{
		int backgroundX =
			-(level3CameraX %
			level3ScreenWidth);


		iShowImage(
			backgroundX,
			0,
			level3ScreenWidth,
			screenHeight,
			level3BackgroundImage2
			);


		iShowImage(
			backgroundX +
			level3ScreenWidth,
			0,
			level3ScreenWidth,
			screenHeight,
			level3BackgroundImage2
			);


		drawPlayerLevel3();

		drawEnemyLevel3();
	}


	// ========================================================
	// STAGE 2
	// BACKGROUND 3 + SECOND GATE
	// ========================================================

	else if (level3Stage == 2)
	{
		level3CameraX = 0;


		iShowImage(
			0,
			0,
			screenWidth,
			screenHeight,
			level3BackgroundImage3
			);


		drawPlayerLevel3();
	}


	// ========================================================
	// STAGE 3
	// BACKGROUND 4 + SECOND ENEMY TYPE
	// ========================================================

	else if (level3Stage == 3)
	{
		int backgroundX =
			-(level3CameraX %
			level3ScreenWidth);


		iShowImage(
			backgroundX,
			0,
			level3ScreenWidth,
			screenHeight,
			level3BackgroundImage4
			);


		iShowImage(
			backgroundX +
			level3ScreenWidth,
			0,
			level3ScreenWidth,
			screenHeight,
			level3BackgroundImage4
			);


		drawPlayerLevel3();

		drawEnemyLevel3();
	}


	// ========================================================
	// STAGE 4
	// BACKGROUND 5 + JADE
	// ========================================================

	else if (level3Stage == 4)
	{
		level3CameraX = 0;


		iShowImage(
			0,
			0,
			screenWidth,
			screenHeight,
			level3BackgroundImage5
			);


		drawPlayerLevel3();
	}


	// ========================================================
	// HUD
	// ========================================================

	drawHealthUI();

	drawScoreUI();


	// ========================================================
	// ENEMY COUNT
	// ========================================================

	char enemyText[50];


	sprintf_s(
		enemyText,
		"Enemy: %d / %d",
		level3EnemiesDefeated,
		level3TotalEnemies
		);


	iSetColor(
		255,
		255,
		255
		);


	iText(
		370,
		555,
		enemyText,
		GLUT_BITMAP_HELVETICA_18
		);


	// ========================================================
	// STAGE MESSAGE
	// ========================================================

	if (level3Stage == 0)
	{
		iText(
			430,
			515,
			"GO TO THE GATE",
			GLUT_BITMAP_HELVETICA_18
			);
	}
	else if (level3Stage == 1)
	{
		iText(
			450,
			515,
			"FIGHT!",
			GLUT_BITMAP_HELVETICA_18
			);
	}
	else if (level3Stage == 2)
	{
		iText(
			395,
			515,
			"GO TO THE NEXT GATE",
			GLUT_BITMAP_HELVETICA_18
			);
	}
	else if (level3Stage == 3)
	{
		iText(
			450,
			515,
			"FIGHT!",
			GLUT_BITMAP_HELVETICA_18
			);
	}
	else if (level3Stage == 4)
	{
		iText(
			430,
			515,
			"GET THE JADE",
			GLUT_BITMAP_HELVETICA_18
			);
	}


	// ========================================================
	// LEVEL NAME
	// ========================================================

	iText(
		460,
		580,
		"LEVEL 3",
		GLUT_BITMAP_HELVETICA_18
		);
}


#endif