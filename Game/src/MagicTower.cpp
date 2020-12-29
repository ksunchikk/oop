
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
            area=5;
            cost=10;
            damage = 1;
        }
        if (n_level == TypeOfLevel::Middle) {
            speed = 60;
            area = 10;
            cost = 25;
            damage = 2;
        }
        if (n_level == TypeOfLevel::Strong) {
            speed = 120;
            area = 15;
            cost = 50;
            damage = 5;
        }
        if (n_type == Magic::TypeOfMagic::POISONING) magic = new Poisoning();
        if (n_type == Magic::TypeOfMagic::SLOWDOWN) magic = new Slowdown();
        if (n_type == Magic::TypeOfMagic::WEAKNESS) magic = new Weakness();
        Otype = Type::MAGICTOWER;
    }
    MagicTower::MagicTower(const MagicTower& n_tow):SimpleTower(n_tow) {
        Otype = Type::MAGICTOWER;
    }
    MagicTower::MagicTower(MagicTower&& n_tow):SimpleTower(n_tow) {
        magic = new Magic(*n_tow.magic);
        Otype = Type::MAGICTOWER;
        delete n_tow.magic;
    }
    MagicTower::~MagicTower() {
        delete magic;
    }
    void MagicTower::addSpell(Enemy& enemy) {
        Magic* mag = new Magic(*magic);
        enemy.addMagic(*mag);
    }

    void MagicTower::addDamage(Enemy enemy) {
        if (enemy.Enemy::getTypeOfLevel() == Enemy::TypeOfLevel::Simple) {
            enemy.acceptDamage(damage*0.5);
        }
        if (enemy.Enemy::getTypeOfLevel() == Enemy::TypeOfLevel::Middle) {
            enemy.acceptDamage(damage*0.4);
        }
        if (enemy.Enemy::getTypeOfLevel() == Enemy::TypeOfLevel::Strong) {
            enemy.acceptDamage(damage*0.2);
        }
        addSpell(enemy);
    }
}