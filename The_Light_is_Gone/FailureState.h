#pragma once
#include <SFML\Graphics.hpp>
#include "Engine.h"
#include "Game.h"



class FailureState
{
	RenderWindow* okno;
	Event event;
	bool menu;
	bool playAgain;
	bool failure;
	Font* font;
	Image* image;
	int rounds;
	Clock clock;
public:
	FailureState(RenderWindow &_okno, Font &_font, int roundsS);
	~FailureState();
	bool runFailureScreen(Image &_image);
};

