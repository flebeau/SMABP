#ifndef STRATEGY_HPP_
#define STRATEGY_HPP_

#include <vector>
#include <random>

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
	GreedyStrategy(unsigned n_b) : Strategy(n_b), rewards(n_b,0.), times_played(n_b, 0) {}
	
	virtual unsigned choice() = 0;
	void played(unsigned bandit, double reward);
	
protected:
	std::vector<double> rewards; // Rewards by bandit obtained so far
	std::vector<unsigned> times_played; // Number of times we played each bandit
};

class NaiveGreedy : public GreedyStrategy {
public:
	NaiveGreedy(unsigned n_b) : GreedyStrategy(n_b) {}
	
	unsigned choice();
};

class EpsilonGreedy : public GreedyStrategy {
public:
	EpsilonGreedy(unsigned n_b, double e) : GreedyStrategy(n_b), epsilon(e), engine_epsilon(), distr_epsilon(0.,1.), engine_bandit(), distr_bandit(0, n_b - 1) {}
	
	unsigned choice();
	
private:
	double epsilon;
	std::default_random_engine engine_epsilon;
	std::uniform_real_distribution<double> distr_epsilon;
	std::default_random_engine engine_bandit;
	std::uniform_int_distribution<unsigned> distr_bandit;
};

#endif
