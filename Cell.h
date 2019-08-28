#ifndef CELL_H
#define CELL_H

#include <set>

#include "Environment.h"

#define ICE_THRESHOLD	1.0f

class Cell {
public:
	// uses the global environment 
	Cell();

	// process_rules to determine next state
	void process_rules(void);
	// transitions future frame values to current frame values and updates 
	// cell state variables
	void update_state(void);

	//// Accessors
	// A frozen cell has a total water content greater than the ice threshold
	bool is_frozen(void) const {
		return frozen;
	}
	// A receptive cell is one that is frozen, or adjacent to a frozen cell
	bool is_receptive(void) const {
		return receptive;
	}
	// boundary cells are those at the edge of a grid and are kept at a
	// constant vapor leve
	bool is_boundary_cell(void) const {
		return boundary;
	}
	float get_diffusive_water_level() {
		return u0;
	}

	//// Modifiers
	void set_boundary_cell(const bool is_boundary_cell) {
		boundary = is_boundary_cell;
	}	
	void set_environment(Environment* environment) {
		env = environment;
	}
	// sets water content of the cell
	void set_water_content(const float water_content);

	// add a pointer to a cell that is adjacent to this cell
	void add_adjacent(Cell* const cell) {
		adjacents.insert(cell);
	}

protected:
	// computes the average u value of all adjacent cells
	float compute_avg_u(void);

	// internal only accessors and modifiers
	float get_u0(void) {
		return u0;
	}
	void set_receptive(const bool is_receptive) {
		receptive = is_receptive;		
	}

private:

	// provides shared access to environmental constants
	Environment *env;

	// pointers to all adjacent cells
	std::set<Cell*> adjacents;

	/// Cell state variables
	// frozen cells have values s > ICE_THRESHOLD
	bool frozen;
	// receptive cells are either frozen, or border a frozen cell
	bool receptive;
	// boundary cells exist at max/min i or j values and are fixed at the 
	// background vapor level
	bool boundary;

	/// s0, u0, z0 are all current values and s1, u1, z1, next frame values
	// total amount water content in the cell
	float s;
	// amount of water not participating in diffusion
	float v;
	// amount of water participating in diffusion
	// u0 - current value, u1 - future value
	float u0, u1;
};

#endif /* CELL_H */