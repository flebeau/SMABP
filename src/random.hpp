#ifndef RANDOM_HPP_
#define RANDOM_HPP_

#include <random>

namespace distribution {
class discrete_uniform {
public:
	discrete_uniform(unsigned a, unsigned b) : rd(), mt(rd()), distr(a,b) {}
	
	unsigned operator()() {
		return distr(mt);
	}
	
private:
	std::random_device rd;
	std::mt19937 mt;
	std::uniform_int_distribution<unsigned> distr;
};

class continuous_uniform {
public:
	continuous_uniform(double a, double b) : rd(), mt(rd()), distr(a,b) {}
	
	double operator()() {
		return distr(mt);
	}
	
private:
	std::random_device rd;
	std::mt19937 mt;
	std::uniform_real_distribution<double> distr;
};
}

#endif
