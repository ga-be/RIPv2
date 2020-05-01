#pragma once
#include <string>
#include <vector>
#include <thread>
#include "Packet.h"
#include <list>

class Node {
public:
	enum class type { computer, router };
	Node(std::string name, type typeof);
	virtual ~Node();
	
	std::string getName();
	void setName(std::string name);
	virtual void run() = 0;
	virtual void addNeighbour(Node* node);
	virtual void showTable() = 0;
	virtual void sendPacket(Node* node, Packet* packet) = 0; //buvo galima paprasciau
	virtual void removeAdjacentNode(Node* node) = 0;
	virtual void addToBuffer(Packet* packet);
	std::vector <Node*> getAdjacentNodes();
	std::thread createThread();
	void setOn(bool status);
	type getType();

protected:
	bool on;
	type typeOf;
	std::string name;
	//std::map <std::string, int> pos; //we will find position of node in vector based by name of node. ar tikrai reikia? NE
	std::vector <Node*> adjacentNodes;
	std::list<Packet*> buffer; //we will keep updates and packets here.
};