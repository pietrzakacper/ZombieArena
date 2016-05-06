#pragma once
#include "Pick_up.h"
class Ammo_Pickup :
	public Pickup
{
public:
	float add_ammo;

	Ammo_Pickup(Texture &tekstura, Vector2f pozycja_ciala) 
		: add_ammo(50.0f)
	{

		onCreate_clock.restart();
		body.setTexture(tekstura);
		body.setPosition(pozycja_ciala);

		body.setScale(0.06f,0.06f);

	}
	~Ammo_Pickup() {

	}
};

