#pragma once

#include <stdexcept>
#include <iostream>

namespace dsc {

template <typename T>
struct Node {
  Node(const T* data) : data(data), next(nullptr) {}
  //Node(T&& data) : data(std::move(data)), next(nullptr) {}

  const T* data;
  Node<T>* next;
};

template <typename T>
class DynamicStack {
public:
  DynamicStack() {}
  ~DynamicStack() { Clear(); }

  bool         Push(const T& elem);
  //bool         Push(T&& elem);
  T            Pop();
  const T&     Top() const;
  const size_t Size() const { return m_size; }
  // void         print();

private:
  void Clear();

  Node<T>*    m_head = nullptr;
  std::size_t m_size;
};

} // namespace dsc

template <typename T>
void dsc::DynamicStack<T>::Clear()
{
  std::cout << "Clear\n";
  while (m_head) {
    auto temp = m_head;
    m_head    = temp->next;
    std::cout << "temp: " << temp->data;
    delete temp;
    --m_size;
  }
}

template <typename T>
bool dsc::DynamicStack<T>::Push(const T& elem)
{
  std::cout << "PUSH\n";
  if (m_head) {
    const auto temp = m_head;
    m_head          = new Node<T>(&elem);
    m_head->next    = temp;
  }
  else {
    m_head = new Node<T>(&elem);
  }
  ++m_size;

  return true;
}

// template <typename T>
// bool dsc::DynamicStack<T>::Push(T&& elem)
// {
//   std::cout << "PUSH move\n";
//   if (m_head) {
//     const auto temp = m_head;
//     m_head          = new Node<T>(std::move(elem));
//     m_head->next    = temp;
//   }
//   else {
//     m_head = new Node<T>(std::move(elem));
//   }
//   ++m_size;

//   return true;
// }

template <typename T>
T dsc::DynamicStack<T>::Pop()
{
  if(!m_head){
    throw std::range_error("Stack is empty");
  }

  auto temp = m_head;
  m_head    = temp->next;
  const T* data = std::move(temp->data);
  delete temp;
  --m_size;

  return *data;
}
template <typename T>
const T& dsc::DynamicStack<T>::Top() const
{
  if (m_size == 0) {
    throw "Stack is empty";
  }

  return *(m_head->data);
}