#ifndef Trees_Bst_BST_h
#define Trees_Bst_BST_h

#include <iostream>
#include <memory>
#include "node.h"


namespace dsc {
namespace trees {
namespace bst {

// =============================================================================
// BINARY SEARCH TREE
// =============================================================================

template<typename Tkey, typename Tdata>
class BST{
public:
    // -------------------------------------------------------------------------
	// CONSTRUCTORS
	// -------------------------------------------------------------------------
    BST() noexcept
        : m_root(nullptr)
        , m_size(0)
    {
    }

    // -------------------------------------------------------------------------
	// METHODS
	// -------------------------------------------------------------------------
    void remove(Tkey key)
    {
        remove(m_root, key);
    }

    void insert(Tkey key, Tdata data)
    {
        insert(m_root, key, data);
    }

    void print() const
    {
        print(m_root, 0);
    }

    const dsc::trees::bst::Node<Tkey, Tdata>* findNode(Tkey key) const
    {
        return findNode(m_root, key);
    }

    const Tkey findMaxKey() const
    {
        if(!m_root)
        {
            throw "Tree is empty";
        }

        return findMaxMinKey(m_root, true);
    }

    const Tkey findMinKey() const
    {
        if(!m_root)
        {
            throw "Tree is empty";
        }

        return findMaxMinKey(m_root, false);
    }

    const std::size_t size() const
    {
        return m_size;
    }

private:
    // -------------------------------------------------------------------------
	// AUXILARY METHODS
	// -------------------------------------------------------------------------
    const Tkey findMaxMinKey(
        std::shared_ptr<Node<Tkey, Tdata>> root,
        bool findMaximum) const;

    const Node<Tkey, Tdata>* findNode(
        std::shared_ptr<Node<Tkey, Tdata>> root,
        Tkey key) const;

    void insert(
        std::shared_ptr<Node<Tkey, Tdata>>& root,
        Tkey key,
        Tdata data);

    void print(
        std::shared_ptr<Node<Tkey, Tdata>> root,
         int space) const;

    void remove(
        std::shared_ptr<Node<Tkey, Tdata>>& root,
        Tkey key);

    // -------------------------------------------------------------------------
	// DATA
	// -------------------------------------------------------------------------
    std::shared_ptr<Node<Tkey, Tdata>> m_root;
    std::size_t m_size;
};

}  // namespace bst
}  // namespace trees
}  // namespace dsc

#endif  // Trees_Bst_BST_h
