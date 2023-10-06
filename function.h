// MyClass.h
#ifndef FUNCTION_H
#define FUNCTION_H

class pnDiodeIdeal {
public:
	/* data */
	double Voltage;
	double CurrentSaturartion;
	double Temperature;

    void set_values(double, double, double);
	double pn_diode_ideal();
}ObjPNDiodeIdeal;

#endif