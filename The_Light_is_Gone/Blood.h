#pragma once
#include <SFML\Graphics.hpp>
#include <cstdlib>
#include <time.h>

using namespace sf;

class Blood {

public:
	float lifeTime;
	Clock onCreate_clock;
	Sprite body;
	RectangleShape rect;

	Blood(Texture &tekstura, Vector2f position)
		:lifeTime(10.0f)
	{
		onCreate_clock.restart();
		srand((unsigned int)time(NULL));
		
		body.setTexture(tekstura);
		body.setScale(0.3f, 0.3f);
		body.setTextureRect(IntRect((rand() % 4 )*100, (rand() % 4) *100, 100, 100));
		body.setOrigin(body.getLocalBounds().width / 2.0f, body.getLocalBounds().height / 2.0f);
		body.setPosition(position);
		body.setRotation((float)(rand() % 360) + 1);
	
	}



};