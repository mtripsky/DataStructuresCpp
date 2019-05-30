#ifndef Queue_Queue_h
#define Queue_Queue_h

#include <iostream>


namespace dsc {
namespace fifo {

template <typename T>
class Queue {
public:
    // -------------------------------------------------------------------------
    // CONSTRUCTORS
    // -------------------------------------------------------------------------
    Queue(std::size_t maxSize) noexcept : m_maxSize(maxSize), m_size(0), m_front(0), m_rear(0)
    {
        m_queue = new T[maxSize + 1];
    }

    // -------------------------------------------------------------------------
    // DESTRUCTORS
    // -------------------------------------------------------------------------
    ~Queue()
    {
        delete[] m_queue;
    }

    // -------------------------------------------------------------------------
    // METHODS
    // -------------------------------------------------------------------------
    bool enqueue(const T& elem)
    {
        if(isFull())
            return false;

        if(m_rear + 1 > m_maxSize)
        {
            m_rear = 0;
            m_queue[m_rear] = elem;
        }
        else
        {
            m_queue[m_rear] = elem;
        }
        ++m_rear;
        ++updateSize();

        return true;
    }

    bool dequeue()
    {
        if(isEmpty())
        {
            return false;
        }
        --updateSize();
        m_front = m_front + 1 > m_maxSize - 1 ? 0 : ++m_front;

        return true;
    }

    const T& front() const
    {
        if(isEmpty())
        {
            throw "Queue is empty";
        }

        return m_queue[m_front];
    }

    const bool isEmpty() const
    {
        return size() == 0;
    }

    bool isFull()
    {
        return size() == m_maxSize;
    }

    const size_t size() const
    {
        return m_size;
    }

    void print()
    {
        if(isEmpty())
            std::cout << "Queue is empty\n";
        else
        {
            auto index = m_front;

            for(auto i = 0; i < size(); ++i)
            {
                index = index + 1 > m_maxSize ? 0 : index;
                std::cout << m_queue[index] << "->";
                ++index;
            }
            std::cout << std::endl;
        }
    }

private:
    // -------------------------------------------------------------------------
    // AUXILARY METHODS
    // -------------------------------------------------------------------------
    size_t& updateSize()
    {
        return m_size;
    }

    // -------------------------------------------------------------------------
    // DATA
    // -------------------------------------------------------------------------
    std::size_t m_maxSize;
    std::size_t m_size;
    int m_front;
    int m_rear;
    T *m_queue;
};

}  // namespace fifo
}  // namespace dsc

#endif  // Queue_Queue_h
