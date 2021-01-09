
#include "MagicTower.h"
#include "Poisoning.h"
#include "Slowdown.h"
#include "Weakness.h"

namespace game {
    MagicTower::MagicTower(Magic::TypeOfMagic n_type, TypeOfLevel n_level, TypeOfStrategy n_strategy, double n_x, double n_y ,int  n_speed, double n_area, int n_cost, int n_damage):SimpleTower(n_level,n_strategy,n_x,n_y,n_speed,n_area, n_cost, n_damage) {
        level = n_level;
        strategy = n_strategy;
        if (n_level == TypeOfLevel::Simple) {
            speed=30;
            area=90;
            cost=10;
            damage = 1;
        }
        if (n_level == TypeOfLevel::Middle) {
            speed = 60;
            area = 120;
            cost = 25;
            damage = 2;
        }
        if (n_level == TypeOfLevel::Strong) {
            speed = 120;
            area = 180;
            cost = 50;
            damage = 5;
        }
        if (n_type == Magic::TypeOfMagic::POISONING) magic = new Poisoning();
        if (n_type == Magic::TypeOfMagic::SLOWDOWN) magic = new Slowdown();
        if (n_type == Magic::TypeOfMagic::WEAKNESS) magic = new Weakness();
        Otype = Type::MAGICTOWER;
        lastShot = 0;
    }
    MagicTower::MagicTower(const MagicTower& n_tow):SimpleTower(n_tow) {
        Otype = Type::MAGICTOWER;
    }
    MagicTower::MagicTower(MagicTower&& n_tow):SimpleTower(n_tow) {
        magic = new Magic(*n_tow.magic);
        Otype = Type::MAGICTOWER;
        delete n_tow.magic;
    }
    MagicTower::~MagicTower() {}
    void MagicTower::addSpell(Enemy& enemy) {
        Magic* mag = new Magic(*magic);
        enemy.addMagic(*mag);
    }

    void MagicTower::addDamage(Enemy& enemy, double n_time) {
        if (&enemy != nullptr) {
            double cur = n_time - lastShot;
            if (cur >= (60 / speed)) {
                if (enemy.Enemy::getTypeOfLevel() == Enemy::TypeOfLevel::Simple) {
                    enemy.acceptDamage(damage);
                    lastShot = n_time;
                }
                if (enemy.Enemy::getTypeOfLevel() == Enemy::TypeOfLevel::Middle) {
                    enemy.acceptDamage(damage);
                    lastShot = n_time;
                }
                if (enemy.Enemy::getTypeOfLevel() == Enemy::TypeOfLevel::Strong) {
                    enemy.acceptDamage(damage);
                    lastShot = n_time;
                }
                addSpell(enemy);
            }
           
        }
       
    }
}