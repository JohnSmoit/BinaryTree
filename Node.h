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
		BaseNode() : m_data(nullptr), m_parent(nullptr), m_left(nullptr), m_right(nullptr) {}
		virtual CompareResult evaluate(const T& other) const;


		bool leaf() const;

		T& data();
		BaseNode*& parent();
		BaseNode*& left();
		BaseNode*& right();

	protected:
		BaseNode* m_parent;
		BaseNode* m_left;
		BaseNode* m_right;
		T* m_data;
	};

	template <typename T, typename _Comp = GenericComparison<T>>
	class Node : public BaseNode<T> {
	public:
		Node() : BaseNode<T>() {}
		Node(T&& data); //moves (must be on heap)
		Node(const T& data); //copies

		CompareResult evaluate(const T& other) const override;



	};

	template<typename T>
	inline CompareResult BaseNode<T>::evaluate(const T& other) const
	{
		return bst::GenericComparison<T>::Compare(*this->m_data, other);
	}
}


template <typename T>
inline bool bst::BaseNode<T>::leaf() const 
{
	return !m_left && !m_right;
}

template <typename T, typename _Comp>
bst::Node<T, _Comp>::Node(const T& data) {
	this->m_data = new T();
	*this->m_data = data;

	this->m_parent = nullptr;
	this->m_left = nullptr;
	this->m_right = nullptr;
}

template <typename T, typename _Comp>
bst::Node<T, _Comp>::Node(T&& data) 
{
	this->m_data = new T();
	*this->m_data = std::forward<T>(data);

	this->m_parent = nullptr;
	this->m_left = nullptr;
	this->m_right = nullptr;
}

template<typename T, typename _Comp>
inline bst::CompareResult bst::Node<T, _Comp>::evaluate(const T& other) const
{
	return _Comp::Compare(*this->m_data, other);
}

template <typename T>
inline T& bst::BaseNode<T>::data()
{
	return *this->m_data;
}

template <typename T>
inline bst::BaseNode<T>*& bst::BaseNode<T>::left()
{
	return m_left;
}

template <typename T>
inline bst::BaseNode<T>*& bst::BaseNode<T>::right()
{
	return m_right;
}

template <typename T>
inline bst::BaseNode<T>*& bst::BaseNode<T>::parent()
{
	return m_parent;
}

