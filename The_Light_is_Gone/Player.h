#include <SFML\Graphics.hpp>


#pragma once

using namespace sf;

class Player
{public:
	
	
	Texture tekstura;
	Sprite body;
	bool canMoveUP;
	bool canMoveDown;
	bool canMoveLeft;
	bool canMoveRight;
	float healthPoints;
	float speed;

	Player()
		:canMoveUP(true),
		canMoveDown(true),
		canMoveLeft(true),
		canMoveRight(true),
		healthPoints(3),
		speed(100.0f)
	{
		
		tekstura.loadFromFile("data/player_empty.png");
		body.setTexture(tekstura);
		body.setScale(0.2f, 0.2f);
		body.setOrigin(Vector2f(body.getLocalBounds().width / 2.0f, body.getLocalBounds().height/2.0f-36.0f));
		
	}
	~Player()
	{

	}

	void update(Time czas,float &vx, float &vy, bool isSprint)
	{	
		input(vx,vy,isSprint);
		ruch(czas,vx,vy);
	}

	void ruch(Time czas, float x, float y)
	{
		
		body.move(Vector2f(x*czas.asSeconds(), y*czas.asSeconds()));

	}

	void input(float &vx,float &vy, bool isSprint)
	{
		
			vy = 0;
			vx = 0;
			//if (!canMoveUP&&!Keyboard::isKeyPressed(Keyboard::S))vy = 0;
			if (Keyboard::isKeyPressed(Keyboard::W)&&canMoveUP)
			{
				
				vy = -speed;
			}
			
			//if (!canMoveDown&& !Keyboard::isKeyPressed(Keyboard::W))vy = 0;
			if (Keyboard::isKeyPressed(Keyboard::S)&&canMoveDown)
			{
				
				vy = speed;
			}
		
			//if (!canMoveLeft&&!Keyboard::isKeyPressed(Keyboard::D))vx = 0;
			 if (Keyboard::isKeyPressed(Keyboard::A)&&canMoveLeft)
			{
				
				vx = -speed;
			}
			
			//if (!canMoveRight&&!Keyboard::isKeyPressed(Keyboard::A))vx = 0;
			if (Keyboard::isKeyPressed(Keyboard::D)&&canMoveRight)
			{
				
				vx = speed;
			}
		

			if (vx != 0 && vy != 0)//zmniejszenie prêdkoœci gdy gracz porusza siê po ukosie
			{
				vx=vx/ (float)sqrt(2);
				vy = vy / (float)sqrt(2);
			}
			if (isSprint)
			{
			vx *= 1.5f;
			vy *= 1.5f;
			}

		
		
		
	}

};