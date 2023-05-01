#include "catch.hpp"
#include <dsc/Vector.h>
#include <algorithm>
#include <iostream>
#include <stdio.h>

namespace dsc::tests::vector {

struct TestObject {
  TestObject() : X(0), Y(0) { m_data = new int[5]; }
  TestObject(int scalar) : X(scalar), Y(scalar) { m_data = new int[5]; }
  TestObject(int x, int y) : X(x), Y(y) { m_data = new int[5]; }
  TestObject(const TestObject& other) = delete;
  TestObject(TestObject&& other) : X(other.X), Y(other.Y)
  {
    std::cout << "TestObject Move Constructor" << std::endl;

    m_data       = other.m_data;
    other.m_data = nullptr;
  }
  TestObject& operator=(const TestObject& other)
  {
    // std::cout << "TestObject Copy assign" << std::endl;

    X      = other.X;
    Y      = other.Y;
    m_data = new int[5];
    for (size_t i = 0; i < 5; ++i)
      m_data[i] = other.m_data[i];

    return *this;
  }
  TestObject& operator=(TestObject&& other)
  {
    // std::cout << "TestObject Move assign" << std::endl;
    X            = other.X;
    Y            = other.Y;
    m_data       = other.m_data;
    other.m_data = nullptr;

    return *this;
  }
  ~TestObject()
  {
    delete[] m_data;
    // std::cout << "TestObject Destroyed" << std::endl;
  }

