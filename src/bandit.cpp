#include "bandit.hpp"

double DeterministicBandit::play() {
	return getMean();
}


double UniformBandit::play() {
	return distr();
}
