#ifndef Stack_Stack_h
#define Stack_Stack_h

#include <iostream>


namespace dsc {
namespace lifo {

template<typename T>
class Stack {
public:
	// -------------------------------------------------------------------------
	// CONSTRUCTORS
	// -------------------------------------------------------------------------
	Stack(std::size_t maxSize) noexcept
		: m_maxSize(maxSize)
		, m_size(0)
		, m_top(0)
	{
		m_stack = new T[maxSize + 1];
	}

	// -------------------------------------------------------------------------
	// DESTRUCTORS
	// -------------------------------------------------------------------------
	~Stack()
	{
		delete[] m_stack;
	}

	// -------------------------------------------------------------------------
	// METHODS
	// -------------------------------------------------------------------------
	bool push(const T& elem)
	{
		if(isFull())
			return false;

		if(m_top + 1 > m_maxSize) {
			m_top = 0;
			m_stack[m_top] = elem;
		}
		else {
			m_stack[m_top] = elem;
		}
		++m_top;
		++updateSize();

		return true;
	}

	bool pop()
	{
		if(isEmpty())
			return false;

		--updateSize();
		--m_top;

		return true;
	}

	const T& top() const
	{
		if(isEmpty())
			throw "Stack is empty";

		return m_stack[m_top - 1];
	}

	const bool isEmpty() const
	{
		return size() == 0;
	}

	bool isFull()
	{
		return size() == m_maxSize;
	}

	const size_t size() const
	{
		return m_size;
	}

	void print()
	{
		if(isEmpty())
			std::cout << "Stack is empty\n";
		else {
			auto index = m_top - 1;

			for(auto i = 0; i < size(); ++i) {
				index = index < 0 ? m_maxSize - 1 : index;
				std::cout << m_stack[index] << "->";
				--index;
			}
			std::cout << std::endl;
		}
	}

private:
	// -------------------------------------------------------------------------
	// AUXILARY METHODS
	// -------------------------------------------------------------------------
	size_t& updateSize()
	{
		return m_size;
	}

	// -------------------------------------------------------------------------
	// DATA
	// -------------------------------------------------------------------------
	std::size_t m_maxSize;
	std::size_t m_size;
	int m_top;
	T* m_stack;
};

}  // namespace lifo
}  // namespace dsc

#endif  // Stack_Stack_h
