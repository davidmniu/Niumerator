#ifndef NIUTRON_H 
#define NIUTRON_H 

#include <string>
#include <vector>

class Niutron {
	public:
		// constructors
		Niutron();
		Niutron(std::string expression);

		// getter and  setter
		void setExpression(std::string expression);
		std::vector<char> getExpression();

		// Function to evaluate vector containing postfix
		double evaluate(double x = 0, double y = 0, double z = 0);
	
	private:
		std::vector<char> postVec;

		// Function to turn expression given as string into 
		// a vector of strings representing postfix
		std::vector<char> stringToPostfix(std::string expression);
};

#endif
