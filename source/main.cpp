#include "AIE.h"
#include <iostream>
#include <fstream>
#include <vector>
#include "main.h"
#include "Bullets.h"
#include "Enemies.h"
#include "Player.h"
#include "Time.h"

using namespace std;

void CollisionCheck();
void AddingBullet(float a_deltaTime);
void MoveBullets(float a_deltaTime);
void BulletCollideEnemy();
void AddEnemies(float a_deltaTime);
void MoveEnemies(float a_deltaTime);
void PlayerAnimation();
void WriteHighScores();
void LoadHighScores();
void GameUI();

//GLobal Variables
unsigned int screenHeight = 800;
unsigned int screenWidth = 600;
float reloadTime, currentReloadTime;
float spawnTime, currentSpawnTime;
float myHighScore;


enum PLAYERANIMATION{
	ONE,
	TWO,
	THREE,
	FOUR
};

enum GAMESTATES{
	MAINMENU,
	HOWTOPLAY,
	HIGHSCORE,
	QUIT,
	GAMESTATE
};
GAMESTATES gamestates;

PLAYERANIMATION playerAnim;
Player player;

std::vector<Enemies> enemyPlane;

std::vector<Bullets> bullet;

//"animation" for player
void PlayerAnimation(){
	switch (playerAnim){
	case ONE:
		MoveSprite(player.playerPlane1, player.x, player.y);
		DrawSprite(player.playerPlane1);
		playerAnim = TWO;
		break;
	case TWO:
		MoveSprite(player.playerPlane2, player.x, player.y);
		DrawSprite(player.playerPlane2);
		playerAnim = THREE;
		break;
	case THREE:
		MoveSprite(player.playerPlane3, player.x, player.y);
		DrawSprite(player.playerPlane3);
		playerAnim = FOUR;
		break;
	case FOUR:
		MoveSprite(player.playerPlane4, player.x, player.y);
		DrawSprite(player.playerPlane4);
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
	
	player.Init();
	
	//Timers
	srand(time(NULL));
	reloadTime = .15f;
	currentReloadTime = reloadTime;
	
	spawnTime = .5f;
	currentSpawnTime = spawnTime;

	//player Animation
	playerAnim = ONE;
	gamestates = MAINMENU;

	switch (gamestates){
		
	}
    //Game Loop
    do
    {
		ClearScreen();
		float DeltaT = GetDeltaTime();
		//Game UI
		GameUI();

		//Bullet functions in loop
		AddingBullet(DeltaT);
		MoveBullets(DeltaT);
		BulletCollideEnemy();
		
		
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


   void AddingBullet(float a_deltaTime){
	if (IsKeyDown(32)){
		if (currentReloadTime <= 0.f){
			//left bullet
			bullet.emplace_back();
			bullet.back().spriteID = CreateSprite("./images/bullets.png", bullet.back().width, bullet.back().height, true);
			bullet.back().x = player.x - 12.f;
			bullet.back().y = player.y + 10.f;

			//right bullet
			bullet.emplace_back();
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
		bullet[i].y += 4.5f + a_deltaTime;
		MoveSprite(bullet[i].spriteID, bullet[i].x, bullet[i].y);
        DrawSprite(bullet[i].spriteID);
		}
}

void AddEnemies(float a_deltaTime){ 
	if (currentSpawnTime <= 0.f){
		enemyPlane.emplace_back();
		enemyPlane.back().x += rand() % 550;

		
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

void CollisionCheck(){
	for (int i = 0; i < enemyPlane.size(); i++){
		if (enemyPlane[i].Collide() == true){
			DrawString("you dead...", 200, 200);
		}
	}
}

void BulletCollideEnemy(){
	for (int i = 0; i < enemyPlane.size(); i++){
		for (int j = 0; j < bullet.size(); j++){
			if (bullet[j].x >= enemyPlane[i].x - enemyPlane[i].width * .5f &&
				bullet[j].x <= enemyPlane[i].x + enemyPlane[i].width * .5f &&
				bullet[j].y >= enemyPlane[i].y - enemyPlane[i].height * .5f &&
				bullet[j].y <= enemyPlane[i].y + enemyPlane[i].height * .5f){
					bullet[j].x += 500.f;
					enemyPlane[i].x += 500.f;
					player.AddScore(50);
					
			}
		}
	}
}

void WriteHighScores(){
	fstream Highscores;
	Highscores.open("Highscores.txt", ios::out);
	Highscores << myHighScore;
	Highscores.close();
}

void LoadHighScores(){
	fstream Highscores;
	Highscores.open("Highscores.txt", ios::in);
	char buffer[10];
	Highscores.getline(buffer, 10);
	myHighScore = atoi(buffer);
	Highscores.close();
}

void GameUI(){
	char playerScore[10];
	char buff[30];
	player.GetScore(playerScore);

	DrawString("HIGHSCORE:", screenWidth * .05f, 775);
	DrawString(itoa(myHighScore, buff, 10), screenWidth * .4f, 775);
	DrawString("YOUR SCORE:", screenWidth * .05f, 750);
	DrawString(playerScore, screenWidth * .4f, 750);

}