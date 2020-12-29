
#include "SimpleTower.h"

namespace game {
    SimpleTower::SimpleTower(TypeOfLevel n_level, TypeOfStrategy n_strategy, double n_x, double n_y, int  n_speed, double n_area, int n_cost, int n_damage): ObjectOnMap(Type::TOWER, n_x, n_y){
        level = n_level;
       strategy = n_strategy;
    if (n_level == TypeOfLevel::Simple) {
        speed = 30;
        area = 5;
        cost = 5;
        damage = 1;
    }
    if (n_level == TypeOfLevel::Middle) {
        speed = 60;
        area = 10;
        cost = 10;
        damage = 2;
    }
    if (n_level == TypeOfLevel::Strong) {
        speed = 120;
        area = 15;
        cost = 25;
        damage = 5;
    }
    Otype = Type::TOWER;
}
    SimpleTower::SimpleTower(const SimpleTower& n_tow): ObjectOnMap(n_tow), level(n_tow.level), strategy(n_tow.strategy),damage(n_tow.damage),speed(n_tow.speed),area(n_tow.area), cost(n_tow.cost) {}
    SimpleTower::SimpleTower(SimpleTower&& n_tow) : ObjectOnMap(n_tow), level(n_tow.level), strategy(n_tow.strategy), damage(n_tow.damage), speed(n_tow.speed), area(n_tow.area), cost(n_tow.cost) {}
    SimpleTower::~SimpleTower() {}
    void SimpleTower::addDamage(Enemy& enemy) {
        if (enemy.Enemy::getTypeOfLevel() == Enemy::TypeOfLevel::Simple) {
            enemy.acceptDamage(damage*0.5);
        }
        if (enemy.Enemy::getTypeOfLevel() == Enemy::TypeOfLevel::Middle) {
            enemy.acceptDamage(damage*0.4);
        }
        if (enemy.Enemy::getTypeOfLevel() == Enemy::TypeOfLevel::Strong) {
            enemy.acceptDamage(damage*0.2);
        }
    }

    Enemy* SimpleTower::findCloseEnemy(MainScene& m) {
        double min = 0;
        std::vector<Enemy*>::iterator i = m.enemies.begin();
        std::vector<Enemy*>::iterator j = m.enemies.end()++;
        std::vector<Enemy*>::iterator minIt;
        while (i != j) {
            double xx = (**i).ObjectOnMap::getX();
            double yy = (**i).ObjectOnMap::getY();
            double distance = sqrt((x - xx) * (x - xx) + (y - yy) * (y - yy));
            if (distance <= min) {
                min = distance;
                minIt = i;
            }
            i++;
        }
        return (*minIt);
    }
    Enemy* SimpleTower::findCloseEnemyToCastle(MainScene& m) {
        double min = 0;
        std::vector<Enemy*>::iterator i = m.enemies.begin();
        std::vector<Enemy*>::iterator j = m.enemies.end()++;
        std::vector<Enemy*>::iterator minIt;
        while (i != j) {
            double xx = (**i).ObjectOnMap::getX();
            double yy = (**i).ObjectOnMap::getY();
            double distance = sqrt((m.castle->getX() - xx) * (m.castle->getX() - xx) + (m.castle->getY() - yy) * (m.castle->getY() - yy));
            if (distance <= min) {
                min = distance;
                minIt = i;
            }
            i++;
        }
        return (*minIt);
    }
    Enemy* SimpleTower::findHealthUpEnemy(MainScene& m) {
        double max = 0;
        std::vector<Enemy*>::iterator i = m.enemies.begin();
        std::vector<Enemy*>::iterator j = m.enemies.end()++;
        std::vector<Enemy*>::iterator minIt;
        while (i != j) {
            if ((**i).getHp() > max) minIt = i;
            i++;
        }
        return (*minIt);
    }
    Enemy* SimpleTower::findHealthDownEnemy(MainScene&m) {
        double min = 0;
        std::vector<Enemy*>::iterator i = m.enemies.begin();
        std::vector<Enemy*>::iterator j = m.enemies.end()++;
        std::vector<Enemy*>::iterator minIt;
        while (i != j) {
            if ((**i).getHp() < min) minIt = i;
            i++;
        }
        return (*minIt);
    }
    Enemy* SimpleTower::findSpeedUpEnemy(MainScene&m) {
        double max = 0;
        std::vector<Enemy*>::iterator i = m.enemies.begin();
        std::vector<Enemy*>::iterator j = m.enemies.end()++;
        std::vector<Enemy*>::iterator minIt;
        while (i != j) {
            if ((**i).getSpeed() > max) minIt = i;
            i++;
        }
        return (*minIt);
    }
}