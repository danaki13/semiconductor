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

	objPNDiodeIdeal.setValues(-1.0, 1e-8, 300);

	objPNDiodeIdeal.calculateOutputCurrent();

	objPNDiodeIdeal.writeHeader();
	objPNDiodeIdeal.readHeader();
	objPNDiodeIdeal.printHeader();

	return 0;
}