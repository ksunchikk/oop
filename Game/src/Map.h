

#ifndef _MAP_H
#define _MAP_H
#include <vector> 
#include "Cell.h"
#include "SimpleTower.h"
#include "Enemy.h"
#include "MagicTrap.h"
#include "MagicTower.h"
#include "Den.h"
#include "Castle.h"
using namespace std;
namespace game {
    class Map {
    public:
        Castle* castle = nullptr;
        vector<vector<Cell*>> cells;
        vector<SimpleTower*> towers;
        vector<MagicTrap*> traps;
        Map(){}
        Cell* findCell(double n_x, double n_y);
        SimpleTower* addtower(SimpleTower::TypeOfLevel n_type, SimpleTower::TypeOfStrategy n_s_type, double n_x, double n_y);
        MagicTower* addMagicTower(SimpleTower::TypeOfLevel n_type, SimpleTower::TypeOfStrategy n_s_type, Magic::TypeOfMagic n_m_type, double n_x, double n_y);
        MagicTrap* addtrap(Magic::TypeOfMagic n_type, double n_x, double n_y);
        void moveAll(MainScene& m,double n_time);
        void makeShot(MainScene& m, double n_time);
        void upgradeTower(SimpleTower::TypeOfLevel n_type, SimpleTower& n_tow);
        void makeTrapShot(MainScene& m, double);
        void init(const string& f_name);
        void load(MainScene&,const string& f_name);
        void save(MainScene& ,const string& f_name);
        Den* den[2] = { nullptr, nullptr };
       
    };
}
#endif
