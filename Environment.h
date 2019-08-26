#ifndef ENVRIONMENT_H
#define ENVRIONMENT_H

#include <math>

class Environment {
public:
	Envrionment() = 0;
	
	Environment(int symmetry, float condensation_rate, float diffusion_rate, float vapor_level) : n(symmetry), alpha(condensation_rate), gamma(diffusion_rate), beta(vapor_level) {
		// calculate coordinate angle in radians
		theta = 2 * std::acos(-1) / n;
	}

	// Acessors
	int get_coordinate_angle(void) const {
		return theta;
	}
	float get_condensation_rate(void) const {
		return alpha;
	}
	float get_diffusion_rate(void) const { 
		return gamma;
	}
	float get_vapor_level(void) const { 
		return beta;
	}

private:
	
	/// Vapor constants
	// addition coefficient
	float alpha;
	// diffusion coefficient
	float gamma;
	// background vapor pressure
	float beta;

	/// Space constants
	// n-fold symmetry (6 for water ice)
	int n;
	// angle between i and j vectors (in radians)
	float theta; 
	// dimensions of 2D space where crystals grow
	int max_i, max_j;
}

#endif /* ENVIRONMENT_H */