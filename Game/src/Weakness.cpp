
#include "Weakness.h"

namespace game {
    Weakness::Weakness(double n_pow, int n_maxtime) {
        accept = false;
        maxtime = n_maxtime;
        type = TypeOfMagic::WEAKNESS;
        power = n_pow;
        timeleft = 0;
    }
}
