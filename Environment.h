#ifndef ENVRIONMENT_H
#define ENVRIONMENT_H

#include <math>

#define DEFAULT_DIFFUSION_RATE	1.0f
#define DEFAULT_VAPOR_LEVEL 	0.4f
#define DEFAULT_ADDITION_RATE	0.0001f	

class Environment {
public: 
	Envrionment() : alpha(DEFAULT_DIFFUSION_RATE), beta(DEFAULT_VAPOR_LEVEL), gamma(DEFAULT_ADDITION_RATE) {
		// do nothing
	}
	
	Environment(float diffusion_rate, float vapor_level, float addition_rate ) : alpha(diffusion_rate), beta(diffusion_rate), gamma(addition_rate) {
		// do nothing
	}

	// Acessors
	float get_diffusion_rate(void) const { 
		return alpha;
	}
	float get_vapor_level(void) const { 
		return beta;
	}
	float get_addition_rate(void) const {
		return gamma;
	}

	// Modifiers
	void set_diffusion_rate(const float diffusion_rate) {
		alpha = diffusion_rate;
	}
	void set_vapor_level(const float vapor_level) {
		beta = vapor_level;
	}
	void set_addition_rate(const float condensation_rate) {
		gamma = condensation_rate;
	}

private:
	/// Vapor constants
	// diffusion rate: rate at which water diffuses through the Grid
	float alpha;
	// background vapor level: all cells initialize at this value, and boundary
	// cells are fixed to it
	float beta;
	// vapor addition rate: rate at which vapor is added to each cell except 
	// boundary cells. Can be thought of as the flow of vapor in the 3rd
	// dimension
	float gamma;
}

#endif /* ENVIRONMENT_H */