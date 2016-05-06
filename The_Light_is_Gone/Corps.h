#pragma once
#include <SFML\Graphics.hpp>


using namespace sf;


class Corps
{
public:
	Clock onCreate_clock;
	Sprite body;
	float lifeTime;

	Corps(Texture &tekstura, Vector2f pozycja_ciala, float angle)
	:lifeTime(15.0f)
	{
		onCreate_clock.restart();
		body.setTexture(tekstura);
		body.setPosition(pozycja_ciala);
		body.setRotation(angle);
		body.setScale(0.35f, 0.35f);

	}
	~Corps() {

	}
};

