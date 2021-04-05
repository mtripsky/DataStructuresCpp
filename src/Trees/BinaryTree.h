#pragma once

#include "node.h"
#include <iostream>
#include <memory>
#include <queue>

namespace dsc {
namespace trees {

// =============================================================================
// BINARY TREE
// =============================================================================

template <typename T>
class BinaryTree {
public:
  // -------------------------------------------------------------------------
  // CONSTRUCTORS
  // -------------------------------------------------------------------------
  BinaryTree() noexcept : m_root(nullptr), m_size(0) {}

  // BinaryTree(int size) noexcept
  //     : m_size(size)
  // {
  //     m_root = std::move(createMinimalTreeFromArray(keys, 0, size - 1));
  // }

  // -------------------------------------------------------------------------
  // METHODS
  // -------------------------------------------------------------------------
  // void remove(T data)
  // {
  //     remove(m_root, data);
  // }

  void insert(T data)
  {
    // std::cout << "total depth: " << depth();
    // if(m_root)
    // {
    //     std::cout << ", depth(root): " << depth(m_root);
    //     if(m_root->left)
    //     {
    //         std::cout << ", depth(root->left): " << depth(m_root->left);
    //     }
    //     if(m_root->right)
    //     {
    //         std::cout << ", depth(root->right)" << depth(m_root->right);
    //     }
    // }
    // std::cout << std::endl;
    insert(m_root, data);
  }

  void printTreeStructure() const { printTreeStructure(m_root, 0); }

  void printInOrder() const
  {
    printInOrder(m_root);
    std::cout << std::endl;
  }

  void printBreadthFirst() const
  {
    std::queue<std::shared_ptr<Node<T>>> queue;
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
  // const Node<Tdata>* findNode(T data) const
  // {
  //     return findNode(m_root, data);
  // }

  // const Tkey findMaxKey() const
  // {
  //     if(!m_root)
  //     {
  //         throw "Tree is empty";
  //     }
  //
  //     return findMaxMinKey(m_root, true);
  // }

  // const Tkey findMinKey() const
  // {
  //     if(!m_root)
  //     {
  //         throw "Tree is empty";
  //     }
  //
  //     return findMaxMinKey(m_root, false);
  // }

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
  // std::shared_ptr<KeyNode<Tkey, Tdata>> createMinimalTreeFromArray(
  //     Tkey keys[],
  //     int left,
  //     int right);

  // const Tkey findMaxMinKey(
  //     std::shared_ptr<KeyNode<Tkey, Tdata>> root,
  //     bool findMaximum) const;

  // const KeyNode<Tkey, Tdata>* findNode(
  //     std::shared_ptr<KeyNode<Tkey, Tdata>> root,
  //     Tkey key) const;

  void insert(std::shared_ptr<Node<T>>& root, T data)
  {
    if (!root) {
      // auto temp{std::make_shared<dsc::trees::Node<T>>(node(data))};
      // root = std::move(temp);
      root = std::make_shared<dsc::trees::Node<T>>(node(data));
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

  const int depth(std::shared_ptr<Node<T>> root) const
  {
    if (!root)
      return 0;

    return max(depth(root->left), depth(root->right)) + 1;
  }

  const int max(const int x, const int y) const { return x >= y ? x : y; }

  void printTreeStructure(std::shared_ptr<Node<T>> root, int space) const
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

  void printInOrder(std::shared_ptr<Node<T>> root) const
  {
    if (!root)
      return;

    printInOrder(root->left);
    std::cout << root->data << ", ";
    printInOrder(root->right);
  }

  //
  // void remove(
  //     std::shared_ptr<Node<T>>& root,
  //     T data);

  // -------------------------------------------------------------------------
  // DATA
  // -------------------------------------------------------------------------
  std::shared_ptr<Node<T>>             m_root;
  std::size_t                          m_size;
  std::queue<std::shared_ptr<Node<T>>> m_queue;
};

} // namespace trees
} // namespace dsc
