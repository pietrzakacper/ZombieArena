#include "PauseScreen.h"



PauseScreen::PauseScreen(bool &_pause, RenderWindow &_okno, Font &_font)
	:pause(&_pause),
	okno(&_okno),
	font(&_font)
{
	okno->setMouseCursorVisible(true);
}


PauseScreen::~PauseScreen()
{
	okno->setMouseCursorVisible(false);
	
}

void PauseScreen::runPause(bool &_menu, bool &failure, Image &image)
{
	View view;
	okno->setView(okno->getDefaultView());
	Text title("pause", *font, 80);
	//Image image = okno->capture();

	Texture tekstura;
	tekstura.loadFromImage(image);
	//tekstura.setRepeated(true);


	Sprite background;
	background.setTexture(tekstura);
	background.setPosition(Vector2f(0, 0));
	background.setOrigin(Vector2f(0, 0));
	background.setTextureRect(IntRect(0, 0, 1280, 720));



	title.setColor(Color(138, 7, 7));
	title.setPosition(1280 / 2 - title.getGlobalBounds().width / 2, 10);

	const int ile = 2;

	Text tekst[ile];

	string str[] = { "return to game","menu" };

	for (int i = 0; i<ile; i++)
	{
		tekst[i].setFont(*font);
		tekst[i].setCharacterSize(50);

		tekst[i].setString(str[i]);
		tekst[i].setPosition((float)(1280 / 2.0 - tekst[i].getGlobalBounds().width / 2), (float)(250 + i * 120.0));
	}
	while (*pause)
	{

		Vector2f mouse(Mouse::getPosition(*okno));
		while (okno->pollEvent(event))
		{


			if (event.type == Event::KeyPressed &&
				event.key.code == Keyboard::Escape)
				*pause = false;


			else if (tekst[0].getGlobalBounds().contains(mouse) &&
				event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
				*pause = false;

			else if (tekst[1].getGlobalBounds().contains(mouse) &&
				event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
			{
				*pause = false;
				failure = false;
				_menu = true;
			}
		}
		for (int i = 0; i<ile; i++)
			if (tekst[i].getGlobalBounds().contains(mouse))
			{
				tekst[i].setColor(Color(138, 7, 7));
			}
			else tekst[i].setColor(Color::White);

			okno->clear();

			okno->draw(background);
			okno->draw(title);

			for (int i = 0; i<ile; i++)
				okno->draw(tekst[i]);
			okno->display();
	}
}