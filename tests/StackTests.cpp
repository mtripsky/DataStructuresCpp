#include "catch.hpp"
#include "Stack/Stack.h"
#include "Vector/Vector.h"
#include <stdio.h>

namespace dsc::tests {

SCENARIO("testing Stack constructor with int as data")
{
  GIVEN("constructing  stack of maxSize 2")
  {
    auto sut = Stack<int>(2);

    WHEN("do nothing")
    {
      THEN("size should be 0") { REQUIRE(sut.size() == 0); }
    }
  }
}

SCENARIO("testing Stack push with int as data")
{
  GIVEN("constructing stack of size 2")
  {
    auto sut = Stack<int>(2);

    WHEN("push 1")
    {
      auto result1 = sut.push(1);

      auto vec = Vector<int>{1, 2, 3};
      auto it  = vec.begin();

      THEN("size should be 1, is not full and top element should be 1")
      {
        REQUIRE(sut.size() == 1);
        REQUIRE(sut.top() == 1);
        REQUIRE_FALSE(sut.isFull());
        REQUIRE(result1);
      }
    }

    WHEN("push 1 and then 2")
    {
      auto result1 = sut.push(1);
      auto result2 = sut.push(2);

      THEN("size should be 2, is full, and top element should be 2")
      {
        REQUIRE(sut.size() == 2);
        REQUIRE(sut.top() == 2);
        REQUIRE(sut.isFull());
        REQUIRE(result1);
        REQUIRE(result2);
      }
    }

    WHEN("push 1, 2 and then 3")
    {
      auto result1 = sut.push(1);
      auto result2 = sut.push(2);
      auto result3 = sut.push(3);

      THEN("size should be 2 and top element should be 2 and last push should be false and "
           "stack should be full")
      {
        REQUIRE(sut.size() == 2);
        REQUIRE(sut.top() == 2);
        REQUIRE(result1);
        REQUIRE(result2);
        REQUIRE_FALSE(result3);
        REQUIRE(sut.isFull());
      }
    }
  }
}

SCENARIO("testing Stack pop with int as data")
{
  GIVEN("constructing stack of size 2")
  {
    auto sut = Stack<int>(2);

    WHEN("pop from empty queue")
    {
      auto result1 = sut.pop();

      THEN("pop methods should return false size should be 0")
      {
        REQUIRE(sut.size() == 0);
        REQUIRE_FALSE(result1);
      }
    }

    WHEN("pop from queue containing 1 and 2 (in order)")
    {
      sut.push(1);
      sut.push(2);
      auto result1 = sut.pop();

      THEN("size should be 1 and top element should be 1")
      {
        REQUIRE(sut.size() == 1);
        REQUIRE(sut.top() == 1);
        REQUIRE(result1);
      }
    }

    WHEN("pop three times from queue containing 1 and 2 (in order)")
    {
      sut.push(1);
      sut.push(2);
      auto result1 = sut.pop();
      auto result2 = sut.pop();
      auto result3 = sut.pop();

      THEN("size should be 0 and top should throw exception and last pop should be false and "
           "stack should be empty")
      {
        REQUIRE(sut.size() == 0);
        REQUIRE_THROWS_WITH(sut.top(), "Stack is empty");
        REQUIRE(result1);
        REQUIRE(result2);
        REQUIRE_FALSE(result3);
        REQUIRE(sut.isEmpty());
      }
    }
  }
}

SCENARIO("testing Stack push and pop to test circular buffer with int as data")
{
  GIVEN("constructing stack of size 4 containing 1, 2, 3, 4 (in order)")
  {
    auto sut = Stack<int>(4);
    sut.push(1);
    sut.push(2);
    sut.push(3);
    sut.push(4);
    std::cout << "Stack BEFORE: " << std::endl;
    sut.print();

    WHEN("pop from stack and then push 5 ")
    {
      sut.pop();
      sut.push(5);
      std::cout << "Stack AFTER pop and push(5): " << std::endl;
      sut.print();

      THEN("size should be 4, stack is full and top element should be 5")
      {
        REQUIRE(sut.size() == 4);
        REQUIRE(sut.isFull());
        REQUIRE_FALSE(sut.isEmpty());
        REQUIRE(sut.top() == 5);
      }
    }

    WHEN("pop from queue twice and then push 5 and 6")
    {
      sut.pop();
      sut.pop();
      sut.push(5);
      sut.push(6);

      std::cout << "Stack AFTER twice pop and push(5,6): " << std::endl;
      sut.print();

      THEN("size should be 4, stack is full and top element should be 6")
      {
        REQUIRE(sut.size() == 4);
        REQUIRE(sut.isFull());
        REQUIRE_FALSE(sut.isEmpty());
        REQUIRE(sut.top() == 6);
      }
    }

    WHEN("pop from stack three times and then push 5, 6 ")
    {
      sut.pop();
      sut.pop();
      sut.pop();
      sut.push(5);
      sut.push(6);

      std::cout << "Stack AFTER three times pop and push(5, 6): " << std::endl;
      sut.print();

      THEN("size should be 3, stack is not full and top element should be 6")
      {
        REQUIRE(sut.size() == 3);
        REQUIRE_FALSE(sut.isFull());
        REQUIRE_FALSE(sut.isEmpty());
        REQUIRE(sut.top() == 6);
      }
    }

    WHEN("pop from stack four times and then push 5, 6, 7, 8")
    {
      sut.pop();
      sut.pop();
      sut.pop();
      sut.pop();
      sut.push(5);
      sut.push(6);
      sut.push(7);
      sut.push(8);

      std::cout << "Stack AFTER four times pop and push(5, 6, 7, 8): " << std::endl;
      sut.print();

      THEN("size should be 4, stack is full and top element should be 8")
      {
        REQUIRE(sut.size() == 4);
        REQUIRE(sut.isFull());
        REQUIRE_FALSE(sut.isEmpty());
        REQUIRE(sut.top() == 8);
      }
    }
  }
}

SCENARIO("testing Stack pop and push and order of top elements")
{
  GIVEN("constructing  stack of size 4 containing 1, 2, 3, 4 (in order)")
  {
    auto sut = Stack<int>(4);
    sut.push(1);
    sut.push(2);
    sut.push(3);
    sut.push(4);
    auto testOrderVector = std::vector<int>();

    WHEN("pop from stack and then push 5 ")
    {
      sut.pop();
      sut.push(5);

      while (!sut.isEmpty()) {
        testOrderVector.push_back(sut.top());
        sut.pop();
      }

      auto expectedOrderVector = std::vector<int>{5, 3, 2, 1};

      THEN("testOrderVector should match expectedOrderVector {5,3,2,1}")
      {
        REQUIRE(testOrderVector == expectedOrderVector);
      }
    }

    WHEN("pop from stack twice and then push 5 and 6")
    {
      sut.pop();
      sut.pop();
      sut.push(5);
      sut.push(6);

      while (!sut.isEmpty()) {
        testOrderVector.push_back(sut.top());
        sut.pop();
      }

      auto expectedOrderVector = std::vector<int>{6, 5, 2, 1};

      THEN("testOrderVector should match expectedOrderVector {6,5,2,1}")
      {
        REQUIRE(testOrderVector == expectedOrderVector);
      }
    }

    WHEN("pop from stack three times and then push 5 and 6")
    {
      sut.pop();
      sut.pop();
      sut.pop();
      sut.push(5);
      sut.push(6);

      while (!sut.isEmpty()) {
        testOrderVector.push_back(sut.top());
        sut.pop();
      }

      auto expectedOrderVector = std::vector<int>{6, 5, 1};

      THEN("testOrderVector should match expectedOrderVector {6,5,1}")
      {
        REQUIRE(testOrderVector == expectedOrderVector);
      }
    }

    WHEN("pop from queue four times and then push 5, 6, 7, 8")
    {
      sut.pop();
      sut.pop();
      sut.pop();
      sut.pop();
      sut.push(5);
      sut.push(6);
      sut.push(7);
      sut.push(8);

      while (!sut.isEmpty()) {
        testOrderVector.push_back(sut.top());
        sut.pop();
      }

      auto expectedOrderVector = std::vector<int>{8, 7, 6, 5};

      THEN("testOrderVector should match expectedOrderVector {8,7,6,5}")
      {
        REQUIRE(testOrderVector == expectedOrderVector);
      }
    }
  }
}

} // namespace dsc::tests
