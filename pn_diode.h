// function.h
#include <vector>
#include <string>

#define E_CHARGE 1.602E-19
#define K_BOLTZMANN 1.3806488E-23

#ifndef FUNCTION_H
#define FUNCTION_H

#ifdef MESSAGE
#include "message.h"
#endif

class PNDiodeIdeal {
public:
	/* data */
	double voltage;
	double saturation_current;
	double temperature;
	double output_current;

	/* File header */
	std::string version;
	std::string type;
	std::vector<std::string> datasets;

	/* Data */
	std::vector<std::vector<double>> data;

	void setValues(double, double, double);
	double calculateOutputCurrent();

	void writeHeader();
	void readHeader();
	void printHeader();

	void writeData();
	void readData();
	void printData();
};

#endif