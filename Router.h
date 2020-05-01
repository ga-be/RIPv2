#pragma once
#include "Node.h"
#include "Timer.h"
#include <list>
#include <mutex>
#include "RoutingTableEntry.h"
#include "Packet.h"

#define INFINITY 16

class Router : public Node{
public:
	Router(std::string name);
	~Router();
	
	virtual void run() override;
	virtual void addNeighbour(Node* node) override;
	virtual void removeAdjacentNode(Node* node) override;
	virtual void addToBuffer(Packet* packet) override;
	void showTable();
	
	
private:
	std::mutex objectMutex;
	void broadcastRoutingTable();
	Packet* generatePacketFor(std::string router);
	void sendPacket(Node* node,Packet* packet);

private:
	bool update; //trigger if changes in topology occur
	Timer* timer;
	std::list<RoutingTableEntry*> routingTable;
};