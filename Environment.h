// ----------------------------------------------------------------------------
// PROJECT       : Snowflakes
// AUTHOR        : Thomas Stucky
// EMAIL         : thomas@astrostucky.com
// CREATED       : 08-25-2019
// PURPOSE       : Define the environment class for containing all environmental
//                 constants, which can be accessed or modified via its member
//                 functions. Defines a global environment.
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

#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#define DEFAULT_DIFFUSION_RATE 	2.69f
#define DEFAULT_VAPOR_LEVEL 	0.4f
#define DEFAULT_ADDITION_RATE	0.0001f	

class Environment {
public: 
	Environment() : alpha(DEFAULT_DIFFUSION_RATE), beta(DEFAULT_VAPOR_LEVEL), 
			gamma(DEFAULT_ADDITION_RATE) {
		// do nothing;
	}
	
	Environment(float diffusion_rate, float vapor_level, float addition_rate ) 
			: alpha(diffusion_rate), beta(diffusion_rate), gamma(addition_rate) {
		// do nothing
	}

	// Acessors
	float get_diffusion_rate(void) const { 
		return alpha;
	}
	float get_vapor_level(void) const { 
		return beta;
	}
	float get_addition_rate(void) const {
		return gamma;
	}

	// Modifiers
	void set_diffusion_rate(const float diffusion_rate) {
		alpha = diffusion_rate;
	}
	void set_vapor_level(const float vapor_level) {
		beta = vapor_level;
	}
	void set_addition_rate(const float condensation_rate) {
		gamma = condensation_rate;
	}

private:
	//// Water environment constants
	// diffusion rate: rate at which water diffuses through the Grid
	float alpha;
	// background vapor level: all cells initialize at this value, and boundary
	// cells are fixed to it
	float beta;
	// vapor addition rate: rate at which vapor is added to each cell except 
	// boundary cells. Can be thought of as the flow of vapor in the 3rd
	// dimension
	float gamma;
};

// global environment: settings can be overwritten by calling it directly
extern Environment g_environment;

#endif /* ENVIRONMENT_H */