#pragma once
#include <vector>
#include <iostream>
#include <sstream>
#include <algorithm>
#include "Node.h"


struct DummyIntComparison
{
	static bst::CompareResult Compare(const int& A, const int& B)
	{
		return (A > B) ? bst::GREATER_THAN : ((A < B) ? bst::LESS_THAN : bst::EQUAL);
	}
};

using namespace std;
namespace bst
{

	enum TraversalOrder
	{
		PRE_ORDER,
		POST_ORDER,
		IN_ORDER
	};
	template <typename T, typename Compare = GenericComparison<T>>
	class BinaryTree {
	public:
		BinaryTree() : root(nullptr) {}
		BinaryTree(T& root) : root(new Node<T, Compare>(root)) {}
		BinaryTree(BaseNode<T>* root) : root(root) {}

		template <typename NodeComp = Compare>
		void insertNode(const T& data);
		void deleteNode(const T& data);
		void clear();
		BaseNode<T>* find(const T& data) const;
		bool isBalanced();

		template <typename NodeComp = Compare>
		Node<T, NodeComp>* NewNode(const T& data, BaseNode<T>* parent = nullptr, BaseNode<T>* left = nullptr, BaseNode<T>* right = nullptr); //uses less template mess this way.
		bool isEmpty() {
			return root == nullptr;
		}
		T findMin();

		static BinaryTree<T, Compare> FromList(std::vector<T>& values);

		template <typename..._Ty>
		static BinaryTree<T, Compare> CreateFromValues(_Ty&&...vals);

		vector<BaseNode<T>*> TraverseInOrder();

		vector<BaseNode<T>*> TraversePostOrder();

		vector<BaseNode<T>*> TraversePreOrder();

		template <typename NewComp>
		void SwapConditionFor(const T& data);


		string ToString(TraversalOrder order = IN_ORDER);

		int getHeight() const;

	protected:

		template <typename NodeComp = Compare>
		BaseNode<T>* insertNode(BaseNode<T>* newNode, BaseNode<T>* node);
		BaseNode<T>* deleteNode(const T& data, BaseNode<T>* node);
	private:
		BaseNode<T>* root;
		BaseNode<T>* findHelper(BaseNode<T>* current, const T& data) const;
		T findMinHelper(BaseNode<T>* node);

		void clear_Worker(BaseNode<T>* node);

		void postOrder_Worker(vector<BaseNode<T>*>& values, BaseNode<T>* node) const;
		void preOrder_Worker(vector<BaseNode<T>*>& values, BaseNode<T>* node) const;
		void inOrder_Worker(vector<BaseNode<T>*>& values, BaseNode<T>* node) const;
		int getHeight(BaseNode<T>* node) const;
		bool isBalanced(BaseNode<T>* node);
	};

	template <typename T, typename Compare>
	template <typename NodeComp>
	void BinaryTree<T, Compare>::insertNode(const T& data)
	{
		auto newNode = NewNode<NodeComp>(data);
		if (root == nullptr) {
			root = newNode;
		}
		else {
			insertNode(newNode, root);
		}
	}

	template <typename T, typename Compare>
	template <typename NodeComp> //NodeComp is the actual comparison you want to use for the node.
	BaseNode<T>* BinaryTree<T, Compare>::insertNode(BaseNode<T>* newNode, bst::BaseNode<T>* node)
	{
		CompareResult result = node->evaluate(newNode->data());
		if (result == CompareResult::LESS_THAN) {
			if (node->left() == nullptr) {
				node->left() = newNode;
				newNode->parent() = node;
				return node->left();
			}
			else {
				return insertNode(newNode, node->left());
				return insertNode(newNode, node->left());
			}
		}
		else if (result == EQUAL) 
		{
			return node;
		}
		else {
			if (node->right() == nullptr) {
				node->right() = newNode;
				newNode->parent() = node;
				return node->right();
			}
			else {
				return insertNode(newNode, node->right());
			}
		}
	}
	
