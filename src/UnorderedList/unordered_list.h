#ifndef Unordered_List_Unordered_List_h
#define Unordered_List_Unordered_List_h

#include <iostream>
#include <memory>
#include "node.h"

namespace dsc{
namespace lists {

template <typename T>
class UnorderedList
{
public:
    // -------------------------------------------------------------------------
    // CONSTRUCTORS
    // -------------------------------------------------------------------------
    UnorderedList() noexcept : m_head(nullptr), m_tail(nullptr), m_size(0)
    {
    }

    // -------------------------------------------------------------------------
    // METHODS
    // -------------------------------------------------------------------------
    bool push(const T& data);
    bool pop();
    bool remove(const T& data);
    const Node<T>* back() const;
    const Node<T>* front() const;
    void print() const;

    size_t& size()
    {
        return m_size;
    }

    const bool isEmpty() const
    {
        return m_head == nullptr;
    }

private:
    // -------------------------------------------------------------------------
    // DATA
    // -------------------------------------------------------------------------
    std::shared_ptr<Node<T>> m_head;
    std::shared_ptr<Node<T>> m_tail;
    std::size_t m_size;
};

}  // namespace lists
}  // namespace dsc

#include "unordered_list.cpp"

#endif  // Unordered_List_Unordered_List_h
