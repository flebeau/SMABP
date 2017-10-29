#ifndef SMAB_HPP_
#define SMAB_HPP_

#include <vector>
#include <memory>
#include "bandit.hpp"

class SMAB {
public:
	SMAB() : max_mean(0.) {}
	
	unsigned size() const; // Returns number of bandits
	double getMean(unsigned b) const; // Returns the mean of bandit b
	double getMaxMean() const; // Returns the maximum mean
	
	double play(unsigned b) const; // Simulate the reward by taking bandit b
	void add(Bandit *bandit);
	
private:
	std::vector<std::unique_ptr<Bandit> > bandits;
	double max_mean;
};

#endif
