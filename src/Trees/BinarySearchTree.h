#pragma once

#include "Node.h"
#include <iostream>
#include <memory>

namespace dsc {

template <typename Tkey, typename Tdata>
class BinarySearchTree {
public:
  BinarySearchTree() noexcept : m_root(nullptr), m_size(0) {}

  BinarySearchTree(Tkey keys[], int size) noexcept : m_size(size)
  {
    m_root = std::move(createMinimalTreeFromArray(keys, 0, size - 1));
  }

  void remove(Tkey key) { remove(m_root, key); }

  void insert(Tkey key, Tdata data) { insert(m_root, key, data); }

  void printTreeStructure() const { printTreeStructure(m_root, 0); }

  void printInOrder() const
  {
    printInOrder(m_root);
    std::cout << std::endl;
  }

  const trees::KeyNode<Tkey, Tdata>* findNode(Tkey key) const { return findNode(m_root, key); }

  const Tkey findMaxKey() const
  {
    if (!m_root) {
      throw "Tree is empty";
    }

    return findMaxMinKey(m_root, true);
  }

  const Tkey findMinKey() const
  {
    if (!m_root) {
      throw "Tree is empty";
    }

    return findMaxMinKey(m_root, false);
  }

  const std::size_t size() const { return m_size; }

  const int depth() const
  {
    if (!m_root)
      return 0;

    return max(depth(m_root->left), depth(m_root->right)) + 1;
  }

private:
  std::shared_ptr<dsc::trees::KeyNode<Tkey, Tdata>> createMinimalTreeFromArray(Tkey keys[],
                                                                               int left, int right);

  const Tkey findMaxMinKey(std::shared_ptr<dsc::trees::KeyNode<Tkey, Tdata>> root,
                           bool                                              findMaximum) const;

  const dsc::trees::KeyNode<Tkey, Tdata>*
  findNode(std::shared_ptr<dsc::trees::KeyNode<Tkey, Tdata>> root, Tkey key) const;

  void insert(std::shared_ptr<dsc::trees::KeyNode<Tkey, Tdata>>& root, Tkey key, Tdata data);

  const int depth(std::shared_ptr<dsc::trees::KeyNode<Tkey, Tdata>> root) const
  {
    if (!root)
      return 0;

    return max(depth(root->left), depth(root->right)) + 1;
  }

  const int max(const int x, const int y) const { return x >= y ? x : y; }

  void printTreeStructure(std::shared_ptr<dsc::trees::KeyNode<Tkey, Tdata>> root, int space) const;

  void printInOrder(std::shared_ptr<dsc::trees::KeyNode<Tkey, Tdata>> root) const
  {
    if (!root)
      return;

    printInOrder(root->left);
    std::cout << root->key << ", ";
    printInOrder(root->right);
  }

  void remove(std::shared_ptr<dsc::trees::KeyNode<Tkey, Tdata>>& root, Tkey key);

  std::shared_ptr<dsc::trees::KeyNode<Tkey, Tdata>> m_root;
  std::size_t                                       m_size;
};

} // namespace dsc

template <typename Tkey, typename Tdata>
std::shared_ptr<dsc::trees::KeyNode<Tkey, Tdata>>
dsc::BinarySearchTree<Tkey, Tdata>::createMinimalTreeFromArray(Tkey keys[], int left, int right)
{
  if (left > right)
    return nullptr;

  int  mid = (left + right) / 2;
  auto result{std::make_shared<dsc::trees::KeyNode<Tkey, Tdata>>(
      dsc::trees::keyNode(keys[mid], keys[mid]))};
  result->left  = std::move(createMinimalTreeFromArray(keys, left, mid - 1));
  result->right = std::move(createMinimalTreeFromArray(keys, mid + 1, right));

  return result;
}

template <typename Tkey, typename Tdata>
const Tkey dsc::BinarySearchTree<Tkey, Tdata>::findMaxMinKey(
    std::shared_ptr<dsc::trees::KeyNode<Tkey, Tdata>> root, bool findMaximum) const
{
  if (findMaximum) {
    if (root->right) {
      return findMaxMinKey(root->right, true);
    }

    return root->key;
  }
  else {
    if (root->left) {
      return findMaxMinKey(root->left, false);
    }

    return root->key;
  }
}

template <typename Tkey, typename Tdata>
const dsc::trees::KeyNode<Tkey, Tdata>*
dsc::BinarySearchTree<Tkey, Tdata>::findNode(std::shared_ptr<dsc::trees::KeyNode<Tkey, Tdata>> root,
                                             Tkey key) const
{
  if (!root || root.get()->key == key) {
    return root.get();
  }
  else if (root.get()->key > key) {
    return findNode(root->left, key);
  }
  else {
    return findNode(root->right, key);
  }
}

template <typename Tkey, typename Tdata>
void dsc::BinarySearchTree<Tkey, Tdata>::insert(
    std::shared_ptr<dsc::trees::KeyNode<Tkey, Tdata>>& root, Tkey key, Tdata data)
{
  if (!root) {
    auto temp{std::make_shared<dsc::trees::KeyNode<Tkey, Tdata>>(dsc::trees::keyNode(key, data))};
    root = std::move(temp);
    ++m_size;
  }
  else if (key == root->key) {
    root->data = data;
  }
  else if (key < root->key) {
    insert(root->left, key, data);
  }
  else {
    insert(root->right, key, data);
  }
}

template <typename Tkey, typename Tdata>
void dsc::BinarySearchTree<Tkey, Tdata>::printTreeStructure(
    std::shared_ptr<dsc::trees::KeyNode<Tkey, Tdata>> root, int space) const
{
  if (!root)
    return;

  // Increase distance between levels
  space += 4;

  // Process right child first
  print(root->right, space);

  // Print a key of current node after space
  std::cout << std::endl;
  for (int i = 2; i < space; i++)
    std::cout << " ";
  std::cout << root.get()->key << "\n";

  // Process left child
  print(root->left, space);
}

template <typename Tkey, typename Tdata>
void dsc::BinarySearchTree<Tkey, Tdata>::remove(
    std::shared_ptr<dsc::trees::KeyNode<Tkey, Tdata>>& root, Tkey key)
{
  if (root && root->key > key) {
    return remove(root->left, key);
  }
  else if (root && root->key < key) {
    return remove(root->right, key);
  }
  else if (root && root->key == key) {
    if (!root->right) {
      root = std::move(root->left);
      --m_size;
    }
    else if (!root->left) {
      root = std::move(root->right);
      --m_size;
    }
    else {
      auto temp = root->left;
      while (temp->right)
        temp = temp->right;
      root->key  = temp->key;
      root->data = temp->data;
      remove(root->left, temp->key);
    }
  }
}