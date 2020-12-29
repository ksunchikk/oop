\

#ifndef _POISONING_H
#define _POISONING_H

#include "Magic.h"

namespace game {
    class Poisoning : virtual public Magic {
    public:
        Poisoning(double n_pow = 10, int n_maxtime = 10);
        int getMaxTime()const { return maxtime; }
        TypeOfMagic getType() const { return type; }
        double getTime()const { return timeleft; }
        bool getAccept()const { return accept; }
        double getPower() const { return power; }
        void setPower(double n_pow) { power = n_pow; }
        void setTime(double n_time) { timeleft = n_time; }
        void setMTime(int n_time) { maxtime = n_time; }
        void setType(TypeOfMagic n_type) { type = n_type; }
        void setAccept(bool n_accep) { accept = n_accep; }
    };
}
#endif 