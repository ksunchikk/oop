

#include "Cell.h"
#include <iostream>
namespace game {
	Cell::Cell(TypeOfCell n_type, double n_x, double n_y, bool n_c, int n_t) {
		if (n_type == ROAD) {
			state = C_B_TR;
			road = 1;
			type = n_type;
			isChoice = n_c;
			t_choice = n_t;
		}
		if (n_type == FOREST) {
			state = N_B;
			road = 0;
			type = n_type;
			isChoice = n_c;
			t_choice = n_t;
		}
		if (n_type == LEA) {
			state = C_B_T;
			road = 0;
			type = n_type;
			isChoice = n_c;
			t_choice = n_t;
		}
		if (n_x < 0) throw std::runtime_error("Wrong data! X info error!");
		x = n_x;
		if (n_y < 0) throw std::runtime_error("Wrong data! Y info error!");
		y = n_y;
	}
	Cell::Cell(const Cell& n_cell): type(n_cell.type), state(n_cell.state),road(n_cell.road), x(n_cell.x), y(n_cell.y), tower(n_cell.tower), trap(n_cell.trap), den(n_cell.den),castle(n_cell.castle), isChoice(n_cell.isChoice), t_choice(n_cell.t_choice) {}
	Cell::Cell(Cell&& n_cell): x(n_cell.x), y(n_cell.y), road(n_cell.road),state(n_cell.state),type(n_cell.type), isChoice(n_cell.isChoice), t_choice(n_cell.t_choice) {
		den = n_cell.den->clone();
		castle = n_cell.castle->clone();
		tower= n_cell.tower->clone();
		trap= n_cell.trap->clone();
		delete(n_cell.den);
		delete(n_cell.trap);
		delete(n_cell.castle);
		delete(n_cell.tower);
	}
	
	Cell::~Cell() {
		delete(den);
		delete(trap);
		delete(castle);
		delete(tower);
	}
}
