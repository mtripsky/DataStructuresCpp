#ifndef Linked_List_Unordered_Linked_List_h
#define Linked_List_Unordered_Linked_List_h

#include <iostream>
#include <memory>
#include "../node.h"


namespace dsc {
namespace lists {
namespace unordered {

template<typename T>
class LinkedList {
public:
	// -------------------------------------------------------------------------
	// CONSTRUCTORS
	// -------------------------------------------------------------------------
	LinkedList() noexcept
		: m_head(nullptr)
		, m_tail(nullptr)
		, m_size(0)
	{
	}

	// -------------------------------------------------------------------------
	// DESTRUCTORS
	// -------------------------------------------------------------------------
	~LinkedList()
	{
		clean();
	}

	// -------------------------------------------------------------------------
	// METHODS
	// -------------------------------------------------------------------------
	bool push(const T& data);
	bool push_back(const T& data);
	bool pop();
	bool remove(const T& data);
	const Node<T>* back() const;
	const Node<T>* front() const;
	void reverse();
	void print() const;

	size_t& size()
	{
		return m_size;
	}

	const bool isEmpty() const
	{
		return m_head == nullptr;
	}

private:
	// -------------------------------------------------------------------------
	// AUXILARY METHODS
	// -------------------------------------------------------------------------
	void clean()
	{
		while(m_head) {
			m_head = std::move(m_head->next);
		}
		m_tail = m_head;
	}

	// -------------------------------------------------------------------------
	// DATA
	// -------------------------------------------------------------------------
	std::shared_ptr<Node<T>> m_head;
	std::shared_ptr<Node<T>> m_tail;
	std::size_t m_size;
};

}  // namespace unordered
}  // namespace lists
}  // namespace dsc

#include "linkedList.cpp"

#endif  // Linked_List_Unordered_Linked_List_h
