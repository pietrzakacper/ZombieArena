#include "Engine.h"



Engine::Engine(sf::RenderWindow &win,View &widok, Image &_image, int &roundsS)
	:generated_zombie(0),
	 generate(true),
	 menu(false),
	 isSprint(false),
	 canSprint(true),
	 wsk_gun(&pistol),
	 runda(1),
	 vx(0),
	 vy(0),
	 pistol(Gun("data/bullet.png", "data/gun.png", "colt .44", 80.0f, 16.0f, 2000.0f, 2.0f, Vector2f(2, 2), Vector2f(1, 1), gracz.body.getPosition(), 0.1f, "data/shot.wav", 1.0f)),
	 ak_47(Gun("data/bullet.png", "data/ak_47.png", "ak 47", 120.0f, 30.0f, 2800.0f, 2.0f, Vector2f(2, 2), Vector2f(1, 1), gracz.body.getPosition(), 0.08f, "data/AKS-74u.wav", 1.f)),
	okno(&win),
	view(&widok),
	room(Room(500,500,Vector2f(0,0),2,cos)),
	fraps(0),
	failure(true),
	image(&_image),
	ptrRoundsSurvived(&roundsS),
	hasPlayerChosenAk(false)
{
	
	
}

Engine::~Engine()
{
	okno->setMouseCursorVisible(true);
	okno->setView(okno->getDefaultView());
}

bool Engine::runEngine()
{
	
	srand((unsigned int)time(NULL));
	while (!menu)
	{	

		
			generator_manager();
			event_manager();
			update();
			interfejs();
			draw();
			if (_pause)pause_screen();
			
			fraps++;
			
			if (fpsClock.getElapsedTime().asSeconds() >= 1.0f)
			{
				fps = fraps;
				fraps = 0;
				fpsClock.restart();
				cout << fps << endl;
			
			}
			
	}
	return failure;
}

void Engine::generator_manager()
{
	if (generate)max_zombie_per_round = runda * 4 * 4;

	if (generated_zombie >= max_zombie_per_round)
	{
		generate = false;

	}
	if (!generate&&tab_z.empty())
	{
		zombies_killed_in_round = 0;
		generated_zombie = 0;
		generate = true;
		runda++;

	}
	if (generate && (zombie_generator_timer.getElapsedTime().asSeconds() >= 1.0f) && tab_z.size() <= 20)
	{
		zombie_generator_timer.restart();


		generated_zombie += 4;
		zombie_generator(tab_z, Vector2f((tab_wall[0].getPosition().x + rand() % ((int)tab_wall[0].getGlobalBounds().width + 1)), (tab_wall[0].getPosition().y + tab_wall[0].getGlobalBounds().height)), tekstura_z, runda, tab_wall[8]);
		zombie_generator(tab_z, Vector2f((tab_wall[1].getPosition().x + rand() % ((int)tab_wall[1].getGlobalBounds().width + 1)), (tab_wall[1].getPosition().y + tab_wall[1].getGlobalBounds().height)), tekstura_z, runda, tab_wall[9]);
		zombie_generator(tab_z, Vector2f((tab_wall[2].getPosition().x + tab_wall[2].getGlobalBounds().width), (tab_wall[2].getPosition().y + rand() % ((int)tab_wall[2].getGlobalBounds().height + 1))), tekstura_z, runda, tab_wall[10]);
		zombie_generator(tab_z, Vector2f((tab_wall[3].getPosition().x + tab_wall[3].getGlobalBounds().width), (tab_wall[3].getPosition().y + rand() % ((int)tab_wall[3].getGlobalBounds().height + 1))), tekstura_z, runda, tab_wall[11]);
	}


}

