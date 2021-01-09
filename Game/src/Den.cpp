
#include "Den.h"
#include <iostream>
namespace game {
    Den::Den(int n_amount, std::vector<Enemy> n_enem, double n_x, double n_y): ObjectOnMap(Type::DEN, n_x, n_y) {
        if (n_amount < 0) throw std::runtime_error("Wrong data! Amount info error!");
         amount = n_amount;
         Enemies = n_enem;
         Otype = Type::DEN; 
    }
    Den::Den(const Den& n_den): ObjectOnMap(n_den) {
        amount = n_den.amount;
        Enemies = n_den.Enemies;
    }
    Den::Den(Den&& n_den):ObjectOnMap(n_den){
        amount = n_den.amount;
        Enemies = std::move(n_den.Enemies);
    }
    Den::~Den() {
        while (!Enemies.empty()) {
            std::vector<Enemy>::iterator i = Enemies.end()-1;
            Enemies.erase(i);
        }
    }
    void Den::setAmount(int n_amount) {
        amount = n_amount;
    }
    void Den::setEnemies(std::vector<Enemy> n_enemies) {
        Enemies = n_enemies;
    }
    void Den::putNewEnemy(MainScene& n_scene, double n_time) {
        std::vector<Enemy>::iterator i = Enemies.begin();
        std::vector<Enemy>::iterator j = Enemies.end();
        while (i != j) {
            double t = (i->getTime());
            if (t <= n_time) {
                n_scene.enemies.push_back(&*i);
                (*i).Enemy::setTime(10000000);
            }
            i++;
        }
    }
}