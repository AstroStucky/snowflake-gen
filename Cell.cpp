#include "Cell.h"

// Initialize cells as though they are non-boundary, non-frozen, and 
// non-receptive, with a starting water content, s0, equal to the background 
// vapor level of their envirnoment.
Cell::Cell(void) : env(g_environment), frozen(false), receptive(false),
		boundary(false) {
	u0 = env->get_vapor_level();
	v0 = 0;
	s0 = u0;
}

void Cell::process_rules(const float avg_u) {
	// do nothing for boundary cells
	if (is_boundary()) {
		return;
	}

	// add a constant to receptive cells 
	if (is_receptive()) {
		v1 = v0 + env->get_condensation_rate();
		u1 = 0;
	}

	// diffuse over both nonreceptive cells and cells that border frozen cells
	if (!is_frozen()) {
		const float alpha = env->get_diffusion_rate();
		const float avg_u = compute_local_average_u();
		u1 = u0 + alpha*(avg_u - u0)/2.0;
		v1 = 0;
	}

	// add total water
	s1 = v1 + u1;
}

void Cell::update_state(const bool frozen_neighbors = false) {
	// update cell state variables
	if (s0 > ICE_THRESHOLD) {
		frozen = true;
		receptive = true;
		// TOOD: implement callback to visualizer
	} else if (has_frozen_neighbors) {
		receptive = true;
	}

	// transition current values to next frame
	s0 = s1;
	v0 = v1;
	u0 = u1;
}

void set_water_content(const float water_content) {
	s0 = water_content;
	s1 = water_content;
	z0 = water_content;
	z1 = water_content;	
	update_state();
}