// function.h

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

	void setValues(double, double, double);

	#ifndef MESSAGE
	double calculateOutputCurrent();
	#else
	double calculateOutputCurrent(Message);
	#endif
};

#endif