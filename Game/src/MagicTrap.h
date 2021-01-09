
#ifndef _MAGICTRAP_H
#define _MAGICTRAP_H

#include "Magic.h"
#include "Enemy.h"
#include "ObjectOnMap.h"
namespace game {
    class Map;
    class MagicTrap : public ObjectOnMap {
    private:
        int cost;
        double area;
        Magic* magic=nullptr;
    public:
        double lastshot = 0;
        MagicTrap(Magic::TypeOfMagic n_type = Magic::TypeOfMagic::POISONING,double n_x=0, double n_y=0, double n_area = 120, int n_cost = 30);
        MagicTrap(const MagicTrap&);
        MagicTrap(MagicTrap&&) noexcept;
        ~MagicTrap();
        Magic* getMagic()const { return magic; }
        double getArea()const { return area; }
        int getCost() const { return cost; };
        void setMagic(Magic* n_magic) { magic = n_magic; }
        void setArea(double n_area) { area = n_area; }
        void setCost(int n_cost) { cost = n_cost; }
        void addSpell(Enemy& enemy);
        MagicTrap* clone() const {
            return new MagicTrap(*this);
        }

    };
}

#endif //_MAGICTRAP_H