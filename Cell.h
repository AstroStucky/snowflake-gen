#ifndef CELL_H
#define CELL_H

#include "Environment.h"

class Cell {
public:
	Cell() = 0;

	Cell();

	bool check_for_surrounding_ice() const;

	float compute_local_average_u() const;

	// Update vapor state variables based on adjacent cells
	void process(void);

	/// Cell state accessors
	bool is_frozen(void) const {
		return frozen;
	}
	bool is_receptive(void) const {
		return receptive;
	}
	bool is_boundary(void) const {
		return boundary
	}

	// accessor for water participating in diffusion
	float get_u();

private:

	const float ICE_THRESHOLD = 1.0;

	// provides shared access to environmental constants
	Environment *env;

	/// Cell state variables
	// frozen cells have values s > ICE_THRESHOLD
	bool frozen;
	// receptive cells are either frozen, or border a frozen cell
	bool receptive;
	// boundary cells exist at max/min i or j values and are fixed at the 
	// background vapor level
	bool boundary;

	// total amount water content in the cell
	float s;
	// amount of water participating in diffusion
	float u;
	// amount of water not participating in diffusion
	float z;

}

#endif /* CELL_H */