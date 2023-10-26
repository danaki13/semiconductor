#include <iostream>
#include <fstream>
#include <limits>
#include <regex>
#include <cmath>
#include "configure.h"
#include "message.h"

int readCFG(const std::string &file_name, std::vector<Input> &vectorInput) {
	int flag = -1;
	Input vectorTemp;
	std::string line;
	std::regex reg_exp_section("\\[([^\\]]+)\\]");
	std::regex reg_exp_output("\\s*output\\s*=\\s*(\\S+)");
	std::regex reg_exp_variable("\\s*(\\w+)\\s*=");
	std::regex reg_exp_float("[+-]?([0-9]*[.])?([0-9]+)([eE][+-]?[0-9]+)?");
	std::smatch match;

	std::ifstream infile(file_name);
	if(infile) {
		while(getline(infile, line)) {
			/* Extract Section */
			if(line.find("[") != std::string::npos
				&& line.find("]") != std::string::npos
				&& line.find("#") == std::string::npos) {
				
				/* Update the Vector */
				if(!vectorTemp.simulation.empty()) {
					if(vectorTemp.output.empty()) {
						std::cout << "WARNING: no output is defined, using default.plt!" << std::endl;
						vectorTemp.output = "default.plt";
						flag = 1;
					}
					vectorInput.push_back(vectorTemp);
					vectorTemp = Input();
				}

				regex_search(line, match, reg_exp_section);
				vectorTemp.simulation = match.str(1);
			/* Extract Section VALUES */
			} else if (line.find("[") == std::string::npos
					&& line.find("]") == std::string::npos
					&& line.find("#") == std::string::npos
					&& line.find("=") != std::string::npos) {
				
				if(line.find("output") != std::string::npos) {
					regex_search(line, match, reg_exp_output);
					vectorTemp.output = match.str(1);
				} else if(line.find("points") == std::string::npos) { /* NOT points*/
					regex_search(line, match, reg_exp_variable);
					vectorTemp.variable.push_back(match.str(1));
					line = match.suffix(); /* remove part that is extracted */

					if(line.find(",") == std::string::npos) { /* NOT , */
						regex_search(line, match, reg_exp_float);
						vectorTemp.constant.push_back(std::stod(match.str()));

						vectorTemp.minimum.push_back(std::numeric_limits<double>::quiet_NaN());
						vectorTemp.maximum.push_back(std::numeric_limits<double>::quiet_NaN());
						vectorTemp.points.push_back(-1);
					} else if(line.find(",") != std::string::npos) { /* Has , */
					vectorTemp.constant.push_back(std::numeric_limits<double>::quiet_NaN());
					// left is minimum
					regex_search(line, match, reg_exp_float);
					vectorTemp.minimum.push_back(std::stod(match.str()));
					line = match.suffix();
					// right is maximum
					regex_search(line, match, reg_exp_float);
					vectorTemp.maximum.push_back(std::stod(match.str()));

					size_t size_temp = vectorTemp.minimum.size() - 1;
					if(vectorTemp.minimum[size_temp] > vectorTemp.maximum[size_temp]) {
						double temp = vectorTemp.minimum[size_temp];

						std::cout << "WARNING: for [" << vectorTemp.variable[size_temp] << "] with [" << vectorTemp.minimum[size_temp] << "," << vectorTemp.maximum[size_temp] << "] the left side value must be smaller than the right! Swapping." << std::endl;
						/* Swapping left with right */
						vectorTemp.maximum[size_temp] = vectorTemp.minimum[size_temp];
						vectorTemp.minimum[size_temp] = temp;
						vectorTemp.output = "default.plt";
						flag = 1;
					}
					
					getline(infile, line);
					if(line.find("points") != std::string::npos) { /* Must be points */
						regex_search(line, match, reg_exp_float);
						vectorTemp.points.push_back(std::stoi(match.str()));

						size_t size_temp = vectorTemp.points.size() - 1;
						if(vectorTemp.points[size_temp] < 1
							|| std::fabs(std::stod(match.str()) - std::stoi(match.str())) > 1e-9) {
							std::cout << "WARNING: points must be an integer, and equal or greater than 1! Setting to default 1." << std::endl;
							/* Setting 1 */
							vectorTemp.points[size_temp] = 1;
							flag = 1;
						}
					} else {
						vectorTemp.points.push_back(1);
						size_t size_temp = vectorTemp.points.size() - 1;
						std::cout << "WARNING: no points are defined for the [" << vectorTemp.variable[size_temp] << "] with [" << vectorTemp.minimum[size_temp] << "," << vectorTemp.maximum[size_temp] << "]! Setting to default 1." << std::endl;
						flag = 1;
					}
					}
				}
			}
		}
		vectorInput.push_back(vectorTemp);
		infile.close();
		if(flag == -1) flag = 0;
	} else {
		std::cout << "ERROR: configuration file does not exist!" << std::endl;
		flag = 2;
	}
	return flag;
}