void Engine::event_manager()
{
	while (okno->pollEvent(event))
	{

		if (event.type == Event::Closed) {
			
			
			_pause = true;
		}

		if(event.type == Event::LostFocus)
			_pause = true;
		if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)_pause = true;
		//if (event.type == Event::MouseButtonPressed && Mouse::isButtonPressed(Mouse::Right))//stworzenie zombie i dodanie go do tablicy
		//{

		//	Zombie zombie(gracz.body.getPosition(), tekstura_z, 80, rand() % (runda)+1,tab_wall[7]);
		//	zombie.body.setPosition(mysz);
		//	tab_z.push_back(zombie);

		//}
		// strza³ broni¹ jednostrza³ow¹ //
		
			if (wsk_gun == &pistol) {
				if (event.type == Event::MouseButtonPressed && Mouse::isButtonPressed(Mouse::Left))//stworzenie pocisku i dodanie go do tablicy
				{
					if (wsk_gun->magazynek == 0)
					{
						sound_ammo_out.play();
						if (wsk_gun->bulletsLeft != 0 && !wsk_gun->reload_demand&& !wsk_gun->reloading)
						{
							sound_reload.play();
							wsk_gun->reload_demand = true;
						}
					}
					else if (!wsk_gun->reloading)
					{
						//sound.play();
						wsk_gun->shoot(gracz.body.getPosition());


						wsk_gun->magazynek--;

					}
					else {
						sound_ammo_out.play();
					}
				}
			}


			if (event.type == Event::MouseButtonPressed && Mouse::isButtonPressed(Mouse::Left) && (wsk_gun->magazynek == 0 || wsk_gun->reloading || wsk_gun->reload_demand))
				sound_ammo_out.play();



			if (event.type == Event::KeyPressed && event.key.code == Keyboard::R && wsk_gun->bulletsLeft != 0 && wsk_gun->magazynek != wsk_gun->magazynekSize &&!wsk_gun->reloading&& !wsk_gun->reload_demand)
			{
				wsk_gun->reload_demand = true;
				sound_reload.play();
			}

		
			if (event.type == Event::KeyPressed && event.key.code == Keyboard::Num2)
			{
				if (runda >= 3)
				{
					wsk_gun = &ak_47;
					hasPlayerChosenAk = true;
				}//buffer = wsk_gun->shot;
			}
			/*if (event.type == Event::KeyPressed && event.key.code == Keyboard::Up)view->zoom(1.2f);
			if (event.type == Event::KeyPressed && event.key.code == Keyboard::Down)view->zoom(1.0f / 1.2f);*/
		
	
	}//koniec while'a

	 // strza³ broni¹ szybkostrzeln¹ //		

if (wsk_gun != &pistol)
{
	if (wsk_gun->fire_timer.getElapsedTime().asSeconds() >= wsk_gun->fireRate && Mouse::isButtonPressed(Mouse::Left))
	{
	
			if (wsk_gun->magazynek == 0)
			{
				if (wsk_gun->bulletsLeft != 0 && !wsk_gun->reload_demand&& !wsk_gun->reloading)
				{
					sound_reload.play();
					wsk_gun->reload_demand = true;
				}
			}
			else if (!wsk_gun->reloading)
			{
				//sound.play();
				wsk_gun->shoot(gracz.body.getPosition());


				wsk_gun->magazynek--;
				wsk_gun->fire_timer.restart();
			}
		}
		
	
		
	}

}

void Engine::sprint_manager()
{
	// obs³uga sprintu //

	if (Keyboard::isKeyPressed(Keyboard::LShift) && canSprint)
	{
		if (sprint_ui.getSize().x < 1)
		{
			canSprint = false;
		}
		isSprint = true;
	}
	else
	{
		if (sprint_ui.getSize().x > 15)
		{
			canSprint = true;
		}
		isSprint = false;
	}
}

