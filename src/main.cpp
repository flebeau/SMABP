#include <iostream>
#include <fstream>

#include "bandit.hpp"
#include "SMAB.hpp"
#include "strategy.hpp"
#include <boost/program_options.hpp>

// Simulate the strategy with given bandits for N steps, recording regret at each step
void SimulateStrategyOnce(SMAB &bandits, Strategy &strat, std::vector<double> &regrets, unsigned N);

void SimulateNaiveGreedy(SMAB &bandits, unsigned N, unsigned iteration);

void SimulateEpsilonGreedy(SMAB &bandits, double eps, unsigned N, unsigned iteration);

int main(int argc, char *argv[]) {
	unsigned N = 300; // Number of steps to play
	unsigned iteration = 10000; // Number of times to play the game for computing the mean regret
	std::string bandits_file;
	std::vector<double> epsilons;
	
	/* Handle program options */
	namespace po = boost::program_options;
	try {
		po::options_description opt_descr("Options description");
		opt_descr.add_options()
			("help,h", "Display this help message")
			("number-steps,N", po::value<unsigned>(&N)->required(),"Specify number of steps of a simulation")
			("iteration,I", po::value<unsigned>(&iteration)->required(),"Specify number of times to run the simulation")
			("bandit-file,B", po::value<std::string>(&bandits_file)->required(),"Input file describing the bandits")
			("epsilons,e", po::value<std::vector<double> >(&epsilons)->multitoken()->zero_tokens()->composing(), "Parameters for the epsilon-greedy strategies");
		po::variables_map vm;
		po::store(po::command_line_parser(argc, argv).options(opt_descr).run(), vm);
	
		if (vm.count("help")) {
			std::cerr << opt_descr << "\n";
			return EXIT_SUCCESS;
		}
	
		po::notify(vm);
	}
	catch (std::exception &e) {
		std::cerr << "Error: " << e.what() << "\n";
		return EXIT_FAILURE;
	}

    /* First define the bandits according to the specification file */
	SMAB bandits;
	std::ifstream bandit_spec;
	bandit_spec.open(bandits_file);
	std::string letter;
	double mean, lower;
	
	while (bandit_spec >> letter) {
		if (letter == "D") {
			bandit_spec >> mean;
			bandits.add(new DeterministicBandit(mean));
		}
		else if (letter == "U") {
			bandit_spec >> mean >> lower;
			bandits.add(new UniformBandit(mean, lower));
		}
		else {
			std::cerr << "Error: bandits specification file is invalid.\n";
			return EXIT_FAILURE;
		}
	}
	
	
	/* Now we play with the different strategies */
	SimulateNaiveGreedy(bandits, N, iteration);
	
	for (const double &eps : epsilons) 
		SimulateEpsilonGreedy(bandits, eps, N, iteration);
	
	return EXIT_SUCCESS;
}

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
	std::cout << "n \"Greedy\"\n";
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
