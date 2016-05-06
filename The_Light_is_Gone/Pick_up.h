#pragma once
#include <SFML\Graphics.hpp>


using namespace sf;
class Pickup
{
public:
	
	Clock onCreate_clock;
	Sprite body;
	float lifeTime;

	Pickup() 
		:lifeTime(20.0f)
	{

	}
	~Pickup() {

	}
};

