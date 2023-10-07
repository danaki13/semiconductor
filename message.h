#define DEBUG 0
#define INFO 1
#define WARNING 2
#define ERROR 3

#ifndef MESSAGE_H
#define MESSAGE_H

class Message {
public:
	/* data */
	int verbosity;

    void setVerbosity(int);
    void printMessage(int, const std::string&);
};

#endif