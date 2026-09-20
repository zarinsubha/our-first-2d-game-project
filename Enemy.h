#ifndef ENEMY_H
#define ENEMY_H

extern int gameState;


// ============================================================
// LEVEL 2 ENEMY PLATFORM
// ============================================================
// IMPORTANT:
// Enemy.h is included before Environment.h.
// So we do NOT use level2PlatformY here.
// ============================================================

const int level2EnemyPlatformY = 105;


// ============================================================
// LEVEL 1 ENEMY IMAGES
// ============================================================

int enemyImage;

int enemyRunImage[3];

int enemyAttackImage[2];


// ============================================================
// LEVEL 2 - FIRST ENEMY TYPE
// ============================================================

int level2EnemyImage;

int level2EnemyRunImage[3];

int level2EnemyAttackImage[3];


// ============================================================
// LEVEL 2 - SECOND ENEMY TYPE
// ============================================================

int level2Enemy1Image;

int level2Enemy1RunImage[3];

int level2Enemy1AttackImage[3];


// ============================================================
// ENEMY VARIABLES
// ============================================================

int enemyX = 1100;

int enemyY = groundY;

int enemyWidth = 158;

int enemyHeight = 150;

int enemySpeed = 2;

int enemyHealth = 100;

bool enemyAlive = true;


// ============================================================
// ENEMY ATTACK
// ============================================================

bool enemyAttacking = false;

int enemyAttackDamage = 1;


// ============================================================
// ENEMY ANIMATION
// ============================================================

int enemyRunFrame = 0;

int enemyAttackFrame = 0;


// ============================================================
// LEVEL 1 ENEMY SYSTEM
// ============================================================

const int totalEnemies = 10;

int enemiesDefeated = 0;

int currentEnemy = 1;


// ============================================================
// LEVEL 2 ENEMY SYSTEM
// ============================================================

// 0 = First enemy type
// 1 = Second enemy type

int level2EnemyType = 0;

const int level2FirstEnemyCount = 5;

const int level2TotalEnemies = 10;

int level2EnemiesDefeated = 0;


// ============================================================
// LEVEL 1 SPAWN
// ============================================================

void spawnEnemy()
{
	enemyHealth = 100;

	enemyAlive = true;

	enemyAttacking = false;

	enemyRunFrame = 0;

	enemyAttackFrame = 0;

	enemyX = 1100;

	enemyY = groundY;
}


// ============================================================
// LEVEL 1 NEXT WAVE
// ============================================================

void spawnNextWave()
{
	currentEnemy++;

	spawnEnemy();
}


// ============================================================
// LEVEL 2 FIRST ENEMY TYPE
// ============================================================

void spawnLevel2Enemy()
{
	enemyHealth = 100;

	enemyAlive = true;

	enemyAttacking = false;

	enemyRunFrame = 0;

	enemyAttackFrame = 0;

	enemyX = playerX + 450;

	enemyY = level2EnemyPlatformY;
}


// ============================================================
// LEVEL 2 SECOND ENEMY TYPE
// ============================================================

void spawnLevel2Enemy1()
{
	enemyHealth = 100;

	enemyAlive = true;

	enemyAttacking = false;

	enemyRunFrame = 0;

	enemyAttackFrame = 0;

	enemyX = playerX + 450;

	enemyY = level2EnemyPlatformY;
}


// ============================================================
// ENEMY RUN ANIMATION
// ============================================================

void updateEnemyAnimation()
{
	if (
		gameState != 2 &&
		gameState != 5
		)
	{
		enemyRunFrame = 0;

		return;
	}


	if (
		enemyAlive &&
		!enemyAttacking &&
		abs(enemyX - playerX) > 100
		)
	{
		enemyRunFrame++;

		if (enemyRunFrame >= 3)
		{
			enemyRunFrame = 0;
		}
	}
	else
	{
		enemyRunFrame = 0;
	}
}


// ============================================================
// ENEMY ATTACK ANIMATION
// ============================================================

void updateEnemyAttackAnimation()
{
	if (
		gameState != 2 &&
		gameState != 5
		)
	{
		enemyAttackFrame = 0;

		return;
	}


	if (
		enemyAlive &&
		enemyAttacking
		)
	{
		enemyAttackFrame++;

		if (enemyAttackFrame >= 3)
		{
			enemyAttackFrame = 0;
		}
	}
	else
	{
		enemyAttackFrame = 0;
	}
}


// ============================================================
// ENEMY ATTACK UPDATE
// ============================================================

void enemyAttackUpdate()
{
	if (
		gameState != 2 &&
		gameState != 5
		)
	{
		return;
	}


	if (
		enemyAlive &&
		enemyAttacking
		)
	{
		playerHealth -= enemyAttackDamage;
	}


	if (playerHealth <= 0)
	{
		playerHealth = 0;

		enemyAttacking = false;

		gameState = 3;

		mciSendString(
			"play ggsong from 0",
			NULL,
			0,
			NULL
			);
	}
}

#endif