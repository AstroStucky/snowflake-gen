#ifndef HEX_GRID_H
#define HEX_GRID_H

#include <array>

#include "Cell.h"

#define CELL_GRID_MAX_Q 400
#define CELL_GRID_MAX_R 400

/// HexGrid
// Manages a 2D array of Cells by (q,r) hexagonal grid coordinates, where q_hat
// is a unit vector that points 30 degrees above the x-axis, and r_hat is a
// unit vector parrallel to the y-axis. q > 0 and r > 0. This meands the domain
// is constrained to a 60 degree zone of the x-axis. The constraint is for
// computational purposes, since an initial condition at (0,0) will always have
// 6-fold symmetry.
class HexGrid {
public:
	HexGrid() = 0;

	HexGrid(const float intial_condition);

	// processes automata rules of every cell in grid
	float process_all(void);

protected:
	// computes the average value of all cells adjacent to (q,r)
	// NOTE: The Grid computes the local average instead of the Cell because: 
	// 		a) It has direct access to the grid member variables.
	//      b) The average is dependent on nearest neighbors, and therefore
	//      is dependent on the geometry of grid space. If Cell were dependent 
	//      on the geometry of grid space, a new Cell class would have to be 
	//      constructed for each type of grid space (e.g. square grids)
	float compute_local_avg_u(const int q, const int r) const;

	// returns true if there exist a neighbor to Cell (q,r) that is frozen
	bool has_frozen_locals(const int q, const int r) const;

private:

	// all cells organized by their (q,r) coordinate
	Array2D<Cell,CELL_GRID_MAX_Q,CELL_GRID_MAX_R> grid;

}

#endif /* HEX_GRID_H */