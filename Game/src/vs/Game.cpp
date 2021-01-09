// Game.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include "Castle.h"
#include "MagicTower.h"
#include "MagicTower.h"
#include"SimpleTower.h"
#include "Magic.h"
#include "Cell.h"
#include <SFML\Graphics.hpp>
#include "GrafCell.h"
#include "GrafMap.h"
#include <vector>
#include "Map.h"
#include"GraphObject.h"
#include "ObjectOnMap.h"
#include "Button.h"
using namespace sf;

void load_map_tex(Texture* T) {
	T[0].loadFromFile("img/Forest.png");
	T[1].loadFromFile("img/Grass.png");
	T[2].loadFromFile("img/Road.png");
	T[3].loadFromFile("img/Castle.png");
	T[4].loadFromFile("img/Den.png");
	T[5].loadFromFile("img/Tow_S.png");
	T[6].loadFromFile("img/Tow_M.png");
	T[7].loadFromFile("img/Tow_St.png");
	T[8] .loadFromFile("img/Trap.png");
	T[9].loadFromFile("img/Enemy1.png");
	T[10].loadFromFile("img/Enemy2.png");
	T[11].loadFromFile("img/Enemy3.png");
}

using namespace game;
int main(){
	int cont;
	bool mt = false;
	Texture MT[12];
	load_map_tex(MT);
	Map m; GrafMap gm; MainScene SCENE;
	m.Map::init("../files/map.txt");
	std::cout << "Eneter 0 to start new game, enter 1 to continue old";
	std::cin >> cont;
	if (cont == 0) {
		m.load(SCENE, "../files/buildings.txt");
	}
	else m.load(SCENE, "../files/buildings_saved.txt");
	Castle CASTLE = *m.castle; SCENE.castle = m.castle;
	Den DEN_1 = *m.den[0];
	Den DEN_2 = *m.den[1];
	GraphObject G_CASTLE(&MT[3], CASTLE);
	GraphObject G_DEN_1(&MT[4], DEN_1);
	GraphObject G_DEN_2(&MT[4], DEN_2);
	Font font;
	font.loadFromFile("ArialRegular.ttf");
	G_CASTLE.tex.setPosition(CASTLE.getX() - 102, CASTLE.getY() - 102);
	G_CASTLE.tex.setScale(0.1, 0.1);
	G_CASTLE.hp.setFont(font);
	G_CASTLE.hp.setPosition(G_CASTLE.obj.getX(), G_CASTLE.obj.getY() - 110);
	G_CASTLE.hp.setCharacterSize(30);
	G_CASTLE.hp.setFillColor(sf::Color::Black);
	int h = 0;
	G_DEN_1.tex.setPosition(DEN_1.getX() - 102, DEN_1.getY() - 102);
	G_DEN_2.tex.setPosition(DEN_2.getX() - 153, DEN_2.getY() - 153);
	G_DEN_1.tex.setScale(0.1, 0.1);
	G_DEN_2.tex.setScale(0.1, 0.1);
	Clock clock;
	int o_t = std::clock(), holder = -1000;
	gm.init(SCENE, m, MT);//инициализация графической карты, башен и ловушек из файла
	double curtime, lasttime=o_t/1000;
	std::vector<Button*> mt_buttons, t_buttons;
	
	std::vector<Button*> strategies;
	string names[5] = { "Location", "Location\nto castle","Health \n  up","Health \n down","Speed \n  up" };
	for(int i = 0;i<5;i++)
		strategies.push_back(new Button(names[i], 0, 900 - 80*(i+2), font));
	Button trap("Trap", 539, 820, font);
	mt_buttons.push_back(new Button("Simple", 0, 820,font));
	t_buttons.push_back(new Button("Simple", 837, 820, font));
	mt_buttons.push_back(new Button("Middle", 121, 820, font));
	t_buttons.push_back(new Button("Middle", 958, 820, font));
	mt_buttons.push_back(new Button("Strong", 242, 820, font));
	t_buttons.push_back(new Button("Strong", 1079, 820, font));
	bool mt_chosen = false, t_chosen = false, trap_chosen = false;
	SimpleTower::TypeOfLevel level;
	SimpleTower::TypeOfStrategy strategy;
	int traptime=0;
	bool strat_chosen = false;
	//MagicTower
	RenderWindow Win(VideoMode(1200, 900), "TOWER DEFENSE");
	Text won;
	won.setFont(font);
	won.setPosition(350, 300);
	won.setCharacterSize(100);
	won.setFillColor(sf::Color(231, 84, 128));
	won.setString("ITS A TRAP!");
	while (Win.isOpen()) {
		o_t = std::clock();
		curtime = o_t / 1000;
		Event event;
		Vector2i mpos = Mouse::getPosition(Win);
		while (Win.pollEvent(event)) {
			if (event.type == Event::Closed)//закрытие окна
				Win.close();
			if (event.type == Event::MouseButtonPressed)//нажатие кнопки
				if (event.key.code == Mouse::Left)
					for (auto it : mt_buttons) {
						if (it->is_being_pressed(mpos.x, mpos.y)) {
							if (mt_chosen)
								for (auto it1 : mt_buttons)
									if (it1->isPressed())
										it1->press();
							mt_chosen = false;
							if (t_chosen)
								for (auto it1 : t_buttons)
									if (it1->isPressed())
										it1->press();
							t_chosen = false;
							if (trap_chosen)
								trap.press();
							trap_chosen = false;
							it->press();
							for (auto iter : strategies) {
								Vector2f pos = it->getp();
								iter->setx(pos.x);
							}
							mt_chosen = true;
							

						}
					}
			if (event.type == Event::MouseButtonPressed)//нажатие кнопки
				if (event.key.code == Mouse::Left)
					for (auto it : t_buttons) {
						if (it->is_being_pressed(mpos.x, mpos.y)) {
							if (mt_chosen)
								for (auto it1 : mt_buttons)
									if (it1->isPressed())
										it1->press();
							mt_chosen = false;
							if (t_chosen)
								for (auto it1 : t_buttons)
									if (it1->isPressed())
										it1->press();
							t_chosen = false;
							if (trap_chosen)
								trap.press();
							trap_chosen = false;

							it->press();
							for (auto iter : strategies) {
								Vector2f pos = it->getp();
								iter->setx(pos.x);
							}
							t_chosen = true;
							
						}
					}
			if (event.type == Event::MouseButtonPressed)//нажатие кнопки со стратегией магическая
				if (event.key.code == Mouse::Left)
					if (mt_chosen) {
						for (auto it : strategies) {
							if (it->is_being_pressed(mpos.x, mpos.y)) {
								for (auto iterat : mt_buttons)
									if (iterat->isPressed())
										level = iterat->type;

								mt_chosen = false;
								for (auto itera : strategies)
									if (itera->isPressed())
										itera->press();
								strategy = it->strat;
								strat_chosen = true;
							}
						}
						mt = true;
					}
			if (event.type == Event::MouseButtonPressed)//нажатие кнопки со стратегией обычная
				if (event.key.code == Mouse::Left)
					if (t_chosen) {
						for (auto it : strategies) {
							if (it->is_being_pressed(mpos.x, mpos.y)) {
								for (auto iterat : t_buttons)
									if (iterat->isPressed())
										level = iterat->type;

								t_chosen = false;
								for (auto itera : strategies)
									if (itera->isPressed())
										itera->press();
								strategy = it->strat;
								strat_chosen = true;
							}
						}
						mt = false;
					}
			if (event.type == Event::MouseButtonPressed)//нажатие кнопки с ловушкой
				if (event.key.code == Mouse::Left) {
					if (trap.is_being_pressed(mpos.x, mpos.y)) {
						trap.press();
						trap_chosen = true;
						if (mt_chosen)
							for (auto it1 : mt_buttons)
								if (it1->isPressed())
									it1->press();
						mt_chosen = false;
						if (t_chosen)
							for (auto it1 : t_buttons)
								if (it1->isPressed())
									it1->press();
						t_chosen = false;
						strat_chosen = false;
						mt = false;

					}
				}
			if (event.type == Event::MouseButtonPressed)//нажатие на место
				if (event.key.code == Mouse::Right) {
					if (strat_chosen && !mt) {
						//mpos.x,mpos.y,level,strategy
						Cell* a = m.findCell(mpos.x, mpos.y);
						if (a->type == Cell::TypeOfCell::LEA && a->state != Cell::State::N_B) {
							if (m.addtower(level, strategy, mpos.x, mpos.y)) {
								gm.putNewTower(m, MT);
								a->state = Cell::State::N_B;
							}
							strat_chosen = false;
						}

					}
					if (strat_chosen && mt) {
						//mpos.x,mpos.y,level,strategy
						Cell* a =m.findCell(mpos.x, mpos.y);
						int mag;
						mag = rand() % (2 - 0 + 1) + 0;
						if (a->type == Cell::TypeOfCell::LEA && a->state != Cell::State::N_B) {
							if (mag == 0) {
								if (m.addMagicTower(level, strategy, Magic::TypeOfMagic::POISONING, mpos.x, mpos.y)) {
									gm.putNewTower(m, MT);
									a->state = Cell::State::N_B;
								}
							}
							if (mag == 1) {
								if (m.addMagicTower(level, strategy, Magic::TypeOfMagic::WEAKNESS, mpos.x, mpos.y)) {
									gm.putNewTower(m, MT);
									a->state = Cell::State::N_B;
								}
							}
							if (mag == 2) if (m.addMagicTower(level, strategy, Magic::TypeOfMagic::SLOWDOWN, mpos.x, mpos.y)) {
								gm.putNewTower(m, MT);
								a->state = Cell::State::N_B;
							}
							strat_chosen = false;
						}
					}
					if (trap_chosen) {
						//mpos.x,mpos.y
						Cell* a = m.findCell(mpos.x, mpos.y);
						int mag;
						mag = rand() % (2 - 0 + 1) + 0;
						if (a->type == Cell::TypeOfCell::ROAD && a->state != Cell::State::N_B) {
							if (mag == 0) if (m.addtrap(Magic::TypeOfMagic::POISONING, mpos.x, mpos.y)) {
								gm.putNewTrap(m, MT);
								a->state = Cell::State::N_B;
								traptime = curtime;
							}
							if (mag == 1) if (m.addtrap(Magic::TypeOfMagic::WEAKNESS, mpos.x, mpos.y)) {
								gm.putNewTrap(m, MT);
								a->state = Cell::State::N_B;
								traptime = curtime;
							}
							if (mag == 2) if (m.addtrap(Magic::TypeOfMagic::SLOWDOWN, mpos.x, mpos.y)) {
								gm.putNewTrap(m, MT);
								a->state = Cell::State::N_B;
								traptime = curtime;
							}
							
							trap_chosen = false;
						}
					}
				}
		}
		
			for (int i = 0; i < 2; i++) {
				m.den[i]->putNewEnemy(SCENE, curtime);
				gm.putNewEnemy(SCENE, MT);
			}
			m.moveAll(SCENE, 0.05);
			gm.moveAll(SCENE, 0.01, m);
			m.makeShot(SCENE, o_t/1000);
			m.makeTrapShot(SCENE, curtime);
			Win.clear(Color::White);
			gm.draw(Win);
			h = m.castle->getcurhealth();
			G_CASTLE.hp.setString(std::to_string(h));
			G_CASTLE.draw(Win);
			G_DEN_1.draw(Win);
			G_DEN_2.draw(Win);
			for (auto it : mt_buttons) {
				it->draw(Win);
			}
			for (auto it : t_buttons) {
				it->draw(Win);
			}
			if (mt_chosen || t_chosen)
				for (auto it : strategies)
					it->draw(Win);
			trap.draw(Win);
			if (gm.amount == 20 && m.castle->getcurhealth() != 0) {
				won.setCharacterSize(100);
				won.setFillColor(sf::Color(231, 84, 128));
				won.setString("You won!");
				Win.draw(won);
			}
			if (m.castle->getcurhealth() == 0) {
				won.setCharacterSize(100);
				won.setFillColor(sf::Color(0, 0, 0));
				won.setString("Enemies won :(");
				Win.draw(won);
			}
			if (traptime + 5 > curtime) {
				Win.draw(won);
			}
			Win.display();
			lasttime = curtime;
		}
	m.save(SCENE, "../files/buildings_saved.txt");
	return 0;
}
	

