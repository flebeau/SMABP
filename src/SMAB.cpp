#include "SMAB.hpp"

unsigned SMAB::size() const {
	return bandits.size();
}

double SMAB::play(unsigned b) const {
	return bandits.at(b)->play();
}

void SMAB::add(Bandit *bandit) {
	bandits.push_back(std::unique_ptr<Bandit>(bandit));
}
