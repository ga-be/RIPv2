#include "Router.h"
#include <iostream>

std::mutex mutexas;

Router::Router(std::string name) :
	Node(name,Node::type::router)
{
	update = false;
	timer = new Timer();
	this->routingTable = std::list<RoutingTableEntry*>();
	this->buffer = std::list<Packet*>();
	timer->start();
	on = true;
}

Router::~Router()
{
	std::lock_guard <std::mutex> guard(objectMutex); //makes sure router wasn't in any process.
}

void Router::run() {
	while (on) {
		
		while (!buffer.empty()) {
			std::lock_guard <std::mutex> guard(objectMutex);
			Packet* packet = buffer.front();
			buffer.pop_front();

			if (packet->getType() == Packet::type::packet) {

				mutexas.lock();
				std::cout << "|||||||||PAKETAS|||||||||| "<<"ROUTERYJE: "<<this->getName()<<" KELIAUJA IS: "<< packet->getSource() << " I: " << packet->getDestination() << "\n";
				bool found = false;
				std::string source = packet->getSource();
				std::string destination = packet->getDestination();

				if (destination == this->getName()) {// pasiekeme tiksla
					std::cout << "Valio\n";
					found = true;
				}
				mutexas.unlock();

				if (!found) {
					for (auto it = routingTable.begin(); it != routingTable.end(); it++) {
						if (destination == (*it)->getDestination()) {
							found = true;
							if ((*it)->getVia() == "D") { //DIRECT CONNECTION
								for (auto it2 = adjacentNodes.begin(); it2 != adjacentNodes.end(); it2++) {
									if ((*it2)->getName() == destination) {
										//Node::sendPacket((*it2), packet);
										(*it2)->addToBuffer(packet);
										break;
									}
								}
							}
							else {
								std::string nextHop = (*it)->getVia();
								for (auto it2 = adjacentNodes.begin(); it2 != adjacentNodes.end(); it2++) {
									if ((*it2)->getName() == nextHop) {
										//Node::sendPacket((*it2), packet);
										(*it2)->addToBuffer(packet);
										break;
									}
								}
							}
							if (found) break;
						}
					}
					if (!found) {
						mutexas.lock();
						std::cout << "Packet Dropped\n";
						mutexas.unlock();
					}
				}
			}
			else {

				std::list<RoutingTableEntry*> temp = packet->getRoutingTable();
				std::string from = packet->getSource();
				//	std::cout << from<<"\n";
				for (auto it2 = temp.begin(); it2 != temp.end(); it2++) {
					bool found = false;
					for (auto it3 = routingTable.begin(); it3 != routingTable.end(); it3++) {
						if ((*it3)->getDestination() == (*it2)->getDestination()) {
							found = true;
							if ((*it3)->getVia() == from) {
								if ((*it3)->getHopCount() != (*it2)->getHopCount() + 1) {
									(*it3)->setHopCount((*it2)->getHopCount() + 1);
									update = true;
								}
								break;
							}
							else {
								if ((*it3)->getHopCount() > (*it2)->getHopCount()) { //if this happens, then we need to send update to other routers.
									(*it3)->setHopCount((*it2)->getHopCount() + 1);
									(*it3)->setVia(from);
									//	update = true;
									break;
								}
							}
						}
					}
					//		if ((*it2)->getHopCount() >= INFINITY) update = true;
					if (!found && (*it2)->getHopCount() < INFINITY) {
						routingTable.push_back(new RoutingTableEntry((*it2)->getDestination(), from, (*it2)->getHopCount() + 1));
						update = true;
					}
				}
			}
		}

		/*mutexas.lock();
		for (std::list<RoutingTableEntry*>::iterator it = routingTable.begin(); it != routingTable.end(); it++) {
			(*it)->print();
		}
		std::cout << "\n";
		mutexas.unlock();*/

		if (timer->getElapsedTime() >= 30.0f || update) {  //TIME TO BROADCAST ROUTING TABLE
		//	objectMutex.unlock();
			broadcastRoutingTable();
			std::lock_guard <std::mutex> guard(objectMutex);
			if (!update) {
				timer->reset();
			}
			auto it6 = routingTable.begin();
				while (it6!=routingTable.end()) { //TODO; when removing adjacent link with NODE remove table entries that goes VIA that NODE
					if ((*it6)->getHopCount() >= INFINITY) {
						it6=routingTable.erase(it6);
					}
					else {
						it6++;
					}
				}
				/*mutexas.lock();
				std::cout << "after deletion";
				std::cout << this->getName() << "\n";
				printf("dst via hops\n");
				for (std::list<RoutingTableEntry*>::iterator it2 = routingTable.begin(); it2 != routingTable.end(); it2++) {
					(*it2)->print();
				}
				std::cout << "\n";
				mutexas.unlock();*/
		}
		update = false;
	}
}

