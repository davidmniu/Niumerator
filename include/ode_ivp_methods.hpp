#ifndef METHODS_H
#define METHODS_H

#include <vector>

class Niutron;

void printSolution(std::vector<std::vector<double>> solution);

std::vector<std::vector<double>> euler(Niutron* f, double a, double b, double N, double init);

std::vector<std::vector<double>> rk4(Niutron* f, double a, double b, double N, double init);

std::vector<std::vector<double>> rkf(Niutron* f, double a, double b, double init, double tol, double hmax, double hmin);

#endif 
