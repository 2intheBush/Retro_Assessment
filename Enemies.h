#ifndef _ENEMIES_H_
#define _ENEMIES_H_

# include "AIE.h"

class Enemies{
public:
	Enemies();
	~Enemies();

	unsigned int spriteID;
	float speed;
	int dir;
	float x;
	float y;
	
	void SetPosition(float a_x, float a_y);

	int width;
	int height;
	void SetSize(float a_width, float a_height);

	int leftExtreme;
	int rightExtreme;
	int bottomExtreme;
	int topExtreme;
	void SetMovementExtremes(float a_leftExtreme, float a_rightExtreme, float a_bottomExtreme, float a_topExtreme);


	void Movement(float a_deltaTime);

	bool Collide();

};

#endif