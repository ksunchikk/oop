
#ifndef _GRAF_CELL_
#define _GRAF_CELL_
#include "Cell.h"
#include <SFML/Graphics.hpp>
using namespace sf;
namespace game {
	class GrafCell {
	public:
		Sprite tex;
		Cell& obj;
		GrafCell(Texture* t, Cell& o) : obj(o) {
			tex.setPosition(o.getX() - 15, o.getY()-15);
			tex.setTexture(*t);
		}
		void draw(RenderWindow& win) {
			win.draw(tex);
		}
	};
}
#endif 

