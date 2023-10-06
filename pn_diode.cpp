#include <iostream>
#include <cmath>

double pn_diode_ideal(double Voltage) {
	double CurrentDiode = 0.0;
	double CurrentSaturartion = 1e-10, eCharge = 1.602e-19, kBoltzmann = 1.3806488e-23, Temperature = 300;

	CurrentDiode = CurrentSaturartion * (exp((eCharge * Voltage)/(kBoltzmann * Temperature)) - 1);
	std::cout << "I_Diode = " << CurrentDiode << std::endl;

	return CurrentDiode;
}