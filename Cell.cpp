// ----------------------------------------------------------------------------
// PROJECT       : Snowflakes
// AUTHOR        : Thomas Stucky
// EMAIL         : thomas@astrostucky.com
// CREATED       : 08-25-2019
// PURPOSE       : Implementation of Cell member functions. Also instantiates
//                 the global environment variable.
//
// -------------------------GPL 3.0 LICENSE-----------------------------------
// Generates snowflakes in a hexagonal grid using the Reiter automata model.
// Copyright (C) 2019 Thomas R. Stucky
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.
// --------------------------	-----------------------------------------------

#include "Cell.h"

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
		const float u0_avg = compute_avg_u();
		u1 = u0 + alpha/2.0 * (u0_avg - u0);
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
