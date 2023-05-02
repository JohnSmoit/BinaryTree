#pragma once
#include "Node.h"

namespace bst 
{
	template <typename T>
	class BinaryTree {
		public:
			BinaryTree(Node root = NULL);
			void insertNode(T data);
			void deleteNode(T data);
			void clear() const;
			bool find() const;
		protected:
			Node* insertNode(T data, Node* node);
		private:
			Node* root;


	};

   /*template <typename T>
    void BinaryTree<T>::insertNode(T data) {
		if(root == nullptr) {
			root = new Node(data);
		} else {
			insertHelper(data, root);
		}
    }

	insertHelper(T data, Node* node) {

	}*/
}
