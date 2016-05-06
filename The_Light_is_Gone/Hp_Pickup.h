#pragma once
#include "Pick_up.h"
class Hp_Pickup :
	public Pickup
{
public:
	float add_hp;

	Hp_Pickup(Texture &tekstura, Vector2f pozycja_ciala)
		:add_hp(1)
	{

		onCreate_clock.restart();
		body.setTexture(tekstura);
		body.setPosition(pozycja_ciala);

		body.setScale(0.15f, 0.15f);

	}
	~Hp_Pickup() {

	}
};
#pragma once
