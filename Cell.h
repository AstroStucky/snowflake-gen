#ifndef CELL_H
#define CELL_H

#include "Environment.h"

#define ICE_THRESHOLD	1.0f

// global environment: settings can be overwritten by calling it directly
Envrionment g_environment;

class Cell {
public:
	// uses the global environment 
	Cell();

	// process_rules to determine next state
	void process_rules(const float avg_u);

	// transitions future frame values to current frame values and modifies 
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
	// constant vapor level
	bool is_boundary_cell(void) const {
		return boundary
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

private:

	// provides shared access to environmental constants
	Environment *env;

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
	float s0, s1;
	// amount of water participating in diffusion
	float u0, u1;
	// amount of water not participating in diffusion
	float z0, z1;
}

#endif /* CELL_H */