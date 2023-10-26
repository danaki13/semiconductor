#define DEBUG 0
#define INFO 1
#define WARNING 2
#define ERROR 3

#ifndef MESSAGE_H
#define MESSAGE_H

void printMessage(int, int, const std::string&);

// Add function to combine debug message: fileString + ":" + std::to_string(__LINE__) + ":" + funcString + ": " + MESSAGE

struct cout_redirect {
	cout_redirect(std::streambuf *new_buffer) 
		: old(std::cout.rdbuf(new_buffer))
	{}

	~cout_redirect() {
		std::cout.rdbuf(old);
	}

private:
	std::streambuf *old;
};

#endif