  int  X;
  int  Y;
  int* m_data = nullptr;
};

SCENARIO("testing vector container for TestObject")
{
  GIVEN("vector with default constructor")
  {
    Vector<TestObject> sut;

    THEN("size should be 0 and capacity 2")
    {
      CHECK(sut.Size() == 0);
      CHECK(sut.Capacity() == 2);
    }
  }

  GIVEN("vector with default constructor and push 3x lvalues")
  {
    Vector<TestObject> sut;
    TestObject         t1;
    TestObject         t2{1};
    TestObject         t3{2, 3};

    sut.PushBack(t1);
    sut.PushBack(t2);
    sut.PushBack(t3);
    
    THEN("size should be 0 and capacity 2")
    {
      CHECK(sut.Size() == 3);
      CHECK(sut.Capacity() == 3);
      CHECK(sut[1].X == 1);
    }
  }

  GIVEN("vector with default constructor and push 3x rvalues")
  {
    Vector<TestObject> sut;

    sut.PushBack(TestObject());
    sut.PushBack(TestObject(2));
    sut.PushBack(TestObject(1, 2));

    THEN("size should be 0 and capacity 2")
    {
      CHECK(sut.Size() == 3);
      CHECK(sut.Capacity() == 3);
    }
  }

  GIVEN("vector with default constructor and Emplace 3 elements")
  {
    Vector<TestObject> sut;
    sut.EmplaceBack();
    sut.EmplaceBack(2);
    sut.EmplaceBack(1, 2);

    THEN("size should be 3 and capacity 3")
    {
      CHECK(sut.Size() == 3);
      CHECK(sut.Capacity() == 3);
    }
  }

  GIVEN("vector with default constructor and Emplace 3 elements and then PopBack")
  {
    Vector<TestObject> sut;
    sut.EmplaceBack();
    sut.EmplaceBack(2);
    sut.EmplaceBack(1, 2);
    sut.PopBack();

    THEN("size should be 2 and capacity 3")
    {
      CHECK(sut.Size() == 2);
      CHECK(sut.Capacity() == 3);
    }
  }
}

SCENARIO("testing vector container for int")
{
  GIVEN("default vector constructor")
  {
    Vector<int> sut;

    THEN("size should be 0 and capacity 2")
    {
      CHECK(sut.Size() == 0);
      CHECK(sut.Capacity() == 2);
    }
  }

  GIVEN("initialize vector using initialize list")
  {
    auto sut = Vector<int>{1, 2, 3, 4};

    THEN("size should be 4 and capacity 4")
    {
      CHECK(sut.Size() == 4);
      CHECK(sut.Capacity() == 4);

      AND_THEN("elements should be in range 1...4")
      {
        for (size_t i = 0; i < sut.Size(); ++i) {
          REQUIRE(sut[i] == i + 1);
        }
      }
    }
  }

  GIVEN("vector of int push 3 times and then reserve capacity 2")
  {
    auto sut = Vector<int>();
    sut.PushBack(1);
    sut.PushBack(2);
    sut.PushBack(3);

    sut.Reserve(2);

    THEN("size should be 2 and capacity 2")
    {
      CHECK(sut.Size() == 2);
      CHECK(sut.Capacity() == 2);

      AND_THEN("first should be 1 and last 2")
      {
        REQUIRE(sut[0] == 1);
        REQUIRE(sut[1] == 2);
      }
    }
  }

  GIVEN("vector of int reserve capacity 4 and push 4 times")
  {
    auto sut = Vector<int>();
    sut.Reserve(4);

    sut.PushBack(1);
    sut.PushBack(2);
    sut.PushBack(3);
    sut.PushBack(4);

    THEN("size should be 4 and capacity 4")
    {
      CHECK(sut.Size() == 4);
      CHECK(sut.Capacity() == 4);

      AND_THEN("first should be 1 and last 2")
      {
        for (size_t i = 0; i < sut.Size(); ++i)
          REQUIRE(sut[i] == i + 1);
      }
    }
  }

  GIVEN("vector of int constructed with capacity 4")
  {
    auto sut = Vector<int>(4);

    sut.PushBack(1);
    sut.PushBack(2);
    sut.PushBack(3);
    sut.PushBack(4);

    THEN("size should be 4 and capacity 4")
    {
      CHECK(sut.Size() == 4);
      CHECK(sut.Capacity() == 4);

      AND_THEN("first should be 1 and last 2")
      {
        for (size_t i = 0; i < sut.Size(); ++i)
          REQUIRE(sut[i] == i + 1);
      }
    }

    THEN("range for loop should give all elements")
    {
      int counter = 1;
      for (const auto& el : sut) {
        REQUIRE(el == counter);
        ++counter;
      }
      std::cout << "\n";
    }

    THEN("looping using iterators should give all elements")
    {
      int counter = 1;
      for (auto it = sut.begin(); it != sut.end(); ++it) {
        REQUIRE(*it == counter);
        ++counter;
      }
      std::cout << "\n";
    }
  }

  GIVEN("vector initialized with 4 elements: (1,2,3,4)")
  {
    auto sut = Vector<int>{1, 2, 3, 4};

    THEN("insert 5 at position 0 should increase vector size to 5 and add element 5 at position 0")
    {
      const size_t shift = 0;
      auto         pos   = sut.begin() + shift;
      auto         it    = sut.Insert(pos, 5);

      REQUIRE(sut.Size() == 5);
      REQUIRE(*it == 5);
      REQUIRE(sut[shift] == 5);
      for (size_t i = 0; i < sut.Size(); ++i) {
        if (i == shift) {
          REQUIRE(sut[i] == 5);
        }
        else if (i < shift) {
          REQUIRE(sut[i] == i + 1);
        }
        else {
          REQUIRE(sut[i] == i);
        }
      }
    }

    THEN("insert 5 at position 1 should increase vector size to 5 and add element 5 at position 1")
    {
      const size_t shift = 1;
      auto         pos   = sut.begin() + shift;
      auto         it    = sut.Insert(pos, 5);

      REQUIRE(sut.Size() == 5);
      REQUIRE(*it == 5);
      REQUIRE(sut[shift] == 5);
      for (size_t i = 0; i < sut.Size(); ++i) {
        if (i == shift) {
          REQUIRE(sut[i] == 5);
        }
        else if (i < shift) {
          REQUIRE(sut[i] == i + 1);
        }
        else {
          REQUIRE(sut[i] == i);
        }
      }
    }

    THEN("insert 5 at position 2 should increase vector size to 5 and add element 5 at position 2")
    {
      const size_t shift = 2;
      auto         pos   = sut.begin() + shift;
      auto         it    = sut.Insert(pos, 5);

      REQUIRE(sut.Size() == 5);
      REQUIRE(*it == 5);
      REQUIRE(sut[shift] == 5);
      for (size_t i = 0; i < sut.Size(); ++i) {
        if (i == shift) {
          REQUIRE(sut[i] == 5);
        }
        else if (i < shift) {
          REQUIRE(sut[i] == i + 1);
        }
        else {
          REQUIRE(sut[i] == i);
        }
      }
    }

    THEN("insert 5 at position 3 should increase vector size to 5 and add element 5 at position 3")
    {
      const size_t shift = 3;
      auto         pos   = sut.begin() + shift;
      auto         it    = sut.Insert(pos, 5);

      REQUIRE(sut.Size() == 5);
      REQUIRE(*it == 5);
      REQUIRE(sut[shift] == 5);
      for (size_t i = 0; i < sut.Size(); ++i) {
        if (i == shift) {
          REQUIRE(sut[i] == 5);
        }
        else if (i < shift) {
          REQUIRE(sut[i] == i + 1);
        }
        else {
          REQUIRE(sut[i] == i);
        }
      }
    }

    THEN("insert 5 at position 4 should increase vector size to 5 and add element 5 at position 4")
    {
      const size_t shift = 4;
      auto         pos   = sut.begin() + shift;
      auto         it    = sut.Insert(pos, 5);

      REQUIRE(sut.Size() == 5);
      REQUIRE(*it == 5);
      REQUIRE(sut[shift] == 5);
      for (size_t i = 0; i < sut.Size(); ++i) {
        if (i == shift) {
          REQUIRE(sut[i] == 5);
        }
        else if (i < shift) {
          REQUIRE(sut[i] == i + 1);
        }
        else {
          REQUIRE(sut[i] == i);
        }
      }
    }

    THEN("insert 5 at end() should increase vector size to 5 and add element 5 at position 4")
    {
      auto         pos   = sut.end();
      const size_t shift = 4;
      auto         it    = sut.Insert(pos, 5);

      REQUIRE(sut.Size() == 5);
      REQUIRE(*it == 5);
      REQUIRE(sut[shift] == 5);
      for (size_t i = 0; i < sut.Size(); ++i) {
        if (i == shift) {
          REQUIRE(sut[i] == 5);
        }
        else if (i < shift) {
          REQUIRE(sut[i] == i + 1);
        }
        else {
          REQUIRE(sut[i] == i);
        }
      }
    }
  }

  GIVEN("vector initialized with 3 elements: (1,2,3)")
  {
    auto sut = Vector<int>{1, 2, 3};

    THEN("erase at position 0 should decrease vector size to 2 and remove element at position 0")
    {
      auto pos = sut.begin() + 0;
      auto it  = sut.Erase(pos);

      REQUIRE(sut.Size() == 2);
      REQUIRE(*it == 2);
      REQUIRE(sut[0] == 2);
      REQUIRE(sut[1] == 3);
    }

    THEN("erase at position 1 should decrease vector size to 2 and remove element at position 1")
    {
      auto pos = sut.begin() + 1;
      auto it  = sut.Erase(pos);

      REQUIRE(sut.Size() == 2);
      REQUIRE(*it == 3);
      REQUIRE(sut[0] == 1);
      REQUIRE(sut[1] == 3);
    }

    THEN("erase at position 2 should decrease vector size to 2 and remove element at position 2")
    {
      auto pos = sut.begin() + 2;
      auto it  = sut.Erase(pos);

      REQUIRE(sut.Size() == 2);
      REQUIRE(it == sut.end());
      REQUIRE(sut[0] == 1);
      REQUIRE(sut[1] == 2);
    }
  }

  //
  //   GIVEN("vector of int constructing with size (3) and 1 as element as
  //   argument")
  //   {
  //     auto sut = Vector<int>(3, 1);
  //
  //     THEN("size should be 3 and capacity 3")
  //     {
  //       CHECK(sut.Size() == 3);
  //       CHECK(sut.Capacity() == 3);
  //
  //       // AND_THEN("every element should be equal to one")
  //       // {
  //       //   for(auto i = 0; i < sut.size(); ++i)
  //       //   {
  //       //     REQUIRE(sut[i] == 1);
  //       //   }
  //       // }
  //     }
  //   }
  // }
  //
  // 		// WHEN("push 1, 2, 3, 4")
  // 		// {
  //     //   sut.push_back(1);
  //     //   sut.push_back(2);
  //     //   sut.push_back(3);
  //     //   sut.push_back(4);
  //
  // 		// 	THEN("size should be 4 and all data should be 1, 2, 3,
  // 4")
  // 		// 	{
  // 		// 		REQUIRE(sut.size()  == 4);
  //     //     REQUIRE(sut.front() == 1);
  //     //     REQUIRE(sut.back()  == 4);
  //     //     for(size_t i = 0; i < sut.size(); ++i)
  //     //       std::cout << "Vector[" << i << "] = " << sut[i] << std::endl;
  // 		// 	}
  //     // }
  // //   }
}

SCENARIO("testing comparison operators for Vector")
{
  GIVEN("vector v1 containing 1, 2, 3")
  {
    auto sut1 = Vector<int>{1, 2, 3};

    WHEN("comparing to empty vector v2")
    {
      auto sut2 = Vector<int>();

      THEN("vectors should not be equal") { REQUIRE(sut1 != sut2); }
    }

    WHEN("comparing to vector with same size but different elements")
    {
      auto sut2 = Vector<int>{1, 1, 1};

      THEN("vectors should not be equal") { REQUIRE(sut1 != sut2); }
    }

    WHEN("comparing to vector with same size and same elements")
    {
      auto sut2 = Vector<int>{1, 2, 3};

      THEN("vectors should be equal") { REQUIRE(sut1 == sut2); }
    }
  }
}

} // namespace dsc::tests
