#pragma once

#include <cassert>

namespace dsc
{
  template <typename T, size_t S>
  class Array
  {
    using iterator = T*;
    using const_iterator = const T*;

  public:
    constexpr size_t size() const { return S; }
    bool empty() const {return S==0;}
    void fill(const T& value)
    {
      for(size_t index = 0; index < S; ++index) 
        m_data[index] = value;
    }
    void fill_n(const T& value, const size_t n)
    {
      if(n > S) 
        throw("n is larger than the array size");
      for(size_t index = 0; index < n; ++index) 
        m_data[index] = value;
    }

    T& operator[](const size_t index) { 
      assert(index < S);
      return m_data[index]; 
    }
    const T& operator[](const size_t index) const { 
      assert(index < S);
      return m_data[index]; 
    }

    T& at(const size_t index) {
      if(index >= S)
        throw std::out_of_range("array::at");
      return m_data[index];
    }
    const T& at(const size_t index) const {
      if(index >= S)
        throw std::out_of_range("array::at");
      return m_data[index];
    }

    T* data() { return m_data; }
    const T* data() const { return m_data; }

    T& back() { return m_data[S - 1]; }
    const T& back() const { return m_data[S - 1]; }

    T& front() { return m_data[0]; }
    const T& front() const { return m_data[0]; }

    iterator begin() { return iterator(data()); }
    const_iterator cbegin() const { return const_iterator(data()); }
    iterator end() { return iterator(data() + S); }
    const_iterator cend() const { return const_iterator(data() + S); }

  private:
    T m_data[S];
  };

} // namespace dsc