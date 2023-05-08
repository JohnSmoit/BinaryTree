#pragma once
#include <vector>
#include <iostream>
#include <sstream>
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


		string ToString(TraversalOrder order = IN_ORDER);

	protected:

		template <typename NodeComp = Compare>
		BaseNode<T>* insertNode(const T& data, BaseNode<T>* node);
		BaseNode<T>* deleteNode(const T& data, BaseNode<T>* node);
		bool isBalanced(BaseNode<T>* node);
	private:
		BaseNode<T>* root;
		BaseNode<T>* findHelper(BaseNode<T>* current, const T& data) const;
		T findMinHelper(BaseNode<T>* node);

		void clear_Worker(BaseNode<T>* node);

		void postOrder_Worker(vector<BaseNode<T>*>& values, BaseNode<T>* node) const;
		void preOrder_Worker(vector<BaseNode<T>*>& values, BaseNode<T>* node) const;
		void inOrder_Worker(vector<BaseNode<T>*>& values, BaseNode<T>* node) const;
	};

	template <typename T, typename Compare>
	template <typename NodeComp>
	void BinaryTree<T, Compare>::insertNode(const T& data)
	{
		if (root == nullptr) {
			root = NewNode<NodeComp>(data);
		}
		else {
			insertNode(data, root);
		}
	}

	template <typename T, typename Compare>
	template <typename NodeComp> //NodeComp is the actual comparison you want to use for the node.
	inline BaseNode<T>* BinaryTree<T, Compare>::insertNode(const T& data, bst::BaseNode<T>* node)
	{
		CompareResult result = node->evaluate(data);
		if (result == CompareResult::LESS_THAN) {
			if (node->left() == nullptr) {
				node->left() = NewNode<NodeComp>(data);
				return node->left();
			}
			else {
				return insertNode(data, node->left());
			}
		}
		else {
			if (node->right() == nullptr) {
				node->right() = NewNode(data);
				return node->right();
			}
			else {
				return insertNode(data, node->right());
			}
		}
	}

	template <typename T, typename Compare>
	void BinaryTree<T, Compare>::deleteNode(const T& data) {
		if (isEmpty()) {
			cerr << "Error: cannot remove node from an empty tree!" << endl;
		}
		else {
			root = deleteNode(data, root);
		}
	}
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

	template<typename T, typename Compare>
	T bst::BinaryTree<T, Compare>::findMin() {
		if (isEmpty()) {
			cerr << "cannot find if tree is empty!" << endl;
		}
		else {
			return findMinHelper(root);
		}
	}

	template <typename T, typename Compare>
	T bst::BinaryTree<T, Compare>::findMinHelper(bst::BaseNode<T>* node) {
		if (node->left() != nullptr) {
			return findMinHelper(node->left());
		}
		else {
			return node->data();
		}
	}


	// Helper function that search the data in the tree
	// return Node
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

	template<typename T, typename Compare>
	inline vector<BaseNode<T>*> BinaryTree<T, Compare>::TraverseInOrder()
	{
		vector<BaseNode<T>*> values;
		inOrder_Worker(values, root);

		return values;
	}

	template<typename T, typename Compare>
	inline vector<BaseNode<T>*> BinaryTree<T, Compare>::TraversePostOrder()
	{
		vector<BaseNode<T>*> values;
		postOrder_Worker(values, root);

		return values;
	}

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



	// search data in the tree
	// return Node
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
		if (parent) newNode->parent() = parent;
		if (left) newNode->left() = left;
		if (right) newNode->right() = right;

		return newNode;
	} //this is the copy version

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

	template <typename T, typename Compare>
	void BinaryTree<T, Compare>::clear()
	{
		clear_Worker(root);
	}

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

}