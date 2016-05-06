#include "FailureState.h"
#include <string>



FailureState::FailureState(RenderWindow &_okno, Font &_font, int roundsS)
	:menu(false),
	okno(&_okno),
	font(&_font),
	playAgain(false),
	failure(true),
	rounds(roundsS)
{
	okno->setMouseCursorVisible(true);
}


FailureState::~FailureState()
{
}


bool FailureState::runFailureScreen(Image &_image)
{
	clock.restart();
	View view;
	okno->setView(okno->getDefaultView());

	Text title("you died", *font, 80);
	Text survived("you have survived " + to_string(rounds) +" rounds", *font, 40);
	
	image = &_image;

	Texture tekstura;
	tekstura.loadFromImage(*image);

	Sprite background;
	background.setTexture(tekstura);
	background.setPosition(Vector2f(0, 0));
	background.setOrigin(Vector2f(0, 0));
	background.setTextureRect(IntRect(0, 0, 1280, 720));

	title.setColor(Color(138, 7, 7));
	title.setPosition(1280 / 2 - title.getGlobalBounds().width / 2, 10);
	survived.setColor(Color(138, 7, 7));
	survived.setOrigin(Vector2f(survived.getGlobalBounds().width / 2.f, survived.getGlobalBounds().height / 2.f));
	survived.setPosition(1280 / 2, 110);

	const int ile = 2;

	Text tekst[ile];

	string str[] = { "play again","return to menu" };

	for (int i = 0; i<ile; i++)
	{
		tekst[i].setFont(*font);
		tekst[i].setCharacterSize(50);

		tekst[i].setString(str[i]);
		tekst[i].setPosition((float)(1280 / 2.0 - tekst[i].getGlobalBounds().width / 2), (float)(250 + i * 120.0));
	}

	while (failure)
	{

		Vector2f mouse(Mouse::getPosition(*okno));
		while (okno->pollEvent(event))
		{
			if (clock.getElapsedTime().asSeconds() >= 1.f)
			{
				if (tekst[0].getGlobalBounds().contains(mouse) &&
					event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
				{
					failure = false;
					playAgain = true;
				}
				else if (tekst[1].getGlobalBounds().contains(mouse) &&
					event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
				{
					failure = false;
					menu = true;
				}
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
			okno->draw(survived);

			for (int i = 0; i<ile; i++)
				okno->draw(tekst[i]);
			okno->display();
	}
	if (menu)return false;
	else if(playAgain) return true;
}