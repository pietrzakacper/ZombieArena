#include "Room.h"


Room::Room(void)
{

}

Room::Room(float width, float height, Vector2f _center, int entrancesNumber, Vector2f tab[])
	:center(_center),
	_width(width),
	_height(height)
{
	tab[0] = Vector2f(0, 200);
	tab[1] = Vector2f(3, 300);

	for (int i = 0; i < 4; i++)
	{
		if (i == 0 || i ==1)walls[i].setSize(Vector2f(width+20,20));
		if (i == 2 || i == 3)walls[i].setSize(Vector2f(20,height+20));
		walls[i].setOrigin(walls[i].getGlobalBounds().width/2.0f, walls[i].getGlobalBounds().height / 2.0f);
		if (i == 0)walls[i].setPosition(center-Vector2f(0.0f,height/2.0f));
		if (i == 1)walls[i].setPosition(center + Vector2f(0.0f, height / 2.0f));
		if (i == 2)walls[i].setPosition(center - Vector2f(width / 2.0f,0.0f));
		if (i == 3)walls[i].setPosition(center + Vector2f(width / 2.0f, 0.0f));
		walls[i].setFillColor(Color::Cyan);
	}
	for (int i = 0; i < entrancesNumber;i++)
	{
		RectangleShape entrance;
		if (tab[i].x == 0 || tab[i].x == 1)entrance.setSize(Vector2f(100, 20));
		if (tab[i].x == 2 || tab[i].x == 3)entrance.setSize(Vector2f(20, 100));
		entrance.setOrigin(entrance.getGlobalBounds().width / 2.0f, entrance.getGlobalBounds().height / 2.0f);
		if (tab[i].x == 0)entrance.setPosition(walls[0].getPosition()-Vector2f(width/2.0f,0.0f)+Vector2f(tab[i].y,0.0f));
		if (tab[i].x == 1)entrance.setPosition(walls[1].getPosition() - Vector2f(width / 2.0f, 0.0f) + Vector2f(tab[i].y, 0.0f));
		if (tab[i].x == 2)entrance.setPosition(walls[2].getPosition() - Vector2f(0.0f, height / 2.0f) + Vector2f(0.0,tab[i].y));
		if (tab[i].x == 3)entrance.setPosition(walls[3].getPosition() - Vector2f(0.0f, height / 2.0f) + Vector2f(0.0, tab[i].y));
		entrance.setFillColor(Color::Red);
		entrances.push_back(entrance);
	}


}


Room::~Room()
{
}

void Room::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (int i = 0; i < 4; i++)
	target.draw(walls[i], states);
	for (unsigned int i = 0; i < entrances.size();i++)
	target.draw(entrances[i], states);
}