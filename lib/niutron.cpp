#include <algorithm>
#include <iostream>
#include <unordered_set>
#include <cmath>
#include "niutron.hpp"
#include "helper.hpp"

// convert expression string to postfix vector of chars
// using Dijkstra's shunting yard algorithm:
/*
	https://en.wikipedia.org/wiki/Shunting-yard_algorithm#The_algorithm_in_detail
*/

Niutron::Niutron() {
	postVec = {0};
}

Niutron::Niutron(std::string expression) {
	// TODO: Validate expression
	postVec = stringToPostfix(expression);
}

void Niutron::setExpression(std::string expression) {
	// TODO: Validate expression
	postVec = stringToPostfix(expression);
}

std::vector<char> Niutron::getExpression() {
	return postVec;
}

std::vector<char> Niutron::stringToPostfix(std::string expression) {
	std::vector<char> output;
	std::vector<char> opStack;
	for (std::vector<char>::size_type i = 0; i < expression.length(); i++) {
		char token = expression[i];
		/*
		// * for debugging
		std::cout << "output: ";
		print(output);
		std::cout << "opStack: ";
		print(opStack);
		*/
		// if number, put into output queue
		if (isDig(token)) {
			// if (i == 0 || !isDig(expression[i-1])) output.push_back('[');
			output.push_back(token);
			// if (i == expression.length - 1 || !isDig(expression[i+1]) output.push_back(']');
		// if variable or exponential, put into output queue
		} else if (isVar(token) || token == 'e') {
			if (i > 0) {
				// check if it follows multiplier
				if (followsMult(expression, i)) {
					parseOp(opStack, output, '*');
				}
			}
			output.push_back(token);
		// if constant is pi, put into output queue 
		} else if (token == 'p' && expression[i+1] == 'i') {
			// again, if pi follows multiplier
			if (followsMult(expression, i)) {
				parseOp(opStack, output, '*');
			}
			output.push_back(token);
			i++;
		// if trig function (sin, cos, tan), push onto opStack
		} else if ((token == 's' && expression[i+1] == 'i' && expression[i+2] == 'n') ||
			(token == 'c' && expression[i+1] == 'o' && expression[i+2] == 's') ||
			(token == 't' && expression[i+1] == 'a' && expression[i+2] == 'n')) {
			// once more, if follows multiplier
			if (!output.empty()) {
				if (followsMult(expression, i)) {
					parseOp(opStack, output, '*');
				}
			}
			opStack.push_back(token);
			i+=2;
		// if operator, pop operators with lower precedence on opStack
		// onto output, then put token onto output as well
		} else if (isOp(token)) {
			parseOp(opStack, output, token);
		// if '(', push onto opStack
		} else if (token == '(') {
			opStack.push_back(token);
		// if ')', go back down opStack until hit '('
		} else if (token == ')') {
			// pop out operators onto output queue
			// until closing left parenthesis is found
			while (opStack.back() != '(') {
				if (!opStack.empty()) {
					output.push_back(opStack.back());
					opStack.pop_back();
				// error if empty and left parenthesis not found
				} else return returnError('1');
			}
			// check for matching left parenthesis
			if (opStack.back() == '(') {
				opStack.pop_back();
			} else return returnError('2');
			// take care of case of preceeding trig function
			if (opStack.back() == 's' || opStack.back() == 'c' || opStack.back() == 't') {
				output.push_back(opStack.back());
				opStack.pop_back();
			}
			i++;
		}
	}
	// now pop remaining elements from opStack onto output
	for (int i = opStack.size() - 1; i >= 0; i--) {
		// check that there are no parenthesis on opStack
		if (opStack[i] != '(' && opStack[i] != ')') {
			output.push_back(opStack[i]);
		// if parenthesis are still left, we have a problem
		} else {
			return returnError('3');
		} 
	}
	return output;
}

// evaluate postfix char vector and return double
double Niutron::evaluate(double x, double y, double z) {
	std::vector<double> valStack = {};
	// iterate through vector containg postfix
	for (char token : postVec) {
		// if digit, const, or variable, push onto valStack
		if (token >= '0' && token <= '9') {
			valStack.push_back(token - 48);
		} else if (token == 'e') valStack.push_back(std::exp(1.0));
		else if (token == 'p') valStack.push_back(M_PI);
		else if (token == 'x') valStack.push_back(x);
		else if (token == 'y') valStack.push_back(y);
		else if (token == 'z') valStack.push_back(z);
		// if operator, pop last two values off valStack 
		// and evalute, then put result back onto valStack
		else if (isOp(token)) {
			double b = valStack.back();
			valStack.pop_back();
			double a = valStack.back();
			valStack.pop_back();
			valStack.push_back(doOp(token, a, b));			
		// if function, pop last value off valStack 
		// and evalute, then put result back onto valStack
		} else if (token == 's' || token == 'c' || token == 't') {
			double a = valStack.back();
			valStack.pop_back();
			valStack.push_back(doTrig(a, token));
		// invalid input, return NaN
		} else return nan("");
	}
	return valStack[0];
}
