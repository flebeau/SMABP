#include <iostream>

#include "bandit.hpp"
#include "SMAB.hpp"
#include "strategy.hpp"

int main(int argc, char *argv[]) {
	const unsigned N = 1000;

    /* First define the bandits */
	SMAB bandits;
	bandits.add(new DeterministicBandit(0.7));
	bandits.add(new UniformBandit(0.71, 0.5));
	
	unsigned n_bandits = bandits.size();
	double max_mean = bandits.getMaxMean();
	
	/* Now we play with the naive greedy strategy */
	EpsilonGreedy naive_greedy(n_bandits, 0.1);
	double regret = 0.;
	double reward;
	unsigned choice;
		
	for (unsigned i = 0; i<N; i++) {
		choice = naive_greedy.choice();
		reward = bandits.play(choice);
		naive_greedy.played(choice, reward);
		regret += (max_mean - bandits.getMean(choice));
		std::cout << i+1 << " iteration: " << reward << "," << regret << "\n";
	}
	
	return 0;
}
