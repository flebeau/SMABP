#include "strategy.hpp"

void GreedyStrategy::played(unsigned bandit, double reward) {
	times_played.at(bandit)++;
	rewards[bandit] += reward;
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
	if (distr_epsilon(engine_epsilon) < epsilon) { // We sample uniformly with probability epsilon
		return distr_bandit(engine_bandit);
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
