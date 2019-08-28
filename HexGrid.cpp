#include <cmath>
#include <iostream>

#include "HexGrid.h"

HexGrid::HexGrid(const float initial_condition) {
	// set boundary cells 
	for (size_t i = 0; i < MAX_Q; ++i) {
		grid[0][MAX_R].set_boundary_cell(true);
		grid[i][MAX_R].set_boundary_cell(true);
	}
	for (size_t j = 0; j < MAX_R; ++j) {
		grid[MAX_Q][0].set_boundary_cell(true);
		grid[MAX_Q][j].set_boundary_cell(true);
	}

	// size_tegrated over all non-boundary cells and assign their adjacents
	for (size_t i = 1; i < MAX_Q - 1; ++i) {
		for (size_t j = 1; j < MAX_R - 1; ++j) {
			grid[i][j].add_adjacent( &grid [i - 1] [j]     );
			grid[i][j].add_adjacent( &grid [i + 1] [j]     );
			grid[i][j].add_adjacent( &grid [i]     [j - 1] );
			grid[i][j].add_adjacent( &grid [i]     [j + 1] );
			grid[i][j].add_adjacent( &grid [i - 1] [j + 1] );
			grid[i][j].add_adjacent( &grid [i + 1] [j - 1]);
		}
	}

	// set water content of the cell at (0,0)
	size_t central_q = floor(MAX_Q/2) - 1;
	size_t central_r = floor(MAX_R/2) - 1;
	grid[central_q][central_r].set_water_content(initial_condition);
}

void HexGrid::process_all(void) {
	// process rules for all non-boundary cells 
	for (size_t i = 1; i < MAX_Q - 1; ++i) {
		for (size_t j = 1; j < MAX_R - 1; ++j) {
			grid[i][j].process_rules();
		}
	}
	// update state of all non-boundary cells
	for (size_t i = 1; i < MAX_Q-1; ++i) {
		for (size_t j = 1; j < MAX_R-1; ++j) {
			grid[i][j].update_state();
		}
	}
}

void HexGrid::print(void) {	
	for (size_t i = 0; i < MAX_Q; ++i) {
		std::cout<<std::endl;
		for (size_t j = 0; j < MAX_R; ++j) {
			if (grid[i][j].is_frozen()) {
				std::cout<<" ♦ "; //indicates frozen cell
			} else if (grid[i][j].is_receptive()) {
				std::cout<<" + "; //indicates boundary cell
			} else {
				std::cout<<" . "; //indicates nonreceptie cell
			}
		}
		std::cout<<std::endl;
	}
}