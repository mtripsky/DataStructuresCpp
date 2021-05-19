#include "catch.hpp"
#include "Queue/Queue.h"
#include <stdio.h>

namespace dsc::tests {

SCENARIO("testing Queue constructor with int as data")
{
  GIVEN("constructing  queue of maxSize 2")
  {
    auto sut = Queue<int>(2);

    WHEN("do nothing")
    {
      THEN("size should be 0") { REQUIRE(sut.Size() == 0); }
    }
  }
}

SCENARIO("testing Queue push with int as data")
{
  GIVEN("constructing  queue of size 2")
  {
    auto sut = Queue<int>(2);

    WHEN("push 1")
    {
      auto result1 = sut.Push(1);

      THEN("size should be 1 and front element should be 1")
      {
        REQUIRE(sut.Size() == 1);
        REQUIRE(sut.Front() == 1);
        REQUIRE(result1);
      }
    }

    WHEN("push 1 and then 2")
    {
      auto result1 = sut.Push(1);
      auto result2 = sut.Push(2);

      THEN("size should be 2 and front element should be 1")
      {
        REQUIRE(sut.Size() == 2);
        REQUIRE(sut.Front() == 1);
        REQUIRE(result1);
        REQUIRE(result2);
      }
    }

    WHEN("push 1, 2 and then 3")
    {
      auto result1 = sut.Push(1);
      auto result2 = sut.Push(2);
      auto result3 = sut.Push(3);

      THEN("size should be 2 and front element should be 1 and last push should be false "
           "and queue should be full")
      {
        REQUIRE(sut.Size() == 2);
        REQUIRE(sut.Front() == 1);
        REQUIRE(result1);
        REQUIRE(result2);
        REQUIRE_FALSE(result3);
        REQUIRE(sut.IsFull());
      }
    }
  }
}

SCENARIO("testing Queue dequeue with int as data")
{
  GIVEN("constructing  queue of size 2")
  {
    auto sut = Queue<int>(2);

    WHEN("dequeue from empty queue")
    {
      auto result1 = sut.Pop();

      THEN("dequeue methods should return false size should be 0")
      {
        REQUIRE(sut.Size() == 0);
        REQUIRE_FALSE(result1);
      }
    }

    WHEN("push from queue containing 1 and 2 (in order)")
    {
      sut.Push(1);
      sut.Push(2);
      auto result1 = sut.Pop();

      THEN("size should be 1 and front element should be 2")
      {
        REQUIRE(sut.Size() == 1);
        REQUIRE(sut.Front() == 2);
        REQUIRE(result1);
      }
    }

    WHEN("push three times from queue containing 1 and 2 (in order)")
    {
      sut.Push(1);
      sut.Push(2);
      auto result1 = sut.Pop();
      auto result2 = sut.Pop();
      auto result3 = sut.Pop();

      THEN("size should be 0 and front should throw exception and last push should be "
           "false and queue should be empty")
      {
        REQUIRE(sut.Size() == 0);
        REQUIRE_THROWS_WITH(sut.Front(), "Queue is empty");
        REQUIRE(result1);
        REQUIRE(result2);
        REQUIRE_FALSE(result3);
        REQUIRE(sut.IsEmpty());
      }
    }
  }
}

SCENARIO("testing Queue dequeue and push to test circular buffer with int as data")
{
  GIVEN("constructing  queue of size 4 containing 1, 2, 3, 4 (in order)")
  {
    auto sut = Queue<int>(4);
    sut.Push(1);
    sut.Push(2);
    sut.Push(3);
    sut.Push(4);
    std::cout << "Queue BEFORE: " << std::endl;
    sut.Print();

    WHEN("dequeue from queue and then queue 5 ")
    {
      sut.Pop();
      sut.Push(5);
      std::cout << "Queue AFTER dequeue and enqueu(5): " << std::endl;
      sut.Print();

      THEN("size should be 4, queue is full and front element should be 2")
      {
        REQUIRE(sut.Size() == 4);
        REQUIRE(sut.IsFull());
        REQUIRE_FALSE(sut.IsEmpty());
        REQUIRE(sut.Front() == 2);
      }
    }

    WHEN("dequeue from queue twice and then queue 5 and 6")
    {
      sut.Pop();
      sut.Push(5);
      sut.Pop();
      sut.Push(6);

      std::cout << "Queue AFTER twice dequeue and enqueu(5) and enqueu(6): " << std::endl;
      sut.Print();

      THEN("size should be 4, queue is full and front element should be 3")
      {
        REQUIRE(sut.Size() == 4);
        REQUIRE(sut.IsFull());
        REQUIRE_FALSE(sut.IsEmpty());
        REQUIRE(sut.Front() == 3);
      }
    }

    WHEN("dequeue from queue three times and then queue 5 and 6")
    {
      sut.Pop();
      sut.Push(5);
      sut.Pop();
      sut.Pop();
      sut.Push(6);

      std::cout << "Queue AFTER three times dequeue and enqueu(5, 6): " << std::endl;
      sut.Print();

      THEN("size should be 3, queue is not full and front element should be 4")
      {
        REQUIRE(sut.Size() == 3);
        REQUIRE_FALSE(sut.IsFull());
        REQUIRE_FALSE(sut.IsEmpty());
        REQUIRE(sut.Front() == 4);
      }
    }

    WHEN("dequeue from queue four times and then queue 5, 6, 7, 8")
    {
      sut.Pop();
      sut.Pop();
      sut.Pop();
      sut.Pop();
      sut.Push(5);
      sut.Push(6);
      sut.Push(7);
      sut.Push(8);

      std::cout << "Queue AFTER four times dequeue and enqueu(5, 6, 7, 8): " << std::endl;
      sut.Print();

      THEN("size should be 4, queue is full and front element should be 5")
      {
        REQUIRE(sut.Size() == 4);
        REQUIRE(sut.IsFull());
        REQUIRE_FALSE(sut.IsEmpty());
        REQUIRE(sut.Front() == 5);
      }
    }
  }
}

SCENARIO("testing Queue dequeue and push and order of front elements")
{
  GIVEN("constructing  queue of size 4 containing 1, 2, 3, 4 (in order)")
  {
    auto sut = Queue<int>(4);
    sut.Push(1);
    sut.Push(2);
    sut.Push(3);
    sut.Push(4);
    auto testOrderVector = std::vector<int>();

    WHEN("dequeue from queue and then queue 5 ")
    {
      sut.Pop();
      sut.Push(5);

      while (!sut.IsEmpty()) {
        testOrderVector.push_back(sut.Front());
        sut.Pop();
      }

      auto expectedOrderVector = std::vector<int>{2, 3, 4, 5};

      THEN("testOrderVector should match expectedOrderVector {2,3,4,5}")
      {
        REQUIRE(testOrderVector == expectedOrderVector);
      }
    }

    WHEN("dequeue from queue twice and then queue 5 and 6")
    {
      sut.Pop();
      sut.Push(5);
      sut.Pop();
      sut.Push(6);

      while (!sut.IsEmpty()) {
        testOrderVector.push_back(sut.Front());
        sut.Pop();
      }

      auto expectedOrderVector = std::vector<int>{3, 4, 5, 6};

      THEN("testOrderVector should match expectedOrderVector {3,4,5,6}")
      {
        REQUIRE(testOrderVector == expectedOrderVector);
      }
    }

    WHEN("dequeue from queue three times and then queue 5 and 6")
    {
      sut.Pop();
      sut.Push(5);
      sut.Pop();
      sut.Pop();
      sut.Push(6);

      while (!sut.IsEmpty()) {
        testOrderVector.push_back(sut.Front());
        sut.Pop();
      }

      auto expectedOrderVector = std::vector<int>{4, 5, 6};

      THEN("testOrderVector should match expectedOrderVector {4,5,6}")
      {
        REQUIRE(testOrderVector == expectedOrderVector);
      }
    }

    WHEN("dequeue from queue four times and then queue 5, 6, 7, 8")
    {
      sut.Pop();
      sut.Pop();
      sut.Pop();
      sut.Pop();
      sut.Push(5);
      sut.Push(6);
      sut.Push(7);
      sut.Push(8);

      while (!sut.IsEmpty()) {
        testOrderVector.push_back(sut.Front());
        sut.Pop();
      }

      auto expectedOrderVector = std::vector<int>{5, 6, 7, 8};

      THEN("testOrderVector should match expectedOrderVector {5,6,7,8}")
      {
        REQUIRE(testOrderVector == expectedOrderVector);
      }
    }
  }
}

} // namespace dsc::tests
