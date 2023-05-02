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
			void binarySearch();
		protected:
			Node* insertNode(T data, Node* node);
		private:
			Node* root;
	};
}

