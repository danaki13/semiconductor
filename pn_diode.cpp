#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>
#include <regex>
#include "pn_diode.h"

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

void PNDiodeIdeal::writeHeader(const std::string &file_name) {
	std::ofstream outfile(file_name);

	outfile << "Info {" << std::endl;
	outfile << "  version = 1.0" << std::endl;
	outfile << "  type = xyplot" << std::endl;
	outfile << "  datasets  = [\n    \"voltage\"\n"
				"    \"saturation current\" \"temperature\" \"output current\" ]" << std::endl;
	outfile << "}" << std::endl;
	outfile << "Data {" << std::endl;
	outfile.close();
}

void PNDiodeIdeal::readHeader(const std::string &file_name) {
	std::string line;
	std::ifstream infile(file_name);
	std::regex reg_exp_version("([0-9]*[.])?[0-9]+");
	std::regex reg_exp_type("\\b\\w+plot\\b");
	std::regex reg_exp_datasets("\"([^\"]+)\"");
	std::smatch match;

	while(getline(infile, line)) {
		if(line.find("version") != std::string::npos) {
			regex_search(line, match, reg_exp_version);
			version = match.str();
		}

		if(line.find("type") != std::string::npos) {
			regex_search(line, match, reg_exp_type);
			type = match.str();
		}

		if(line.find("datasets") != std::string::npos) {
			do {
				while(regex_search(line, match, reg_exp_datasets)) {
					datasets.push_back(match.str(1));
					line = match.suffix();
				}
				/* Not necessary to read further, the header reading is completed. */
				if(line.find("]") != std::string::npos) {
					infile.close();
					return;
				}
			} while(getline(infile, line));
		}
	}	
	infile.close();
}

void PNDiodeIdeal::printHeader() { // NEEDS TEST!!!
	int count = 0;
	std::cout << "Version: " + version << std::endl;
	std::cout << "Type: " + type << std::endl;
	for(std::string value : datasets) {
		std::cout << "Dataset[" << count << "]: " << value << std::endl;
		count++;
	}
	
}

void PNDiodeIdeal::writeData(const std::string &file_name) {
	std::ofstream outfile(file_name, std::ios::app);

	/* Set the output format */
	outfile << std::scientific << std::showpos << std::setprecision(6);
	outfile << "\t" << voltage << " "
					<< saturation_current << " "
					<< temperature << " "
					<< output_current
					<< std::endl;

	outfile.close();
}

void PNDiodeIdeal::readData(const std::string &file_name) {
	std::string line;
	std::ifstream infile(file_name);
	std::regex reg_exp_data("[+-]?([0-9]*[.])?([0-9])+e[+-]?[0-9]+");
	std::smatch match;

	while(getline(infile, line)) {
		if(line.find("Data {") != std::string::npos) {
			do {
				std::vector<double> row;
				while(regex_search(line, match, reg_exp_data)) {
					row.push_back(std::stod(match.str()));
					line = match.suffix();
				}
				if(row.size() > 0) {
					data.push_back(row);
				}
			} while(getline(infile, line));
		}
	}
	
	infile.close();
}

void PNDiodeIdeal::printData() { // NEEDS TEST!!!
	std::cout << std::scientific << std::showpos << std::setprecision(6);
	for(const auto& row : data) {
		for(double value : row) {
			std::cout << value << ' ';
		}
		std::cout << '\n';
	}	
}