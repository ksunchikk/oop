

#ifndef _OBGECTONMAP_H
#define _OBGECTONMAP_H
#include <string>
//#include "Magic.h"
#include <vector>
namespace game {
    class ObjectOnMap {
    public:
        enum class Type { CASTLE, TOWER, MAGICTOWER, ENEMY, TRAP, DEN };
        Type Otype;
        double x;
        double y;
        ObjectOnMap(Type type=Type::TOWER,double n_x = 0, double n_y = 0);
        ObjectOnMap(const ObjectOnMap&);
        ObjectOnMap(ObjectOnMap&&);
        ~ObjectOnMap(){}
        double getX()const { return x; }
        double getY()const { return y; }
        Type getOType()const { return Otype; }
        //virtual std::vector <Magic*>& getVecMagic() = 0;
        void setX(double n_x) { x = n_x; }
        void setY(double n_y) { y = n_y; }
        void setOType(Type n_type) { Otype = n_type; }
    };

}
#endif 