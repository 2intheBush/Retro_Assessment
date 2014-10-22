#include "Player.h"
#include "AIE.h"

Player::Player(){

	Player::x = 300;
	Player::y = 200;
	Player::width = 50;
	Player::height = 50;
	
	

}

void Player::Init()
{
//Player Sprites
	Player::playerPlane1 = CreateSprite("./images/PlayerPlane.png", width, height, true);
	Player::playerPlane2 = CreateSprite("./images/PlayerPlane2.png", width, height, true);
	Player::playerPlane3 = CreateSprite("./images/PlayerPlane3.png", width, height, true);
	Player::playerPlane4 = CreateSprite("./images/PlayerPlane4.png", width, height, true);
}

Player::~Player(){
	/*DestroySprite(Player::playerPlane1);
	DestroySprite(Player::playerPlane2); 
	DestroySprite(Player::playerPlane3);
	DestroySprite(Player::playerPlane4);*/
}




void Player::MovementKeys(float a_deltaTime){
	//player controls
	if (IsKeyDown(87)){
		y += 150.f * a_deltaTime;
	}
	if (IsKeyDown(83)){
		y -= 150.f * a_deltaTime;
	}
	if (IsKeyDown(68)){
		x += 200.f * a_deltaTime;
	}
	if (IsKeyDown(65)){
		x -= 200.f * a_deltaTime;
	}
}


