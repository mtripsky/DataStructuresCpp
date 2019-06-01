#ifndef Heap_Heap_h
#define Heap_Heap_h

#include <iostream>


namespace dsc {
namespace heap {

template <typename T>
class Heap {
public:
    // -------------------------------------------------------------------------
    // CONSTRUCTORS
    // -------------------------------------------------------------------------
    Heap(std::size_t maxSize) noexcept : m_size(0), m_maxSize(maxSize)
    {
        m_heap = new T[maxSize + 1];
    }

    // -------------------------------------------------------------------------
    // DESTRUCTORS
    // -------------------------------------------------------------------------
    ~Heap()
    {
        delete[] m_heap;
    }

    // -------------------------------------------------------------------------
    // METHODS
    // -------------------------------------------------------------------------
    bool push(const T& elem)
    {
        if(isFull())
            return false;

        ++updateSize();
        m_heap[size()] = elem;
        moveElementUp();

        return true;
    }

    template <typename Iterator>
    bool push(Iterator start, Iterator end)
    {
        for (Iterator it = start; it != end; ++it)
        {
            push(*it);
        }

        return true;
    }

    bool pop()
    {
        if(isEmpty())
            return false;

        m_heap[1] = m_heap[size()];
        --updateSize();
        moveElementDown();

        return true;
    }

    const T& top()
    {
        return m_heap[1];
    }

    const size_t size() const
    {
        return m_size;
    }

    void print()
    {
        for( auto i=1; i<= size(); ++i)
        {
            std::cout << m_heap[i] << " ";
        }
        std::cout << std::endl;
    }

private:
    // -------------------------------------------------------------------------
    // AUXILARY METHODS
    // -------------------------------------------------------------------------
    size_t& updateSize()
    {
        return m_size;
    }

    const bool isFull() const
    {
        return m_size == m_maxSize;
    }

    const bool isEmpty() const
    {
        return m_size == 0;
    }

    bool moveElementUp()
    {
        auto temp = m_heap[size()];
        auto index = size();

        if(index == 1)
            return true;

        while( index != 1 && m_heap[index/2] < temp)
        {
            m_heap[index] = m_heap[index/2];
            index /= 2;
        }
        m_heap[index] = temp;

        return true;
    }

    bool moveElementDown()
    {
        auto index = 1;
        while(true)
        {
            auto child = 2*index;
            if(child > size())
                break;
            if(child+1 <= size() && m_heap[child] < m_heap[child+1])
                ++child;
            if(m_heap[index] > m_heap[child])
                break;
            std::swap(m_heap[index], m_heap[child]);
            index = child;
        }

        return true;
    }

    // -------------------------------------------------------------------------
    // DATA
    // -------------------------------------------------------------------------
    T *m_heap;
    std::size_t m_size;
    std::size_t m_maxSize;
};

}  // namespace heap
}  // namespace dsc

#endif  // Heap_Heap_h
