#pragma once
#include "RoutingTableEntry.h"
#include <string>
#include <list>

class Packet  {
public:
	enum class type { update, packet };
private:
	std::string source;
	std::string destination;
	Packet::type t;

	std::list <RoutingTableEntry*> routingTable; //siunciamas routing table;
public:
	Packet(std::string source, std::string destination, Packet::type t);
	Packet(std::string source, std::list <RoutingTableEntry*> routingTable, Packet::type t);
	~Packet();
	std::string getSource();
	std::string getDestination();
	void setSource(std::string source);
	void setDestination(std::string destination);
	std::list <RoutingTableEntry*> getRoutingTable();
	Packet::type getType();

};