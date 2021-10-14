#include <iostream>

#include "../include/ode_ivp_methods.hpp"
#include "../lib/eqparser.hpp"

int main() {
	EqParser *expr = new EqParser("y-x^2+1");
	//std::vector<std::vector<double>> solution = rk4(expr, 0, 2, 10, 0.5);
	std::vector<std::vector<double>> solution = rkf(expr, 0, 2, 0.5, 10e-5, 0.25, 0.01);
	printSolution(solution);
	return 0;
}
