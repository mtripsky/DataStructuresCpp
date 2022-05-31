#pragma once

#include <stdexcept>
#include <iostream>

namespace dsc {

template <typename T>
struct Node {
  Node(T&& d) : data(std::forward<T>(d)), next(nullptr) {}
  Node(const T& d) : data(d), next(nullptr) {}

  T data;
  Node<T>* next;
};

template <typename T>
class DynamicStack {
public:
  DynamicStack() : m_head(nullptr), m_size(0) {}
  ~DynamicStack() { Clear(); }

  void  Push(const T& elem);
  void  Push(T&& elem);
  template <typename... Args>
  T&    Emplace(Args&&... args);

  void  Pop();
  T&    Top();
  
  const size_t Size() const { return m_size; }
  bool         Empty() const {return m_size == 0;}

private:
  void Clear();

  Node<T>*    m_head;
  std::size_t m_size;
};

} // namespace dsc

template <typename T>
void dsc::DynamicStack<T>::Clear()
{
  while (m_head) {
    auto temp = m_head;
    m_head    = temp->next;
    temp->data.~T();
    ::operator delete(temp,  sizeof(Node<T>));
    --m_size;
  }
}

template <typename T>
void dsc::DynamicStack<T>::Push(const T& elem)
{
  if (m_head) {
    const auto temp = std::move(m_head);
    m_head          = new Node<T>(elem);
    m_head->next = temp;
  }
  else {
    m_head = new Node<T>(elem);
  }
  ++m_size;
}

template <typename T>
void dsc::DynamicStack<T>::Push(T&& elem)
{
  if (m_head) {
    const auto temp = std::move(m_head);
    m_head          = new Node<T>(std::move(elem));
    m_head->next    = temp;
  }
  else {
    m_head = new Node<T>(std::move(elem));
  }
  ++m_size;
}

template <typename T>
template <typename... Args>
T& dsc::DynamicStack<T>::Emplace(Args&&... args)
{
  Node<T>* newHead = (Node<T>*)::operator new(sizeof(Node<T>));
  new (&newHead->data) T(std::forward<Args>(args)...);
  newHead->next = m_head;

  m_head = newHead;
  ++m_size;

  return m_head->data;
}

template <typename T>
void dsc::DynamicStack<T>::Pop()
{
  if(!m_head){
    return;
  }

  auto temp = m_head;
  m_head    = temp->next;
  --m_size;

  temp->data.~T();
  ::operator delete(temp,  sizeof(Node<T>));
}

template <typename T>
T& dsc::DynamicStack<T>::Top()
{
  if (m_size == 0) {
    throw "Stack is empty";
  }

  return m_head->data;
}