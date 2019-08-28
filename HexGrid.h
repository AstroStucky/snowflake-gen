#ifndef HEX_GRID_H
#define HEX_GRID_H

#include <array>
#include <cassert>

#include "Cell.h"

template <class T, size_t X, size_t Y>
	using Array2D = std::array<std::array<T,Y>, X>;

static const size_t Q_NUM = 80;
static const size_t R_NUM = 80;

//// HexGrid
// Manages a 2D array of Cells arranged by (q,r) in a hexagonal grid 
class HexGrid {
public:
	// no default constructor
	HexGrid() = delete;
	// construct hexgrid with an initial value to assign to center cell
	HexGrid(const float intial_condition_value);

	// processes automata rules of every cell in grid
	void process_all(void);
	// output grid in text format
	void print(size_t spacing = 1);
	// sets the value of the cell located at (q,r)
	void set_cell_value(const size_t q, const size_t r, const float value) {
		assert(q < Q_NUM);
		assert(r < R_NUM);
		grid[q][r].set_water_content(value);		
	}

private:
	// all cells organized by their (q,r) coordinate
	Array2D<Cell,Q_NUM,R_NUM> grid;
};

#endif /* HEX_GRID_H */