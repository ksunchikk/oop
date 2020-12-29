
#include "Magic.h"
#include <iostream>
namespace game {
    Magic::Magic( int n_maxtime, TypeOfMagic n_type, double n_pow, bool n_accep, double n_time) {
        maxtime = n_maxtime;
        type = n_type;
        timeleft = n_time;
        accept = n_accep;
        if (n_type == TypeOfMagic::POISONING) power = 10;
        if (n_type == TypeOfMagic::WEAKNESS) power = 0.2;
        if (n_type == TypeOfMagic::SLOWDOWN) power = 4;
    }
}
