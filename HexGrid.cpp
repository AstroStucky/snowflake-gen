#include "HexGrid.h"

HexGrid::HexGrid(const float initial_condition) {
	// set boundaries at edge of grid
	for (int i = 0; i < CELL_GRID_MAX_Q; ++i) {
		grid[i][0].set_boundary_cell(true);
		grid[i][CELL_GRID_MAX_R].set_boundary_cell(true);
	}
	for (int j = 0; j < CELL_GRID_MAX_R; ++j) {
		grid[0][j].set_boundary_cell(true);
		grid[CELL_GRID_MAX_Q][j].set_boundary_cell(true);
	}

	// set water content of the cell at (0,0)
	grid[0][0].set_water_content(initial_condition);
}

void HexGrid::process_all(void) {
	// process rules for all non-boundary cells 
	for (int i = 1; i < CELL_GRID_MAX_Q-1; ++i) {
		for (int j = 1; j < CELL_GRID_MAX_R-1; ++j) {
			const float local_avg_u = compute_local_avg_u(i, j);
			grid.process_rules(local_avg_u);
		}
	}
	// update state of all non-boundary cells
	for (int i = 1; i < CELL_GRID_MAX_Q-1; ++i) {
		for (int j = 1; j < CELL_GRID_MAX_R-1; ++j) {
			bool frozen_locals = false;
			// frozen cells don't unfreeze, so don't waste computation on them
			if (!grid[i][j].is_receptive()) {
				frozen_locals = has_frozen_locals(i, j);
			}
			grid[i][j].update_state();
		}
	}
}

float HexGrid::compute_local_avg_u(const int q, const int r) {
	float sum = 0;
	// sum over all adjacent cells
	for (int i = -1; i < 1; ++i) {
		for (int j = -1; j < 1; ++j) {
			sum += grid[q + i][r + j].get_u();
		}
	}
	return sum/6;
}

bool has_frozen_locals(const int q, const int r) {
	for (int i = -1; i < 1; ++i) {
		for (int j = -1; i < 1; ++j) {
			if grid[q + i][r + j].is_frozen() {
				return true;
			}
		}
	}
	return false;
}