#pragma once


namespace bst 
{
	template <typename T>
	class BinaryTree
	{
		public:
			BinaryTree(Node root = NULL);
			void PrintAll() const; // print all the node in the bin
			bool AddNode(T newVal) const;// would be Node or a type of data
			bool Find(T data) const;// sreach node, return true if find else return false
			bool Compare(BinaryTree tree);//compare with another binary tree
			void Clear() const;//empty the tree
		private:
			Node root;
	};
}

