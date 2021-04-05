#pragma once

#include "../node.h"
#include <iostream>
#include <memory>

namespace dsc {
namespace trees {
namespace bst {

// =============================================================================
// BINARY SEARCH TREE
// =============================================================================

template <typename Tkey, typename Tdata>
class BST {
public:
  // -------------------------------------------------------------------------
  // CONSTRUCTORS
  // -------------------------------------------------------------------------
  BST() noexcept : m_root(nullptr), m_size(0) {}

  BST(Tkey keys[], int size) noexcept : m_size(size)
  {
    m_root = std::move(createMinimalTreeFromArray(keys, 0, size - 1));
  }

  // -------------------------------------------------------------------------
  // METHODS
  // -------------------------------------------------------------------------
  void remove(Tkey key) { remove(m_root, key); }

  void insert(Tkey key, Tdata data) { insert(m_root, key, data); }

  void printTreeStructure() const { printTreeStructure(m_root, 0); }

  void printInOrder() const
  {
    printInOrder(m_root);
    std::cout << std::endl;
  }

  const KeyNode<Tkey, Tdata>* findNode(Tkey key) const { return findNode(m_root, key); }

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
  // -------------------------------------------------------------------------
  // AUXILARY METHODS
  // -------------------------------------------------------------------------
  std::shared_ptr<KeyNode<Tkey, Tdata>> createMinimalTreeFromArray(Tkey keys[], int left,
                                                                   int right);

  const Tkey findMaxMinKey(std::shared_ptr<KeyNode<Tkey, Tdata>> root, bool findMaximum) const;

  const KeyNode<Tkey, Tdata>* findNode(std::shared_ptr<KeyNode<Tkey, Tdata>> root, Tkey key) const;

  void insert(std::shared_ptr<KeyNode<Tkey, Tdata>>& root, Tkey key, Tdata data);

  const int depth(std::shared_ptr<KeyNode<Tkey, Tdata>> root) const
  {
    if (!root)
      return 0;

    return max(depth(root->left), depth(root->right)) + 1;
  }

  const int max(const int x, const int y) const { return x >= y ? x : y; }

  void printTreeStructure(std::shared_ptr<KeyNode<Tkey, Tdata>> root, int space) const;

  void printInOrder(std::shared_ptr<KeyNode<Tkey, Tdata>> root) const
  {
    if (!root)
      return;

    printInOrder(root->left);
    std::cout << root->key << ", ";
    printInOrder(root->right);
  }

  void remove(std::shared_ptr<KeyNode<Tkey, Tdata>>& root, Tkey key);

  // -------------------------------------------------------------------------
  // DATA
  // -------------------------------------------------------------------------
  std::shared_ptr<KeyNode<Tkey, Tdata>> m_root;
  std::size_t                           m_size;
};

} // namespace bst
} // namespace trees
} // namespace dsc
