#include <iostream>

#include "bandit.hpp"
#include "SMAB.hpp"
#include "strategy.hpp"

// Simulate the strategy with given bandits for N steps, recording regret at each step
void SimulateStrategyOnce(SMAB &bandits, Strategy &strat, std::vector<double> &regrets, unsigned N) {
	double regret = 0.;
	double reward;
	unsigned choice;
	double max_mean = bandits.getMaxMean();
	
	for (unsigned i = 0; i<N; i++) {
		choice = strat.choice();
		reward = bandits.play(choice);
		strat.played(choice, reward);
		regret += (max_mean - bandits.getMean(choice));
		regrets[i] += regret;
	}
}

void SimulateNaiveGreedy(SMAB &bandits, unsigned N, unsigned iteration) {
	unsigned n_bandits = bandits.size();
	NaiveGreedy naive_greedy(n_bandits);	
	std::vector<double> regrets(N,0.);
	
	/* Simulate strategy multiple times */
	for (unsigned j = 0; j<iteration; j++) {
		SimulateStrategyOnce(bandits, naive_greedy, regrets, N);
	}
	
	/* Output result (taking mean of regrets) */
	std::cout << "n \"Naive greedy\"\n";
	for (unsigned i = 0; i<N; i++) {
		std::cout << i << " " << regrets[i]/iteration << "\n";
	}
	
	std::cout << "\n\n";
}

void SimulateEpsilonGreedy(SMAB &bandits, double eps, unsigned N, unsigned iteration) {
	unsigned n_bandits = bandits.size();
	EpsilonGreedy eps_greedy(n_bandits, eps);	
	std::vector<double> regrets(N,0.);
	
	/* Simulate strategy multiple times */
	for (unsigned j = 0; j<iteration; j++) {
		SimulateStrategyOnce(bandits, eps_greedy, regrets, N);
	}
	
	/* Output result (taking mean of regrets) */
	std::cout << "n \"{/Symbol e}=" << eps << "\"\n";
	for (unsigned i = 0; i<N; i++) {
		std::cout << i << " " << regrets[i]/iteration << "\n";
	}
	
	std::cout << "\n\n";
}

int main(int argc, char *argv[]) {
	const unsigned N = 300; // Number of steps to play
	const unsigned iteration = 10000; // Number of times to play the game for computing the mean regret

    /* First define the bandits */
	SMAB bandits;
	bandits.add(new UniformBandit(0.7, 0.6));
	bandits.add(new DeterministicBandit(0.7));
	bandits.add(new UniformBandit(0.71, 0.5));
	
	/* Now we play with the different strategies */
	SimulateNaiveGreedy(bandits, N, iteration);
	SimulateEpsilonGreedy(bandits, 0.1, N, iteration);
	SimulateEpsilonGreedy(bandits, 0.2, N, iteration);
	SimulateEpsilonGreedy(bandits, 0.5, N, iteration);
	SimulateEpsilonGreedy(bandits, 0.8, N, iteration);
	SimulateEpsilonGreedy(bandits, 0.01, N, iteration);
	
	return 0;
}
