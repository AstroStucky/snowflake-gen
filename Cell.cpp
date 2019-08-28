#include "Cell.h"

#ifdef _WIN32
#include <windows.h>
#endif
#include <GL/glut.h>  // GLUT, include glu.h and gl.h

// global environment: settings can be overwritten by calling it directly
Environment g_environment;

// Initialize cells as though they are non-boundary, non-frozen, and 
// non-receptive, with a starting water content, s0, equal to the background 
// vapor level of their envirnoment.
Cell::Cell(void) : env(&g_environment), frozen(false), receptive(false), boundary(false) {
	u0 = env->get_vapor_level();
	v = 0;
	s = u0;
}

void Cell::process_rules(void) {
	// do nothing for boundary cells
	if (is_boundary_cell()) {
		return;
	}

	if (is_receptive()) {
		// add vapor addition rate to receptive cells and clamp their diffusive 
		// water at zero
		v = s + env->get_addition_rate();
		u1 = 0;
	} else {
		// non-receptive cells have no non-diffusive water
		v = 0;
	}

	// diffuse over all non-frozen cells
	if (!is_frozen()) {
		const float alpha = env->get_diffusion_rate();
		const float avg_u = compute_avg_u();
		u1 = u0 + alpha*(avg_u - u0)/2.0;
	}

	// add total water
	s = v + u1;
}

void Cell::update_state(void) {
	// transition values to next frame
	u0 = u1;

	// update cell state variables
	if (s >= ICE_THRESHOLD) {
		frozen = true;
		receptive = true;
		// set all adjacent cells to receptive
		// TODO: Could be made significantly faster if adjacents members are
		//       removed as they freeze.
		for (auto cell : adjacents) {
			cell->set_receptive(true);
		}
	}
}

void Cell::set_water_content(const float water_content) {
	s = water_content;
	update_state();
}

float Cell::compute_avg_u(void) {
	float sum = 0;
	for (auto cell : adjacents) {
		sum += cell->get_u0();
	}
	return sum/adjacents.size();	
}
