#include "Packet.h"

Packet::Packet(std::string source, std::string destination, type t) //pagal ideja sis konstruktorius skirtas konstruoti siunciamam paketui per tinkla
{
	this->source = source;
	this->destination = destination;
	this->t = t;
	this->routingTable = std::list<RoutingTableEntry*>();
}

Packet::Packet(std::string source, std::list <RoutingTableEntry*> routingTable, type t) //pagal ideja sis konstruktorius skirtas updeitam
{
	this->source = source;
	this->t = t;
	this->routingTable = std::list<RoutingTableEntry*>(routingTable);
}

Packet::~Packet()
{
	routingTable.clear();
}

std::string Packet::getSource()
{
	return source;
}

std::string Packet::getDestination()
{
	return destination;
}

void Packet::setSource(std::string source)
{
	this->source = source;
}

void Packet::setDestination(std::string destination)
{
	this->destination = destination;
}

std::list<RoutingTableEntry*> Packet::getRoutingTable()
{
	return routingTable;
}

Packet::type Packet::getType()
{
	return t;
}