void Engine::update()
{	
	*ptrRoundsSurvived = runda-1;
	view->setCenter(gracz.body.getPosition()); //gracz ca³y czas w centrum widoku


	mysz.x = (float)Mouse::getPosition(*okno).x + view->getCenter().x - 1280 / 2, mysz.y = (float)Mouse::getPosition(*okno).y + view->getCenter().y - 720 / 2; //zapisanie pozycji myszy wzgl?dem lewgo górnego rogu widoku

	celownik.setPosition(mysz); //przypisanie pozycji celownika 

	angle = (float)atan2((float)(mysz.y - gracz.body.getPosition().y), (float)(mysz.x - gracz.body.getPosition().x)) * 180.0f / (float)M_PI - 90.0f; //zapisanie k?t mi?dzy ?rodkiem ekranu a pozycji myszy
	gracz.body.setRotation(angle);		//obrócenie gracza w kierunku myszy

										/////////////////////////////
	if (tab_p.size() != 30)				//wype?nienie tablicy pozycjami gracza z ostatnich 30 klatek (czyli 1/3 sekundy)
		tab_p.push_back(gracz.body.getPosition());

	if (tab_p.size() == 30)
	{
		tab_p.pop_front();
		tab_p.push_back(gracz.body.getPosition());
	}
	// interfejs //

	

	collision(); //zarz¹dza kolizjami

	//	update //

	sprint_manager();
	gracz.update(czas, vx, vy, isSprint); //gracz
	wsk_gun->update(angle, czas, gracz.body.getPosition()); //broñ

		
	for (unsigned int i = 0; i < tab_z.size(); i++) //zombie
	{
		if (!tab_z[i].goingThrough)
			tab_z[i].update(gracz.body.getPosition(), czas, tab_p[0], tab_z, tab_wall);
		else
			tab_z[i].update(Vector2f(0,0), czas, tab_p[0], tab_z, tab_wall);
	}
// zombie isInside update 
	for (unsigned int i = 0; i < tab_z.size(); i++)
	{
		if (!tab_z[i].goingThrough && tab_z[i].body.getGlobalBounds().contains(tab_z[i].target_wall.getPosition()))
			tab_z[i].goingThrough = true;
		
	}
	
	for (unsigned int i = 0; i < tab_z.size(); i++)
		if (tab_z[i].goingThrough && !tab_z[i].body.getGlobalBounds().intersects(tab_z[i].target_wall.getGlobalBounds()))
		{	
			tab_z[i].goingThrough = false;
			tab_z[i].isInside = true;
		}
	//////////////////////////////////////////////////

	// usuwanie obiektów po u³yniêciu ich lifeTime //

	for (unsigned int i = 0; i < wsk_gun->bullets_fired.size(); i++)
	{
		if (wsk_gun->bullets_fired[i].onCreate_clock.getElapsedTime().asSeconds() >= wsk_gun->bullets_fired[i].lifeTime)
		{
			bullet_destroy( i);
		}
	}

	for (unsigned int i = 0; i < tab_bl.size(); i++)
	{
		if (tab_bl[i].onCreate_clock.getElapsedTime().asSeconds() >= tab_bl[i].lifeTime)
		{
			blood_destroy( i);
		}
	}
	for (unsigned int i = 0; i < tab_corps.size(); i++)
	{
		if (tab_corps[i].onCreate_clock.getElapsedTime().asSeconds() >= tab_corps[i].lifeTime)
		{
			corps_destroy(i);
		}
	}

	for (unsigned int i = 0; i < tab_am.size(); i++)
	{
		if (tab_am[i].onCreate_clock.getElapsedTime().asSeconds() >= tab_am[i].lifeTime)
		{
			ammo_destroy(i);
		}
	}

	for (unsigned int i = 0; i < tab_hp.size(); i++)
	{
		if (tab_hp[i].onCreate_clock.getElapsedTime().asSeconds() >= tab_hp[i].lifeTime)
		{
			hp_destroy( i);
		}
	}
	///////////////////////////////////////////

	
		czas = zegar.getElapsedTime();
		zegar.restart();
	
}

