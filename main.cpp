#include <iostream>
#include <string>
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

void MenuAction();



enum 
{
	EXITS = -1,
	PRINT_TREE = 0,
	INSERT_NODE = 1,
	DELETE_NODE = 2,
	CLEAR_TREE = 3,
	FIND_NODE = 4,
	LOAD_TREE = 5,
	SET_CONDITION_FOR = 6 // ask the user for a specific node, if found, switch out the node for a new node with the condition the user requests
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

void LoadTree_Option(TestTree& tree){
	tree.clear();
	
}

void MenuAction() {
	int choice;
	BinaryTree<string> tree; //use this as the tree

	cout << "Options menu:\n"
		<< "(-1) Exits the program\n"
		<< "(0) Print the tree\n"
		<< "(1) Insert new node\n"
		<< "(2) Delete node\n"
		<< "(3) Clear the tree\n"
		<< "(4) Find node\n"
		<< "(5) Load an another tree\n"
		<< "(6) Switch out the node for a new node with the condition if the node found\n"
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
				break;
			default:
				cout << "Not a valid input." << endl;
				break;
		}
	}
}

int main()
{
	cout << "Hello world!" << endl;
	return 0;
}

#endif