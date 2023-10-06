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
	double calculate_output_current();
}ObjPNDiodeIdeal;

#endif