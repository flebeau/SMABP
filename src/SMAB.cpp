#include "SMAB.hpp"

unsigned SMAB::size() const {
	return bandits.size();
}

double SMAB::getMean(unsigned int b) const {
	return bandits.at(b)->getMean();
}

double SMAB::getMaxMean() const {
	return max_mean;
}

double SMAB::play(unsigned b) const {
	return bandits.at(b)->play();
}

void SMAB::add(Bandit *bandit) {
	bandits.push_back(std::unique_ptr<Bandit>(bandit));
	if (max_mean < bandit->getMean())
		max_mean = bandit->getMean();
}
