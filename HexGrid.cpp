
float HexGrid::compute_local_avg_u(int const q, int const r) {
	// sum over adjacent cells
	float sum = 0;
	for (int i = -1; i < 1; i++) { // iterate over q
		for (int j = -1; j< 1; j++) { // iterate over r
			sum += grid[q + i][r + j].get_u();
		}
	}
	return sum/6;
}
