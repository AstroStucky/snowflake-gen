#include <cmath>
#include <iostream>
#include <sstream>

#include "HexGrid.h"

HexGrid::HexGrid(const float initial_condition) {
	// set boundary cells 
	for (size_t i = 0; i < Q_NUM; ++i) {
		grid[0][R_NUM-1].set_boundary_cell(true);
		grid[i][R_NUM-1].set_boundary_cell(true);
	}
	for (size_t j = 0; j < R_NUM; ++j) {
		grid[Q_NUM-1][0].set_boundary_cell(true);
		grid[Q_NUM-1][j].set_boundary_cell(true);
	}

	// size_tegrated over all non-boundary cells and assign their adjacents
	for (size_t i = 1; i < Q_NUM - 1; ++i) {
		for (size_t j = 1; j < R_NUM - 1; ++j) {
			grid[i][j].add_adjacent( &grid [i - 1] [j]     );
			grid[i][j].add_adjacent( &grid [i + 1] [j]     );
			grid[i][j].add_adjacent( &grid [i]     [j - 1] );
			grid[i][j].add_adjacent( &grid [i]     [j + 1] );
			grid[i][j].add_adjacent( &grid [i - 1] [j + 1] );
			grid[i][j].add_adjacent( &grid [i + 1] [j - 1]);
		}
	}

	// set water content of the cell at (0,0)
	size_t central_q = floor(Q_NUM/2) - 1;
	size_t central_r = floor(R_NUM/2) - 1;
	grid[central_q][central_r].set_water_content(initial_condition);
}

void HexGrid::process_all(void) {
	// process rules for all non-boundary cells 
	for (size_t i = 1; i < Q_NUM - 1; ++i) {
		for (size_t j = 1; j < R_NUM - 1; ++j) {
			grid[i][j].process_rules();
		}
	}
	// update state of all non-boundary cells
	for (size_t i = 1; i < Q_NUM-1; ++i) {
		for (size_t j = 1; j < R_NUM-1; ++j) {
			grid[i][j].update_state();
		}
	}
}

void HexGrid::print(size_t spacing) {
	std::stringstream vertical_ws;
	std::stringstream horizontal_ws;
	for (size_t k = 0; k < spacing; ++k) {
		vertical_ws<<std::endl;
		horizontal_ws<<" ";
	}
	for (size_t i = 0; i < Q_NUM; ++i) {
		std::cout<<vertical_ws.str();
		// offset every other row
		if (i % 2 == 0) {
			std::cout<<horizontal_ws.str();
		}
		for (size_t j = 0; j < R_NUM; ++j) {
			std::cout<<horizontal_ws.str();
			if (grid[i][j].is_frozen()) {
				std::cout<<"♦"; //indicates frozen cell
			} else if (grid[i][j].is_receptive()) {
				std::cout<<"+"; //indicates boundary cell
			} else {
				std::cout<<"."; //indicates nonreceptie cell
			}
		}
	}
	std::cout<<std::endl;
}