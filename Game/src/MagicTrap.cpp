

#include "MagicTrap.h"
#include "Poisoning.h"
#include "Slowdown.h"
#include "Weakness.h"
namespace game {
    MagicTrap::MagicTrap(Magic::TypeOfMagic n_type, double n_x, double n_y,double n_area, int n_cost) {
        area = n_area;
        cost = n_cost;
        if (n_type == Magic::TypeOfMagic::POISONING) magic = new Poisoning();
        if (n_type == Magic::TypeOfMagic::SLOWDOWN) magic = new Slowdown();
        if (n_type == Magic::TypeOfMagic::WEAKNESS) magic = new Weakness();
        Otype = Type::TRAP;
        x = n_x;
        y = n_y;
    }
    MagicTrap::MagicTrap(const MagicTrap& n_tr) {
        area = n_tr.area;
        cost = n_tr.cost;
        magic = n_tr.magic;
        Otype = Type::TRAP;
        x = n_tr.x;
        y = n_tr.y;
    }
    MagicTrap::MagicTrap(MagicTrap&& n_tr) noexcept{
        area = n_tr.area;
        cost = n_tr.cost;
        magic = new Magic(*n_tr.magic);
        Otype = Type::TRAP;
        x = n_tr.x;
        y = n_tr.y;
        delete n_tr.magic;
    }
    MagicTrap::~MagicTrap() {}
    
    void MagicTrap::addSpell(Enemy& enemy) {
        Magic* mag = new Magic(*magic);
        enemy.addMagic(*mag);
    }
}