

#ifndef _MAP_H
#define _MAP_H
#include <vector> 
#include "Cell.h"
#include"SimpleTower.h"
#include "Enemy.h"
#include "MagicTrap.h"
namespace game {
    class Map {
    public:
        std::vector<std::vector<Cell*>> cells;
        std::vector<SimpleTower*> towers;
        std::vector<MagicTrap> traps;
        SimpleTower* addtower();
        MagicTrap addtrap();
    };
}
#endif
