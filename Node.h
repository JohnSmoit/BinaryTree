#pragma once


namespace bst 
{
	template <typename T>
	class Node {
		public:
			T data;
			Node* parent;
			Node* leaf;
			Node* left;
			Node* right;

			Node(T key) {
				data = key;
				left = nullptr;
				right = nullptr;
				parent = nullptr;
				leaf = nullptr;
			}
	};


}

