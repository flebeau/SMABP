#include "strategy.hpp"
#include <cmath>

void GreedyStrategy::played(unsigned bandit, double reward) {
	times_played.at(bandit)++;
	rewards[bandit] += reward;
	step++;
}

unsigned NaiveGreedy::choice() {
	unsigned choice = 0;
	double max_mean = 0.;
	if (times_played.at(0) > 0)
		max_mean = rewards[0] / times_played[0];
	
	for (unsigned i = 1; i<rewards.size(); i++) {
		if (times_played[i] > 0 && rewards[i] / times_played[i] > max_mean) {
			max_mean = rewards[i] / times_played[i];
			choice = i;
		}
	}
	return choice;
}

unsigned EpsilonGreedy::choice() {
	if (distr_epsilon() < epsilon) { // We sample uniformly with probability epsilon
		return distr_bandit();
	}
	// Else we do as in the naive greedy algorithm
	unsigned choice = 0;
	double max_mean = 0.;
	if (times_played.at(0) > 0)
		max_mean = rewards[0] / times_played[0];
	
	for (unsigned i = 1; i<rewards.size(); i++) {
		if (times_played[i] > 0 && rewards[i] / times_played[i] > max_mean) {
			max_mean = rewards[i] / times_played[i];
			choice = i;
		}
	}
	return choice;
}

void VanishingGreedy::computeValues() {
	gamma = 1.;
	if (step > 2 && d > 0)
		gamma = std::min(1.,5*n_bandits*log(step-1) / (d * d * (step-1)));
	max_value = rewards.at(0); // First determine max value
	max_bandits[0] = false;
	for (unsigned i = 1; i<rewards.size(); i++) {
		max_bandits[i] = false;
		if (rewards[i] > max_value) {
			max_value = rewards[i];
		}
	}
	n_max_bandits = 0;
	for (unsigned i = 0; i<rewards.size(); i++) {
		if (rewards[i] == max_value) {
			max_bandits[i] = true;
			n_max_bandits++;
		}
	}
	values_computed = true;
}

void VanishingGreedy::played(unsigned bandit, double reward) {
	if (!values_computed)
		computeValues();

	double Q = gamma / n_bandits;
	if (max_bandits[bandit])
		Q += (1. - gamma) / n_max_bandits;
	
	rewards[bandit] += reward / Q;
	
	step++;
	times_played.at(bandit)++;
	values_computed = false;
}

unsigned VanishingGreedy::choice() {
	if (!values_computed)
		computeValues();
	
	if (distr_epsilon() < gamma) // We sample uniformly with probability gamma
			return distr_bandit();
	
	unsigned b = distr_bandit();
	while (!max_bandits[b]) {
		b = distr_bandit();
	}
	return b;
}
