#include "bst.h"
#include "../node.h"

template <typename Tkey, typename Tdata>
std::shared_ptr<dsc::trees::KeyNode<Tkey, Tdata>>
dsc::trees::bst::BST<Tkey, Tdata>::createMinimalTreeFromArray(Tkey keys[], int left, int right)
{
  if (left > right)
    return nullptr;

  int  mid = (left + right) / 2;
  auto result{std::make_shared<dsc::trees::KeyNode<Tkey, Tdata>>(keyNode(keys[mid], keys[mid]))};
  result->left  = std::move(createMinimalTreeFromArray(keys, left, mid - 1));
  result->right = std::move(createMinimalTreeFromArray(keys, mid + 1, right));

  return result;
}

template <typename Tkey, typename Tdata>
const Tkey dsc::trees::bst::BST<Tkey, Tdata>::findMaxMinKey(
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
dsc::trees::bst::BST<Tkey, Tdata>::findNode(std::shared_ptr<dsc::trees::KeyNode<Tkey, Tdata>> root,
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
void dsc::trees::bst::BST<Tkey, Tdata>::insert(
    std::shared_ptr<dsc::trees::KeyNode<Tkey, Tdata>>& root, Tkey key, Tdata data)
{
  if (!root) {
    auto temp{std::make_shared<dsc::trees::KeyNode<Tkey, Tdata>>(keyNode(key, data))};
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
void dsc::trees::bst::BST<Tkey, Tdata>::printTreeStructure(
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
void dsc::trees::bst::BST<Tkey, Tdata>::remove(
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
