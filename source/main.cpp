#include "AIE.h"
#include <iostream>
#include <vector>
#include "Bullets.h"
#include "Enemies.h"
#include "Player.h"
#include "Time.h"

void CollisionCheck();
void AddingBullet(float a_deltaTime);
void MoveBullets(float a_deltaTime);
void AddEnemies(float a_deltaTime);
void MoveEnemies(float a_deltaTime);
void PlayerAnimation();

//GLobal Variables
unsigned int screenHeight;
unsigned int screenWidth;
float reloadTime, currentReloadTime;
float spawnTime, currentSpawnTime;


enum PLAYERANIMATION{
	ONE,
	TWO,
	THREE,
	FOUR,
};

PLAYERANIMATION playerAnim;
Player player;

std::vector<Enemies> enemyPlane;

std::vector<Bullets> bullet;

//"animation" for player
void PlayerAnimation(){
	switch (playerAnim){
	case ONE:
		MoveSprite(Player::Player().playerPlane1, Player::Player().x, Player::Player().y);
		DrawSprite(Player::Player().playerPlane1);
		playerAnim = TWO;
		break;
	case TWO:
		MoveSprite(Player::Player().playerPlane2, Player::Player().x, Player::Player().y);
		DrawSprite(Player::Player().playerPlane2);
		playerAnim = THREE;
		break;
	case THREE:
		MoveSprite(Player::Player().playerPlane3, Player::Player().x, Player::Player().y);
		DrawSprite(Player::Player().playerPlane3);
		playerAnim = FOUR;
		break;
	case FOUR:
		MoveSprite(Player::Player().playerPlane4, Player::Player().x, Player::Player().y);
		DrawSprite(Player::Player().playerPlane4);
		playerAnim = ONE;
		break;
	default:
		break;
	}
}

int main( int argc, char* argv[] )
{	
    Initialise(screenWidth, screenHeight, false, "My Awesome Game");
	
    SetBackgroundColour(SColour(0, 100, 200, 50));
	
	//global Variables Initialziation
	screenWidth = 600;
	screenHeight = 800;
	
	//Timers
	srand(time(NULL));
	reloadTime = .15f;
	currentReloadTime = reloadTime;
	
	spawnTime = 1.0f;
	currentSpawnTime = spawnTime;

	//player Animation
	playerAnim = ONE;
	
    //Game Loop
    do
    {
		ClearScreen();
		float DeltaT = GetDeltaTime();

		//Bullet functions in loop
		AddingBullet(DeltaT);
		MoveBullets(DeltaT);
		
		//player functions in game loop
		player.MovementKeys(DeltaT);
		PlayerAnimation();

		//enemy functions in game loop
		AddEnemies(DeltaT);
		MoveEnemies(DeltaT);
		CollisionCheck();


    } while(!FrameworkUpdate());

    Shutdown();
    return 0;
}


void CollisionCheck(){
	for (int i = 0; i < enemyPlane.size(); i++){
		if (enemyPlane[i].Collide() == true){
			DrawString("you dead...", 200, 200);
		}
	}
}

void AddingBullet(float a_deltaTime){
	if (IsKeyDown(32)){
		if (currentReloadTime <= 0.f){
			//left bullet
			bullet.emplace_back(Bullets());
			bullet.back().spriteID = CreateSprite("./images/bullets.png", bullet.back().width, bullet.back().height, true);
			bullet.back().x = player.x - 12.f;
			bullet.back().y = player.y + 10.f;

			//right bullet
			bullet.emplace_back(Bullets());
			bullet.back().spriteID = CreateSprite("./images/bullets.png", bullet.back().width, bullet.back().height, true);
			bullet.back().x = player.x + 12.f;
			bullet.back().y = player.y + 10.f;
			
			currentReloadTime = reloadTime;
		}
		else {
			currentReloadTime -= a_deltaTime;
		}
	}
}
    
void MoveBullets(float a_deltaTime){
	
	for (int i = 0; i < bullet.size(); i++){
		bullet[i].y += 2.45f + a_deltaTime;
		MoveSprite(bullet[i].spriteID, bullet[i].x, bullet[i].y);
		DrawSprite(bullet[i].spriteID);
	}
}

void AddEnemies(float a_deltaTime){ 
	if (currentSpawnTime <= 0.f){

		enemyPlane.emplace_back();
		enemyPlane.back().x += rand()%575;
		
		currentSpawnTime = spawnTime;
	}
	else {
		currentSpawnTime -= a_deltaTime;
	}
}

void MoveEnemies(float a_deltaTime){
	for (int i = 0; i < enemyPlane.size(); i++){
		enemyPlane[i].Movement(a_deltaTime);
	}
}