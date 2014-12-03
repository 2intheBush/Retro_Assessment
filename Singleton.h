#pragma once
#include <iostream>

class Singleton
{
public:
	static Singleton* GetInstance();
	void Test();
	unsigned int screenHeight;
	unsigned int screenWidth;
	~Singleton();

protected:
	Singleton();
	static Singleton* instance;
};