	/// @brief Deletes a node
	/// @pre must not be empty !isEmpty()
	/// @param data - The data to delete from the tree
	template <typename T, typename Compare>
	void BinaryTree<T, Compare>::deleteNode(const T& data) {
		if (isEmpty()) {
			cerr << "Error: cannot remove node from an empty tree!" << endl;
		}
		else {
			root = deleteNode(data, root);
		}
	}

	/// @brief the Private helper function of deleteNode();
	/// @param data the data to remove
	/// @param node the current node the pointer is pointing to
	/// @return node
	template <typename T, typename Compare>
	inline BaseNode<T>* BinaryTree<T, Compare>::deleteNode(const T& data, bst::BaseNode<T>* node) {
		CompareResult result = node->evaluate(data);
		if (node == nullptr) {
			return nullptr;
		}
		else if (result == CompareResult::LESS_THAN) {
			node->left() = deleteNode(data, node->left());
		}
		else if (result == CompareResult::GREATER_THAN) {
			node->right() = deleteNode(data, node->right());
		}
		else {
			if (node->left() == nullptr && node->right() == nullptr) {
				node = nullptr;
			}
			else if (node->left() != nullptr && node->right() == nullptr) {
				node = node->left();
			}
			else if (node->right() != nullptr && node->left() == nullptr) {
				node = node->right();
			}
			else {
				findMinHelper(node->right());
				node->data() = findMinHelper(node->right());
				node->right() = deleteNode(findMinHelper(node->right()), node->right());
			}
		}
	}

	/// @brief finds the minimum node in the tree
	/// @pre must not be empty !isEmpty();
	/// @return the FindMinHelper();
	template<typename T, typename Compare>
	T bst::BinaryTree<T, Compare>::findMin() {
		if (isEmpty()) {
			cerr << "cannot find if tree is empty!" << endl;
		}
		else {
			return findMinHelper(root);
		}
	}
	
	/// @brief the private helper function for FindMin();
	/// @param node the current node the pointer is pointing to
	/// @return the left most node, which is the smallest node
	template <typename T, typename Compare>
	T bst::BinaryTree<T, Compare>::findMinHelper(bst::BaseNode<T>* node) {
		if (node->left() != nullptr) {
			return findMinHelper(node->left());
		}
		else {
			return node->data();
		}
	}

	
	/// @brief Helper that search the tree to find the matching data
	/// @pre 
	/// @param BaseNode<T>* current - the current node that the pointer point to 
	/// @param const T& data - data that need to be found
	/// @return node address
	
	template <typename T, typename Compare>
	BaseNode<T>* bst::BinaryTree<T, Compare>::findHelper(BaseNode<T>* current, const T& data) const {
		if (current != nullptr) {
			CompareResult result = current->evaluate(data);
			if (result == CompareResult::EQUAL) {
				return current;
			}
			else if (result == CompareResult::LESS_THAN) {
				return findHelper(current->left(), data);
			}
			return findHelper(current->right(), data);
		}
		return nullptr;
	}
	
	/// @brief given a vector of values, insert each data into the tree
	/// @param values the vector which contains the list of data to insert to create a working tree
	/// @return the tree that has been created
	template <typename T, typename Compare>
	bst::BinaryTree<T, Compare> bst::BinaryTree<T, Compare>::FromList(std::vector<T>& values)
	{
		if (values.size() == 0)
		{
			return BinaryTree<T, Compare>();
		}
		BinaryTree<T, Compare> newTree(values.at(0));

		for (int i = 1; i < values.size(); ++i)
		{
			newTree.insertNode(values.at(i));
		}

		return newTree;
	}

	/// @brief traverses the tree containing the data in order
	/// @return the vector of nodes
	template<typename T, typename Compare>
	inline vector<BaseNode<T>*> BinaryTree<T, Compare>::TraverseInOrder()
	{
		vector<BaseNode<T>*> values;
		inOrder_Worker(values, root);

		return values;
	}
	
