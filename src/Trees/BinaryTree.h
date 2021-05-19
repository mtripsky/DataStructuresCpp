#pragma once

#include "Node.h"
#include <iostream>
#include <memory>
#include <queue>

namespace dsc {

template <typename T>
class BinaryTree {
public:
  BinaryTree() noexcept : m_root(nullptr), m_size(0) {}

  void              insert(T data) { insert(m_root, data); }
  void              printTreeStructure() const { printTreeStructure(m_root, 0); }
  void              printInOrder() const;
  void              printBreadthFirst() const;
  const std::size_t size() const { return m_size; }
  const int         depth() const;

private:
  void      insert(std::shared_ptr<trees::Node<T>>& root, T data);
  const int depth(std::shared_ptr<trees::Node<T>> root) const;
  const int max(const int x, const int y) const { return x >= y ? x : y; }
  void      printTreeStructure(std::shared_ptr<trees::Node<T>> root, int space) const;
  void      printInOrder(std::shared_ptr<trees::Node<T>> root) const;

  std::shared_ptr<trees::Node<T>>             m_root;
  std::size_t                                 m_size;
  std::queue<std::shared_ptr<trees::Node<T>>> m_queue;
};

} // namespace dsc

template <typename T>
void dsc::BinaryTree<T>::printInOrder() const
{
  printInOrder(m_root);
  std::cout << std::endl;
}

template <typename T>
void dsc::BinaryTree<T>::printBreadthFirst() const
{
  std::queue<std::shared_ptr<dsc::trees::Node<T>>> queue;
  queue.push(m_root);

  while (!queue.empty()) {
    const auto n = queue.front();
    queue.pop();
    std::cout << n->data;
    if (n->left) {
      queue.push(n->left);
    }
    if (n->right) {
      queue.push(n->right);
    }
  }
}

template <typename T>
const int dsc::BinaryTree<T>::depth() const
{
  if (!m_root)
    return 0;

  return max(depth(m_root->left), depth(m_root->right)) + 1;
}

template <typename T>
void dsc::BinaryTree<T>::insert(std::shared_ptr<trees::Node<T>>& root, T data)
{
  if (!root) {
    // auto temp{std::make_shared<dsc::trees::trees::Node<T>>(node(data))};
    // root = std::move(temp);
    root = std::make_shared<dsc::trees::Node<T>>(dsc::trees::node(data));
    m_queue.push(root);
    ++m_size;
  }
  else {
    if (m_queue.front()->left && m_queue.front()->right) {
      m_queue.pop();
      insert(m_queue.front(), data);
    }
    else if (m_queue.front()->left) {
      insert(m_queue.front()->right, data);
    }
    else {
      insert(m_queue.front()->left, data);
    }
  }
}

template <typename T>
const int dsc::BinaryTree<T>::depth(std::shared_ptr<trees::Node<T>> root) const
{
  if (!root)
    return 0;

  return max(depth(root->left), depth(root->right)) + 1;
}

template <typename T>
void dsc::BinaryTree<T>::printTreeStructure(std::shared_ptr<trees::Node<T>> root, int space) const
{
  if (!root)
    return;

  // Increase distance between levels
  space += 4;

  // Process right child first
  printTreeStructure(root->right, space);

  // Print a key of current node after space
  std::cout << std::endl;
  for (int i = 2; i < space; i++)
    std::cout << " ";
  std::cout << root->data << "\n";

  // Process left child
  printTreeStructure(root->left, space);
}

template <typename T>
void dsc::BinaryTree<T>::printInOrder(std::shared_ptr<dsc::trees::Node<T>> root) const
{
  if (!root)
    return;

  printInOrder(root->left);
  std::cout << root->data << ", ";
  printInOrder(root->right);
}