void Engine::draw()
{	// rysowanie //
	okno->setView(*view);
	okno->clear();

	okno->draw(map);	//ziemia
	okno->draw(floor);//pod³oga

	for (unsigned int i = 0; i < wsk_gun->bullets_fired.size(); i++)//pociski
		if (!wsk_gun->bullets_fired[i].body.getGlobalBounds().intersects(gracz.body.getGlobalBounds()))
			okno->draw(wsk_gun->bullets_fired[i].body);

	for (unsigned int i = 0; i < tab_bl.size(); i++)//zw³oki zombie
	{
		bool drawing = true;
		for (unsigned int j = 4; j < 8; j++)
		{

			if (tab_bl[i].body.getGlobalBounds().intersects(tab_wall[j].getGlobalBounds()))
				drawing = false;

		}
		if (drawing)okno->draw(tab_bl[i].body);
	}

	for (unsigned int i = 0; i < tab_corps.size(); i++)//zw³oki zombie
	{
		bool drawing = true;
		for (unsigned int j = 4; j < 8; j++)
		{
			
			if (tab_corps[i].body.getGlobalBounds().intersects(tab_wall[j].getGlobalBounds()))
				drawing =false;
			
		}
		if(drawing)okno->draw(tab_corps[i].body);
	}
		for (unsigned int i = 0; i < tab_am.size(); i++)//pickup ammo
	{
		if (tab_am[i].onCreate_clock.getElapsedTime().asSeconds() < tab_am[i].lifeTime - 8.0f)
			okno->draw(tab_am[i].body);
		if (tab_am[i].onCreate_clock.getElapsedTime().asSeconds() >= tab_am[i].lifeTime - 8.0f)
		{
			if (tab_am[i].onCreate_clock.getElapsedTime().asMilliseconds() % 500 >= 0 && tab_am[i].onCreate_clock.getElapsedTime().asMilliseconds() % 500 <= 125)
			{
				// efekt migania
			}
			else okno->draw(tab_am[i].body);
		}
	}

	for (unsigned int i = 0; i < tab_hp.size(); i++)//pickup hp
	{
		if (tab_hp[i].onCreate_clock.getElapsedTime().asSeconds() < tab_hp[i].lifeTime - 8.0f)
			okno->draw(tab_hp[i].body);
		if (tab_hp[i].onCreate_clock.getElapsedTime().asSeconds() >= tab_hp[i].lifeTime - 8.0f)
		{
			if (tab_hp[i].onCreate_clock.getElapsedTime().asMilliseconds() % 500 >= 0 && tab_hp[i].onCreate_clock.getElapsedTime().asMilliseconds() % 500 <= 125)
			{
				// efekt migania
			}
			else okno->draw(tab_hp[i].body);
		}
	}

	for (unsigned int i = 4; i < tab_wall.size(); i++)//œciana
		okno->draw(tab_wall[i]);
	for (unsigned int i = 0; i < tab_z.size(); i++)//zombie
		okno->draw(tab_z[i].body);

	
	//okno->draw(room);
	okno->draw(celownik);//celownik
	okno->draw(gracz.body);//gracz
	okno->draw(wsk_gun->body);//broñ
	if (!_pause && gracz.healthPoints!=0) 
	{
		for (int i = 0; i < 5; i++)
			okno->draw(UI[i]);	//interfejs
		if (wsk_gun->magazynek <= wsk_gun->magazynekSize / 2.0f && !wsk_gun->reloading)okno->draw(UI[5]);
		if (wsk_gun->reloading)okno->draw(UI[6]);
	if(runda==3 && !hasPlayerChosenAk)
		okno->draw(note);
	okno->draw(sprint_ui);//wskaŸnik sprintu
	}
	else *image = okno->capture();
	//////////////////////////////////

	okno->display();
}