	/// @brief traverses the tree containing the data in  post order
	/// @return the vector of nodes
	template<typename T, typename Compare>
	inline vector<BaseNode<T>*> BinaryTree<T, Compare>::TraversePostOrder()
	{
		vector<BaseNode<T>*> values;
		postOrder_Worker(values, root);

		return values;
	}

	/// @brief traverses the tree containing the data in pre order
	/// @return the vector of nodes
	template<typename T, typename Compare>
	inline vector<BaseNode<T>*> BinaryTree<T, Compare>::TraversePreOrder() 
	{
		vector<BaseNode<T>*> values;
		preOrder_Worker(values, root);

		return values;
	}

	template<typename T, typename Compare>
	inline string BinaryTree<T, Compare>::ToString(TraversalOrder order)
	{
		vector<BaseNode<T>*> values;
		stringstream stream;
		switch(order) 
		{
		case PRE_ORDER:
			values = TraversePreOrder();
			break;
		case POST_ORDER:
			values = TraversePostOrder();
			break;
		default:
			values = TraverseInOrder();
			break;
		}

		for (const auto& node : values) 
		{
			stream << node->data() << endl;
		}

		return stream.str();
	}



	/// @brief search the tree to find the matching data
	/// @pre  
	/// @param const T& data - data that need to be found
	/// @return node address
	template <typename T, typename Compare>
	bst::BaseNode<T>* bst::BinaryTree<T, Compare>::find(const T& data) const {
		if (root == NULL) {
			return nullptr;
		}

		CompareResult result = root->evaluate(data);
		if (result == CompareResult::EQUAL) {
			return root;
		}
		else if (result == CompareResult::LESS_THAN) {
			return findHelper(root->left(), data);
		}
		return findHelper(root->right(), data);
	}

    template<typename T, typename Compare>
	template<typename NodeComp>
	inline Node<T, NodeComp>* BinaryTree<T, Compare>::NewNode(const T& data, BaseNode<T>* parent, BaseNode<T>* left, BaseNode<T>* right)
	{
		auto newNode = new Node<T, NodeComp>(data);
		if (parent) { 
			newNode->parent() = parent; 
			
			CompareResult comp = parent->evaluate(data);
			if (comp == LESS_THAN) 
			{
				parent->left() = newNode;
			}
			else 
			{
				parent->right() = newNode;
			}
		}
		if (left) 
		{
			newNode->left() = left; 
			left->parent() = newNode;
		}
		if (right) 
		{ 
			newNode->right() = right;
			right->parent() = newNode;
		}

		return newNode;
	} //this is the copy version

	/// @brief create tree form multiple values
	/// @pre 
	/// @param _Ty && ...vals - multiple values
	/// @return BinaryTree<T, Compare> newTree
	template<typename T, typename Compare>
	template<typename ..._Ty>
	inline BinaryTree<T, Compare> BinaryTree<T, Compare>::CreateFromValues(_Ty && ...vals)
	{
		BinaryTree<T, Compare> newTree;


		vector<T> values;

		([&] {
			values.push_back(static_cast<T>(std::forward<_Ty>(vals)));
			}(), ...);

		for (auto& val : values) {
			newTree.insertNode(static_cast<T>(val));
		}

		return newTree;
	}

	template<typename T, typename Compare>
	template<typename NewComp>
	void BinaryTree<T, Compare>::SwapConditionFor(const T& data)
	{
		auto found = find(data);
		if (!found) 
		{
			return;
		}

		auto parent = found->parent();
		auto left = found->left();
		auto right = found->right();

		left->makeSubTree();
		right->makeSubTree();


		auto replacementNode = NewNode<NewComp>(found->data(), parent);
		insertNode(replacementNode, left); //re insert the left and right node in the right places
		insertNode(replacementNode, right);
		delete found;
	}

