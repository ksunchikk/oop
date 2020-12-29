

#ifndef _MAGICTOWER_H
#define _MAGICTOWER_H

#include "SimpleTower.h"
#include "Magic.h"
#include "Enemy.h"

namespace game {
    class MagicTower : public SimpleTower {
    private:
        Magic* magic=nullptr;
    public:
        MagicTower(Magic* nmagic): SimpleTower() {magic = nmagic;}
        MagicTower(Magic::TypeOfMagic n_type, TypeOfLevel n_level = TypeOfLevel::Simple, TypeOfStrategy n_strategy = TypeOfStrategy::Location, double n_x=0, double n_y=0, int  n_speed = 10, double n_area = 5, int n_cost = 5, int n_damage = 1);
        MagicTower(const MagicTower&);
        MagicTower(MagicTower&&);
        ~MagicTower();
        Magic* getMagic()const { return magic; }
        void setMagic(Magic* n_magic){ magic = n_magic; }
        void addSpell(Enemy& enemy);
        void addDamage(Enemy enemy);
    };
}
#endif 