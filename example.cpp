#include <iostream>
#include "function.h"

int main(void) {
	PNDiodeIdeal objPNDiodeIdeal;

#ifdef MESSAGE
	printMessage(VERBOSITY, DEBUG, "Debug message ON");
	printMessage(VERBOSITY, INFO, "Information message ON");
	printMessage(VERBOSITY, WARNING, "Warning message ON");
	printMessage(VERBOSITY, ERROR, "Error message ON");
#endif

	objPNDiodeIdeal.writeHeader();
	for(int i = 0; i < 100; i++) {
		objPNDiodeIdeal.setValues(0.01*i, 1e-10, 300);
		objPNDiodeIdeal.calculateOutputCurrent();
		objPNDiodeIdeal.writeData();
	}

	return 0;
}