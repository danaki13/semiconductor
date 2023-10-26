#include <iostream>
#include "message.h"

void printMessage(int verbosity, int level, const std::string &message) {
	if (level >= verbosity) {
		std::cout << message << std::endl;
	}
}