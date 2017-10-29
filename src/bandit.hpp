#ifndef BANDIT_HPP_
#define BANDIT_HPP_

#include <random>

class Bandit {
public:
	Bandit(double m) : mean(m) {}
	
	const double &getMean() const {return mean;}
	
	virtual double play() const = 0;
	
private:
	double mean;
};

class DeterministicBandit : public Bandit {
public:
	DeterministicBandit(double m) : Bandit(m) {}
	
	virtual double play() const;	
};

class UniformBandit : public Bandit {
public:
	UniformBandit(double m, double lower = 0.) : Bandit(m), engine(), distr(lower,2.*m - lower) {}
	
	virtual double play() const;
	
private:
	std::default_random_engine engine;
	std::uniform_real_distribution<double> distr;
};

#endif
