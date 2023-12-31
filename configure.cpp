#include <iostream>
#include <fstream>
#include <limits>
#include <regex>
#include <cmath>
#include "configure.h"
#include "message.h"

/* Read and process configuration for simulations.
	Simulation options:
		PN_DIODE_IDEAL - possible variables are [voltage, saturation_current, temperature, output]
			[points] is a possible option for one variable at a time to be simulated for a range of values
	FLAGS:
		flag - returns 0 on success and 2 on file error
		flag_points - check that the variable that has a range of simulation is followed by points, and
			that only one variable has a range of values for a single simulation set
*/
int readCFG(const std::string &file_name, std::vector<Input> &vectorInput) {
	int flag = -1, flag_points = 0;
	int line_counter = 0;
	Input vectorTemp;
	std::string line;
	std::regex reg_exp_section("\\[([^\\]]+)\\]"); /* [EXTRACT] */
	std::regex reg_exp_output("\\s*output\\s*=\\s*(\\S+)"); /* output = EXTRACT */
	std::regex reg_exp_variable("\\s*(\\w+)\\s*="); /* EXTRACT = */
	std::regex reg_exp_float("[+-]?([0-9]*[.])?([0-9]+)([eE][+-]?[0-9]+)?"); /* -1.0e-12 */
	std::smatch match;

	std::ifstream infile(file_name);
	if(infile) {
		while(getline(infile, line)) {
			++line_counter;

			/* Extract Section [SECTION] */
			if(line.find("[") != std::string::npos
				&& line.find("]") != std::string::npos
				&& line.find("#") == std::string::npos) {
				
				/* Update the Vector */
				updateVector(vectorTemp.simulation, vectorTemp, vectorInput, flag_points);

				regex_search(line, match, reg_exp_section);
				vectorTemp.simulation = match.str(1);
			/* Extract Section VALUES <variable> = <value> or <variable> = <value, value> or <output> = <file_name> */
			} else if (line.find("[") == std::string::npos
					&& line.find("]") == std::string::npos
					&& line.find("#") == std::string::npos
					&& line.find("=") != std::string::npos
					&& vectorTemp.simulation == "PN_DIODE_IDEAL") {
				
				/* Part that reads the points for the variable simulated for a range
				that must be followed by points */
				if(line.find("points") != std::string::npos
					&& flag_points == 1) {

					regex_search(line, match, reg_exp_float);
					
					size_t size_temp = vectorTemp.points.size() - 1;
					vectorTemp.points[size_temp] = std::stoi(match.str());

					if(vectorTemp.points[size_temp] < 1) {
						std::cout << "WARNING(" << line_counter << "): points must be equal or greater than 1! Setting to default 2." << std::endl;
						vectorTemp.points[size_temp] = 2;
					} else if(std::fabs(std::stod(match.str()) - std::stoi(match.str())) > 1e-9) {
						std::cout << "WARNING(" << line_counter << "): points must be an integer! Converted to " << vectorTemp.points[size_temp] << "." << std::endl;
					}
					flag_points = 2; /* avoid picking up more than one line with points */
				} else if(line.find("points") != std::string::npos
					&& flag_points == 0) {

					std::cout << "WARNING(" << line_counter << "): variable has no range on previous line! Ignoring points." << std::endl;
				}

				/* Get variables and values */
				if(line.find("output") != std::string::npos) { /* output */
					regex_search(line, match, reg_exp_output);
					vectorTemp.output = match.str(1);
				} else if(line.find("points") == std::string::npos) { /* NO points */
					regex_search(line, match, reg_exp_variable);
					vectorTemp.variable.push_back(match.str(1));
					line = match.suffix(); /* remove part that is extracted */

					if(line.find(",") == std::string::npos) { /* NO , (constant value) */
						regex_search(line, match, reg_exp_float);
						vectorTemp.constant.push_back(std::stod(match.str()));

						vectorTemp.minimum.push_back(std::numeric_limits<double>::quiet_NaN());
						vectorTemp.maximum.push_back(std::numeric_limits<double>::quiet_NaN());
						vectorTemp.points.push_back(-1);
					} else if(line.find(",") != std::string::npos
						&& flag_points == 0) { /* Has , (value, value) */

						vectorTemp.constant.push_back(std::numeric_limits<double>::quiet_NaN());
						/* left is minimum */
						regex_search(line, match, reg_exp_float);
						vectorTemp.minimum.push_back(std::stod(match.str()));
						line = match.suffix();
						/* right is maximum */
						regex_search(line, match, reg_exp_float);
						vectorTemp.maximum.push_back(std::stod(match.str()));

						size_t size_temp = vectorTemp.minimum.size() - 1;
						if(vectorTemp.minimum[size_temp] > vectorTemp.maximum[size_temp]) {
							double temp = vectorTemp.maximum[size_temp];

							std::cout << "WARNING(" << line_counter << "): for [" << vectorTemp.variable[size_temp] << "] with [" << vectorTemp.minimum[size_temp] << "," << vectorTemp.maximum[size_temp] << "] the left side value must be smaller than the right! Swapping." << std::endl;

							/* Swapping left with right */
							vectorTemp.maximum[size_temp] = vectorTemp.minimum[size_temp];
							vectorTemp.minimum[size_temp] = temp;
						}

						vectorTemp.points.push_back(2); /* Set default 2 */
						flag_points = 1; /* Set to 1 so we know the next line must have points and no more ranges for future variables are allowed */
					} else if(line.find(",") != std::string::npos
						&& flag_points > 0) { /* Case when line has , but points were already added or does not follow range variable */

						std::cout << "WARNING(" << line_counter << "): Only one variable can have range for a simulation set." << std::endl;

						regex_search(line, match, reg_exp_float);
						vectorTemp.constant.push_back(std::stod(match.str()));
						vectorTemp.minimum.push_back(std::numeric_limits<double>::quiet_NaN());
						vectorTemp.maximum.push_back(std::numeric_limits<double>::quiet_NaN());
						vectorTemp.points.push_back(-1);
					}
				}
			}
		}
		/* Update the Vector */
		updateVector(vectorTemp.simulation, vectorTemp, vectorInput, flag_points);

		infile.close();
		if(flag == -1) {
			flag = 0;
		}
	} else {
		std::cerr << "ERROR: configuration file does not exist!" << std::endl;
		flag = 2;
	}
	return flag;
}

