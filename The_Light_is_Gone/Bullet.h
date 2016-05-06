#pragma once
#include <SFML\Graphics.hpp>

using namespace sf;
#include <cmath>
#define M_PI 3.14159265359


class Bullet
{
	float speed;
public:
	float angle;
	float lifeTime;
	Clock onCreate_clock;
	Sprite body;
	
	Bullet(float a, Vector2f poz, Texture &tekstura)
		:speed(1500.0f)
	{
		onCreate_clock.restart();
		
		angle = a;
		lifeTime = 1.0f;
		body.setTexture(tekstura);
		body.setPosition(poz);
		body.setScale(0.018f, 0.018f);
		body.setOrigin(body.getLocalBounds().width/2.0f, body.getLocalBounds().height/2.0f);
		body.setRotation(angle);
	}

	void ruch(Time czas)
	{
		
		body.move(Vector2f((float)-sin(angle*M_PI / 180)*speed*(float)czas.asSeconds(), (float)cos(angle*M_PI / 180)*speed*(float)czas.asSeconds()));
		
	}
	void rotate()
	{



		
		
		



	}

};