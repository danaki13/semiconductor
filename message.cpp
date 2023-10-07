#include <iostream>
#include "message.h"


void Message::setVerbosity(int v) {
	verbosity = v;
}

void Message::printMessage(int level, const std::string& message) {
	if (level >= verbosity) {
		std::cout << message << std::endl;
	}
}