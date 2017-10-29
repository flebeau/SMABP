#ifndef BANDIT_HPP_
#define BANDIT_HPP_

#include <random>
#include "random.hpp"

class Bandit {
public:
	Bandit(double m) : mean(m) {}
	
	const double &getMean() const {return mean;}
	
	virtual double play() = 0;
	
protected:
	double mean;
};

class DeterministicBandit : public Bandit {
public:
	DeterministicBandit(double m) : Bandit(m) {}
	
	virtual double play();
};

class UniformBandit : public Bandit {
public:
	UniformBandit(double m, double lower = 0.) : Bandit(m), distr(lower,2.*m - lower) {}
	
	virtual double play();
	
private:
	distribution::continuous_uniform distr;
};

#endif
