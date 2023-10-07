#include <iostream>
#include <cmath>
#include "function.h"

void PNDiodeIdeal::setValues(double voltV, double currentA, double tempK) {
	voltage = voltV;
	saturation_current = currentA;
	temperature = tempK;
}

#ifndef MESSAGE
double PNDiodeIdeal::calculateOutputCurrent() {
	double output_current = 0.0;

	output_current = saturation_current * (exp((E_CHARGE * voltage)/(K_BOLTZMANN * temperature)) - 1);

	return output_current;
}
#else
double PNDiodeIdeal::calculateOutputCurrent(Message objMessage) {
	double output_current = 0.0;

	output_current = saturation_current * (exp((E_CHARGE * voltage)/(K_BOLTZMANN * temperature)) - 1);

	objMessage.printMessage(DEBUG, std::to_string(voltage) + " " + std::to_string(output_current));

	return output_current;
}
#endif