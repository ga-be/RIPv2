#pragma once
#include <string>

class Command {
private:
	std::string command;
	int argc;
public:
	Command(std::string command, int argc) { this->command = command; this->argc = argc; };
	~Command() {};
	bool is(std::string command) { if (this->command == command) return true; return false; }
	bool valid(int argc) { if (this->argc == argc) return true; return false; }
};