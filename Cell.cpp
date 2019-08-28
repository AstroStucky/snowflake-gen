#include "Cell.h"

// global environment: settings can be overwritten by calling it directly
Environment g_environment;

// Initialize cells as though they are non-boundary, non-frozen, and 
// non-receptive, with a starting water content, s0, equal to the background 
// vapor level of their envirnoment.
Cell::Cell(void) : env(&g_environment), frozen(false), receptive(false),
		boundary(false) {
	u0 = env->get_vapor_level();
	v0 = 0;
	s0 = u0;
}

void Cell::process_rules(void) {
	// do nothing for boundary cells
	if (is_boundary_cell()) {
		return;
	}

	// add a constant to receptive cells 
	if (is_receptive()) {
		v1 = v0 + env->get_addition_rate();
		u1 = 0;
	}

	// diffuse over both nonreceptive cells and cells that border frozen cells
	if (!is_frozen()) {
		const float avg_u = compute_avg_u();
		const float alpha = env->get_diffusion_rate();
		u1 = u0 + alpha*(avg_u - u0)/2.0;
		v1 = 0;
	}

	// add total water
	s1 = v1 + u1;
}

void Cell::update_state(void) {
	// update cell state variables
	if (s0 >= ICE_THRESHOLD) {
		frozen = true;
		receptive = true;
		for (auto cell : adjacents) {
			cell->receptive = true;
		}
		// TOOD: implement callback to visualizer
	}
	//  else if (has_frozen_neighbor()) {
	// 	receptive = true;
	// }

	// transition current values to next frame
	s0 = s1;
	v0 = v1;
	u0 = u1;
}

void Cell::set_water_content(const float water_content) {
	s0 = water_content;
	s1 = water_content;
	v0 = water_content;
	v1 = water_content;	
	update_state();
}

float Cell::compute_avg_u(void) {
	float sum = 0;
	for (auto cell : adjacents)
		sum += cell->u0;
	return sum/adjacents.size();	
}

bool Cell::has_frozen_neighbor(void) {
	for (auto cell : adjacents) {
		if (cell->frozen) {
			return true;
		}
	}
	return false;
}