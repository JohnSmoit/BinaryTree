#pragma once
#include "Node.h"


namespace bst 
{
	template <typename T, typename Compare = GenericComparison<T>>
	class BinaryTree {
		public:
			BinaryTree(Node<T, Compare> root = NULL);
			void insertNode(T data);
			void deleteNode(T data);
			void clear() const;
			bool find() const;
			bool isBalanced();

			Node<T, Compare>* NewNode(T& data, Node<T, Compare>* parent = nullptr, Node<T, Compare>* left = nullptr, Node<T, Compare>* right = nullptr); //uses less template mess this way.
		protected:
			Node<T, Compare>* insertNode(T data, Node<T, Compare>* node);
			Node<T, Compare>* deleteNode(T data, Node<T, Compare>* node);
			bool isBalanced(Node<T, Compare>* node);
		private:
			Node<T, Compare>* root;
	};
}

