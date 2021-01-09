#pragma once
#include "ObjectOnMap.h"
#include <SFML/Graphics.hpp>
using namespace sf;
namespace game {
	class GraphObject
	{ public:
		Sprite tex;
		ObjectOnMap& obj;
		Text hp;
		GraphObject(Texture* t, ObjectOnMap& o): obj(o) {
			tex.setPosition(o.getX(), o.getY());
			tex.setTexture(*t);
		}
		void draw(RenderWindow& win) {
			win.draw(tex);
			win.draw(hp);
		}
	};
}

