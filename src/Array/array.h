#pragma once

#include <cassert>
#include "../Iterators/ArrayIterator.h"

namespace dsc {

template <typename T, size_t S>
class Array {
public:
  using ValueType = T;
  using Iterator = ArrayIterator<Array<T, S>>;

public:
  constexpr size_t Size() const { return S; }
  bool Empty() const { return S == 0; }
  void Fill(const T& value);
  void Fill_n(const T& value, const size_t n);

  T& operator[](const size_t index) {
    assert(index < S);
    return m_data[index];
  }

  const T& operator[](const size_t index) const {
    assert(index < S);
    return m_data[index];
  }

  T& At(const size_t index);
  const T& At(const size_t index) const;

  T* Data() { return m_data; }
  const T* Data() const { return m_data; }

  T& Back() { return m_data[S - 1]; }
  const T& Back() const { return m_data[S - 1]; }
  T& Front() { return m_data[0]; }
  const T& Front() const { return m_data[0]; }

  Iterator begin() { return Iterator(m_data); }
  // const_iterator cbegin() const { return const_iterator(Data()); }
  Iterator end() { return Iterator(m_data + S); }
  //const_iterator cend() const { return const_iterator(Data() + S); }

private:
  T m_data[S];
};

template <typename T, size_t S>
inline void Array<T, S>::Fill(const T& value) {
  for (size_t index = 0; index < S; ++index)
    m_data[index] = value;
}

template <typename T, size_t S>
inline void Array<T, S>::Fill_n(const T& value, const size_t n) {
  if (n > S)
    throw("n is larger than the array size");
  for (size_t index = 0; index < n; ++index)
    m_data[index] = value;
}

template <typename T, size_t S>
inline T& Array<T, S>::At(const size_t index) {
  if (index >= S)
    throw std::out_of_range("array::at");
  return m_data[index];
}

template <typename T, size_t S>
inline const T& Array<T, S>::At(const size_t index) const {
  if (index >= S)
    throw std::out_of_range("array::at");
  return m_data[index];
}
} // namespace dsc