void Engine::collision()
{
	// kolizje //	

	// kolizja zombie-gracz	
	for (unsigned int i = 0; i < tab_z.size(); i++)
	{
		//if(gracz.body.getGlobalBounds().intersects(tab_z[i].body.getGlobalBounds()))
		if (Collision::PixelPerfectTest(gracz.body, tab_z[i].body))
		{
			tab_z[i].collidesWithPlayer = true;

			if (((tab_z[i].body.getPosition().y > gracz.body.getPosition().y) && gracz.body.getPosition().y > 0) || (gracz.body.getPosition().y < tab_z[i].body.getPosition().y && tab_z[i].body.getPosition().y < 0))
			{
				gracz.canMoveDown = false;
			}

			if ((gracz.body.getPosition().y > tab_z[i].body.getPosition().y && tab_z[i].body.getPosition().y > 0) || (tab_z[i].body.getPosition().y < gracz.body.getPosition().y && gracz.body.getPosition().y < 0))
			{
				gracz.canMoveUP = false;
			}

			if ((tab_z[i].body.getPosition().x > gracz.body.getPosition().x &&  gracz.body.getPosition().x > 0) || (gracz.body.getPosition().x < tab_z[i].body.getPosition().x && tab_z[i].body.getPosition().x < 0))
			{
				gracz.canMoveRight = false;
			}

			if ((gracz.body.getPosition().x > tab_z[i].body.getPosition().x && tab_z[i].body.getPosition().x > 0) || (tab_z[i].body.getPosition().x < gracz.body.getPosition().x && gracz.body.getPosition().x < 0))
			{
				gracz.canMoveLeft = false;
			}


			if (tab_z[i].playerCollisionTimer.getElapsedTime().asSeconds() >= tab_z[i].biteFrequency) {

				tab_z[i].playerCollisionTimer.restart();

				sound_bite.play();

				gracz.healthPoints--;

				if (gracz.healthPoints == 0)
				{
					menu = true;
				}
				break;
			}
		}
		else tab_z[i].collidesWithPlayer = false;
	}

	// kolizja gracz-?ciana
	if (tab_wall[4].getGlobalBounds().intersects(gracz.body.getGlobalBounds()) || tab_wall[4].getGlobalBounds().intersects(wsk_gun->body.getGlobalBounds()))
	{
		gracz.canMoveUP = false;
	}
	else
	{
		gracz.canMoveUP = true;
	}

	if (tab_wall[5].getGlobalBounds().intersects(gracz.body.getGlobalBounds()) || tab_wall[5].getGlobalBounds().intersects(wsk_gun->body.getGlobalBounds()))
	{
		gracz.canMoveDown = false;
	}
	else
	{
		gracz.canMoveDown = true;
	}

	if (tab_wall[6].getGlobalBounds().intersects(gracz.body.getGlobalBounds()) || tab_wall[6].getGlobalBounds().intersects(wsk_gun->body.getGlobalBounds()))
	{
		gracz.canMoveLeft = false;
	}
	else
	{
		gracz.canMoveLeft = true;
	}

	if (tab_wall[7].getGlobalBounds().intersects(gracz.body.getGlobalBounds()) || tab_wall[7].getGlobalBounds().intersects(wsk_gun->body.getGlobalBounds()))
	{
		gracz.canMoveRight = false;
	}
	else
	{
		gracz.canMoveRight = true;
	}



	///////////kolizja zombie pocisk

	if (!tab_z.empty() && !wsk_gun->bullets_fired.empty())
	{
		for (unsigned int i = 0; i < wsk_gun->bullets_fired.size(); i++)
		{
			for (unsigned int j = 0; j < tab_z.size(); j++)
			{
				if (wsk_gun->bullets_fired[i].body.getGlobalBounds().intersects(tab_z[j].body.getGlobalBounds()))
				{
					sound_hit.play();

					bullet_destroy( i);

					Blood krew(tekstura_bl, tab_z[j].body.getPosition());
					tab_bl.push_back(krew);

					tab_z[j].healthPoints -= wsk_gun->damage;
					tab_z[j].speed -= 5;

					if (tab_z[j].healthPoints == 0)
					{	//?œmieræ zombie
						Corps corpses(tekstura_corps, tab_z[j].body.getPosition(), tab_z[j].rotate_angle);
						tab_corps.push_back(corpses);

						if (tab_z[j].isInside)//losowanie pickup-a
						{
							Ammo_Pickup am(tekstura_ammo, tab_z[j].body.getPosition());
							
							Hp_Pickup hp(tekstura_hp, tab_z[j].body.getPosition());
							for (unsigned int i = 4; i < 8; i++) 
							{
								if (corpses.body.getGlobalBounds().intersects(tab_wall[i].getGlobalBounds())) {
									
									corpses.body.move((Vector2f(0,0) - corpses.body.getPosition())*0.3f);
								}
								if (am.body.getGlobalBounds().intersects(tab_wall[i].getGlobalBounds()))
									am.body.move((floor.getPosition() - am.body.getPosition())*0.4f);
								if (hp.body.getGlobalBounds().intersects(tab_wall[i].getGlobalBounds()))
									hp.body.move((floor.getPosition() - hp.body.getPosition())*0.4f);
							}
							switch (rand() % 10)
							{
							case 0:
								if (wsk_gun->bulletsLeft < 450 && tab_am.size() <= 2)tab_am.push_back(am);
								break;
							case 1:
								if (wsk_gun->bulletsLeft < 450 && tab_am.size() <= 2)tab_am.push_back(am);
								break;
							case 2:
								if (gracz.healthPoints + tab_hp.size() < 3 && tab_hp.size() == 0)
									tab_hp.push_back(hp);
								break;
							}
						}
						zombie_destroy( j);
						zombies_killed_in_round++;
						break;
					}
					break;
				}
			}
		}
	}

	//kolizja gracz-ammo_pickup
	for (unsigned int i = 0; i < tab_am.size(); i++)
	{
		if (gracz.body.getGlobalBounds().intersects(tab_am[i].body.getGlobalBounds()))
		{
			ammo_collect.play();

			wsk_gun->bulletsLeft += (int)wsk_gun->magazynekSize/2 *(int)runda;

			ammo_destroy( i);
		}
	}

	//kolizja gracz-hp_pickup
	for (unsigned int i = 0; i < tab_hp.size(); i++)
	{
		if (gracz.body.getGlobalBounds().intersects(tab_hp[i].body.getGlobalBounds()))
		{

			if (gracz.healthPoints + tab_hp[i].add_hp <= 5)
			{
				health_collect.play();
				gracz.healthPoints += tab_hp[i].add_hp;
				hp_destroy( i);
			}
		}
	}
	//kolizja pocisk œciana
	for (unsigned int j = 4; j < tab_wall.size() - 4; j++)
		for (unsigned int i = 0; i < wsk_gun->bullets_fired.size(); i++)
		{

			if (wsk_gun->bullets_fired[i].body.getGlobalBounds().intersects(tab_wall[j].getGlobalBounds())|| !wsk_gun->bullets_fired[i].body.getGlobalBounds().intersects(floor.getGlobalBounds()))
				bullet_destroy( i);
		}

}

