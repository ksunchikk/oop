#pragma once
#include <vector>
#include "GrafCell.h"
#include "GraphObject.h"
#include "MainScene.h"
#include"Map.h"
using namespace std;
namespace game {
	class GrafMap
	{
	public:
		vector<vector<GrafCell>> cells;
		vector<GraphObject*> towers;
		vector<GraphObject*> traps;
		vector<GraphObject*> enemies;
		int amount =0;

		void init(MainScene& c, Map& m, Texture* MT) {
			std::vector<vector<Cell*>>::iterator c_b = m.cells.begin();
			for (int i = 0; i < 30; i++) {
				vector<Cell* >::iterator cc_b = (*c_b).begin();
				vector<GrafCell> gc;
				for (int j = 0; j < 40; j++) {
					if ((*cc_b)->Cell::type == Cell::TypeOfCell::FOREST) {
						gc.push_back(*(new GrafCell(&MT[0], **cc_b)));
					}
					if ((*cc_b)->Cell::type == Cell::TypeOfCell::LEA) {
						gc.push_back(*(new GrafCell(&MT[1], **cc_b)));
					}
					if ((*cc_b)->Cell::type == Cell::TypeOfCell::ROAD) {
						gc.push_back(*(new GrafCell(&MT[2], **cc_b)));
					}
					cc_b++;
				}
				cells.push_back(gc);
				c_b++;
			}
			std::vector<SimpleTower*>::iterator tow_b = m.towers.begin();
			std::vector<SimpleTower*>::iterator tow_e = m.towers.end();
			while (tow_b != tow_e) {
				if ((*tow_b)->getLevel() == SimpleTower::TypeOfLevel::Simple) {
					towers.push_back(new GraphObject(&MT[5], **tow_b));
					(**(towers.end() - 1)).tex.setScale(0.05, 0.05);
					(**(towers.end() - 1)).tex.setPosition((**tow_b).getX() - 51, (**tow_b).getY() - 51);
				}
				if ((*tow_b)->getLevel() == SimpleTower::TypeOfLevel::Middle) {
					towers.push_back(new GraphObject(&MT[6], **tow_b));
					(**(towers.end() - 1)).tex.setScale(0.05, 0.05);
					(**(towers.end() - 1)).tex.setPosition((**tow_b).getX() - 51, (**tow_b).getY() - 51);
				}
				if ((*tow_b)->getLevel() == SimpleTower::TypeOfLevel::Strong) {
					towers.push_back(new GraphObject(&MT[7], **tow_b));
					(**(towers.end() - 1)).tex.setScale(0.05, 0.05);
					(**(towers.end() - 1)).tex.setPosition((**tow_b).getX() - 51, (**tow_b).getY() - 51);
				}
				tow_b++;
			}
			std::vector<MagicTrap*>::iterator tr_b = m.traps.begin();
			std::vector<MagicTrap*>::iterator tr_e = m.traps.end();
			while (tr_b != tr_e) {
				traps.push_back(new GraphObject(&MT[8], **tow_b));
				(**(traps.end() - 1)).tex.setScale(0.05, 0.05);
				(**(traps.end() - 1)).tex.setPosition((**tow_b).getX() - 51, (**tow_b).getY() - 51);
				tow_b++;
			}
			std::vector<Enemy*>::iterator e_b = c.enemies.begin();
			std::vector<Enemy*>::iterator e_e = c.enemies.end();
			while (e_b != e_e) {
				Enemy::TypeOfLevel tow = (*e_b)->getTypeOfLevel();
				if (tow == Enemy::TypeOfLevel::Simple) {
					enemies.push_back(new GraphObject(&MT[9], **e_b));
					(*(--enemies.end()))->tex.setScale(0.05, 0.05);
					(*(--enemies.end()))->tex.setPosition((**e_b).getX() - 40, (**e_b).getY() - 72);
				}
				if (tow == Enemy::TypeOfLevel::Middle) {
					enemies.push_back(new GraphObject(&MT[10], **e_b));
					(*(--enemies.end()))->tex.setScale(0.05, 0.05);
					(*(--enemies.end()))->tex.setPosition((**e_b).getX() - 40, (**e_b).getY() - 72);
				}
				if (tow == Enemy::TypeOfLevel::Strong) {
					enemies.push_back(new GraphObject(&MT[11], **e_b));
					(*(--enemies.end()))->tex.setScale(0.05, 0.05);
					(*(--enemies.end()))->tex.setPosition((**e_b).getX() - 40, (**e_b).getY() - 72);
				}
				e_b++;
			}

		}
		void putNewTower(Map& m, Texture* MT) {
			SimpleTower* ptr = *((m.towers.end()) - 1);
			if (ptr->getLevel() == SimpleTower::TypeOfLevel::Simple) towers.push_back(new GraphObject(&MT[5], *ptr));
			if (ptr->getLevel() == SimpleTower::TypeOfLevel::Middle) towers.push_back(new GraphObject(&MT[6], *ptr));
			if (ptr->getLevel() == SimpleTower::TypeOfLevel::Strong) towers.push_back(new GraphObject(&MT[7], *ptr));
			(**(towers.end() - 1)).tex.setScale(0.05, 0.05);
			(**(towers.end() - 1)).tex.setPosition(ptr->getX()-66, ptr->getY() - 66);
			if (ptr->getMagic() != nullptr) {
				(**(towers.end() - 1)).tex.setColor(Color(231, 84, 128));
			}
		}
		void putNewTrap(Map& m, Texture* MT) {
			MagicTrap* ptr = *((m.traps.end()) - 1);
			 traps.push_back(new GraphObject(&MT[8], *ptr));
			(**(traps.end() - 1)).tex.setScale(0.05, 0.05);
			(**(traps.end() - 1)).tex.setPosition(ptr->getX() - 66, ptr->getY() - 66);
		}
		void draw(RenderWindow& Win) {
			Font font;
			font.loadFromFile("ArialRegular.ttf");
			vector<vector<GrafCell >>::iterator c = cells.begin();
			for (int i = 0; i < 30; i++) {
				vector<GrafCell>::iterator gc = (*c).begin();
				for (int j = 0; j < 40; j++) {
					(*gc).draw(Win);
					gc++;
				}
				c++;
			}
			std::vector<GraphObject*>::iterator tow_b = towers.begin();
			std::vector<GraphObject*>::iterator tow_e = towers.end();
			while (tow_b != tow_e) {
				(**tow_b).draw(Win);
				tow_b++;
			}
			std::vector<GraphObject*>::iterator tr_b = traps.begin();
			std::vector<GraphObject*>::iterator tr_e = traps.end();
			while (tr_b != tr_e) {
				(**tr_b).draw(Win);
				tr_b++;
			}
			std::vector<GraphObject*>::iterator e_b = enemies.begin();
			std::vector<GraphObject*>::iterator e_e = enemies.end();
			while (e_b != e_e) {
				(**e_b).hp.setFont(font);
				(**e_b).hp.setPosition((*e_b)->obj.getX(), (*e_b)->obj.getY()-55);
				(**e_b).hp.setCharacterSize(20);
				(**e_b).hp.setFillColor(sf::Color::Red);
				Enemy* ptr = reinterpret_cast<Enemy*>(&(**e_b).obj);
				int h = ptr->getHp();
				(**e_b).hp.setString(std::to_string(h));
				(**e_b).draw(Win);
				e_b++;
			}
		}
		void putNewEnemy(MainScene& s, Texture* MT) {
			int am = 0;
			std::vector<GraphObject*>::iterator e_b = enemies.begin();
			std::vector<GraphObject*>::iterator e_e = enemies.end();
			while (e_b != e_e) {
				am++;
				e_b++;
			}
			int am2 = 0;
			std::vector<Enemy*>::iterator ee_b = s.enemies.begin();
			std::vector<Enemy*>::iterator ee_e = s.enemies.end();
			while (ee_b != ee_e) {
				am2++;
				ee_b++;
			}
			if (am < am2) {
				std::vector<Enemy*>::iterator eee_b = s.enemies.begin();
				std::vector<Enemy*>::iterator eee_e = s.enemies.end();
				for (int i = 0; i < am; i++) {
					eee_b++;
				}
				while (eee_b != eee_e) {
					Enemy::TypeOfLevel tow = (*eee_b)->getTypeOfLevel();
					if (tow == Enemy::TypeOfLevel::Simple) {
						enemies.push_back(new GraphObject(&MT[9], **eee_b));
						(*(--enemies.end()))->tex.setScale(0.05, 0.05);
						(*(--enemies.end()))->tex.setPosition((**eee_b).getX()-40, (**eee_b).getY() - 72);
					}
					if (tow == Enemy::TypeOfLevel::Middle) {
						enemies.push_back(new GraphObject(&MT[10], **eee_b));
						(*(--enemies.end()))->tex.setScale(0.05, 0.05);
						(*(--enemies.end()))->tex.setPosition((**eee_b).getX() - 40, (**eee_b).getY() - 72);
					}
					if (tow == Enemy::TypeOfLevel::Strong) {
						enemies.push_back(new GraphObject(&MT[11], **eee_b));
						(*(--enemies.end()))->tex.setScale(0.05, 0.05);
						(*(--enemies.end()))->tex.setPosition((**eee_b).getX() - 40, (**eee_b).getY() - 72);

					}
					eee_b++;
				}
			}

		}
		void moveAll(MainScene& m, double time, Map& map) {
			std::vector<Enemy*>::iterator j = m.enemies.begin();
			for (std::vector<GraphObject*>::iterator i = enemies.begin(); i != enemies.end(); i++) {
				(**i).tex.setPosition((**i).obj.getX() - 40, (**i).obj.getY() - 72);
				ObjectOnMap a = *(new ObjectOnMap((**i).obj));
				Enemy* ptr = reinterpret_cast<Enemy*>(&(**i).obj);
				ptr->updateEnemyWithMagic(time);
				if (ptr && ptr->getVecMagic().size() != 0) {
					(**i).tex.setColor(Color(231, 84, 128));
				}
				else{ (**i).tex.setColor(Color(255, 255, 255)); }
				
			}
			for (std::vector<GraphObject*>::iterator i = enemies.begin(); i != enemies.end(); i++) {
				Enemy* ptr = reinterpret_cast<Enemy*>(&(**i).obj);
				if (ptr->getHp() == 0) {
					enemies.erase(i);
					m.enemies.erase(j);
					m.castle->acceptCost(ptr->getCost());
					amount += 1;
					break;
					
				}
				Cell* a = map.findCell(m.castle->getX(), m.castle->getY());
				Cell* b = map.findCell(ptr->getX(), ptr->getY());
				if ((a->getX() == b->getX()) && (a->getY() == b->getY())) {
					m.castle->acceptDamage(ptr->getCost());
					enemies.erase(i);
					m.enemies.erase(j);
					amount += 1;
					break;
				}
				j++;
			}
		}
	};
}

