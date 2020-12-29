
#ifndef _DEN_H
#define _DEN_H

#include "ObjectOnMap.h"
#include <vector>
#include "MainScene.h"
namespace game {
    class Enemy;
    class Den : public ObjectOnMap {
    private:
        int amount;
        std::vector<Enemy> Enemies;
    public:
        Den(int n_amount = 0, std::vector<Enemy> n_enem= {}, double n_x=0, double n_y=0);
        Den(const Den&);
        Den(Den&&);
        ~Den();
        void setAmount(int n_amount);
        void setEnemies(std::vector<Enemy> n_enemies);
        void putNewEnemy(MainScene& n_scene, double n_time);
        int getAmount()const { return amount; }
        std::vector <Enemy>& getEnemies() { return Enemies; }
        Den* clone() const {
            return new Den(*this);
        }
    };
}

#endif 