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
bool endGame;

enum PLAYERANIMATION{
	ONE,
	TWO,
	THREE,
	FOUR
};

enum GAMESTATES{
	SPLASHSCREEN,
	MAIN_START_GAME,
	MAIN_HIGHSCORES,
	MAIN_QUIT,
	HIGHSCOREPAGE,
	HOWTOPLAY,
	HIGHSCORE,
	QUIT,
	GAMESTATE,
	PRE_GAME_MENU
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
	
	//Menu Sprites
	unsigned int mainStartGame = CreateSprite("./images/Menu_Start_Game.png", screenWidth, screenHeight, true);
	unsigned int mainHighScores = CreateSprite("./images/Menu_High_Score.png", screenWidth, screenHeight, true);
	unsigned int mainQuit = CreateSprite("./images/Menu_Quit.png", screenWidth, screenHeight, true);
	unsigned int splashScreen = CreateSprite("./images/Splash Screen.png", screenWidth, screenHeight, true);

	//player Animation
	playerAnim = ONE;
	gamestates = SPLASHSCREEN;
	endGame = false;

    //Game Loop
    do
    {
		ClearScreen();
		float DeltaT = GetDeltaTime(); 
		
		switch (gamestates){
		case SPLASHSCREEN:
			MoveSprite(splashScreen, screenWidth *.5f, screenHeight * .5f);
			DrawSprite(splashScreen);
			if (IsKeyDown(32)){
				gamestates = MAIN_START_GAME;
			}
			break;
		case MAIN_START_GAME:
			MoveSprite(mainStartGame, screenWidth *.5f, screenHeight * .5f);
			DrawSprite(mainStartGame);
			
			if (IsKeyDown(257)){
				gamestates = PRE_GAME_MENU;
			}
			//moving arrow across menu
			if (IsKeyDown(265)){
				gamestates = MAIN_QUIT;
			}
			if (IsKeyDown(264)){
				gamestates = MAIN_HIGHSCORES;
			}
			break;
		
		case MAIN_HIGHSCORES:
			MoveSprite(mainHighScores, screenWidth *.5f, screenHeight * .5f);
			DrawSprite(mainHighScores);
			if (IsKeyDown(257)){
				gamestates = HIGHSCOREPAGE;
			}
			//moving arrow across menu
			if (IsKeyDown(265)){
				gamestates = MAIN_START_GAME;
			}
			if (IsKeyDown(264)){
				gamestates = MAIN_QUIT;
			}
			break;

		case MAIN_QUIT:
			MoveSprite(mainQuit, screenWidth *.5f, screenHeight * .5f);
			DrawSprite(mainQuit);
			if (IsKeyDown(257)){
				endGame = true;
			}
			
			//moving arrow across menu
			if (IsKeyDown(265)){
				gamestates = MAIN_HIGHSCORES;
			}
			if (IsKeyDown(264)){
				gamestates = MAIN_START_GAME;
			}
			break;
		case HIGHSCOREPAGE:
			LoadHighScores();
			DrawString("HIGHSCORE: ", screenWidth * .45f, 400);
			char buff[30];
			DrawString(itoa(myHighScore, buff, 10), screenWidth * .4f, 775);
			if (IsKeyDown(81)){
				gamestates = MAIN_START_GAME;
			}
			break;
		case PRE_GAME_MENU:
			DrawString("W,A,S,D are to move", 150, 600);
			DrawString("SpaceBar is to shoot", 150, 550);
			DrawString("SpaceBar to Continue", 150, 500);

			if (IsKeyDown(32)){
				gamestates = GAMESTATE;
			}
			break;
		case GAMESTATE:
			if (IsKeyDown(81)){
				gamestates = MAIN_QUIT;
			}
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
			break;
		}
    } while(!FrameworkUpdate() && !endGame);

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
			gamestates = MAIN_START_GAME;
			WriteHighScores();
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
	player.GetScore(playerScore);
	if (player.score >= myHighScore){
		myHighScore = player.score;
	}
	char buff[30];
	DrawString("HIGHSCORE:", screenWidth * .05f, 775);
	DrawString(itoa(myHighScore, buff, 10), screenWidth * .4f, 775);
	DrawString("YOUR SCORE:", screenWidth * .05f, 750);
	DrawString(playerScore, screenWidth * .4f, 750);

}