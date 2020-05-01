#pragma once
#include <vector>
#include <stdexcept>
#include "Router.h"
#include <stdio.h>
#include <map>

class Network {
public:
	Network ();
	~Network ();

	void showTable(std::string name);
	void addRouter(std::string name);
	void addComputer(std::string name); //it's more appropriate to say that computer represents other sub-networks that connects to routers via switches, because RIPv2 doesn't usually save information about how to get to hosts in it's routing table.
	void deleteRouter(std::string name);
	void addLink(std::string name1, std::string name2);
	void deleteLink(std::string name1, std::string name2);
	void sendPacket(std::string source, std::string dest);
private:
	std::map <std::string, int> pos;
	std::vector <Node*> nodes; //maybe i will need to seperate computers and routers, idk.
};

