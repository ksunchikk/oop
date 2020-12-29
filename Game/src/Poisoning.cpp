
#include "Poisoning.h"

namespace game {
    Poisoning::Poisoning( double n_pow, int n_maxtime) {
        accept = false;
        maxtime = n_maxtime;
        type = TypeOfMagic::POISONING;
        power = n_pow;
        timeleft = 0;
    }
}