void Engine::zombie_generator(vector <Zombie> &tab_z, Vector2f poz, Texture &tekstura_z, int runda, RectangleShape &target_wal)
{

	Zombie zombie(poz, tekstura_z, 50.f+rand()%(runda+1) *4, rand() % (runda)+1,target_wal);
	tab_z.push_back(zombie);

}

void Engine::interfejs()
{
	UI[0].setString("hp: " + to_string((int)gracz.healthPoints));
	UI[3].setString("ammo: " + to_string((int)wsk_gun->magazynek) + " / " + to_string((int)wsk_gun->bulletsLeft));
	UI[0].setPosition(view->getCenter().x + 1280 / 2 - 80, view->getCenter().y - 360 + 20);
	UI[3].setPosition(view->getCenter().x + 1280 / 2 - 220, view->getCenter().y + 360 - 40);
	UI[2].setString(wsk_gun->name);
	UI[2].setPosition(view->getCenter().x + 1280 / 2 - 220, view->getCenter().y + 360 - 80);
	UI[1].setString("round: " + to_string(runda));
	UI[1].setPosition(view->getCenter().x - 1280 / 2 + 10, view->getCenter().y + 360 - 40);
	UI[4].setString("zombies left to kill: " + to_string(max_zombie_per_round - zombies_killed_in_round));
	UI[4].setPosition(view->getCenter().x - 1280 / 2 + 10, view->getCenter().y - 360 + 20);
	sprint_ui.setPosition(view->getCenter().x + 1280 / 2 - 90, view->getCenter().y - 360 + 70);
	if (isSprint && tab_p[0] != gracz.body.getPosition() && sprint_ui.getSize().x > 0)
		sprint_ui.setSize(Vector2f(sprint_ui.getGlobalBounds().width - (15.0f*czas.asSeconds()), sprint_ui.getGlobalBounds().height));
	else
	{
		if (sprint_ui.getSize().x <= 15 * 5)sprint_ui.setSize(Vector2f(sprint_ui.getGlobalBounds().width + (7.5f*0.5f*czas.asSeconds()), sprint_ui.getGlobalBounds().height));
	}
	UI[5].setPosition(view->getCenter().x + 1280 / 2 - 550, view->getCenter().y + 360 - 40);
	UI[6].setPosition(view->getCenter().x + 1280 / 2 - 450, view->getCenter().y + 360 - 40);
	note.setPosition(view->getCenter().x - 620, view->getCenter().y);
}

// metody pomocnicze //
void Engine::bullet_destroy(int i)
{

	wsk_gun->bullets_fired[i] = wsk_gun->bullets_fired[wsk_gun->bullets_fired.size() - 1];
	wsk_gun->bullets_fired.pop_back();

}

void Engine::zombie_destroy(int i)
{

	tab_z[i] = tab_z[tab_z.size() - 1];
	tab_z.pop_back();

}

void Engine::blood_destroy(int i)
{

	tab_bl[i] = tab_bl[tab_bl .size() - 1];
	tab_bl.pop_back();

}

void Engine::corps_destroy(int i)
{

	tab_corps[i] = tab_corps[tab_corps.size() - 1];
	tab_corps.pop_back();

}

void Engine::ammo_destroy(int i)
{

	tab_am[i] = tab_am[tab_am.size() - 1];
	tab_am.pop_back();

}

void Engine::hp_destroy( int i)
{

	tab_hp[i] = tab_hp[tab_hp.size() - 1];
	tab_hp.pop_back();

}

void Engine::pause_screen()
{
	
	Time i = zegar.getElapsedTime();
	muzyka.pause();
	PauseScreen pauza(_pause,*okno, font);
	pauza.runPause(menu, failure, *image);
	muzyka.play();
	zegar.restart();
	czas = i;
}

