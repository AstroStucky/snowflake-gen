// ----------------------------------------------------------------------------
// PROJECT       : Snowflakes
// AUTHOR        : Thomas Stucky
// EMAIL         : thomas@astrostucky.com
// CREATED       : 08-26-2019
// PURPOSE       : Top level implmentation file that handles command line 
//                 input. Runs the snowflake simulations by instantiating
//                 HexGrid.
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

#include <iostream>
#include <chrono>
#include <cstring>
 
#include "HexGrid.h"

static bool g_debug;

void show_usage(void) {
	std::cout<<"./snowflakes [-h -d DIFFUSION_RATE -l VAPOR_LEVEL -a VAPOR_ADDITION_RATE]"        << std::endl;
	std::cout<<"\t-h --help         Show this message."                                           << std::endl;
	std::cout<<"\t-v --verbose      Display execution times for each cycle."                      << std::endl;
	std::cout<<"\t-d --diffusion    Rate with which water vapor diffuses through cells."          << std::endl;
	std::cout<<"\t-l --vapor_level  Background vapor level all cell initialize at."               << std::endl;
	std::cout<<"\t-a --add_rate     Rate at which external vapor is added to each receptive cell" << std::endl;
	std::cout<<"\t-i --init_value   Starting vapor level of the central point in the grid."       << std::endl;
}

int main(int argc, char* argv[]) {
	
	// default argument values

	g_debug = false;
	float diffusion   = 2.69;
	float vapor_level = 0.4;
	float add_rate    = 0.0001;
	float init_value  = 1.0;


	// parse arguments
	for (int i = 1; i < argc; ++i) {  
		// flag with no argument
		if (std::strcmp(argv[i], "-h") == 0 || std::strcmp(argv[i], "--help") == 0) {                 
			show_usage();
			return 0;
		} else if (std::strcmp(argv[i], "-v") == 0 || std::strcmp(argv[i], "--verbose") == 0) {                 
			g_debug = true;
		}
		// flag with argument
		if (i + 1 != argc) {
			if (std::strcmp(argv[i], "-d") == 0 || std::strcmp(argv[i], "--diffusion") == 0) {
				diffusion = std::stof(argv[++i]);
			} else if (std::strcmp(argv[i], "-l") == 0 || std::strcmp(argv[i], "--vapor_level") == 0) {                 
				vapor_level = std::stof(argv[++i]);
			} else if (std::strcmp(argv[i], "-a") == 0 || std::strcmp(argv[i], "--add_rate") == 0) {                 
				add_rate = std::stof(argv[++i]);
			} else if (std::strcmp(argv[i], "-i") == 0 || std::strcmp(argv[i], "--init_value") == 0) {                 
				init_value = std::stof(argv[++i]);
			}
		}
	}

	// Modify global environment values
	g_environment.set_diffusion_rate(diffusion);
	g_environment.set_vapor_level(vapor_level);
	g_environment.set_addition_rate(add_rate);

	// Build hex grid with
	HexGrid grid(init_value);	

	// print hexagonal grid initial conditions
	grid.print();

	for (int i = 0; i < 150; i++ ) {
		// Record start time
		auto start = std::chrono::high_resolution_clock::now();
		grid.process_all();
		// Record end time
		auto end = std::chrono::high_resolution_clock::now();
		// print grid present state
		grid.print();
		std::chrono::duration<double> elapsed = end - start;
		if (g_debug) std::cout<<"Elapsed time: "<<elapsed.count()<<"s"<<std::endl;
	}
	return 0;
}