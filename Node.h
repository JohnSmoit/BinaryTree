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

	template <typename T>
	class BaseNode 
	{
	public:
		BaseNode() : m_data(nullptr) {}
		virtual CompareResult evaluate(const T& other) const;
	protected:
		T* m_data;
	};

	template <typename T, typename _Comp = GenericComparison<T>>
	class Node : public BaseNode<T> {
	public:
		Node() : m_parent(nullptr), m_left(nullptr), m_right(nullptr), BaseNode<T>() {}
		Node(T&& data); //moves (must be on heap)
		Node(T& data); //copies

		CompareResult evaluate(const T& other) const override;
		T& data();
		Node*& parent();
		Node*& left();
		Node*& right();
		
		bool leaf() const;
	private:
		Node<T, _Comp>* m_parent;
		Node<T, _Comp>* m_left;
		Node<T, _Comp>* m_right;


	};

	template<typename T>
	inline CompareResult BaseNode<T>::evaluate(const T& other) const
	{
		return bst::GenericComparison<T>::Compare(*this->m_data, other);
	}
}



template <typename T, typename _Comp>
bst::Node<T, _Comp>::Node(T& data) {
	this->m_data = new T();
	*this->m_data = data;

	m_parent = nullptr;
	m_left = nullptr;
	m_right = nullptr;
}

template <typename T, typename _Comp>
bst::Node<T, _Comp>::Node(T&& data) 
{
	this->m_data = new T();
	*this->m_data = std::forward<T>(data);

	m_parent = nullptr;
	m_left = nullptr;
	m_right = nullptr;
}

template<typename T, typename _Comp>
inline bst::CompareResult bst::Node<T, _Comp>::evaluate(const T& other) const
{
	return _Comp::Compare(*this->m_data, other);
}

template <typename T, typename _Comp>
inline T& bst::Node<T, _Comp>::data()
{
	return *this->m_data;
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

