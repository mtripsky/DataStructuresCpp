#include "catch.hpp"
#include "Stack/DynamicStack.h"
#include <stdio.h>
#include <iostream>

namespace dsc::tests {

struct TestObject {
  TestObject() : X(0)
  {
    std::cout << "TestObject Constructor (1)" << std::endl;
    m_data = new int[5];
  }
  TestObject(int scalar) : X(scalar)
  {
    std::cout << "TestObject Constructor (2)" << std::endl;
    m_data = new int[5];
  }
  TestObject(const TestObject& other)
  {
    std::cout << "TestObject Copy Constructor" << std::endl;
    m_data = new int[5];
    X      = other.X;

    for (size_t i = 0; i < 5; ++i)
      m_data[i] = other.m_data[i];
  }
  TestObject(TestObject&& other) : X(other.X)
  {
    std::cout << "TestObject Move Constructor" << std::endl;
    m_data       = other.m_data;
    other.m_data = nullptr;
  }
  TestObject& operator=(const TestObject& other)
  {
    std::cout << "TestObject Copy assign" << std::endl;

    X      = other.X;
    m_data = new int[5];
    for (size_t i = 0; i < 5; ++i)
      m_data[i] = other.m_data[i];

    return *this;
  }
  TestObject& operator=(TestObject&& other)
  {
    std::cout << "TestObject Move assign" << std::endl;
    X            = other.X;
    m_data       = other.m_data;
    other.m_data = nullptr;

    return *this;
  }
  ~TestObject()
  {
    std::cout << "Address of array" << m_data << ", size: " << sizeof(m_data) << std::endl;
    delete[] m_data;
    std::cout << "TestObject Destroyed" << std::endl;
  }

  friend std::ostream& operator<<(std::ostream& out, const TestObject& t)
  {
    return out << t.X << "\n";
  }

  int  X;
  int* m_data = nullptr;
};

// SCENARIO("testing Dynamic Stack push and pop on int as data")
// {
//   GIVEN("dynamic stack")
//   {
//     auto sut = DynamicStack<int>();

//     WHEN("push twice")
//     {
//       sut.Push(1);
//       sut.Push(2);

//       THEN("top element should be 2") { REQUIRE(sut.Top() == 2); }
//       THEN("top element should be 1 after one pop")
//       {
//         sut.Pop();
//         REQUIRE(sut.Top() == 1);
//       }
//     }
//   }
// }

SCENARIO("testing Dynamic Stack push and pop on TestObject as data")
{
  GIVEN("dynamic stack")
  {
    auto sut = DynamicStack<TestObject>();

    WHEN("push twice")
    {
      //sut.Push(TestObject());
      // to test whether they are moved from stack memory to heap
      {
        TestObject t1;
        TestObject t2(2);
        
        //sut.Push(std::move(TestObject()));
        sut.Push(t1);
        sut.Push(t2);

        // sut.Push(std::move(t2));
      }
      THEN("top element should be t2 with 2 as X") { REQUIRE(sut.Top().X == 2); }
      THEN("after pop it should return t2 with X = 2 and top should be t1 with X=0") { 
        const auto t = sut.Pop();
        REQUIRE(t.X == 2); 
        REQUIRE(sut.Top().X == 0); 
      }
      // sut.Pop();
      // THEN("top element should be t2 with 2 as X") { REQUIRE(sut.Top().X == 2); }
      // THEN("top element should be t1 with 0 as X after one pop")
      // {
      //   sut.Pop();

      //     REQUIRE(sut.Top().X == 0);
      //   sut.Pop();
      // }
    }
  }
}

} // namespace dsc::tests
