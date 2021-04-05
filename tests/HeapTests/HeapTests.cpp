#include "../../libs/catch.hpp"
#include "../../libs/fakeit.hpp"
#include "../../src/Heap/Heap.h"
#include <stdio.h>
#include <vector>

namespace dsc {
namespace heap {
namespace tests {

SCENARIO("testing Heap constructor with int as data")
{
  GIVEN("constructing  heap of maxSize 2")
  {
    auto sut = Heap<int>(2);

    WHEN("do nothing")
    {
      THEN("size should be 0") { REQUIRE(sut.size() == 0); }
    }
  }
}

SCENARIO("testing Heap push of one element with int as data")
{
  GIVEN("constructing  heap of maxSize 4")
  {
    auto sut = Heap<int>(4);

    WHEN("pushing 2")
    {
      sut.push(2);

      THEN("size should be 1 and top element should be 2")
      {
        REQUIRE(sut.size() == 1);
        REQUIRE(sut.top() == 2);
      }
    }

    WHEN("pushing 2,4")
    {
      sut.push(2);
      sut.push(4);

      THEN("size should be 2 and top element should be 4")
      {
        REQUIRE(sut.size() == 2);
        REQUIRE(sut.top() == 4);
      }
    }

    WHEN("pushing 2,4,1")
    {
      sut.push(2);
      sut.push(4);
      sut.push(1);

      THEN("size should be 3 and top element should be 4")
      {
        REQUIRE(sut.size() == 3);
        REQUIRE(sut.top() == 4);
      }
    }

    WHEN("pushing 2,4,1,6")
    {
      sut.push(2);
      sut.push(4);
      sut.push(1);
      sut.push(6);

      THEN("size should be 4 and top element should be 6")
      {
        REQUIRE(sut.size() == 4);
        REQUIRE(sut.top() == 6);
      }
    }
  }
}

SCENARIO("testing Heap push of general container with int as data")
{
  GIVEN("constructing  heap of maxSize 4")
  {
    auto sut = Heap<int>(4);

    WHEN("pushing a vector containing 2")
    {
      auto vec = std::vector<int>{2};
      sut.push(vec.begin(), vec.end());

      THEN("size should be 1 and top element should be 2")
      {
        REQUIRE(sut.size() == 1);
        REQUIRE(sut.top() == 2);
      }
    }

    WHEN("pushing a vector containing 2,4")
    {
      auto vec = std::vector<int>{2, 4};
      sut.push(vec.begin(), vec.end());

      THEN("size should be 2 and top element should be 4")
      {
        REQUIRE(sut.size() == 2);
        REQUIRE(sut.top() == 4);
      }
    }

    WHEN("pushing a vector containing 2,4,1")
    {
      auto vec = std::vector<int>{2, 4, 1};
      sut.push(vec.begin(), vec.end());

      THEN("size should be 3 and top element should be 4")
      {
        REQUIRE(sut.size() == 3);
        REQUIRE(sut.top() == 4);
      }
    }

    WHEN("pushing a vector containing 2,4,1,6")
    {
      auto vec = std::vector<int>{2, 4, 1, 6};
      sut.push(vec.begin(), vec.end());

      THEN("size should be 4 and top element should be 6")
      {
        REQUIRE(sut.size() == 4);
        REQUIRE(sut.top() == 6);
      }
    }
  }
}

SCENARIO("testing Heap push and pop with int as data")
{
  GIVEN("constructing  heap of maxSize = 6")
  {
    auto sut = Heap<int>(6);
    auto vec = std::vector<int>{2, 4, 1, 6, 9, 3};
    sut.push(vec.begin(), vec.end());

    WHEN("loop over heap and pop every time the top element it should create sorted sequence "
         "9,6,4,3,2,1")
    {
      auto expected = std::vector<int>{9, 6, 4, 3, 2, 1};
      auto result   = std::vector<int>();

      while (sut.size() > 0) {
        result.push_back(sut.top());
        sut.pop();
      }

      THEN("size should be 0 and sequence in result should match expected")
      {
        REQUIRE(sut.size() == 0);
        REQUIRE(expected == result);
      }
    }
  }
}

} // namespace tests
} // namespace heap
} // namespace dsc
