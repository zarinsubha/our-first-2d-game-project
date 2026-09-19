#ifndef ENEMY_H
#define ENEMY_H

extern int gameState;


// ============================================================
// ENEMY IMAGES
// SAME ENEMY FOR LEVEL 1 AND LEVEL 2
// ============================================================

int enemyImage;

int enemyRunImage[3];

int enemyAttackImage[2];


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
// SPAWN ENEMY
// SAME ENEMY USED FOR BOTH LEVELS
// ============================================================

void spawnEnemy()
{
	enemyHealth = 100;

	enemyAlive = true;

	enemyAttacking = false;

	enemyRunFrame = 0;

	enemyAttackFrame = 0;


	// Spawn from right side

	enemyX = 1100;

	enemyY = groundY;
}


// ============================================================
// SPAWN NEXT LEVEL 1 WAVE
// ============================================================

void spawnNextWave()
{
	currentEnemy++;

	spawnEnemy();
}


// ============================================================
// ENEMY RUN ANIMATION
// ============================================================

void updateEnemyAnimation()
{
	if (gameState != 2 && gameState != 5)
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
	if (gameState != 2 && gameState != 5)
	{
		enemyAttackFrame = 0;
		return;
	}

	if (enemyAlive && enemyAttacking)
	{
		enemyAttackFrame++;

		if (enemyAttackFrame >= 2)
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
// ENEMY DAMAGES PLAYER
// TIMER = 1 SECOND
// ============================================================

void enemyAttackUpdate()
{
	if (gameState != 2 && gameState != 5)
	{
		return;
	}

	if (enemyAlive && enemyAttacking)
	{
		playerHealth -= enemyAttackDamage;
	}


	// ========================================================
	// PLAYER DEAD
	// ========================================================

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