#pragma once
#include <string>

class RoutingTableEntry{
public:
	RoutingTableEntry(std::string destination,std::string via, int hopCount);
	RoutingTableEntry(const RoutingTableEntry* entry);
	~RoutingTableEntry();

	void print();
	std::string getDestination();
	//void setDestination();
	std::string getVia();
	void setVia(std::string via);
	int getHopCount();
	void setHopCount(int hopcount);

private:
	std::string destination;
	std::string via;
	int hopCount;
};