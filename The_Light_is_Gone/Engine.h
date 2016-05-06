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
#include <SFML/Audio.hpp>
#include "PauseScreen.h"
#include "Game.h"
#include "Room.h"

class Engine
{
public:

	Engine(sf::RenderWindow &win, View &widok, Image &_image, int &roundsS);
	~Engine();
	bool runEngine();
	 void event_manager();
	 bool init();
	Room room;
private:
	Vector2f cos[2];
	Text note;
	sf::RenderWindow *okno;
	int fps;
	int fraps;
	Clock fpsClock;
	View *view;
	Player gracz;
	Gun* wsk_gun;
	Gun pistol;
	Gun ak_47;
	/////////////////////////// tablice obiektów
	vector<Blood> tab_bl;
	vector <Zombie> tab_z; //zombie
	deque <Vector2f> tab_p;//pozycje gracza z ostatnich 100 klatek
	vector <Corps> tab_corps;
	vector <Ammo_Pickup> tab_am;
	vector <Hp_Pickup> tab_hp;
	vector<RectangleShape> tab_wall;
	//Tekstury, w przysz³oœci bêd¹ w jednym pliku
	Texture tekstura_cel;
	Texture tekstura_z;
	Texture tekstura;
	Texture tekstura_bl;
	Texture tekstura_floor;
	Texture tekstura_corps;
	Texture tekstura_ammo;
	Texture tekstura_hp;
	Texture tekstura_wall;
	/*Texture tekstura_bullet;
	Texture tekstura_pistol;
	Texture tekstura_ak_47;*/

	SoundBuffer buffer_z;
	Sound sound_hit;
	SoundBuffer zombie_bite;
	Sound sound_bite;
	SoundBuffer reload_wav, ammo_out;
	SoundBuffer health_wav, ammo_wav;
	Sound health_collect, ammo_collect;
	

	Sound sound_reload, sound_ammo_out;
	Music muzyka;
	Font font;
	Text UI[7]; // hp[0],round[1],gun_name[2],bullets_Left[3],licznik_zomibe[4], reloading_info[5], reloading_reminder[6] 
	Sprite celownik;
	RectangleShape sprint_ui;
	Sprite map;
	Sprite floor;
	
	int runda;
	float vx, vy; //pr?dko?? gracza
	float angle;
	bool hasPlayerChosenAk;
	Clock reload_time;
	Clock zombie_generator_timer;
	Clock zegar;
	Time czas;
	Event event;
	Vector2f mysz; //x,y myszy
	int max_zombie_per_round;
	int generated_zombie;
	bool generate;
	bool menu;
	bool _pause;
	bool isSprint;
	bool canSprint;
	bool failure;
	int zombies_killed_in_round;
	Image* image;
	int* ptrRoundsSurvived;
	Texture wall_t;
	Texture entrance;
	
	
	
	///////////////////////
	
	//metody//
	void generator_manager();
	
	void sprint_manager();

	void update();
	void draw();
	void collision();
	void bullet_destroy(int i);
	void zombie_destroy(int i);
	void blood_destroy(int i);
	void zombie_generator(vector <Zombie> &tab_z, Vector2f poz, Texture &tekstura_z, int runda, RectangleShape &target_wal);
	void corps_destroy( int i);
	void ammo_destroy(int i);
	void hp_destroy(int i);
	void interfejs();
	void pause_screen();
	
};

