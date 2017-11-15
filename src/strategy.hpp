#ifndef STRATEGY_HPP_
#define STRATEGY_HPP_

#include <vector>
#include <random>
#include "random.hpp"

class Strategy {
public:
	Strategy(unsigned n_b) : n_bandits(n_b) {}

	virtual unsigned choice() = 0; // Choose a bandit according to strategy
	virtual void played(unsigned bandit, double reward) = 0; // Take the info of the reward obtained as feedback

protected:
	unsigned n_bandits;
};

class GreedyStrategy : public Strategy {
public:
	GreedyStrategy(unsigned n_b) : Strategy(n_b), rewards(n_b,0.), times_played(n_b, 0), step(0) {}

	virtual unsigned choice() = 0;
	void played(unsigned bandit, double reward);

protected:
	std::vector<double> rewards; // Rewards by bandit obtained so far
	std::vector<unsigned> times_played; // Number of times we played each bandit
	unsigned step;
};

class NaiveGreedy : public GreedyStrategy {
public:
	NaiveGreedy(unsigned n_b) : GreedyStrategy(n_b) {}

	unsigned choice();
};

class EpsilonGreedy : public GreedyStrategy {
public:
	EpsilonGreedy(unsigned n_b, double e) : GreedyStrategy(n_b), epsilon(e), distr_epsilon(0.,1.), distr_bandit(0, n_b - 1) {}

	unsigned choice();

private:
	double epsilon;
	distribution::continuous_uniform distr_epsilon;
	distribution::discrete_uniform distr_bandit;
};

class VanishingGreedy : public GreedyStrategy {
public:
	VanishingGreedy(unsigned n_b, double e) : GreedyStrategy(n_b), d(e), distr_epsilon(0.,1.), distr_bandit(0, n_b - 1), values_computed(false), gamma(1.), max_value(0.), max_bandits(n_b, false) {}

	void computeValues();
	void played(unsigned bandit, double reward);
	unsigned choice();


private:
	double d;
	distribution::continuous_uniform distr_epsilon;
	distribution::discrete_uniform distr_bandit;
	bool values_computed;
	double gamma;
	double max_value; // Max value in vector rewards
	unsigned n_max_bandits;
	std::vector<bool> max_bandits; // Bandits with max value
};

class UCB : public GreedyStrategy {
public:
	UCB(unsigned n_b, double alpha=4) : GreedyStrategy(n_b), distr_bandit(0, n_b - 1), alpha(alpha), values_computed(false), max_value(0.), max_bandits(n_b, false) {}

	void computeValues();
	void played(unsigned bandit, double reward);
	unsigned choice();

private:
	distribution::discrete_uniform distr_bandit;
	double alpha;
	bool values_computed;
	double max_value; // Max value in vector rewards
	unsigned n_max_bandits;
	std::vector<bool> max_bandits; // Bandits with max value
};

#endif
