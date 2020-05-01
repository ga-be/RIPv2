
#include "Network.h"
#include <thread>
#include <iostream>
#include "Util.h"

int main() {
	
	Network* network = new Network();

	/*~~~Tests~~
	network->addRouter("R1");
	std::this_thread::sleep_for(std::chrono::seconds(1));
	network->addRouter("R2");
	std::this_thread::sleep_for(std::chrono::seconds(1));
	network->addRouter("R3");
	std::this_thread::sleep_for(std::chrono::seconds(1));
	network->addRouter("R4");
	std::this_thread::sleep_for(std::chrono::seconds(1));
	network->addLink("R2", "R3");
	std::this_thread::sleep_for(std::chrono::seconds(1));
	network->addLink("R1", "R4");
	std::this_thread::sleep_for(std::chrono::seconds(1));
	network->addLink("R4", "R3");
	std::this_thread::sleep_for(std::chrono::seconds(1));
	network->addLink("R1", "R2");

	std::this_thread::sleep_for(std::chrono::seconds(10));

	std::cout << "VUOLAAAAsssssssssssssssssssssssssssssssaaAAAAAAAA";

//	network->deleteRouter("R1");

	std::this_thread::sleep_for(std::chrono::seconds(5));

	std::cout << "Siusime paketuka";

	network->sendPacket("R2", "R4");

	std::this_thread::sleep_for(std::chrono::seconds(50));

	/*network->deleteLink("R1", "R4");

	std::this_thread::sleep_for(std::chrono::seconds(10));

	std::cout << "VUOLAAAAsssssssssssssssssssssssssssssssaaAAAAAAAasdascxcascA";

	network->deleteLink("R1", "R2");

	std::this_thread::sleep_for(std::chrono::seconds(10));

	std::cout << "VUOLAAAAsssssssssssssssssssssssssssssssaaAAAAAAAasdascxcascA";

	network->addLink("R1", "R2");

//	network->showTable("R2");
//	network->showTable("R1");
//	network->showTable("R3");
	while (true) {

	}*/	

	std::string input;
	while (std::getline(std::cin, input)) {

		std::string command;
		int argc = 0;
		std::string argv[2]; //max two arguments

		command = parseCommand(input, &argc, argv);

		if (command == "showtable") { //reikejo daryti komandas kaip klases.
			if (argc == 1) {
				network->showTable(argv[0]);
			}
		}else if (command == "addrouter") {
			if (argc == 1) {
				network->addRouter(argv[0]);
			}
		}else if (command == "addcomputer") {
			if (argc == 1) {
				network->addComputer(argv[0]);
			}
		}else if (command == "deleterouter") {
			if (argc == 1) {
				network->deleteRouter(argv[0]);
			}
		}else if (command == "addlink") {
			if (argc == 2) {
				network->addLink(argv[0],argv[1]);
			}
		}else if (command == "deletelink") {
			if (argc == 2) {
				network->deleteLink(argv[0],argv[1]);
			}
		}else if (command == "sendpacket"){
			if (argc == 2) {
				network->sendPacket(argv[0],argv[1]);

			}
		}else {
			std::cout << "Komanda nerasta\n";
		}
	}

	return 0;
}

