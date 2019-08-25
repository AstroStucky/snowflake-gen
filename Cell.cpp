#include "Cell.h"

Cell::process() {
	if 


	if (state == FROZEN) {
		v = v + env->get_condensation_rate();
		s = v
	} else {
		const float alpha = env->get_diffusion_rate();
		const float avg_u = compute_local_average();
		u = u + alpha*(avg_u - u)/2.0;
		s = u 
	}

	// check if it is now receptive
	if (is_receptive()) {
		u = 0.0;
	} else {
		v = 0.0;
	}
}
