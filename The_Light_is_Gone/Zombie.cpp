#include "Zombie.h"
#define M_PI 3.14159265359




Zombie::Zombie(Vector2f poz,Texture &tekstura_z, float v, float hp,RectangleShape &target_wal)
	:window_target(target_wal.getPosition()),
	speed(v),
	healthPoints(hp),
	texture_iterator(2),
	pauseTime(0.4f),
	collides_zombie(2),
	collide_parameter(1.0f),
	isInside(false),
	collidesWithZombie(false),
	haveAttacked(false),
	collidesWithPlayer(false),
	biteFrequency(0.8f),
	target_wall(target_wal),
	goingThrough(false),
	building_center(Vector2f(0,0)),
	rotation(0)
{
	body.setTexture(tekstura_z);
	body.setScale(0.2f, 0.2f);
	body.setOrigin(body.getGlobalBounds().width / 2.0f, body.getGlobalBounds().height / 2.0f);
	body.setPosition(poz);
	body.setTextureRect(IntRect(0, 0, 618 / 3, 210));
	texture_timer.restart();

}

void Zombie::ruch(Time czas, vector <Zombie> &tab, vector<RectangleShape> &walls)
{
	if(texture_timer.getElapsedTime().asSeconds()>=0 && texture_timer.getElapsedTime().asSeconds() <= 0.15f)texture_iterator = 0;
	else if (texture_timer.getElapsedTime().asSeconds() >= 0.16f && texture_timer.getElapsedTime().asSeconds() <= 0.30f)texture_iterator = 1;
	else if (texture_timer.getElapsedTime().asSeconds() >= 0.31f && texture_timer.getElapsedTime().asSeconds() <= 0.45f)texture_iterator = 2;
	else if (texture_timer.getElapsedTime().asSeconds() >= 0.46f)texture_timer.restart();

	boids_vector = (Vector2f((float)-sin(angle*M_PI / 180)*speed*(float)czas.asSeconds(), (float)cos(angle*M_PI / 180)*speed*(float)czas.asSeconds())) + collision(tab,czas, walls);
	body.move(boids_vector);
	body.setTextureRect(IntRect(texture_iterator * 617 / 3, 0, 617 / 3, 210));

}

void Zombie::setSpeed(float s)
{
	speed = s;
}

void Zombie::update(Vector2f cel, Time czas, Vector2f recentPlayerPosition, vector <Zombie> &tab, vector<RectangleShape> &walls)
{	
	if (!isInside)
	{	
		if (!collidesWithPlayer)
		{
			if(!goingThrough)angle = (float)atan2((float)(window_target.y - body.getPosition().y), (float)(window_target.x - body.getPosition().x)) * 180.0f / (float)M_PI - 90.0f;
			else angle = (float)atan2((float)(building_center.y - body.getPosition().y), (float)(building_center.x - body.getPosition().x)) * 180.0f / (float)M_PI - 90.0f;
			ruch(czas,tab, walls);
			body.setRotation(angle);
		}
	}


	else 
	{
		if (!collidesWithPlayer)
		{
			angle = (float)atan2((float)(cel.y - body.getPosition().y), (float)(cel.x - body.getPosition().x)) * 180.0f / (float)M_PI - 90.0f;
			/*for (unsigned int i = 4; i < 8; i++)
				if(!walls[i].getGlobalBounds().contains(body.getPosition() + Vector2f((float)-sin(angle*M_PI / 180)*speed*(float)czas.asSeconds(), (float)cos(angle*M_PI / 180)*speed)) )*/
				ruch(czas,tab, walls);
			rotate_angle = (float)atan2((float)(recentPlayerPosition.y - body.getPosition().y), (float)(recentPlayerPosition.x - body.getPosition().x)) * 180.0f / (float)M_PI - 90.0f;
			body.setRotation(rotate_angle);
		}
	}

}


Vector2f Zombie::collision(vector <Zombie> &tab, Time czas, vector <RectangleShape> &walls){
	Vector2f c = Vector2f(0,0);

	for (unsigned int i = 0; i < tab.size(); i++)
	{
		
		if (tab[i].body.getPosition() != body.getPosition())
		{	
			if(Collision::PixelPerfectTest(tab[i].body, body)&& !tab[i].goingThrough)
			{
				c = c - (tab[i].body.getPosition() - body.getPosition())*czas.asSeconds();
			}
			
		}
	}

	for (unsigned int i = 4; i < 8;i++)
		if (body.getGlobalBounds().intersects(walls[i].getGlobalBounds()) && !body.getGlobalBounds().intersects(walls[i+4].getGlobalBounds()))
		{
			if (isInside && !goingThrough)c = c + (building_center - body.getPosition())*czas.asSeconds();
			
		}
	
	return c;
}

void Zombie::rotate(float angle, Time czas){
//{
//		angle = fabs(angle);
//		if ((int)fabs(body.getRotation()) < (int)-angle)
//		{
//			//rotation++;
//			if ((int)body.getRotation() == 360)body.setRotation(0.0f);
//			body.rotate(1.0f);
//		}
//		else if ((int)fabs(body.getRotation()) > (int)-angle)
//		{
//			if ((int)body.getRotation() == 360)body.setRotation(0.0f);
//			body.rotate(-1.0f);
//			//rotation--;
//		}
//		//body.setRotation(rotation);
//		cout << angle << " | " << rotation << endl;
	
	
}
