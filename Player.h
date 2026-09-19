#ifndef PLAYER_H
#define PLAYER_H

extern int gameState;

// ============================================================
// PLAYER VARIABLES
// ============================================================

int playerX = 150;
int playerY = 180;

int playerWidth = 158;
int playerHeight = 150;

int playerSpeed = 8;

bool faceRight = true;


// ============================================================
// PLAYER IMAGES
// ============================================================

int playerImage;

int runImage[3];

int runFrame = 0;

bool playerMoving = false;


// ============================================================
// PLAYER ATTACK
// ============================================================

int attackImage[4];

int attackFrame = 0;

bool isAttacking = false;

int attackTimer = 0;

int attackDamage = 20;

bool attackHit = false;


// ============================================================
// PLAYER HEALTH
// ============================================================

int playerHealth = 20;

int playerMaxHealth = 20;


// ============================================================
// JUMP
// ============================================================

int velocityY = 0;

bool isJumping = false;

const int gravity = 1;

const int jumpPower = 18;

const int groundY = 130;


// ============================================================
// PLAYER RUN ANIMATION
// WORKS IN LEVEL 1 AND LEVEL 2
// ============================================================

void updatePlayerAnimation()
{
	if (gameState != 2 && gameState != 5)
	{
		runFrame = 0;
		return;
	}

	// Do not run while attacking

	if (isAttacking)
	{
		runFrame = 0;
		return;
	}

	if (playerMoving && !isJumping)
	{
		runFrame++;

		if (runFrame >= 3)
		{
			runFrame = 0;
		}
	}
	else
	{
		runFrame = 0;
	}
}


// ============================================================
// PLAYER ATTACK ANIMATION
// WORKS IN LEVEL 1 AND LEVEL 2
// ============================================================

void updateAttackAnimation()
{
	if (gameState != 2 && gameState != 5)
	{
		attackFrame = 0;
		isAttacking = false;
		attackHit = false;

		return;
	}

	if (isAttacking)
	{
		attackFrame++;

		if (attackFrame >= 4)
		{
			attackFrame = 0;

			isAttacking = false;

			attackHit = false;
		}
	}
	else
	{
		attackFrame = 0;
	}
}

#endif