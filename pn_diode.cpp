#include <iostream>
#include <cmath>
#include "function.h"

void PNDiodeIdeal::setValues(double voltV, double currentA, double tempK) {
	voltage = voltV;
	saturation_current = currentA;
	temperature = tempK;
}

double PNDiodeIdeal::calculateOutputCurrent() {
	double output_current = 0.0;

	output_current = saturation_current * (exp((E_CHARGE * voltage)/(K_BOLTZMANN * temperature)) - 1);
	std::cout << voltage << " " << output_current << std::endl;

	return output_current;
}