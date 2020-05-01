#include "Computer.h"

Computer::Computer(std::string name) :
	Node(name, Node::type::computer)
{
}

Computer::~Computer()
{
}
