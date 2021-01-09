
#include "SimpleTower.h"

namespace game {
    SimpleTower::SimpleTower(TypeOfLevel n_level, TypeOfStrategy n_strategy, double n_x, double n_y, int  n_speed, double n_area, int n_cost, int n_damage): ObjectOnMap(Type::TOWER, n_x, n_y){
        level = n_level;
       strategy = n_strategy;
    if (n_level == TypeOfLevel::Simple) {
        speed = 30;
        area = 90;
        cost = 5;
        damage = 1;
    }
    if (n_level == TypeOfLevel::Middle) {
        speed = 60;
        area = 120;
        cost = 10;
        damage = 2;
    }
    if (n_level == TypeOfLevel::Strong) {
        speed = 120;
        area = 180;
        cost = 25;
        damage = 5;
    }
    Otype = Type::TOWER;
    lastShot = 0;
}
    
    SimpleTower::SimpleTower(const SimpleTower& n_tow): ObjectOnMap(n_tow), level(n_tow.level), strategy(n_tow.strategy),damage(n_tow.damage),speed(n_tow.speed),area(n_tow.area), cost(n_tow.cost) {}
    SimpleTower::SimpleTower(SimpleTower&& n_tow) : ObjectOnMap(n_tow), level(n_tow.level), strategy(n_tow.strategy), damage(n_tow.damage), speed(n_tow.speed), area(n_tow.area), cost(n_tow.cost) {}
    SimpleTower::~SimpleTower() {}
    void SimpleTower::addDamage(Enemy& enemy, double  n_time) {
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
            }
        }
    }

    std::vector<Enemy*>::iterator SimpleTower::findCloseEnemy(MainScene& m) {
        double min = 10000000;
        std::vector<Enemy*>::iterator i = m.enemies.begin();
        std::vector<Enemy*>::iterator j = m.enemies.end();
        std::vector<Enemy*>::iterator minIt =j;
        while (i != j) {
            double xx = (**i).ObjectOnMap::getX();
            double yy = (**i).ObjectOnMap::getY();
            double narea = sqrt((x - xx) * (x - xx) + (y - yy) * (y - yy));
            double distance = sqrt((x - xx) * (x - xx) + (y - yy) * (y - yy));
            if (narea <= area) {
                if (distance <= min) {
                    min = distance;
                    minIt = i;
                }
            }
            i++;
        }
        return minIt;
    }
    std::vector<Enemy*>::iterator SimpleTower::findCloseEnemyToCastle(MainScene& m) {
        double min = 100000;
        std::vector<Enemy*>::iterator i = m.enemies.begin();
        std::vector<Enemy*>::iterator j = m.enemies.end();
        std::vector<Enemy*>::iterator minIt = j;
        while (i != j) {
            double xx = (**i).ObjectOnMap::getX();
            double yy = (**i).ObjectOnMap::getY();
            double narea = sqrt((x - xx) * (x - xx) + (y - yy) * (y - yy));
            double distance = sqrt((m.castle->getX() - xx) * (m.castle->getX() - xx) + (m.castle->getY() - yy) * (m.castle->getY() - yy));
            if (narea <= area) {
                if (distance <= min) {
                    min = distance;
                    minIt = i;
                }
            }
            i++;
        }
        return minIt;
    }
    std::vector<Enemy*>::iterator SimpleTower::findHealthUpEnemy(MainScene& m) {
        double max = 0;
        std::vector<Enemy*>::iterator i = m.enemies.begin();
        std::vector<Enemy*>::iterator j = m.enemies.end();
        std::vector<Enemy*>::iterator minIt = j;
        while (i != j) {
            double xx = (**i).ObjectOnMap::getX();
            double yy = (**i).ObjectOnMap::getY();
            double narea = sqrt((x - xx) * (x - xx) + (y - yy) * (y - yy));
            if (narea <= area) {
                if ((**i).getHp() > max) { minIt = i; max = (**i).getHp(); }
            }
            i++;
        }
        return minIt;
    }
    std::vector<Enemy*>::iterator SimpleTower::findHealthDownEnemy(MainScene& m) {
        double min = 100000;
        std::vector<Enemy*>::iterator i = m.enemies.begin();
        std::vector<Enemy*>::iterator j = m.enemies.end();
        std::vector<Enemy*>::iterator minIt=j;
        while (i != j) {
            double xx = (**i).ObjectOnMap::getX();
            double yy = (**i).ObjectOnMap::getY();
            double narea = sqrt((x - xx) * (x - xx) + (y - yy) * (y - yy));
            if (narea <= area) {
                if ((**i).getHp() < min) { minIt = i; min = (**i).getHp(); }
            }
            i++;
        }
        return minIt;
    }
    std::vector<Enemy*>::iterator SimpleTower::findSpeedUpEnemy(MainScene& m) {
        double max = 0;
        std::vector<Enemy*>::iterator i = m.enemies.begin();
        std::vector<Enemy*>::iterator j = m.enemies.end();
        std::vector<Enemy*>::iterator minIt=j;
        while (i != j) {
            double xx = (**i).ObjectOnMap::getX();
            double yy = (**i).ObjectOnMap::getY();
            double narea = sqrt((x - xx) * (x - xx) + (y - yy) * (y - yy));
            if (narea <= area) {
                if ((**i).getSpeed() > max) { minIt = i; max = (**i).getSpeed(); }
            }
            i++;
        }
        return minIt;
    }
}