
#include "Enemy.h"
#include <iostream>

namespace game {
    
    Enemy& Enemy::operator =(const Enemy& n_enem){
        type = n_enem.type;
        speed = n_enem.speed;
        cost = n_enem.cost;
        starttime = n_enem.starttime;
        magic = n_enem.magic;
        maxhp = n_enem.maxhp;
        hp = n_enem.hp;
        alive = n_enem.alive;
        x = n_enem.x;
        y = n_enem.y;
        Otype = n_enem.Otype;
        return *this;
    }
   Enemy::Enemy(const Enemy& n_enem): ObjectOnMap(n_enem), type(n_enem.type),cost(n_enem.cost),speed(n_enem.speed),magic(n_enem.magic),starttime(n_enem.starttime),hp(n_enem.hp),maxhp(n_enem.maxhp),alive(n_enem.alive) {
   }
   Enemy::Enemy(Enemy&& n_enem) : ObjectOnMap(n_enem) {
        type = n_enem.type;
        speed = n_enem.speed;
        cost = n_enem.cost;
        starttime = n_enem.starttime;
        magic=std::move(n_enem.magic);
        alive = n_enem.alive;
        maxhp = n_enem.maxhp;
        hp = n_enem.hp;
    }
    Enemy::Enemy(TypeOfLevel n_type, double n_time, double n_x, double n_y) : ObjectOnMap(Type::ENEMY, n_x, n_y) {
        if (n_time < 0) throw std::runtime_error("Wrong data! Start time info error!");
        starttime = n_time;
        if (n_type == TypeOfLevel::Simple) {
            magic = {};
            cost = 2;
            speed = 15;
            type = n_type;
            maxhp = 10;
            hp = maxhp;
        }
        if (n_type == TypeOfLevel::Middle) {
            magic = {};
            cost = 5;
            speed = 15;
            type = n_type;
            maxhp = 15;
            hp = maxhp;
        }
        if (n_type == TypeOfLevel::Strong) {
            magic = {};
            cost = 10;
            speed = 25;
            type = n_type;
            maxhp = 25;
            hp = maxhp;
        }
    }
    Enemy::~Enemy() {
        while (!magic.empty()) {
            std::vector<Magic*>::iterator i = magic.end()-1;
            magic.erase(i);
        }
    }
    
    int Enemy::getMagicInfo() {
        std::vector<Magic*>::iterator i = this->begin();
        std::vector<Magic*>::iterator j = this->end()++;
        int amount=0;
        while (i != j) {
            amount++;
            i++;
        }
        return amount;
    }
    void Enemy::setCost(int n_cost) {
        if (n_cost < 0) throw std::runtime_error("Wrong data! Cost info error!");
        cost = n_cost;
    }
    void Enemy::setSpeed(int n_speed) {
        if (n_speed < 0) throw std::runtime_error("Wrong data! Speed info error!");
        speed = n_speed;
    }
    void Enemy::setTime(double n_time) {
        if (n_time < 0) throw std::runtime_error("Wrong data! Start time info error!");
        starttime = n_time;
    }
    void Enemy::addMagic(Magic n_magic) {
        magic.push_back(new Magic(n_magic));
    }
    void Enemy::updateEnemyWithMagic(double n_time) {
        std::vector<Magic*>::iterator i = magic.begin();
        std::vector<Magic*>::iterator j = magic.end();
        while (i != j) {
            if ((*i)->type == Magic::TypeOfMagic::SLOWDOWN) {
                if ((*i)->getAccept() == false) {
                    speed -= (speed*(*i)->getPower() * 0.005);
                    (*i)->setAccept(true);
                    (*i)->setTime((*i)->getTime() + n_time);
                }
                else (*i)->setTime((*i)->getTime() + n_time);
            }
            else if ((*i)->type == Magic::TypeOfMagic::WEAKNESS) {
                if ((*i)->getAccept() == false) {
                    weakness += (*i)->getPower()*0.05;
                    (*i)->setAccept(true);
                }
                (*i)->setTime((*i)->getTime() + n_time);
            }
            else if ((*i)->type == Magic::TypeOfMagic::POISONING) {
                hp = (*i)->getPower() * n_time * 0.05;
                (*i)->setTime((*i)->getTime() + n_time);
            }
            i++;
        }
        if (magic.begin() != magic.end()) {
            std::vector<Magic*>::iterator ii = magic.begin();
            for (ii; ii != magic.end(); ii++) {
                if ((*ii)->getTime() >= (*ii)->getMaxTime()) {
                    if ((*ii)->type == Magic::TypeOfMagic::SLOWDOWN) {
                        speed += (speed * (*ii)->getPower() * 0.05);
                    }
                    else if ((*ii)->type == Magic::TypeOfMagic::WEAKNESS) {
                        weakness -= (*ii)->getPower() * 0.05;
                    }
                    magic.erase(ii);
                    break;
                }
            }
        }
        
    }
    void Enemy::acceptDamage(double n_damage) {
        if ((hp - weakness*n_damage) <= 0) {
            hp = 0;
            alive = false;
        }
        else hp -= weakness*n_damage;
    }
    void Enemy::addDamage(Castle& castle) {
        double dam;
        if (type == TypeOfLevel::Simple) {
            dam = hp * 0.5;
            castle.acceptDamage(dam);
        }
        if (type == TypeOfLevel::Middle) {
            dam = hp * 0.7;
            castle.acceptDamage(dam);
        }
        if (type == TypeOfLevel::Strong) {
            dam = hp;
            castle.acceptDamage(dam);
        }
    }
}
