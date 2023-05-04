#pragma once
#include <vector>
#include <iostream>
#include "Node.h"


using namespace std;
namespace bst 
{
	template <typename T, typename Compare = GenericComparison<T>>
	class BinaryTree {
		public:
			BinaryTree() : root(nullptr) {}
			BinaryTree(T& root) : root(new Node<T, Compare>(root)) {}
			BinaryTree(Node<T, Compare>* root) : root(root) {}
			void insertNode(T data);
			void deleteNode(T data);
			void clear() const;
			Node<T, Compare>* find(T data) const;
			bool isBalanced();
			Node<T, Compare>* NewNode(T& data, Node<T, Compare>* parent = nullptr, Node<T, Compare>* left = nullptr, Node<T, Compare>* right = nullptr); //uses less template mess this way.
			bool isEmpty() {
				return root == nullptr;
			}
			T findMin();

			static BinaryTree<T, Compare> FromList(std::vector<T>& values);
			
			template <typename..._Ty>
			static BinaryTree<T, Compare> CreateFromValues(_Ty&&...vals);
		protected:
			Node<T, Compare>* insertNode(T data, Node<T, Compare>* node);
			Node<T, Compare>* deleteNode(T data, Node<T, Compare>* node);
			bool isBalanced(Node<T, Compare>* node);
		private:
			Node<T, Compare>* root;
			Node<T, Compare>* findHelper(Node<T, Compare>* current, T data) const;
			T findMinHelper(Node<T, Compare>* node);

	};

    template <typename T, typename Compare>
    void BinaryTree<T, Compare>::insertNode(T data)
    {
            if (root == nullptr) {
                root = NewNode(data);
            }
            else {
            	insertNode(data, root);
            }
    }

    template <typename T, typename Compare>
    inline Node<T, Compare> *BinaryTree<T, Compare>::insertNode(T data, bst::Node<T, Compare> *node)
    {
        if(Compare::Compare(data, node->data()) == CompareResult::LESS_THAN) {
			if(node->left() == nullptr) {
				node->left() = NewNode(data);
				return node->left();
			} else {
				return insertNode(data, node->left());
			}
		} else {
			if(node->right() == nullptr) {
				node->right() = NewNode(data);
				return node->right();
			} else {
				return insertNode(data, node->right());
			}
		}
    }

template <typename T, typename Compare>
void BinaryTree<T, Compare>::deleteNode(T data) {
	if(isEmpty()) {
		cerr << "Error: cannot remove node from an empty tree!" << endl;
	} else {
		root = deleteNode(data, root);
	}
}
template <typename T, typename Compare>
inline Node<T, Compare> *BinaryTree<T, Compare>::deleteNode(T data, bst::Node<T, Compare> *node) {
	if(node == nullptr) {
		return nullptr;
	} else if(Compare::Compare(data, node->data()) == CompareResult::LESS_THAN) {
		node->left() = deleteNode(data, node->left());
	} else if(Compare::Compare(data, node->data()) == CompareResult::GREATER_THAN) {
		node->right() = deleteNode(data, node->right());
	} else {
		if(node->left() == nullptr && node->right() == nullptr) {
			node = nullptr;
		} else if(node->left() != nullptr && node->right() == nullptr) {
			node = node->left();
		} else if(node->right() != nullptr && node->left() == nullptr) {
			node = node->right();
		} else {
			findMinHelper(node->right());
			node->data() = findMinHelper(node->right());
			node->right() = deleteNode(findMinHelper(node->right()), node->right());
		}
	}
}

template<typename T, typename Compare>
T bst::BinaryTree<T, Compare>::findMin() {
	if(isEmpty()) {
		cerr << "cannot find if tree is empty!" << endl;
	} else {
		return findMinHelper(root);
	}
}

template <typename T, typename Compare>
T bst::BinaryTree<T, Compare>::findMinHelper(bst::Node<T, Compare>* node) {
	if(node->left() != nullptr) {
		return findMinHelper(node->left());
	} else {
		return node->data();
	}
}


// Helper function that search the data in the tree
// return Node
template <typename T, typename Compare> 
Node<T, Compare>* bst::BinaryTree<T, Compare>::findHelper(Node<T, Compare>* current, T data) const{
	if(current != NULL){
		if(Compare::Compare(data, current->data()) == CompareResult::EQUAL){
			return current;
		}
		else if(Compare::Compare(data, current->data()) == CompareResult::LESS_THAN){
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



// search data in the tree
// return Node
template <typename T, typename Compare> 
bst::Node<T, Compare>* bst::BinaryTree<T, Compare>::find(T data) const{
	if(root == NULL){
		return nullptr;
	}
	else if(Compare::Compare(data, root->data()) == CompareResult::EQUAL){
		return root;
	}
	else if(Compare::Compare(data, root->data()) == CompareResult::LESS_THAN){
		return findHelper(root->left(), data);
	}
	return findHelper(root->right(), data);
}

template<typename T, typename Compare>
inline Node<T, Compare>* BinaryTree<T, Compare>::NewNode(T& data, Node<T, Compare>* parent, Node<T, Compare>* left, Node<T, Compare>* right)
{
	auto newNode = new Node<T, Compare>(data);
	if (parent) newNode->parent() = parent;
	if (left) newNode->left() = left;
	if (right) newNode->right() = right;

	return newNode;
}







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

}