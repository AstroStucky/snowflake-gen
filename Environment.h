#ifndef ENVRIONMENT_H
#define ENVRIONMENT_H

#include <math>

class Environment {
public:
	Envrionment() = 0;
	Environment(int symmetry, float condensation_rate, float diffusion_rate, float vapor_level) : n(symmetry), alpha(condensation_rate), gamma(diffusion_rate), beta(vapor_level) {
		// calculate coordinate angle
		theta = 2 * std::acos(-1) / n;
	}

	// Acessors
	const int get_coordinate_angle(void) {
		return theta;
	}
	const float get_condensation_rate(void) {
		return alpha;
	}
	const float get_diffusion_rate(void) { 
		return gamma;
	}
	const float get_vapor_level(void) { 
		return beta;
	}

private:
	
	// Vapor environment variables
	// addition coefficient
	float alpha;
	// diffusion coefficient
	float gamma;
	// background vapor pressure
	float beta;

	// n-fold symmetry (6 for water ice)
	int n;
	// angle between i and j vectors (in radians)
	float theta; 


}

#endif /* ENVIRONMENT_H */