void updateVector(const std::string &simulation_name, Input &vectorTemp, std::vector<Input> &vectorInput, int &flag_points) {
	if(!vectorTemp.simulation.empty()
		&& vectorTemp.simulation == "PN_DIODE_IDEAL") {

		if(vectorTemp.output.empty()) {
			vectorTemp.output = "output.plt";
		}

		bool flag_voltage = false, flag_saturation_current = false, flag_temperature = false;
		if(vectorTemp.variable.empty())	{ /* no variable was defined -> set default values */
			initialisePNDiodeIdeal(vectorTemp, flag_voltage, flag_saturation_current, flag_temperature);
		} else if(vectorTemp.variable.size() < 3) {
			for(int i = 0; i < vectorTemp.variable.size(); i++) { /* loop through to identify which variables are already added */
				if(vectorTemp.variable[i] == "voltage") { /* voltage is present */
					flag_voltage = true;
				}
				if(vectorTemp.variable[i] == "saturation_current") { /* saturation_current is present */
					flag_saturation_current = true;
				}
				if(vectorTemp.variable[i] == "temperature") { /* temperature is present */
					flag_temperature = true;
				}
			}
			initialisePNDiodeIdeal(vectorTemp, flag_voltage, flag_saturation_current, flag_temperature);
		}
		
		vectorInput.push_back(vectorTemp);
		vectorTemp = Input();
		flag_points = 0; /* this is to avoid if incomplete CFG definition is at the EOF of CFG */
	}
}

void initialisePNDiodeIdeal(Input &vectorTemp, bool flag_voltage, bool flag_saturation_current, bool flag_temperature) {
	if(!flag_voltage) {
		vectorTemp.variable.push_back("voltage");
		vectorTemp.constant.push_back(0.7);
		vectorTemp.minimum.push_back(std::numeric_limits<double>::quiet_NaN());
		vectorTemp.maximum.push_back(std::numeric_limits<double>::quiet_NaN());
		vectorTemp.points.push_back(-1);
	}

	if(!flag_saturation_current) {
		vectorTemp.variable.push_back("saturation_current");
		vectorTemp.constant.push_back(1e-8);
		vectorTemp.minimum.push_back(std::numeric_limits<double>::quiet_NaN());
		vectorTemp.maximum.push_back(std::numeric_limits<double>::quiet_NaN());
		vectorTemp.points.push_back(-1);
	}

	if(!flag_temperature) {
		vectorTemp.variable.push_back("temperature");
		vectorTemp.constant.push_back(300);
		vectorTemp.minimum.push_back(std::numeric_limits<double>::quiet_NaN());
		vectorTemp.maximum.push_back(std::numeric_limits<double>::quiet_NaN());
		vectorTemp.points.push_back(-1);
	}
}