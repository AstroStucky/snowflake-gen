#ifndef HEX_GRID_H
#define HEX_GRID_H

#include <array>

#include "Cell.h"

template <class T, size_t X, size_t Y>
	using Array2D = std::array<std::array<T,Y>, X>;

static const size_t MAX_Q = 20;
static const size_t MAX_R = 20;

/// HexGrid
// Manages a 2D array of Cells by (q,r) hexagonal grid coordinates, where q_hat
// is a unit vector that points 30 degrees above the x-axis, and r_hat is a
// unit vector parrallel to the y-axis. q > 0 and r > 0. This meands the domain
// is constrained to a 60 degree zone of the x-axis. The constraint is for
// computational purposes, since an initial condition at (0,0) will always have
// 6-fold symmetry.
class HexGrid {
public:
	// construct hexgrid with an initial value to assign to center cell
	HexGrid(const float intial_condition);

	// no default constructor
	HexGrid() = delete;

	// processes automata rules of every cell in grid
	void process_all(void);

	// output grid in text format
	void print(void);

private:
	// all cells organized by their (q,r) coordinate
	Array2D<Cell,MAX_Q,MAX_R> grid;
};

#endif /* HEX_GRID_H */