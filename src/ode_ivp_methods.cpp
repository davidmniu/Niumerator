#include <iostream>
#include <cmath>
#include "../lib/niutron.hpp"
#include "../include/ode_ivp_methods.hpp"

void printSolution(std::vector<std::vector<double>> solution) {
	for (auto i : solution) {
		std::cout << "(" << i[0] << ", " << i[1] << ")" << std::endl;
	}
}

std::vector<std::vector<double>> euler(Niutron* f, double a, double b, double N, double init) {
	std::vector<std::vector<double>> output;
	double h = (b-a)/N;
	double t = a;
	double w = init;
	output.push_back({t,w});
	for (int i = 1; i <= N; i++) {
		w = w + h*(f->evaluate(t,w));
		t = a + i*h;
		output.push_back({t,w});
	}
	return output;
}

std::vector<std::vector<double>> rk4(Niutron* f, double a, double b, double N, double init) {
	std::vector<std::vector<double>> output;
	double k1, k2, k3, k4;
	double h = (b-a)/N;
	double t = a;
	double w = init;
	output.push_back({t,w});
	for (int i = 1; i <= N; i++) {
		k1 = h*(f->evaluate(t,w));
		k2 = h*(f->evaluate(t+h/2, w+k1/2));
		k3 = h*(f->evaluate(t+h/2, w+k2/2));
		k4 = h*(f->evaluate(t+h, w+k3));
		w = w + (k1 + 2*k2 + 2*k3 + k4) / 6;
		t = a + i*h;
		output.push_back({t,w});
	}
	return output;
}

// TODO: Check method for mistakes
std::vector<std::vector<double>> rkf(Niutron* f, double a, double b, double init, double tol, double hmax, double hmin) {
	std::vector<std::vector<double>> output;
	double k1, k2, k3, k4, k5, k6, r, delta;
	double h = hmax;
	double t = a;
	double w = init;
	output.push_back({t,w});
	while (true) {
		k1 = h*(f->evaluate(t,w));
		k2 = h*(f->evaluate(t+h/4, w+k1/4));
		k3 = h*(f->evaluate(t+3*h/8, w+3*k1/32 + 9*k2/32));
		k4 = h*(f->evaluate(t + 12*h/13, w + 1932*k1/2197 - 7200*k2/2197 + 7296*k3/2197));
		k5 = h*(f->evaluate(t+h, w + 439*k1/216 - 8*k2 + 3680*k2/513 - 845*k4/4104));
		k6 = h*(f->evaluate(t+h/2, w - 8*k1/27 + 2*k2 - 3544*k3/2565 + 1859*k4/4104 - 11*k5/40));
		r = fabs(k1/360 - 128*k3/4275 - 2197*k4/75240 + k5/50 + 2*k6/55)/h;
		if (r <= tol) {
			t = t+h;
			w = w + 25*k1/216 + 1408*k3/2565 + 2197*k4/4104 - k5/5;
			output.push_back({t,w,h});
		}
		delta = 0.84*pow((tol/r), 0.25);
		if (delta <= 0.1) {
			h = 0.1*h;
		} else if (delta >= 4) {
			h = 4*h;
		} else h = delta*h;
		if (h > hmax) h = hmax;
		if (t >= b) {
			break;
		} else if (t + h > b) {
			h = b-t;
		} else if (h < hmin) {
			break;
			// minimum h exceeded
		}
	}
	return output;
}