	/// @brief empty the tree
	template <typename T, typename Compare>
	void BinaryTree<T, Compare>::clear()
	{
		clear_Worker(root);
	}

	/// @brief process to empty the tree
	/// @param BaseNode<T>* node - the root of the tree
	template <typename T, typename Compare>
	void BinaryTree<T, Compare>::clear_Worker(BaseNode<T>* node)
	{
		if (!node) //handles root being null
		{
			return;
		}

		if (node->leaf()) //delete the node if it is a leaf
		{
			delete node;
			node = nullptr;
		}
		else
		{
			if (node->left()) //recursively delete the childnodes first before deleting the parent.
			{
				clear_Worker(node->left());
			}
			if (node->right())
			{
				clear_Worker(node->right());
			}

			delete node;
			node = nullptr;
		}
	}

	/// @brief print the traverse postorder of the tree
	/// @param vector<BaseNode<T>*>& values - the 
	/// @param BaseNode<T>* node
	template<typename T, typename Compare>
	void BinaryTree<T, Compare>::postOrder_Worker(vector<BaseNode<T>*>& values, BaseNode<T>* node) const
	{
		if (!node) return;

		if (node->leaf())
		{
			values.push_back(node);
			return;
		}

		postOrder_Worker(values, node->left());
		postOrder_Worker(values, node->right());

		values.push_back(node);
	}

	template<typename T, typename Compare>
	void BinaryTree<T, Compare>::preOrder_Worker(vector<BaseNode<T>*>& values, BaseNode<T>* node) const
	{
		if (!node) return;

		if (node->leaf())
		{
			values.push_back(node);
			return;
		}

		values.push_back(node);

		preOrder_Worker(values, node->left());
		preOrder_Worker(values, node->right());
	}

	template<typename T, typename Compare>
	void BinaryTree<T, Compare>::inOrder_Worker(vector<BaseNode<T>*>& values, BaseNode<T>* node) const
	{
		if (!node) return;

		if (node->leaf())
		{
			values.push_back(node);
			return;
		}


		inOrder_Worker(values, node->left());
		values.push_back(node);
		inOrder_Worker(values, node->right());
	}

	/// @brief finds the height of the tree
	/// @pre if the root is nullptr, then the height of the tree is just 0
	/// @return the getHeight helper function
	template<typename T, typename Compare>
	int BinaryTree<T, Compare>::getHeight() const {
		if(root == nullptr) {
			return 0;
		} else {
			return getHeight(root);
		}
	}

	/// @brief the private helper function of getHeight();
	/// @param node the current node the pointer is pointing at
	/// @return the Height of the tree which should be an int
	template<typename T, typename Compare>
	int BinaryTree<T, Compare>::getHeight(BaseNode<T>* node) const {
		if(node == nullptr) {
			return -1;
		} else {
			return max(getHeight(node->left()), getHeight(node->right())) + 1;
		}
	}

	/// @brief determines whether the tree is balanced or not - meaning the left side of the tree is equal to the right side of the tree
	/// @pre if the root is nullptr, then the tree has no node, which means the tree is already balanced
	/// @return the helper function for isBalanced();
	template <typename T, typename Compare> 
	bool BinaryTree<T, Compare>::isBalanced() {
        if(root == nullptr) {
			return true;
		} else {
			return isBalanced(root);
		}
    }

	/// @brief the private helper function for isBalanced();
	/// @param node the current node that the pointer is pointing to
	/// @return true if the tree is balanced
	/// @return false if the tree is skewed
	template <typename T, typename Compare> 
	bool BinaryTree<T, Compare>::isBalanced(BaseNode<T>* node) {
        if(node != nullptr) {
			if(abs(getHeight(node->left()) - getHeight(node->right())) > 1) {
				return false;
			}
			return isBalanced(node->left()) && isBalanced(node->right());
		}
		return true;
    }

}