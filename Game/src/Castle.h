
#ifndef _CASTLE_H
#define _CASTLE_H

#include "ObjectOnMap.h"

namespace game {
    class Castle : public ObjectOnMap {
    private:
        bool alive;
        int purse;
        double curhealth;
        int maxhealth;
    public:
        Castle(int nPurse=100, double nCur = 100, int maxHealth = 100, bool nAlive=true, double n_x=0,double n_y=0);
        Castle(const Castle&);
        Castle(Castle&&);
        ~Castle() {};
        bool getalive() const { return alive; }
        int getpurse()const { return purse; }
        double getcurhealth()const { return curhealth; }
        int getmaxhealth()const { return maxhealth; }
        void setAlive(bool n_alive);
        void setPurse(int n_purse);
        void setCurHealth(double n_cur);
        void setMaxHealth(int n_mhealth);
        void acceptDamage(double damagefrom);
        void acceptCost(int cost);
        void buynewTower(int n_cost);
        void buynewTrap(int n_cost);
        Castle* clone() const {
            return new Castle(*this);
        }
    };
}

#endif 