
#ifndef _SIMPLETOWER_H
#define _SIMPLETOWER_H
#include"ObjectOnMap.h"
#include <vector>
#include <string>
#include "Enemy.h"
#include "MainScene.h"

namespace game {
    class MainScene;
    class SimpleTower : public ObjectOnMap { 
    protected:
        enum class TypeOfStrategy { Location, LocationFromCastle, HealthUp, HealthDown, Speed };
        enum class TypeOfLevel { Simple, Middle, Strong };
        TypeOfLevel level;
        TypeOfStrategy strategy;
        double speed;
        double area;
        int cost;
        int damage;
    public:
        SimpleTower(TypeOfLevel n_level = TypeOfLevel::Simple, TypeOfStrategy n_strategy = TypeOfStrategy::Location, double n_x = 0, double n_y = 0, int  n_speed = 10, double n_area = 5, int n_cost = 5, int n_damage = 1);
        SimpleTower(const SimpleTower&);
        SimpleTower(SimpleTower&&);
        ~SimpleTower();
        TypeOfStrategy getStrategy()const { return strategy; }
        TypeOfLevel getLevel()const { return level; }
        double getArea()const { return area; }
        int getCost() const { return cost; }
        double getSpeed()const { return speed; }
        int getDamage()const { return damage; }
        void setDamage(double n_dam) { damage = n_dam; }
        void setArea(double n_area) { area = n_area; }
        void setSpeed(double n_speed) { speed = n_speed; }
        void setCost(int n_cost) { cost = n_cost; }
        void setStrategy(TypeOfStrategy chosenstradegy) { strategy = chosenstradegy; }
        void setLevel(TypeOfLevel chosenLevel) { level = chosenLevel; }
        void addDamage(Enemy& enemy);
        Enemy* findCloseEnemy(MainScene&);
        Enemy* findCloseEnemyToCastle(MainScene&);
        Enemy* findHealthUpEnemy(MainScene&);
        Enemy* findHealthDownEnemy(MainScene&);
        Enemy* findSpeedUpEnemy(MainScene&);
        SimpleTower* clone() const {
            return new SimpleTower(*this);
        }
    };
}
#endif 