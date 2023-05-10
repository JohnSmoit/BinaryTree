#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include "BinaryTree.h"

#define USE_MAIN_1

#ifdef USE_MAIN_1

using namespace std;
using namespace bst;
struct StringComp 
{
	bool compare(std::string A, std::string B) const 
	{
		return A == B;
	}
};

template <typename T>
struct GenericComp_Reverse
{
	static bst::CompareResult Compare(const T& A, const T& B) 
	{
		return (A > B) ? bst::LESS_THAN : ((A < B) ? bst::GREATER_THAN : bst::EQUAL);
	}
};

template <typename T>
struct GenericComp_Random 
{
	static bst::CompareResult Compare(const T & A, const T& B) 
	{
		srand(time(NULL));

		int randVal = rand() % 3;

		return static_cast<bst::CompareResult>(randVal);
	}
};

void MenuAction(bool& finish);



enum 
{
	EXITS = -1, // exits the program
	PRINT_TREE = 0, // print the tree
	INSERT_NODE = 1, // create and insert node into the tree
	DELETE_NODE = 2, // remove node from the tree
	CLEAR_TREE = 3, // empty the tree
	FIND_NODE = 4, // search the tree, return node if found
	LOAD_TREE = 5, // remove current tree and load another tree
	SET_CONDITION_FOR = 6, // ask the user for a specific node, if found, switch out the node for a new node with the condition the user requests
	GET_HEIGHT = 7,
	IS_BALANCED = 8
};


void InsertNode_Option(BinaryTree<string>& tree) 
{
	cout << "Please enter the new node you would like to insert (type a word): " << endl;
	string word;
	getline(cin, word);

	cout << "Inserting Node " << word << "..." << endl;
	tree.insertNode(word);
	cout << "Insertion Successful!" << endl;
}

void DeleteNode_Option(BinaryTree<string>& tree) {
	if (tree.isEmpty()) 
	{
		cout << "Tree is already empty" << endl;
		return;
	}

	cout << "Please enter the node you would like to delete (type a word): " << endl;
	string word;
	getline(cin, word);
	
	if(tree.find(word) == nullptr) {
		cout << "Cannot delete if Node is not found!" << endl;
	} else {
		cout << "Deleting Node " << word << "..." << endl;
		tree.deleteNode(word);
		cout << "Deletion Successful!" << endl;
	}
}

void PrintTree_Option(BinaryTree<string>& tree)
{
	cout << "How would you like the tree to be printed?" << endl;
	cout << "0) Pre-Order" << endl;
	cout << "1) In-Order" << endl;
	cout << "2) Post-Order" << endl;

	int choice;
	cin >> choice;
	if (choice > 2 || choice < 0)
	{
		cout << "That is not a valid option!\nDefaulting to in-order" << endl;
		choice = 1;
	}

	cout << tree.ToString(static_cast<TraversalOrder>(choice)) << endl;
}

using TestTree = BinaryTree<string>;

void FindNode_Option(TestTree& tree) 
{
	string word;
	if(tree.isEmpty()) {
		cout << "cannot search in an empty tree" << endl;
		return;
	}
	cout << "Enter the word to search for: " << endl;
	getline(cin, word);
	
	cout << "searching for Node " << word << "..." << endl;
	BaseNode<string>* node = tree.find(word);
	if(node == nullptr) {
		cout << "Cannot find Node " << word << endl;
	} else {
		cout << "Found Node " << word << endl;
		cout << (node->parent() ? node->parent()->data() : "has no parent node") << endl;
		cout << (node->left() ? node->left()->data() : "has no left child") << endl;
		cout << (node->right() ? node->right()->data() : "has no right child") << endl;
	}
}

void ClearTree_Option(TestTree& tree) 
{
	cout << "Clearing tree..." << endl;
	tree.clear();
	cout << "...Cleared the tree!" << endl;
}

void LoadTree_Option(TestTree& tree) {
	tree.clear();

	cout << "Enter the name of the file you would like to enter: " << endl;
	string fileName;
	getline(cin, fileName);

	ifstream fileData(fileName);

	if (!fileData.is_open()) 
	{
		cerr << "Failed to open file!" << endl;
		return;
	}

	while (!fileData.eof()) 
	{
		string word;
		getline(fileData, word);

		tree.insertNode(word);
	}

	cout << "Successfully parsed file data into a new binary search tree!" << endl;
	fileData.close();
}

void GetHeight_Option(TestTree& tree) {
	cout << "The Height of the Entire Tree is: " << tree.getHeight() << endl;
}

void IsBalanced_Option(TestTree& tree) {
	if(tree.isBalanced() == false) {
		cout << "Tree is skewed and not balanced!" << endl;
	}
	else{
		cout << "Tree is balanced!" << endl;
	}
}

void SwapCondition_Option(TestTree& tree) 
{
	cout << "Which node would you like to swap the condition of? Enter the data of the node to search." << endl;
	string word;
	getline(cin, word);
	if (!tree.find(word)) 
	{
		cout << "Could not find node " << word << "!" << endl;
		return;
	}

	cout << "What test condition would you like to give the node?\n"
		<< "Available:\n "
		<< "0) In-Order comparison\n"
		<< "1) Reverse-Order comparison\n"
		<< "2) Random-Order comparison\n"
		<< endl;

	int val;
	cin >> val;

	switch (val) 
	{
	case 0:
		tree.SwapConditionFor<GenericComparison<string>>(word);
		break;
	case 1:
		tree.SwapConditionFor<GenericComp_Reverse<string>>(word);
		break;
	case 2:
		tree.SwapConditionFor<GenericComp_Random<string>>(word);
		break;
	default:
		cout << "That is not a valid comparison" << endl;
		break;
	}
}

void MenuAction(bool& exit, BinaryTree<string>& tree) {
	int choice;

	cout << "Options menu:\n"
		<< "(-1) Exits the program\n"
		<< "(0) Print the tree\n"
		<< "(1) Insert new node\n"
		<< "(2) Delete node\n"
		<< "(3) Clear the tree\n"
		<< "(4) Find node\n"
		<< "(5) Load an another tree\n"
		<< "(6) Switch out the node for a new node with the condition if the node found\n"
		<< "(7) Get the height of the tree\n"
		<< "(8) Check if the tree is balanced\n"
		<< "Using any other number will be severly punished\n"
	    << endl;
	cin >> choice;
	
	if(!tree.isEmpty()){
		switch (choice) {
			case EXITS:
				cout << "Goodbye!" << endl;
				break;
			case PRINT_TREE:
				PrintTree_Option(tree);
				break;
			case INSERT_NODE:
				InsertNode_Option(tree);
				break;
			case DELETE_NODE:
				DeleteNode_Option(tree);
				break;
			case CLEAR_TREE:
				ClearTree_Option(tree);
				break;
			case FIND_NODE:
				FindNode_Option(tree);
				break;
			case LOAD_TREE:
				LoadTree_Option(tree);
				break;
			case SET_CONDITION_FOR:
				SwapCondition_Option(tree);
				break;
			case GET_HEIGHT:
				GetHeight_Option(tree);
				break;
			case IS_BALANCED:
				IsBalanced_Option(tree);
				break;
			default:
				cout << "Not a valid input." << endl;
				break;
		}
	}
}

int main()
{
	bool finish = false;
	BinaryTree<string> tree; //use this as the tree

	LoadTree_Option(tree);

	while (!finish) 
	{
		MenuAction(finish, tree);
	}
	return 0;
}

#endif