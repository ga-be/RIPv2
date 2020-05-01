#include "Network.h"

Network::Network()
{
}

Network::~Network()
{
}

void Network::showTable(std::string name)
{
	int position;
	try {
		position = pos.at(name);
	}
	catch (const std::out_of_range & e) {
		printf("Irenginys tokiu vardu nerastas\n");
		return;
	}
	nodes[position]->showTable();

}

void Network::addRouter(std::string name)
{
	if (pos.find(name) != pos.end()) {
		printf("Router with this name already exists\n");
		return;
	}
	Node* temp = new Router(name);
	nodes.push_back(temp);
	pos.insert(std::pair<std::string,int>(name,nodes.size() - 1));
	temp->createThread().detach();
}

void Network::addComputer(std::string name)
{
}

void Network::deleteRouter(std::string name)
{
	int position;
	try {
		position = pos.at(name);
	}
	catch (const std::out_of_range & e) {
		printf("Irenginys tokiu vardu nerastas\n");
		return;
	}
	nodes[position]->setOn(false);
	std::vector<Node*> temp = nodes[position]->getAdjacentNodes();
	for (auto it = temp.begin(); it != temp.end(); it++) {
		deleteLink(name, (*it)->getName());
	}
	nodes[position]->~Node();
	nodes.erase(nodes.begin()+position);
	pos.clear();
	position = 0;
	for (auto it = nodes.begin(); it!= nodes.end(); it++) {
		pos.insert(std::pair<std::string, int>((*it)->getName(), position));
		position++;
	}
}

void Network::addLink(std::string name1, std::string name2)
{
	int pos1, pos2;
	try {
		pos1 = pos.at(name1);
		pos2 = pos.at(name2);
	} catch (const std::out_of_range& e) {
		printf("Irenginys tokiu vardu nerastas\n");
		return;
	}
	nodes[pos1]->addNeighbour(nodes[pos2]);
	nodes[pos2]->addNeighbour(nodes[pos1]);
}

void Network::deleteLink(std::string name1, std::string name2)
{
	int pos1, pos2;
	try {
		pos1 = pos.at(name1);
		pos2 = pos.at(name2);
	}
	catch (const std::out_of_range & e) {
		printf("Irenginys tokiu vardu nerastas\n");
		return;
	}
	nodes[pos1]->removeAdjacentNode(nodes[pos2]);
	nodes[pos2]->removeAdjacentNode(nodes[pos1]);
}

void Network::sendPacket(std::string source, std::string dest)
{
	int pos1, pos2;
	try {
		pos1 = pos.at(source);
		pos2 = pos.at(dest);
	}
	catch (const std::out_of_range & e) {
		printf("Irenginys tokiu vardu nerastas\n");
		return;
	}
	nodes[pos1]->addToBuffer(new Packet(nodes[pos1]->getName(), nodes[pos2]->getName(), Packet::type::packet));
}




