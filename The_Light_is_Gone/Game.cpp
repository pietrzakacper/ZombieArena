//Property of Kacper Pietrzak
//Do not fucking copy!!!
//Or you know what... whatever...
//This code is shitty anyway

#include "Game.h"
#include <cmath>
#include <SFML/Audio.hpp>
#define M_PI 3.14159265359




Game::Game(void)
	:roundsSurvived(0)
{
	ContextSettings settings;
	settings.antialiasingLevel = 8;
	view = View(FloatRect(0, 0, 1280,720));
	okno.create(VideoMode(1280,720), "Zombie Arena", Style::Close, settings);
	okno.setVerticalSyncEnabled(true);
	
	
	if (!font.loadFromFile("data/font.ttf"))
	{
		MessageBox(NULL, "Font not found! Chceck data folder!", "ERROR", NULL);
		return;
	}
	state=MENU;
}

Game::~Game(void)
{

}

void Game::beginGame()
{
	while (state != END)
	{
		switch (state)
		{
			case GameState::MENU:
				menu();
				break;
			case GameState::GAME:
				single();
				break;
			case GameState::FAILURE:
				FailureState failure(okno,font, roundsSurvived);
				if (failure.runFailureScreen(image))
					state = GAME;
				else state = MENU;
				break;
				
		}
	}
}

void Game::menu()
{	
	
	Text podpis("Created by Kacper Pietrzak", font,25);

	Text title("Zombie Arena", font,80);
	Texture tekstura;
	tekstura.loadFromFile("data/ground.png");
	tekstura.setRepeated(true);

	Sprite background;
	background.setTexture(tekstura);
	background.setPosition(Vector2f(0, 0));
	background.setOrigin(Vector2f(0, 0));
	background.setTextureRect(IntRect(0, 0, 1280, 720));
	Image ikona;
	ikona.loadFromFile("data/ikona.png");

	okno.setIcon(1024, 1024, ikona.getPixelsPtr());

	title.setColor(Color(138, 7, 7));
	title.setPosition(1280 / 2 - title.getGlobalBounds().width / 2, 10);
	podpis.setPosition(10, 680);
	podpis.setColor(Color(100,100,100));
	
	const int ile = 2;

	Text tekst[ile];

	string str[] = { "PLAY","EXIT"};

	for (int i = 0; i<ile; i++)
	{
		tekst[i].setFont(font);
		tekst[i].setCharacterSize(60);

		tekst[i].setString(str[i]);
		tekst[i].setPosition((float)(1280 / 2.0 - tekst[i].getGlobalBounds().width / 2), (float)(250 + i * 120.0));
	}
	
	while (state == MENU)
	{
		Vector2f mouse(Mouse::getPosition(okno));

		Event event;
		while (okno.pollEvent(event))
		{
			
			if (event.type == Event::Closed || event.type == Event::KeyPressed &&
				event.key.code == Keyboard::Escape)
				state=END;

			
			else if (tekst[1].getGlobalBounds().contains(mouse) &&
				event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
				state=END;

			else if (tekst[0].getGlobalBounds().contains(mouse) &&
				event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
				state=GAME;

		}

		for (int i = 0; i<ile; i++)
			if (tekst[i].getGlobalBounds().contains(mouse))
			{
				tekst[i].setColor(Color(138, 7, 7));
			}
			else tekst[i].setColor(Color::White);



			okno.clear();
			okno.draw(background);
			okno.draw(title);
			okno.draw(podpis);

			for (int i = 0; i<ile; i++)
				okno.draw(tekst[i]);

			okno.display();
	}
	
	
}

void Game::single()
{
	Engine engine(okno, view, image, roundsSurvived);
	if (engine.init())
	{
		if(engine.runEngine())
		state=FAILURE;
		else state = MENU;
	}
	
	
}

