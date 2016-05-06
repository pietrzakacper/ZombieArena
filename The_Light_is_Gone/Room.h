#pragma once
#include <SFML\Graphics.hpp>

using namespace sf;
using namespace std;

class Room
	:public Drawable
{
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

public:
	Room();
	Room(float width, float height, Vector2f center, int entrancesNumber, Vector2f tab[]);
	~Room();
	RectangleShape walls[4];
	vector <RectangleShape> entrances;
	Vector2f center;
	float _width, _height;
};

