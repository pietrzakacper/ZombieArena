#pragma once
#include <SFML\Graphics.hpp>
#include "Bullet.h"
#include <SFML/Audio.hpp>

using namespace sf;
using namespace std;
class Gun
{
public:
	


	string name;
	vector <Bullet> bullets_fired;
	float bulletsLeft;
	float magazynekSize;
	float magazynek;
	float fireRate;
	float angle;
	float bullet_speed;
	float damage;
	Texture tekstura_bullet;
	Texture tekstura_gun;
	Sprite body;
	float reloadTime;
	Clock reload_timer;
	Clock fire_timer;
	bool reloading;
	bool reload_demand;
	Vector2f gun_skala;
	Vector2f bullet_skala;
	SoundBuffer buffer;
	Sound sound;

	Gun()
	{

	}

	Gun(string bullet_path, string gun_path, string nazwa, float ile_pociskow, float rozmiar_magazynka, float predkosc_pociskow, float czas_przeladowania,
		Vector2f skala_dla_broni, Vector2f skala_dla_pocisku, Vector2f pozycja_gracz, float frrate, string shot_wav_path, float _damage)
		:name(nazwa), bulletsLeft(ile_pociskow),
		magazynekSize(rozmiar_magazynka),
		magazynek(magazynekSize),
		bullet_speed(predkosc_pociskow),
		reloadTime(czas_przeladowania),
		gun_skala(skala_dla_broni),
		bullet_skala(skala_dla_pocisku),
		fireRate(frrate),
		reloading(false),
		damage(_damage)
	{	
		buffer.loadFromFile(shot_wav_path);
		sound.setBuffer(buffer);
		sound.setVolume(30.0f);
		tekstura_bullet.loadFromFile(bullet_path);
		tekstura_gun.loadFromFile(gun_path);
		body.setTexture(tekstura_gun);
		body.setOrigin(body.getLocalBounds().width, 0);
		body.setPosition(pozycja_gracz);
		body.setScale(gun_skala / 10.0f);



	}
	void shoot(Vector2f	pozycja_gracz)
	{	
		
			body.setOrigin(body.getLocalBounds().width/2.0f, body.getLocalBounds().height / 2.0f);
			Bullet pocisk(angle,pozycja_gracz, tekstura_bullet);
			sound.play();
			bullets_fired.push_back(pocisk);
			
	
	}
	void update(float angl, Time czas, Vector2f	pozycja_gracz)
	{
		angle = angl;
		
		body.setOrigin(body.getLocalBounds().width, 0);
		body.setPosition(pozycja_gracz);
		body.setRotation(angle);

		// moving fired bullets
		for (unsigned int i = 0; i < bullets_fired.size(); i++)
		{
			bullets_fired[i].body.move(Vector2f((float)-sin(bullets_fired[i].angle*M_PI / 180)*bullet_speed*(float)czas.asSeconds(), (float)cos(bullets_fired[i].angle*M_PI / 180)*bullet_speed*(float)czas.asSeconds()));
		}

		//reload manager
		if (reload_demand) {
			if (!reloading)
			{
				reload_timer.restart();
				reloading = true;
			}
			if (reload_timer.getElapsedTime().asSeconds() >= reloadTime)
			{
				reload();
				reloading = false;
				reload_demand = false;
			}
		}
	}

	void reload()
	{	
		if (magazynek != magazynekSize)
		{

			bulletsLeft -= magazynekSize;
			magazynek += magazynekSize;
			if (bulletsLeft < 0)
			{
				magazynek += bulletsLeft;
				bulletsLeft = 0;
			}
			if (magazynek > magazynekSize) {
				bulletsLeft += magazynek - magazynekSize;
				magazynek = magazynekSize;
			}


			if (magazynek < 0)
				magazynek = 0;
			
		}

	
	}
	~Gun()
	{

	}

};

