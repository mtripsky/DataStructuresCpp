#include "node.h"
#include "unordered_list.h"

template<typename T>
bool dsc::lists::UnorderedList<T>::push(const T& data)
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
bool dsc::lists::UnorderedList<T>::pop()
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
bool dsc::lists::UnorderedList<T>::remove(const T& data)
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
const dsc::lists::Node<T>* dsc::lists::UnorderedList<T>::back() const
{
	return m_tail.get();
}

template<typename T>
const dsc::lists::Node<T>* dsc::lists::UnorderedList<T>::front() const
{
	return m_head.get();
}

template<typename T>
void dsc::lists::UnorderedList<T>::print() const
{
	auto temp = m_head;

	while(temp) {
		std::cout << temp->data << " -> ";
		temp = temp->next;
	}
	std::cout << std::endl;
}
