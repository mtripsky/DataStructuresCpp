#pragma once

#include <iostream>
#include <memory>

namespace dsc::lists {

template <typename T>
struct Node {
  Node(T data) : data(data), next(nullptr) {}

  T                        data;
  std::shared_ptr<Node<T>> next;
};

template <typename T>
Node<T> node(T data)
{
  return Node<T>(data);
}

} // namespace dsc::lists
