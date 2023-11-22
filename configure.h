#include <vector>
#include <string>

#ifndef CONFIGURE_H
#define CONFIGURE_H


struct Input {
	std::string simulation;
	std::string output;

	std::vector<std::string> variable;
	std::vector<double> constant;
	std::vector<double> minimum;
	std::vector<double> maximum;
	std::vector<int> points;
};


int readCFG(const std::string &, std::vector<Input> &vectorInput);
void updateVector(const std::string &, Input &vectorTemp, std::vector<Input> &vectorInput, int &);
void initialisePNDiodeIdeal(Input &vectorTemp, bool, bool, bool);

#endif