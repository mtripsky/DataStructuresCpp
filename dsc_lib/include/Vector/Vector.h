#pragma once

#include <cassert>
#include <iterator>
#include <memory>
#include <dsc/ArrayIterator.h>

namespace dsc {

template <typename T>
class Vector {
public:
  using ValueType       = T;
  using Iterator        = ArrayIterator<Vector<T>>;
  using difference_type = std::ptrdiff_t;

public:
  Vector() noexcept { _ReAlloc(2); }

  Vector(const size_t capacity) noexcept : m_size(0), m_capacity(capacity) { _ReAlloc(capacity); }

  template <typename Iter>
  Vector(Iter begin, Iter end) : m_size(0)
  {
    _ReAlloc(std::distance(begin, end));
    for (auto loop = begin; loop != end; ++loop) {
      EmplaceBack(*loop);
    }
  }

  Vector(std::initializer_list<T> const& list) noexcept : Vector(std::begin(list), std::end(list))
  {}

  ~Vector()
  {
    Clear();                                           // calls destructors of T
    ::operator delete(m_data, m_capacity * sizeof(T)); // clears vector memory
  }

  const size_t Size() const { return m_size; }
  const size_t Capacity() const { return m_capacity; }
  bool         Reserve(const size_t newCapacity) { return _ReAlloc(newCapacity); }

  bool PushBack(const T& element);
  bool PushBack(T&& element);

  template <typename... Args>
  T& EmplaceBack(Args&&... args);

  void PopBack();
  void Clear();

  T& operator[](size_t index)
  {
    assert(index < m_size);
    return m_data[index];
  }
  const T& operator[](size_t index) const
  {
    assert(index < m_size);
    return m_data[index];
  }

  Iterator Insert(Iterator it, const T& element);
  Iterator Erase(Iterator it);

  Iterator end() { return Iterator(m_data + m_size); }
  Iterator begin() { return Iterator(m_data); }

  template <typename T1>
  friend bool operator==(const Vector<T1>& v1, const Vector<T1>& v2);
  template <typename T1>
  friend bool operator!=(const Vector<T1>& v1, const Vector<T1>& v2);

private:
  bool _ReAlloc(const size_t newCapacity)
  {
    // allocates exact memory block on heap
    T* newBlock = (T*)::operator new(newCapacity * sizeof(T));

    size_t newSize = m_size > newCapacity ? newCapacity : m_size;
    for (size_t i = 0; i < newSize; ++i) {
      newBlock[i] = std::move(m_data[i]);
    }
    // calls destructors of T elements
    for (size_t i = 0; i < m_size; ++i) {
      m_data[i].~T();
    }

    // clear memory block of m_data
    ::operator delete(m_data, m_capacity * sizeof(T));

    m_data     = newBlock;
    m_capacity = newCapacity;
    m_size     = newSize;

    return true;
  }

  size_t m_size     = 0;
  size_t m_capacity = 0;
  T*     m_data     = nullptr;
};

template <typename T>
bool Vector<T>::PushBack(const T& element)
{
  if (m_size >= m_capacity) {
    _ReAlloc(m_capacity + m_capacity / 2);
  }
  m_data[m_size++] = element;

  return true;
}

template <typename T>
bool Vector<T>::PushBack(T&& element)
{
  if (m_size >= m_capacity) {
    _ReAlloc(m_capacity + m_capacity / 2);
  }
  m_data[m_size++] = std::move(element);

  return true;
}

template <typename T>
template <typename... Args>
T& Vector<T>::EmplaceBack(Args&&... args)
{
  if (m_size >= m_capacity) {
    _ReAlloc(m_capacity + m_capacity / 2);
  }

  // construct object in place to avoid move and destruction
  new (&m_data[m_size]) T(std::forward<Args>(args)...);
  // m_data[m_size] = T(std::forward<Args>(args)...);

  return m_data[m_size++];
}

template <typename T>
void Vector<T>::PopBack()
{
  if (m_size > 0) {
    --m_size;
    m_data[m_size].~T();
  }
}

template <typename T>
void Vector<T>::Clear()
{
  for (size_t i = 0; i < m_size; ++i) {
    m_data[i].~T();
  }

  m_size = 0;
}

template <typename T>
typename Vector<T>::Iterator Vector<T>::Insert(Iterator it, const T& element)
{
  const size_t dist1 = std::distance(begin(), it);
  if (m_size + 1 > m_capacity) {
    _ReAlloc(m_capacity + m_capacity / 2);

    it = begin() + dist1;
  }

  const size_t dist2      = std::distance(it, end());
  const size_t startIndex = dist1 + dist2;

  for (size_t i = startIndex; i > dist1; --i) {
    m_data[i] = std::move(m_data[i - 1]);
  }
  ++m_size;

  m_data[dist1] = element;

  return it;
}

template <typename T>
typename Vector<T>::Iterator Vector<T>::Erase(Iterator it)
{
  const size_t dist1 = std::distance(begin(), it);

  for (size_t i = dist1; i < m_size - 1; ++i) {
    m_data[i] = std::move(m_data[i + 1]);
  }
  --m_size;

  it = begin() + dist1;

  return it;
}

template <typename T1>
bool operator==(const Vector<T1>& v1, const Vector<T1>& v2)
{
  if (v1.Size() != v2.Size()) {
    return false;
  }

  for (auto i = 0; i < v1.Size(); ++i) {
    if (v1[i] != v2[i]) {
      return false;
    }
  }

  return true;
}

template <typename T1>
bool operator!=(const Vector<T1>& v1, const Vector<T1>& v2)
{
  return !(v1 == v2);
}

} // namespace dsc
