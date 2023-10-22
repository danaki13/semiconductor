#include <iostream>
#include <fstream>
#include <cmath>
#include <regex>
#include "function.h"

void PNDiodeIdeal::setValues(double voltV, double currentA, double tempK) {
	voltage = voltV;
	saturation_current = currentA;
	temperature = tempK;
	output_current = 0.0;
}

double PNDiodeIdeal::calculateOutputCurrent() {
	output_current = saturation_current * (exp((E_CHARGE * voltage)/(K_BOLTZMANN * temperature)) - 1);

	#ifdef MESSAGE
	const char* file = __FILE__;
	const char* func = __func__;
	std::string fileString(file);
	std::string funcString(func);

	printMessage(VERBOSITY, DEBUG, fileString + ":" + std::to_string(__LINE__) + ":" + funcString + ": " + std::to_string(voltage) + " " + std::to_string(output_current));
	#endif

	return output_current;
}

void PNDiodeIdeal::writeHeader() {
	std::ofstream outfile("test.plt");

	outfile << "Info {" << std::endl;
	outfile << "  version = 1.0" << std::endl;
	outfile << "  type = xyplot" << std::endl;
	outfile << "  datasets  = [\n    \"time\"\n"
				"    \"drain OuterVoltage\" \"drain TotalCurrent\" \"source OuterVoltage\"\n"
				"    \"source InnerVoltage\" \"source TotalCurrent\" ]\n" << std::endl;
	outfile << "}" << std::endl;
	outfile.close();
}

void PNDiodeIdeal::readHeader() {
	std::string line;
	std::ifstream infile("test.plt");
	std::regex reg_exp_version("([0-9]*[.])?[0-9]+");
	std::regex reg_exp_type("\\b\\w+plot\\b");
	std::regex reg_exp_datasets("\"([^\"]+)\"");
	std::smatch match;

	while(getline(infile, line)) {
		if (line.find("version") != std::string::npos) {
			regex_search(line, match, reg_exp_version);
			version = match.str();
		}

		if (line.find("type") != std::string::npos) {
			regex_search(line, match, reg_exp_type);
			type = match.str();
		}

		if (line.find("datasets") != std::string::npos) {
			while (line.find("]") == std::string::npos) {
				getline(infile, line);
				while (std::regex_search(line, match, reg_exp_datasets)) {
					datasets.push_back(match.str(1));
					line = match.suffix();
				}
			}
		}
	}
	
	infile.close();
}

void PNDiodeIdeal::printHeader() { // NEEDS TEST!!!
	int count = 0;
	std::cout << "Version: " + version << std::endl;
	std::cout << "Type: " + type << std::endl;
	for (std::string value : datasets) {
		std::cout << "Dataset[" + std::to_string(count) + "]: " << value << std::endl;
		count++;
	}
	
}