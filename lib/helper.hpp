#ifndef HELPER_H
#define HELPER_H

#include <string>
#include <vector>

// check if char is digit
bool isDig(char a);

// check if char is variable
bool isVar(char a);

// check if char is e or pi
bool isConst(char a);

// check if char is mathematical operator
bool isOp(char a);

// get priority level of operator
int opPriority(char a);

// return an error vector 
std::vector<char> returnError(char a);

// print vector<char>
void print(std::vector<char> vec);

// print vector<double>
void print(std::vector<double> vec);

// parse operator as required in Dijkstra's
// shunting yard algorithm
void parseOp(std::vector<char>& opStack, std::vector<char>& output, char token);

// to check if a variable or constant follows a
// digit, variable, or constant
bool followsMult(std::string& equation, std::vector<char>::size_type i);

// do math operation on doubles a and b
double doOp(char op, double a, double b);

// apply trig function to double a
double doTrig(double a, char token);

#endif
