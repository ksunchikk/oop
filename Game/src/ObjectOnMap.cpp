
#include "ObjectOnMap.h"
#include <iostream>
namespace game {
    ObjectOnMap::ObjectOnMap(Type type, double n_x, double n_y) {
		if (n_x < 0) throw std::runtime_error("Wrong data! X info error!");
		x = n_x;
		if (n_y < 0) throw std::runtime_error("Wrong data! Y info error!");
		y = n_y;
		Otype = type;
    }
	ObjectOnMap::ObjectOnMap(const ObjectOnMap& n) : x(n.x),y(n.y),Otype(n.Otype){
		
	}
	ObjectOnMap::ObjectOnMap(ObjectOnMap&& n) {
		x=n.x;
		y=n.y;
		Otype = n.Otype;
	}
}