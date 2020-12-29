
#ifndef _ENEMY_H
#define _ENEMY_H

#include "ObjectOnMap.h"
#include "Magic.h"
#include "Castle.h"
#include <vector>


namespace game{
    class Enemy : public ObjectOnMap {
    public:
        enum class TypeOfLevel { Simple, Middle, Strong };
        Enemy(const Enemy&);
        Enemy(Enemy&&);
        Enemy& operator =(const Enemy& n_enem);
        Enemy(TypeOfLevel n_type, double n_time=0, double n_x=0, double n_y=0);
        Enemy(TypeOfLevel n_type, double n_x = 0, double n_y = 0, double n_speed = 10, int n_cost = 2, double n_time = 0, std::vector<Magic*> n_magic = {}, double n_weakness = 1,bool n_alive=true,double n_hp=10,int n_maxhp=10);
        TypeOfLevel getTypeOfLevel()const { return type; }
        double getSpeed()const { return speed; }
        int getCost()const { return cost; }
        double getTime()const { return starttime; }
        std::vector<Magic*> getMagic()const { return magic; }
        int getMagicInfo();
        void setCost(int n_cost);
        void setSpeed(int n_speed);
        void setTime(double n_time);
        ~Enemy();
        std::vector<Magic*>::iterator begin() { return magic.begin(); }
        std::vector<Magic*>::iterator end() { return magic.end(); }
        void addMagic(Magic n_magic);
        void updateEnemyWithMagic(double n_time);
        void acceptDamage(double n_damage);
        void addDamage(Castle& castle);
        double getHp() const { return hp; }
        int getMaxhp() const { return maxhp; }
        bool getalive() const { return alive; }
        void setHp(double n_hp) { hp = n_hp; }
        void setMaxhp(int n_maxhp) { maxhp = n_maxhp; }
        void setAlive(bool n_alive) { alive = n_alive; }
    private:
        TypeOfLevel type;
        double speed;
        std::vector<Magic*> magic;
        int cost;
        double starttime;
        double weakness=1;
        bool alive;
        double hp;
        int maxhp;
    };
}

#endif 