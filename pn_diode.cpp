#include <iostream>
#include <cmath>

class pnDiodeIdeal {
public:
	/* data */
	double Voltage;
	double CurrentSaturartion;
	double Temperature;
	
	void set_values(double, double, double);
	double pn_diode_ideal();
	//~pnDiodeIdeal();
};

void pnDiodeIdeal::set_values(double voltV, double currentA, double tempK) {
	Voltage = voltV;
	CurrentSaturartion = currentA;
	Temperature = tempK;
}

double pnDiodeIdeal::calculate_output_current() {
	double CurrentDiode = 0.0;
	double eCharge = 1.602e-19, kBoltzmann = 1.3806488e-23;

	CurrentDiode = CurrentSaturartion * (exp((eCharge * Voltage)/(kBoltzmann * Temperature)) - 1);
	std::cout << Voltage << " " << CurrentDiode << std::endl;

	return CurrentDiode;
}