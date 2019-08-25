#ifndef CELL_H
#define CELL_H

#include "Environment.h"

class Cell {
public:
	Cell() = 0;

	Cell();

	enum CellState {
		// water content >= 0
		FROZEN = 0,
		// water content < 0
		THAWED,
		// cell is at edge of
		BOUNDARY, 
		EMPTY
	}

	// manualy set state of cell
	void set_state(const CellState state) {

	}

	// Update vapor state variables based on adjacent cells
	void process( void );

	const bool is_frozen( void ) {
		return s >= 1.0;
	}

	const bool is_receptive( void ) {
		return s < 1;
	}

	const bool is_boundary( void );

private:
	// provides access to environmental constants
	Environment *env;

	// is a boundary cell at a minimum i or j value
	bool boundary;

	// cell coordinates
	int i, j;

	// total amount water content of cell
	float s;
	// amount of water participating in diffusion
	float u;
	// amount of water not participating in diffusion
	float z;

}

#endif /* CELL_H */