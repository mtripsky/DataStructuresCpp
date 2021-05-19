#pragma once

#include <iostream>
#include <memory>

namespace dsc {

template <typename T>
class Stack {
public:
  Stack(std::size_t maxSize) noexcept :
    m_stack(std::make_unique<T[]>(maxSize + 1)), m_maxSize(maxSize), m_size(0), m_top(0)
  {}

  bool push(const T& elem);

  bool pop();

  const T& top() const;

  const bool isEmpty() const { return size() == 0; }

  bool isFull() { return size() == m_maxSize; }

  const size_t size() const { return m_size; }

  void print();

private:
  size_t& updateSize() { return m_size; }

  std::unique_ptr<T[]> m_stack;
  std::size_t          m_maxSize;
  std::size_t          m_size;
  int                  m_top;
};

} // namespace dsc

template <typename T>
bool dsc::Stack<T>::push(const T& elem)
{
  if (isFull())
    return false;

  if (m_top + 1 > m_maxSize) {
    m_top          = 0;
    m_stack[m_top] = elem;
  }
  else {
    m_stack[m_top] = elem;
  }
  ++m_top;
  ++updateSize();

  return true;
}

template <typename T>
bool dsc::Stack<T>::pop()
{
  if (isEmpty())
    return false;

  --updateSize();
  --m_top;

  return true;
}

template <typename T>
const T& dsc::Stack<T>::top() const
{
  if (isEmpty())
    throw "Stack is empty";

  return m_stack[m_top - 1];
}

template <typename T>
void dsc::Stack<T>::print()
{
  if (isEmpty())
    std::cout << "Stack is empty\n";
  else {
    auto index = m_top - 1;

    for (auto i = 0; i < size(); ++i) {
      index = index < 0 ? m_maxSize - 1 : index;
      std::cout << m_stack[index] << "->";
      --index;
    }
    std::cout << std::endl;
  }
}