#include "bandit.hpp"

double DeterministicBandit::play() const {
	return this->getMean();
}


double UniformBandit::play() const {
	return this->distr(this->engine);
}
