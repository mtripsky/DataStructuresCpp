#pragma once

namespace dsc {

template <typename Array>
class ArrayIterator {
public:
  using iterator_category = std::forward_iterator_tag;
  using difference_type   = std::ptrdiff_t;
  using value_type        = typename Array::ValueType;
  using pointer           = value_type*;
  using reference         = value_type&;

public:
  ArrayIterator(pointer ptr) : m_ptr(ptr) {}
  ArrayIterator(const ArrayIterator& other) : m_ptr(other.m_ptr) {}
  ArrayIterator& operator=(const ArrayIterator& other)
  {
    m_ptr = other.m_ptr;
    return *this;
  }
  ArrayIterator& operator++()
  {
    m_ptr++;
    return *this;
  }
  ArrayIterator operator++(int)
  {
    ArrayIterator it = *this;
    ++(*this);
    return it;
  }
  ArrayIterator& operator--()
  {
    m_ptr--;
    return *this;
  }
  ArrayIterator operator--(int)
  {
    ArrayIterator it = *this;
    --(*this);
    return it;
  }
  ArrayIterator operator+(int offset) const
  {
    ArrayIterator it(*this);
    it += offset;
    return it;
  }
  ArrayIterator operator-(int offset) const
  {
    ArrayIterator it(*this);
    it -= offset;
    return it;
  }
  ArrayIterator& operator+=(int offset)
  {
    m_ptr += offset;
    return *this;
  }
  ArrayIterator& operator-=(int offset)
  {
    m_ptr -= offset;
    return *this;
  }

  difference_type operator-(const ArrayIterator& other) const { return m_ptr - other.m_ptr; }
  reference       operator[](int index) { return *(m_ptr + index); }
  pointer         operator->() { return m_ptr; }
  reference       operator*() { return *m_ptr; }

  bool operator<(const ArrayIterator& other) const { return m_ptr < other.m_ptr; }
  bool operator<=(const ArrayIterator& other) const { return m_ptr <= other.m_ptr; }
  bool operator>(const ArrayIterator& other) const { return m_ptr > other.m_ptr; }
  bool operator>=(const ArrayIterator& other) const { return m_ptr >= other.m_ptr; }
  bool operator==(const ArrayIterator& other) const { return m_ptr == other.m_ptr; }
  bool operator!=(const ArrayIterator& other) const { return m_ptr != other.m_ptr; }

private:
  pointer m_ptr;
};

} // namespace dsc