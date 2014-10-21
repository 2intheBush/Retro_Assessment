#ifndef _PLAYER_H_
#define PLAYER_H_

#include "AIE.h"

class Player{
public:
	int playerPlane1;
	int playerPlane2;
	int playerPlane3;
	int playerPlane4;

	Player();
	~Player();

	float x;
	float y;
	float width;
	float height;

	void MovementKeys(float a_deltaTime);

	void PlayerAnimation();
};

#endif