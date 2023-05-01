#pragma once

#include "Node.h"
#include <iostream>
#include <memory>

namespace dsc {

template <typename T>
class OrderedList {
public:
  OrderedList() noexcept : m_head(nullptr), m_tail(nullptr), m_size(0) {}

  ~OrderedList() { clean(); }

  bool                  push(const T& data);
  bool                  pop();
  bool                  remove(const T& data);
  const lists::Node<T>* back() const;
  const lists::Node<T>* front() const;
  void                  reverse();
  void                  print() const;

  size_t& size() { return m_size; }

  const bool isEmpty() const { return m_head == nullptr; }

private:
  void clean()
  {
    while (m_head) {
      m_head = std::move(m_head->next);
    }
    m_tail = m_head;
  }

  std::shared_ptr<lists::Node<T>> m_head;
  std::shared_ptr<lists::Node<T>> m_tail;
  std::size_t                     m_size;
};

} // namespace dsc

template <typename T>
bool dsc::OrderedList<T>::push(const T& data)
{
  auto temp{std::make_shared<lists::Node<T>>(lists::node(data))};

  if (isEmpty()) {
    m_head = std::move(temp);
    m_tail = m_head;
  }
  else {
    auto                            current = m_head;
    std::shared_ptr<lists::Node<T>> previous(nullptr);

    while (current) {
      if (current->data <= data) {
        if (previous) {
          previous->next = temp;
          temp->next     = current;
        }
        else {
          temp->next = current;
          m_head     = std::move(temp);
        }

        ++size();
        return true;
      }
      previous = current;
      current  = current->next;
    }

    previous->next = temp;
    m_tail         = std::move(temp);
  }

  ++size();
  return true;
}

template <typename T>
bool dsc::OrderedList<T>::pop()
{
  if (isEmpty()) {
    return true;
  }

  auto temp = std::move(m_head);
  m_head    = std::move(temp->next);

  --size();
  return true;
}

template <typename T>
bool dsc::OrderedList<T>::remove(const T& data)
{
  auto temp = m_head;

  while (temp) {
    if (temp->data == data) {
      m_head = std::move(temp->next);
      --size();

      return true;
    }

    if (temp->next && temp->next->data == data) {
      if (temp->next->next) {
        temp->next = temp->next->next;
        --size();

        return true;
      }
      else {
        temp->next = nullptr;
        m_tail     = std::move(temp);
        --size();

        return true;
      }
    }

    temp = temp->next;
  }

  return false;
}

template <typename T>
const dsc::lists::Node<T>* dsc::OrderedList<T>::back() const
{
  return m_tail.get();
}

template <typename T>
const dsc::lists::Node<T>* dsc::OrderedList<T>::front() const
{
  return m_head.get();
}

template <typename T>
void dsc::OrderedList<T>::reverse()
{
  if (m_head != m_tail) {
    std::shared_ptr<dsc::lists::Node<T>> previous(nullptr);
    auto                                 current   = m_head;
    auto                                 following = m_head;
    m_tail                                         = m_head;

    while (current) {
      following     = following->next;
      current->next = previous;
      previous      = current;
      current       = following;
    }
    m_head = previous;
  }
}

template <typename T>
void dsc::OrderedList<T>::print() const
{
  auto temp = m_head;

  while (temp) {
    std::cout << temp->data << " -> ";
    temp = temp->next;
  }
  std::cout << std::endl;
}
