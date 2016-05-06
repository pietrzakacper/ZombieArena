#pragma once
#include <SFML\Graphics.hpp>
#include "Engine.h"
#include "Game.h"
using namespace sf;
class PauseScreen
{
private:
	RenderWindow* okno;
	
	bool* pause;
	Event event;
	Font* font;
public:
	PauseScreen(bool &_pause,RenderWindow &_okno,Font &_font);
	~PauseScreen();
	void runPause(bool &_menu, bool &failure, Image &image);
};