bool Engine::init()
{
	okno->setMouseCursorVisible(false);
	Texture SF;
	SF.loadFromFile("data/SFML-logo-big.png");
	Sprite logo;
	logo.setTexture(SF);
	logo.setPosition(Vector2f(50, 600));
	logo.setScale(Vector2f(0.2f, 0.2f));
	if (!font.loadFromFile("data/font_UI.ttf"))
	{
		MessageBox(NULL, "Font not found! Chceck data folder!", "ERROR", NULL);
		return false;
	}
	
	Text loading;
	loading.setFont(font);
	loading.setCharacterSize(50);
	loading.setString("loading...");
	loading.setOrigin(Vector2f(loading.getGlobalBounds().width / 2.0f, loading.getGlobalBounds().height / 2.0f));
	loading.setPosition(Vector2f(okno->getView().getCenter()));

	okno->clear();
	okno->draw(logo);
	okno->draw(loading);
	okno->display();

	if (!tekstura_z.loadFromFile("data/zombie_after_attack_rect.png"))
	{
		MessageBox(NULL, "Missing resources! Chceck data folder!", "ERROR", NULL);
		return false;
	}
	if (!tekstura_cel.loadFromFile("data/cel.png"))
	{
		MessageBox(NULL, "Missing resources! Chceck data folder!", "ERROR", NULL);
		return false;
	}
	
	tekstura.loadFromFile("data/ground.png");
	tekstura_bl.loadFromFile("data/blood.png");
	tekstura_floor.loadFromFile("data/floor.png");
	tekstura_corps.loadFromFile("data/corps.png");
	tekstura_ammo.loadFromFile("data/ammo_pickup.png");
	tekstura_hp.loadFromFile("data/hp_pickup.png");
	tekstura_wall.loadFromFile("data/wall.jpg");
	tekstura_wall.setRepeated(true);
	buffer_z.loadFromFile("data/hit.wav");



	sound_hit.setBuffer(buffer_z);
	zombie_bite.loadFromFile("data/zombie_bite.wav");
	sound_bite.setBuffer(zombie_bite);
	reload_wav.loadFromFile("data/long_reload.wav");
	ammo_out.loadFromFile("data/out_of_ammo.wav");
	health_wav.loadFromFile("data/health.wav");
	ammo_wav.loadFromFile("data/ammo.wav");
	health_collect.setBuffer(health_wav);
	ammo_collect.setBuffer(ammo_wav);

	sound_reload.setBuffer(reload_wav);
	sound_ammo_out.setBuffer(ammo_out);
	muzyka.openFromFile("data/COD4_theme.ogg");
	muzyka.setLoop(true);
	muzyka.play();
	font.loadFromFile("data/font_UI.ttf");
	for (int i = 0; i < 5; i++)
	{
		UI[i].setFont(font);
		UI[i].setCharacterSize(25);
		UI[i].setColor(Color(138, 7, 7));
	}
	UI[5].setFont(font);
	UI[5].setCharacterSize(20);
	UI[5].setColor(Color(138, 7, 7));
	UI[6].setFont(font);
	UI[6].setCharacterSize(20);
	UI[6].setColor(Color(138, 7, 7));
	UI[5].setString("press 'r' to reload");
	UI[6].setString("reloading...");
	note.setFont(font);
	note.setCharacterSize(19);
	note.setColor(Color(138, 7, 7));
	note.setString("you have unlocked ak 47 \n press '2' to change your weapon");
	celownik.setScale(0.045f, 0.045f);
	celownik.setTexture(tekstura_cel);
	celownik.setOrigin(celownik.getLocalBounds().width / 2.0f, celownik.getLocalBounds().height / 2.0f);
	sprint_ui.setSize(Vector2f(15 * 5, 15));
	sprint_ui.setFillColor(Color(138, 7, 7));
	map.setTexture(tekstura);
	tekstura.setRepeated(true);
	map.setTextureRect(IntRect(0, 0, 10000, 10000));
	map.setOrigin(5000, 5000);
	map.setPosition(0, 0);
	floor.setPosition(-515, -500);
	floor.setTexture(tekstura_floor);
	tekstura_floor.setRepeated(true);
	floor.setTextureRect(IntRect(0, 0, 1000, 1000));
	entrance.loadFromFile("data/floor_entrance.png");
	wall_t.loadFromFile("data/wall.png");
	

	for (int i = 0; i < 12; i++)
	{
		RectangleShape wall;
		//wall.setFillColor(Color(7, 138, 7, 100));


		if (i == 0)
		{
			wall.setPosition(-1000, -1000);
			//wall.setFillColor(Color::White);
		}
		else if (i == 1) {
			wall.setPosition(-1000, 1000);
			//wall.setFillColor(Color::Red);
		}
		else if (i == 2) {
			wall.setPosition(-1100, -1000);
			//wall.setFillColor(Color::Cyan);
		}
		else if (i == 3) {
			//wall.setOrigin(100, 0);
			wall.setPosition(1000, -1000);
			//wall.setFillColor(Color::Blue);
		}
		if (i == 0 || i == 1)wall.setSize(Vector2f(2000, 100));
		else if (i == 2 || i == 3)wall.setSize(Vector2f(100, 2100));
		if (i == 4 || i == 5)wall.setSize(Vector2f(1020, 20));
		else if (i == 6 || i == 7)wall.setSize(Vector2f(20, 1020));
		if (i == 4)

		{
			wall.setOrigin(Vector2f(wall.getGlobalBounds().width / 2.0f, wall.getGlobalBounds().height / 2.0f));
			wall.setPosition(0, -500);
			wall.setTexture(&wall_t);
			wall.setTextureRect(IntRect(0,0,wall.getSize().x, wall.getSize().y));
			
		}
		else if (i == 5)
		{
			wall.setOrigin(Vector2f(wall.getGlobalBounds().width / 2.0f, wall.getGlobalBounds().height / 2.0f));
			wall.setPosition(-20, 500);
			wall.setTexture(&wall_t);
			wall.setTextureRect(IntRect(0, 0, wall.getSize().x, wall.getSize().y));
		}
		else if (i == 6)
		{
			wall.setOrigin(Vector2f(wall.getGlobalBounds().width / 2.0f, wall.getGlobalBounds().height / 2.0f));
			wall.setPosition(-520, 0);
			wall.setTexture(&wall_t);
			wall.setTextureRect(IntRect(0, 0, wall.getSize().x, wall.getSize().y));
		}
		else if (i == 7)
		{
			wall.setOrigin(Vector2f(wall.getGlobalBounds().width / 2.0f, wall.getGlobalBounds().height / 2.0f));
			wall.setPosition(500, 0);
			wall.setTexture(&wall_t);
			wall.setTextureRect(IntRect(0, 0, wall.getSize().x, wall.getSize().y));
		}

		if (i == 8 || i == 9)wall.setSize(Vector2f(100, 20));
		else if (i == 10 || i == 11)wall.setSize(Vector2f(20, 100));
		if (i == 8)
		{
			wall.setOrigin(Vector2f(wall.getGlobalBounds().width / 2.0f, wall.getGlobalBounds().height / 2.0f));
			wall.setPosition(0, -500);
			wall.setTexture(&entrance);
			wall.setTextureRect(IntRect(0, 0, wall.getSize().x, wall.getSize().y));
		}
		else if (i == 9)
		{
			wall.setOrigin(Vector2f(wall.getGlobalBounds().width / 2.0f, wall.getGlobalBounds().height / 2.0f));
			wall.setPosition(-20, 500);
			wall.setTexture(&entrance);
			wall.setTextureRect(IntRect(0, 0, wall.getSize().x, wall.getSize().y));
		}
		else if (i == 10)
		{
			wall.setOrigin(Vector2f(wall.getGlobalBounds().width / 2.0f, wall.getGlobalBounds().height / 2.0f));
			wall.setPosition(-520, 0);
			wall.setTexture(&entrance);
			wall.setTextureRect(IntRect(0, 0, wall.getSize().x, wall.getSize().y));
		}
		else if (i == 11)
		{
			wall.setOrigin(Vector2f(wall.getGlobalBounds().width / 2.0f, wall.getGlobalBounds().height / 2.0f));
			wall.setPosition(500, 0);
			wall.setTexture(&entrance);
			wall.setTextureRect(IntRect(0, 0, wall.getSize().x, wall.getSize().y));
		}



		tab_wall.push_back(wall);

	}

	gracz.body.setPosition(0, 0);
	zombie_generator_timer.restart();
	okno->setMouseCursorVisible(false);
	Sleep(1000);
	return true;
}