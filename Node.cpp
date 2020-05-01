#include "Node.h"

Node::Node(std::string name, Node::type typeof)
{
	this->name = name;
	this->typeOf = typeof;
}

Node::~Node()
{
}

std::string Node::getName()
{
	return name;
}

void Node::setName(std::string name)
{
	this->name = name;
}

void Node::addNeighbour(Node* node)
{
	adjacentNodes.push_back(node);
}

void Node::addToBuffer(Packet* packet)
{
	buffer.push_back(packet);
}

std::vector<Node*> Node::getAdjacentNodes()
{
	return adjacentNodes;
}

std::thread Node::createThread() {
	return std::thread(&Node::run, this);
}

void Node::setOn(bool status)
{
	this->on = status;
}

Node::type Node::getType()
{
	return typeOf;
}




