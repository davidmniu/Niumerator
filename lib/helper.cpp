#include <algorithm>
#include <iostream>
#include <unordered_set>
#include <cmath>
#include "helper.hpp"

// check if char is digit
bool isDig(char a) {
	return (a >= '0' && a <= '9');
}

// check if char is variable
bool isVar(char a) {
	return (a == 'x' || a == 'y' || a == 'z'); 
}

// check if char is e or pi
bool isConst(char a) {
	return (a == 'e' || a == 'p');
}

// check if char is mathematical operator
bool isOp(char a) {
	std::unordered_set<char> ops = {'+', '-', '*', '/', '^'};
	std::unordered_set<char>::const_iterator got = ops.find(a);
	return (got != ops.end());
}

// get priority level of operator
int opPriority(char a) {
	if (a == ')' || a == '(') return 4;
	else if (a == '^') return 3;
	else if (a == '*' || a == '/') return 2;
	else if (a == '+' || a == '-') return 1;
	else return 0;
}

// return an error vector 
std::vector<char> returnError(char a) {
	return {'e', 'r', 'r', 'o', 'r', ' ', a};
}

// print vector<char>
void print(std::vector<char> vec) {
	for (char i : vec) {
		std::cout << i << ' ';
	}
	std::cout << '\n';
}

// print vector<double>
void print(std::vector<double> vec) {
	for (double i : vec) {
		std::cout << i << ' ';
	}
	std::cout << '\n';
}

// parse operator as required in Dijkstra's
// shunting yard algorithm
void parseOp(std::vector<char>& opStack, std::vector<char>& output, char token) {
	if (!opStack.empty()) {
		while (isOp(opStack.back()) &&
			(opPriority(opStack.back()) >  opPriority(token) || 
			 (opPriority(opStack.back()) == opPriority(token) && token != '^'))) {
			output.push_back(opStack.back());
			opStack.pop_back();
		}
	}
	opStack.push_back(token);
}

// to check if a variable or constant follows a
// digit, variable, or constant
bool followsMult(std::string& equation, std::vector<char>::size_type i) {
	char a = equation[i-1];
	return (isDig(a) || isVar(a) || isConst(a));
}


// do math operation on doubles a and b
double doOp(char op, double a, double b) {
	if (op == '+') return a + b;
	else if (op == '-') return a - b;
	else if (op == '*') return a * b;
	else if (op == '/') return a / b;
	else if (op == '^') return std::pow(a, b);
	else return nan(""); 
}

// apply trig function to double a
double doTrig(double a, char token) {
	if (token == 's') return std::sin(a);
	else if (token == 'c') return std::cos(a);
	else if (token == 't') return std::tan(a);
	else return nan("");
}
