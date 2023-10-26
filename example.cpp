#include <iostream>
#include <string>
#include <cmath>
#include "pn_diode.h"
#include "configure.h"

int main(int argc, char* argv[]) {
	if (argc < 2) {
		std::cout << "Usage: pn_diode filename.cfg" << std::endl; // NEEDS test
		return 2;
	}

	PNDiodeIdeal objPNDiodeIdeal;
	std::vector<Input> vectorInput;

#ifdef MESSAGE
	printMessage(VERBOSITY, DEBUG, "Debug message ON");
	printMessage(VERBOSITY, INFO, "Information message ON");
	printMessage(VERBOSITY, WARNING, "Warning message ON");
	printMessage(VERBOSITY, ERROR, "Error message ON");
#endif

	/* Read from the config file the simulation setup */
	readCFG(argv[1], vectorInput);
	objPNDiodeIdeal.writeHeader(vectorInput[0].output);

	for(int i = vectorInput[0].variable.size(); i >= 0; i--) { /* So that in the CFG I have the variable on top that i want on the inner loop */
		if(vectorInput[0].points[i] > 1) {
			int j = 0;
			double step = (std::fabs(vectorInput[0].minimum[i]) + std::fabs(vectorInput[0].maximum[i])) / vectorInput[0].points[i];
			double voltage = vectorInput[0].minimum[i]+step*j;
			
			while(voltage <= vectorInput[0].maximum[i]) {
				objPNDiodeIdeal.setValues(voltage, 1e-10, 300);
				objPNDiodeIdeal.calculateOutputCurrent();
				objPNDiodeIdeal.writeData(vectorInput[0].output);
				j++;
				voltage = vectorInput[0].minimum[i]+step*j;
			}
		}
	}

	return 0;
}