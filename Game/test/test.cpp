#include "pch.h"
#include "..\GameLib2\SimpleTower.h"
#include "..\GameLib2\Enemy.h"
#include "..\GameLib2\MagicTrap.h"
#include "..\GameLib2\MagicTower.h"
#include "..\GameLib2\Den.h"
#include "..\GameLib2\Castle.h"
#include "..\GameLib2\MainScene.h"
#include "..\GameLib2\ObjectOnMap.h"
#include<vector>


using namespace game;

TEST(CASTLE, CastleMethods) {//constructor, buy, damage
	ASSERT_ANY_THROW(Castle C(-2, 100, 100));
	Castle CAST;
	CAST.acceptDamage(5);
	ASSERT_EQ(95, CAST.getcurhealth());
	SimpleTower TOW;
	CAST.buynewTower(TOW.getCost());
	ASSERT_EQ(95, CAST.getpurse());
	MagicTower TOW2(Magic::TypeOfMagic::POISONING);
	CAST.buynewTower(TOW2.getCost());
	ASSERT_EQ(85, CAST.getpurse());
	MagicTrap TR(Magic::TypeOfMagic::POISONING);
	CAST.buynewTrap(TR.getCost());
	ASSERT_EQ(65, CAST.getpurse());

}
TEST(DEN, DenMethods) {//contructor,enemy constructor, put enemy
	ASSERT_ANY_THROW(Den D(-1));
	Enemy Enem1(Enemy::TypeOfLevel::Simple, 1), Enem2(Enemy::TypeOfLevel::Strong, 3);
	Den DEN(2);
	std::vector<Enemy> enem;
	enem.push_back(Enem1);
	enem.push_back(Enem2);
	DEN.setEnemies(enem);
	DEN.setAmount(2);
	MainScene m;
	DEN.putNewEnemy(m, 0);
	std::vector<Enemy*>::iterator i = m.enemies.begin();
	std::vector<Enemy*>::iterator j = m.enemies.end();
	int k = 0;
	while (i != j) {
		k++;
		i++;
	}
	ASSERT_EQ(0, k);
	DEN.putNewEnemy(m, 2);
	std::vector<Enemy*>::iterator ii = m.enemies.begin();
	std::vector<Enemy*>::iterator jj = m.enemies.end();
	k = 0;
	while (ii != jj) {
		k++;
		ii++;
	}
	ASSERT_EQ(1, k);
	DEN.putNewEnemy(m, 5);
	std::vector<Enemy*>::iterator iii = m.enemies.begin();
	std::vector<Enemy*>::iterator jjj = m.enemies.end();
	k = 0;
	while (iii != jjj) {
		k++;
		iii++;
	}
	ASSERT_EQ(2, k);
}
TEST(TOWER, TowerMethods) {//strategy, magic, damage
	std::vector<Enemy*> enem;
	Enemy Enem1(Enemy::TypeOfLevel::Simple, 1), Enem2(Enemy::TypeOfLevel::Strong, 3);
	Enem1.setX(20); Enem1.setY(10);
	enem.push_back(&Enem1);
	enem.push_back(&Enem2);
	MainScene m;
	m.enemies = enem;
	Castle CAST(100, 100, 100, 0, 0);
	m.castle = &CAST;
	SimpleTower TOW;
	TOW.addDamage(Enem1, 1);
	ASSERT_EQ(10, Enem1.getHp());
	TOW.addDamage(Enem1, 5);
	ASSERT_EQ(9, Enem1.getHp());
	ASSERT_EQ(true, &Enem2 == *TOW.findCloseEnemy(m));
	ASSERT_EQ(true, &Enem2 == *TOW.findCloseEnemyToCastle(m));
	Enem1.setX(0); Enem1.setY(0);
	ASSERT_EQ(true, &Enem2 == *TOW.findHealthUpEnemy(m));
	ASSERT_EQ(true, &Enem1 == *TOW.findHealthDownEnemy(m));
	ASSERT_EQ(true, &Enem2 == *TOW.findSpeedUpEnemy(m));
	MagicTower TOW2(Magic::TypeOfMagic::POISONING);
	TOW2.addDamage(Enem2, 2);
	ASSERT_EQ(24.8, Enem2.getHp());
	Magic M(10, Magic::TypeOfMagic::POISONING);
	Magic N = **(Enem2.getVecMagic().begin());
	ASSERT_EQ(true, M.getType() == N.getType());
}
