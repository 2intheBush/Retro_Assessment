#include "Singleton.h"

//Static Member
Singleton* Singleton::instance = 0;



Singleton::Singleton()
{
	screenWidth = 600;
	screenHeight = 800;
}
Singleton::~Singleton()
{
}

Singleton* Singleton::GetInstance()
{
	if (instance == 0)
	{
		instance = new Singleton();
	}
	return instance;
}

void Singleton::Test()
{

}