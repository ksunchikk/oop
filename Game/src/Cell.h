
#ifndef _CELL_H
#define _CELL_H
#include "SimpleTower.h"
#include "MagicTrap.h"
#include "Den.h"
#include"Castle.h"

namespace game {
	class Cell {
	protected:
		SimpleTower* tower = nullptr;
		MagicTrap* trap = nullptr;
		Castle* castle = nullptr;
		Den* den = nullptr;
		double x;
		double y;
		bool road = 0;
	public:
		enum TypeOfCell{FOREST,LEA,ROAD};
		enum State{C_B_T, C_B_TR, N_B_T, N_B_TR, N_B};
		State state;
		TypeOfCell type;
		Cell(TypeOfCell n_type, double n_x = 0, double n_y = 0);
		Cell(const Cell&);
		Cell(Cell&&);
	    ~Cell();
		double getX()const { return x; }
		double getY()const { return y; }
		SimpleTower* getTower() { return tower; };
		MagicTrap* getTrap() { return trap; };
		Castle* getCastle() { return castle; };
		Den* getDen() { return den; };
		bool getIsRoad() { return road; };
		void setX(double n_x) { x = n_x; };
		void setY(double n_y) { y = n_y; };
		void setTower(SimpleTower* n_tower) { tower = n_tower; };
		void setTrap(MagicTrap* n_trap) { trap = n_trap; };
		void setCastle(Castle* n_castle) { castle = n_castle; };
		void setLair(Den* n_den) { den = n_den; };
		void setIsRoad(bool n_road) { road = n_road; };
		
	};
}
#endif