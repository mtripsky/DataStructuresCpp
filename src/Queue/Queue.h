#pragma once

#include <iostream>
#include <memory>

namespace dsc {
namespace fifo {

template <typename T>
class Queue {
public:
  Queue(std::size_t maxSize) noexcept :
    m_queue(std::make_unique<T[]>(maxSize + 1)), m_maxSize(maxSize), m_size(0), m_front(0),
    m_rear(0)
  {}

  bool         Push(const T& elem);
  bool         Pop();
  const T&     Front() const;
  const bool   IsEmpty() const { return Size() == 0; }
  const bool   IsFull() const { return Size() == m_maxSize; }
  const size_t Size() const { return m_size; }
  void         Print() const;

private:
  std::unique_ptr<T[]> m_queue;
  std::size_t          m_maxSize;
  std::size_t          m_size;
  int                  m_front;
  int                  m_rear;
};

template <typename T>
bool Queue<T>::Push(const T& elem)
{
  if (IsFull())
    return false;

  if (m_rear + 1 > m_maxSize) {
    m_rear          = 0;
    m_queue[m_rear] = elem;
  }
  else {
    m_queue[m_rear] = elem;
  }
  ++m_rear;
  ++m_size;

  return true;
}

template <typename T>
bool Queue<T>::Pop()
{
  if (IsEmpty()) {
    return false;
  }
  --m_size;
  m_front = m_front + 1 > m_maxSize - 1 ? 0 : ++m_front;

  return true;
}

template <typename T>
const T& Queue<T>::Front() const
{
  if (IsEmpty()) {
    throw "Queue is empty";
  }

  return m_queue[m_front];
}

template <typename T>
void Queue<T>::Print() const
{
  if (IsEmpty())
    std::cout << "Queue is empty\n";
  else {
    auto index = m_front;

    for (auto i = 0; i < m_size; ++i) {
      index = index + 1 > m_maxSize ? 0 : index;
      std::cout << m_queue[index] << "->";
      ++index;
    }
    std::cout << std::endl;
  }
}

} // namespace fifo
} // namespace dsc
