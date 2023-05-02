#include <iostream>
#include <string>
#include "BinaryTree.h"

struct StringComp 
{
	bool compare(std::string A, std::string B) const 
	{
		return A == B;
	}
};

int main() 
{
	std::cout << "Hello World!" << std::endl;

	bst::Node<std::string, StringComp> node("Hello World");

	std::cout << node.data() << std::endl;

	node.data() = "Goodbye World!";

	std::cout << node.data() << std::endl;

