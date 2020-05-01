#include "RoutingTableEntry.h"
#include <iostream>

RoutingTableEntry::RoutingTableEntry(std::string destination, std::string via, int hopCount)
{
	this->destination = destination;
	this->via = via;
	this->hopCount = hopCount;
}

RoutingTableEntry::RoutingTableEntry(const RoutingTableEntry* entry)
{
	this->destination = entry->destination;
	this->via = entry->via;
	this->hopCount = entry->hopCount;
}

RoutingTableEntry::~RoutingTableEntry()
{
}


void RoutingTableEntry::print() {
//	printf("%s , %s , %d\n",destination->getName(), via->getName(), hopCount );
	std::cout<<destination << "\t" << via << "\t" << hopCount << "\n";
}

std::string RoutingTableEntry::getDestination()
{
	return destination;
}

std::string RoutingTableEntry::getVia()
{
	return via;
}

void RoutingTableEntry::setVia(std::string via)
{
	this->via = via;
}

int RoutingTableEntry::getHopCount()
{
	return hopCount;
}

void RoutingTableEntry::setHopCount(int hopcount)
{
	this->hopCount = hopcount;
}
