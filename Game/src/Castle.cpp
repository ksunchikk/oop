

#include "Castle.h"
#include<iostream>
namespace game {
	Castle::Castle(int nPurse, double nCur, int maxHealth, bool nAlive, double n_x, double n_y, std::string n_name): ObjectOnMap(Type::CASTLE,n_x,n_y) {
		if (nPurse < 0) {
			throw std::runtime_error("Wrong data! Purse info error!");
		}
		purse = nPurse;
		if (0>maxHealth) {
			throw std::runtime_error("Wrong data! MaxHealth info error!");
		}
		maxhealth = maxHealth;
		if (nCur < 0 || nCur>maxHealth) {
			throw std::runtime_error("Wrong data! CurHealth info error!");
		}
		curhealth = nCur;
		alive = nAlive;
	}
	Castle::Castle(const Castle& n_castle): alive(n_castle.alive),purse(n_castle.purse),maxhealth(n_castle.maxhealth),curhealth(n_castle.curhealth){
		x=n_castle.x;
		y = n_castle.y;
		Otype = n_castle.Otype;
	}
	Castle::Castle(Castle&& n_castle): alive(n_castle.alive), purse(n_castle.purse), maxhealth(n_castle.maxhealth), curhealth(n_castle.curhealth) {
		x = n_castle.x;
		y = n_castle.y;
		Otype = n_castle.Otype;
	}
	void Castle::setAlive(bool n_alive) {
		alive = n_alive;
	}
	void Castle::setPurse(int n_purse) {
		if (n_purse < 0) {
			throw std::runtime_error("Wrong data! Purse info error!");
		}
		purse = n_purse;
	}
	void Castle::setCurHealth(double n_cur) {
		if (n_cur < 0 || n_cur>maxhealth) {
			throw std::runtime_error("Wrong data! CurHealth info error!");
		}
		curhealth = n_cur;
	}
	void Castle::setMaxHealth(int n_mhealth) {
		if (0 > n_mhealth) {
			throw std::runtime_error("Wrong data! MaxHealth info error!");
		}
		maxhealth = n_mhealth;
	}
	void Castle::acceptDamage(double damagefrom) {
		if ((curhealth-damagefrom) <= 0) {
			curhealth = 0;
		}
		else curhealth -= damagefrom;
	}
	void Castle::acceptCost(int cost) {
		if ((purse + cost) < 0) throw std::runtime_error("Invalid cost!");
		purse += cost;
	}
void Castle::buynewTrap(int n_cost) {
	purse -= n_cost;
}
void Castle::buynewTower(int n_cost) {
	purse -= n_cost;
}
}
