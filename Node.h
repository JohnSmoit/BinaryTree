#pragma once
#include <utility>


namespace bst 
{

	enum CompareResult 
	{
		EQUAL,
		LESS_THAN,
		GREATER_THAN
	};

	template <typename T>
	struct GenericComparison 
	{
		static CompareResult Compare(const T& A, const T& B) 
		{
			return (A > B) ? GREATER_THAN : ((A < B) ? LESS_THAN : EQUAL);
		}
	};

	template <typename T, typename _Comp = GenericComparison<T>>
	class Node {
		public:

			Node() : m_parent(nullptr), m_left(nullptr), m_right(nullptr), m_data(nullptr) {}
			Node(T&& data); //moves (must be on heap)
			Node(T& data); //copies

			T& data();
			Node*& parent();
			Node*& left();
			Node*& right();
		private:
			T* m_data;
			Node<T, _Comp>* m_parent;
			Node<T, _Comp>* m_left;
			Node<T, _Comp>* m_right;
}


template <typename T, typename _Comp>
bst::Node<T, _Comp>::Node(T& data) {
	*m_data = data;

	m_parent = nullptr;
	m_left = nullptr;
	m_right = nullptr;
}

template <typename T, typename _Comp>
bst::Node<T, _Comp>::Node(T&& data) 
{
	m_data = new T();
	*m_data = std::forward<T>(data);

	m_parent = nullptr;
	m_left = nullptr;
	m_right = nullptr;
}

template <typename T, typename _Comp>
inline T& bst::Node<T, _Comp>::data()
{
	return *m_data;
}

template <typename T, typename _Comp>
inline bst::Node<T, _Comp>*& bst::Node<T, _Comp>::left()
{
	return m_left;
}

template <typename T, typename _Comp>
inline bst::Node<T, _Comp>*& bst::Node<T, _Comp>::right()
{
	return m_right;
}

template <typename T, typename _Comp>
inline bst::Node<T, _Comp>*& bst::Node<T, _Comp>::parent()
{
	return m_parent;
}

