#include <iostream>
#include "function.h"

int main(void) {
	PNDiodeIdeal objPNDiodeIdeal;

#ifdef MESSAGE
	Message objMessage;
	objMessage.setVerbosity(VERBOSITY);
	objMessage.printMessage(DEBUG, "Debug message ON");
	objMessage.printMessage(INFO, "Information message ON");
	objMessage.printMessage(WARNING, "Warning message ON");
	objMessage.printMessage(ERROR, "Error message ON");
#endif

	objPNDiodeIdeal.setValues(-1.0, 1e-8, 300);

	#ifndef MESSAGE
	objPNDiodeIdeal.calculateOutputCurrent();
	#else
	objPNDiodeIdeal.calculateOutputCurrent(objMessage);
	#endif

	return 0;
}