void Router::addNeighbour(Node* node)
{
	std::lock_guard <std::mutex> guard(objectMutex);
	bool found = false;
	for (auto it = adjacentNodes.begin() ; it != adjacentNodes.end(); it++) {
		if (node->getName() == (*it)->getName())
			found = true;
	}
	if (!found) {
		Node::addNeighbour(node);
	}
	found = false;
	for (auto it = routingTable.begin(); it != routingTable.end(); it++) {
		if ((*it)->getDestination() == node->getName()) {
			(*it)->setVia("D");
			(*it)->setHopCount(1);
			found = true;
			break;
		}
	}
	if(!found)
	routingTable.push_back(new RoutingTableEntry(node->getName(), "D", 1));
	update = true; //means we will need to send upate cause of trigger
}

void Router::showTable() {
	std::lock_guard <std::mutex> guard(objectMutex);
	mutexas.lock();
	std::cout << "ROUTER: " << this->getName() << " ROUTING TABLE\n";
	std::cout << "DEST\tVIA\thopCOUNT\n";
	for (std::list<RoutingTableEntry*>::iterator it = routingTable.begin(); it != routingTable.end(); it++) {
		(*it)->print();
	}
	std::cout << "\n";
	mutexas.unlock();
}



void Router::broadcastRoutingTable()
{
	std::lock_guard <std::mutex> guard(objectMutex);
	for (std::vector<Node*>::iterator it = adjacentNodes.begin(); it != adjacentNodes.end(); it++ ) {
		if ((*it)->getType()==type::router) {
			Packet* packet = generatePacketFor((*it)->getName());
			sendPacket((*it), packet);
		}
	}
}

Packet* Router::generatePacketFor(std::string router) {
	std::list<RoutingTableEntry*> temp = std::list<RoutingTableEntry*>();
	for (std::list<RoutingTableEntry*>::iterator it = routingTable.begin(); it != routingTable.end(); it++) {
		if ((*it)->getDestination() == router) {
			continue;
		}
		if ((*it)->getVia() == router) {//sitas kolkas neveiks, nes kolkas nebuildinam taku iki destinationu
			continue;
			//temp.back()->setHopCount(16);
		} 
		temp.push_back(new RoutingTableEntry((*it)));
	}
	return new Packet(this->getName(), temp, Packet::type::update);
}

void Router::sendPacket(Node* node, Packet* packet) {
	std::this_thread::sleep_for(std::chrono::milliseconds(30));
	node->Node::addToBuffer(packet);
}

void Router::removeAdjacentNode(Node* node) {
	std::lock_guard <std::mutex> guard(objectMutex);
	for (auto it = adjacentNodes.begin(); it != adjacentNodes.end(); it++) {
		if ((*it) == node) { //need to announce other routers as well that this link is not available
			for (auto it2 = routingTable.begin(); it2 != routingTable.end(); it2++) {
				if ((*it2)->getDestination() == (*it)->getName()) {
					(*it2)->setHopCount(INFINITY);
				}
				if ((*it2)->getVia() == (*it)->getName()) {
					(*it2)->setHopCount(INFINITY);
				}
			}
			adjacentNodes.erase(it);
			update = true;
			break;
		}
	}
}

void Router::addToBuffer(Packet* packet)
{
	std::lock_guard <std::mutex> guard(objectMutex);
	Node::addToBuffer(packet);
}
