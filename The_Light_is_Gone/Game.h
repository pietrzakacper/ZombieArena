#pragma once
#include <SFML\Graphics.hpp>
#include "Player.h"
#include "Bullet.h"
#include "Zombie.h"
#include <Windows.h>
#include <string>
#include <iostream>
#include <deque>
#include "Blood.h"
#include "Collision.h"
#include <string>
#include "Gun.h"
#include "Corps.h"
#include "Ammo_Pickup.h"
#include "Hp_Pickup.h"
#include "Engine.h"
#include "FailureState.h"
using namespace std;
using namespace sf;

class Game 
{
private:
	Font font;
	
	int roundsSurvived;
public:
	
	Image image;
	RenderWindow okno;
	View view;
	enum GameState { MENU, GAME, GAME_OVER, END, FAILURE};
	GameState state;
	Game(void);

	~Game(void);

	void beginGame();
	void menu();
	void single();
	
};