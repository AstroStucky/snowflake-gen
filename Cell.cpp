#include "Cell.h"

void Cell::process(void) {

	if (is_receptive()) {
		v = v + env->get_condensation_rate();
		s = v;

		if (s >= ICE_THRESHOLD) {
			frozen = true;
			// clamp water available for diffusion to zero
			u = 0;
			// TODO: visualizer callback called here to update color
		}

	} else {
		const float alpha = env->get_diffusion_rate();
		const float avg_u = compute_local_average_u();
		u = u + alpha*(avg_u - u)/2.0;
		s = u;
	}

}
