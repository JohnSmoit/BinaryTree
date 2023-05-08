#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include "BinaryTree.h"

#define USE_MAIN_2

#ifdef USE_MAIN_2

using namespace std;
using namespace bst;

vector<string> ReadFromFile(string fileName) 
{
	ifstream inputFileStream(fileName);
	vector<string> values;

	if (!inputFileStream.is_open()) 
	{
		cerr << "Could not open file named " << fileName << endl;
		return values;
	}

	while (!inputFileStream.eof()) 
	{
		string line;
		getline(inputFileStream, line);
		values.push_back(line);
	}

	return values;

}

int main() 
{
	//auto newTree = bst::BinaryTree<std::string>::CreateFromValues("thing1", "thing2", "thing3");
	string fileName;
	cout << "which file would you like to read from for the values?" << endl;
	cin >> fileName;

	auto values = ReadFromFile(fileName);

	auto tree = BinaryTree<string>::FromList(values);

	std::cout << tree.ToString(POST_ORDER) << endl;

	auto literalTree = BinaryTree<string>::CreateFromValues("hello", "goodbye", "cheese", "thing1", "thing2", "chase");

	tree.clear();

	return 0;
}

#endif