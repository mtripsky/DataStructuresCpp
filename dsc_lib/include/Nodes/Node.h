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

namespace dsc::trees {

template <typename T>
struct Node {
  Node(T data) : data(data), left(nullptr), right(nullptr) {}

  T                        data;
  std::shared_ptr<Node<T>> left;
  std::shared_ptr<Node<T>> right;
};

template <typename T>
Node<T> node(T data)
{
  return Node<T>(data);
}

template <typename Tkey, typename Tdata>
struct KeyNode {
  KeyNode(Tkey key, Tdata data) : key(key), data(data), left(nullptr), right(nullptr) {}

  Tkey                                  key;
  Tdata                                 data;
  std::shared_ptr<KeyNode<Tkey, Tdata>> left;
  std::shared_ptr<KeyNode<Tkey, Tdata>> right;
};

template <typename Tkey, typename Tdata>
KeyNode<Tkey, Tdata> keyNode(Tkey key, Tdata data)
{
  return KeyNode<Tkey, Tdata>(key, data);
}


} // namespace dsc::trees

