#include "../node.h"
#include "linkedList.h"

template<typename T>
bool dsc::lists::unordered::LinkedList<T>::push(const T& data)
{
	auto temp{std::make_shared<dsc::lists::Node<T>>(node(data))};

	if(isEmpty()) {
		m_head = std::move(temp);
		m_tail = m_head;
	}
	else {
		temp->next = std::move(m_head);
		m_head = std::move(temp);
	}

	++size();
	return true;
}

template<typename T>
bool dsc::lists::unordered::LinkedList<T>::push_back(const T& data)
{
	auto temp{std::make_shared<dsc::lists::Node<T>>(node(data))};

	if(isEmpty()) {
		m_tail = std::move(temp);
		m_head = m_tail;
	}
	else {
		auto tail = std::move(m_tail);
		temp->next = std::move(m_tail);
		m_tail = std::move(temp);
		tail->next = m_tail;
	}

	++size();
	return true;
}

template<typename T>
bool dsc::lists::unordered::LinkedList<T>::pop()
{
	if(isEmpty()) {
		return true;
	}

	auto temp = std::move(m_head);
	m_head = std::move(temp->next);

	--size();
	return true;
}

template<typename T>
bool dsc::lists::unordered::LinkedList<T>::remove(const T& data)
{
	auto temp = m_head;

	while(temp) {
		if(temp->data == data) {
			m_head = std::move(temp->next);
			--size();

			return true;
		}

		if(temp->next && temp->next->data == data) {
			if(temp->next->next) {
				temp->next = temp->next->next;
				--size();

				return true;
			}
			else {
				temp->next = nullptr;
				m_tail = std::move(temp);
				--size();

				return true;
			}
		}

		temp = temp->next;
	}

	return false;
}

template<typename T>
const dsc::lists::Node<T>* dsc::lists::unordered::LinkedList<T>::back() const
{
	return m_tail.get();
}

template<typename T>
const dsc::lists::Node<T>* dsc::lists::unordered::LinkedList<T>::front() const
{
	return m_head.get();
}

template<typename T>
void dsc::lists::unordered::LinkedList<T>::reverse()
{
	if(m_head != m_tail)
	{
		std::shared_ptr<dsc::lists::Node<T>> previous(nullptr);
		auto current = m_head;
		auto following = m_head;
		m_tail = m_head;

		while(current)
		{
			following = following->next;
			current->next = previous;
			previous = current;
			current = following;
		}
		m_head = previous;
	}
}

template<typename T>
void dsc::lists::unordered::LinkedList<T>::print() const
{
	auto temp = m_head;

	while(temp) {
		std::cout << temp->data << " -> ";
		temp = temp->next;
	}
	std::cout << std::endl;
}
