#include "Player.h"
#include "AIE.h"


Player::Player()
{
	x = 300;
	y = 200;
	width = 50;
	height = 50;
}

void Player::Init()
{
	//Player Sprites
	playerPlane1 = CreateSprite("./images/PlayerPlane.png", width, height, true);
	playerPlane2 = CreateSprite("./images/PlayerPlane2.png", width, height, true);
	playerPlane3 = CreateSprite("./images/PlayerPlane3.png", width, height, true);
	playerPlane4 = CreateSprite("./images/PlayerPlane4.png", width, height, true);
}

Player::~Player()
{
	DestroySprite(playerPlane1);
	DestroySprite(playerPlane2);
	DestroySprite(playerPlane3);
	DestroySprite(playerPlane4);
}

int Player::score = 0;

void Player::AddScore(int a_score)
{
	Player::score += a_score;
}

void Player::GetScore(char* a_result)
{
	itoa(Player::score, a_result, 10);
}


void Player::MovementKeys(float a_deltaTime){
	//player controls
	if (IsKeyDown(87))
	{
		y += 150.f * a_deltaTime;
	}
	if (IsKeyDown(83))
	{
		y -= 150.f * a_deltaTime;
	}
	if (IsKeyDown(68))
	{
		x += 200.f * a_deltaTime;
	}
	if (IsKeyDown(65))
	{
		x -= 200.f * a_deltaTime;
	}
}