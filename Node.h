#pragma once


namespace bst 
{
	template <typename T>
	class Node {
		public:
			T data;
			Node* parent;
			Node* left;
			Node* right;

	};
}

