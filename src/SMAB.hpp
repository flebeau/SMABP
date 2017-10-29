#ifndef SMAB_HPP_
#define SMAB_HPP_

#include <vector>
#include <memory>
#include "bandit.hpp"

class SMAB {
public:
	std::size_t size() const; // Returns number of bandits
	double play(unsigned b) const; // Simulate the reward by taking bandit b
	void add(Bandit *bandit);
	
private:
	std::vector<std::unique_ptr<Bandit> > bandits;
};

#endif
