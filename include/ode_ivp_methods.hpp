#ifndef METHODS_H
#define METHODS_H

#include <vector>

class EqParser;

void printSolution(std::vector<std::vector<double>> solution);

std::vector<std::vector<double>> euler(EqParser* f, double a, double b, double N, double init);

std::vector<std::vector<double>> rk4(EqParser* f, double a, double b, double N, double init);

std::vector<std::vector<double>> rkf(EqParser* f, double a, double b, double init, double tol, double hmax, double hmin);

#endif 
