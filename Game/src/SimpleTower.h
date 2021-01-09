
#ifndef _SIMPLETOWER_H
#define _SIMPLETOWER_H
#include "ObjectOnMap.h"
#include <vector>
#include <string>
#include "Enemy.h"
#include "MainScene.h"

namespace game {
    class MainScene;
    class SimpleTower : public ObjectOnMap { 
    public:
        double lastShot = 0;
        enum class TypeOfStrategy { Location, LocationFromCastle, HealthUp, HealthDown, Speed };
        enum class TypeOfLevel { Simple, Middle, Strong };
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
        void setDamage(int n_dam) { damage = n_dam; }
        void setArea(double n_area) { area = n_area; }
        void setSpeed(double n_speed) { speed = n_speed; }
        void setCost(int n_cost) { cost = n_cost; }
        void setStrategy(TypeOfStrategy chosenstradegy) { strategy = chosenstradegy; }
        void setLevel(TypeOfLevel chosenLevel) { level = chosenLevel; }
        virtual void addDamage(Enemy& enemy, double  n_time);
        std::vector<Enemy*>::iterator findCloseEnemy(MainScene&);
        std::vector<Enemy*>::iterator findCloseEnemyToCastle(MainScene&);
        std::vector<Enemy*>::iterator findHealthUpEnemy(MainScene&);
        std::vector<Enemy*>::iterator findHealthDownEnemy(MainScene&);
        std::vector<Enemy*>::iterator findSpeedUpEnemy(MainScene&);
        virtual Magic* getMagic()const { return nullptr; }
        virtual void setMagic(Magic* n_magic) { ; }
        SimpleTower* clone() const {
            return new SimpleTower(*this);
        }
    protected:
        TypeOfLevel level;
        TypeOfStrategy strategy;
        double speed;
        double area;
        int cost;
        int damage;
        
    
    };
}
#endif 