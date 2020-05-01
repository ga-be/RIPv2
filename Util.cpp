#include "Util.h"

std::string parseCommand(std::string input, int* argc, std::string argv[]) {

	std::string command;
	size_t found;
	//command
	found = input.find(" ");
	if (found != std::string::npos) {
		command = input.substr(0, found);
	}
	else {
		return input;
	}
	int lastFound = found;
	while ((found = input.find(" ", lastFound + 1)) != std::string::npos) {
		argv[*argc] = input.substr(lastFound + 1, found - lastFound - 1);
		lastFound = found;
		(*argc)++;
		if ((*argc) == 2) {
			return "INVALID COMMAND";
		}
	}
	if (found = input.find('\0', lastFound + 1) != lastFound + 1) {
		argv[*argc] = input.substr(lastFound + 1, found - lastFound - 1);
		(*argc)++;
	}
	return command;
}
