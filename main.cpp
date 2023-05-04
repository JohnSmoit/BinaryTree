#include <iostream>
#include <string>
#include "BinaryTree.h"



#ifdef USE_MAIN_1

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

}

#endif