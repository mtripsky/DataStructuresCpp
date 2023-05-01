#include "catch.hpp"
#include "LinkedList/Node.h"
#include "LinkedList/UnorderedList.h"
#include <stdio.h>

namespace dsc::tests {

SCENARIO("testing UnorderedList push method with int as data")
{
  GIVEN("empty list")
  {
    auto sut = UnorderedList<int>();

    WHEN("do nothing")
    {
      THEN("list size should be 0") { REQUIRE(sut.size() == 0); }
    }

    WHEN("push data:1 into list")
    {
      auto result = sut.push(1);

      THEN("list size should be 1")
      {
        REQUIRE(sut.size() == 1);
        REQUIRE(result == true);
      }
    }

    WHEN("push data:1 and then data:2 into list")
    {
      sut.push(1);
      sut.push(2);

      THEN("list size should be 2") { REQUIRE(sut.size() == 2); }
    }
  }
}

SCENARIO("testing UnorderedList push_back method with int as data")
{
  GIVEN("empty list")
  {
    auto sut = UnorderedList<int>();

    WHEN("push_back data:1 into list")
    {
      auto result = sut.push_back(1);

      THEN("list size should be 1 and front and back should be 1")
      {
        REQUIRE(sut.size() == 1);
        REQUIRE(result == true);
        REQUIRE(sut.front()->data == 1);
        REQUIRE(sut.back()->data == 1);
      }
    }

    WHEN("push_back data:1, 2 into list")
    {
      sut.push_back(1);
      sut.push_back(2);

      THEN("list size should be 2 and front should be 1 and back 2")
      {
        REQUIRE(sut.size() == 2);
        REQUIRE(sut.front()->data == 1);
        REQUIRE(sut.back()->data == 2);
      }
    }

    WHEN("push_back data:1, 2, 3 into list")
    {
      sut.push_back(1);
      sut.push_back(2);
      sut.push_back(3);

      THEN("list size should be 3 and front should be 1 and back 3")
      {
        REQUIRE(sut.size() == 3);
        REQUIRE(sut.front()->data == 1);
        REQUIRE(sut.back()->data == 3);
      }
    }

    WHEN("push_back data:1, 2, 3 into list and then remove 3")
    {
      sut.push_back(1);
      sut.push_back(2);
      sut.push_back(3);
      sut.remove(3);

      THEN("list size should be 2 and front should be 1 and back 2")
      {
        REQUIRE(sut.size() == 2);
        REQUIRE(sut.front()->data == 1);
        REQUIRE(sut.back()->data == 2);
      }
    }
  }
}

SCENARIO("testing UnorderedList push and push_back methods combination with int as data")
{
  GIVEN("empty list")
  {
    auto sut = UnorderedList<int>();

    WHEN("push_back data:1, 2 and then push 3 into list")
    {
      sut.push_back(1);
      sut.push_back(2);
      sut.push(3);

      THEN("list size should be 3 and front=3 and back should be 2, list: 3->1->2")
      {
        REQUIRE(sut.size() == 3);
        REQUIRE(sut.front()->data == 3);
        REQUIRE(sut.back()->data == 2);
      }
    }

    WHEN("push data:1, 2 and then push_back 3 and then push 4 into list")
    {
      sut.push(1);
      sut.push(2);
      sut.push_back(3);
      sut.push(4);

      THEN("list size should be 4 and front should be 4 and back 3, list: 4->2->1->3")
      {
        REQUIRE(sut.size() == 4);
        REQUIRE(sut.front()->data == 4);
        REQUIRE(sut.back()->data == 3);
      }
    }

    WHEN("push_back data:1, push data:2, push_back data:3, push data:4 into list")
    {
      sut.push_back(1);
      sut.push(2);
      sut.push_back(3);
      sut.push(4);

      THEN("list size should be 4 and front should be 4 and back 3, list: 4->2->1->3")
      {
        REQUIRE(sut.size() == 4);
        REQUIRE(sut.front()->data == 4);
        REQUIRE(sut.back()->data == 3);
      }
    }

    WHEN("push_back:1, push:2, push_back:3, push:4 remove 4 and 3")
    {
      sut.push_back(1);
      sut.push(2);
      sut.push_back(3);
      sut.push(4);
      sut.remove(4);
      sut.remove(3);

      THEN("list size should be 2 and front should be 2 and back 1, list: 2->1")
      {
        REQUIRE(sut.size() == 2);
        REQUIRE(sut.front()->data == 2);
        REQUIRE(sut.back()->data == 1);
      }
    }
  }
}

SCENARIO("testing UnorderedList pop method with int as data")
{
  GIVEN("empty list")
  {
    auto sut = UnorderedList<int>();

    WHEN("pop from the list")
    {
      auto result = sut.pop();

      THEN("it should not do anything")
      {
        REQUIRE(sut.size() == 0);
        REQUIRE(result == true);
      }
    }
  }

  GIVEN(" list with one node")
  {
    auto sut = UnorderedList<int>();
    sut.push(1);

    WHEN("pop from the list")
    {
      auto result = sut.pop();

      THEN("it should create empty list")
      {
        REQUIRE(sut.size() == 0);
        REQUIRE(result == true);
      }
    }
  }

  GIVEN(" list with two nodes")
  {
    auto sut = UnorderedList<int>();
    sut.push(1);
    sut.push(2);

    WHEN("pop from the list")
    {
      auto result = sut.pop();

      THEN("it should create list with one node (front: 1, back: 1)")
      {
        REQUIRE(sut.size() == 1);
        REQUIRE(sut.back()->data == 1);
        REQUIRE(sut.front()->data == 1);
        REQUIRE(result == true);
      }
    }
  }

  GIVEN(" list with three nodes")
  {
    auto sut = UnorderedList<int>();
    sut.push(1);
    sut.push(2);
    sut.push(3);

    WHEN("pop from the list")
    {
      auto result = sut.pop();

      THEN("it should create list with two nodes (front: 2, back: 1)")
      {
        REQUIRE(sut.size() == 2);
        REQUIRE(sut.back()->data == 1);
        REQUIRE(sut.front()->data == 2);
        REQUIRE(result == true);
      }
    }
  }
}

SCENARIO("testing UnorderedList remove method with int as data")
{
  GIVEN(" list with one node")
  {
    auto sut = UnorderedList<int>();
    sut.push(1);

    WHEN("remove data: 2 from the list")
    {
      auto result = sut.remove(2);

      THEN("it should not remove anything and should return false")
      {
        REQUIRE(sut.size() == 1);
        REQUIRE(result == false);
      }
    }

    WHEN("remove data: 1 from the list")
    {
      auto result = sut.remove(1);

      THEN("it should remove node with data:1, should return true, and empty list")
      {
        REQUIRE(sut.size() == 0);
        REQUIRE(result == true);
      }
    }
  }

  GIVEN(" list with four nodes")
  {
    auto sut = UnorderedList<int>(); // 4->3->2->1
    sut.push(1);
    sut.push(2);
    sut.push(3);
    sut.push(4);

    std::cout << "UnorderedList BEFORE: " << std::endl;
    sut.print();

    WHEN("remove data: 5 from the list")
    {
      auto result = sut.remove(5);

      std::cout << "UnorderedList After remove(5): " << std::endl;
      sut.print();

      THEN("it should not remove anything and should return false (front: 4, back 1)")
      {
        REQUIRE(sut.size() == 4);
        REQUIRE(sut.back()->data == 1);
        REQUIRE(sut.front()->data == 4);
        REQUIRE(result == false);
      }
    }

    WHEN("remove data: 1 from the list")
    {
      auto result = sut.remove(1);

      std::cout << "UnorderedList After remove(1): " << std::endl;
      sut.print();

      THEN("it should remove node with data:1, should return true, and list with size 3 "
           "(front: 4, back 2)")
      {
        REQUIRE(sut.size() == 3);
        REQUIRE(sut.back()->data == 2);
        REQUIRE(sut.front()->data == 4);
        REQUIRE(result == true);
      }
    }

    WHEN("remove data: 2 from the list")
    {
      auto result = sut.remove(2);

      std::cout << "UnorderedList After remove(2): " << std::endl;
      sut.print();

      THEN("it should remove node with data:2, should return true, and list with size 3 "
           "(front: 4, back 1)")
      {
        REQUIRE(sut.size() == 3);
        REQUIRE(sut.back()->data == 1);
        REQUIRE(sut.front()->data == 4);
        REQUIRE(result == true);
      }
    }

    WHEN("remove data: 3 from the list")
    {
      auto result = sut.remove(3);

      std::cout << "UnorderedList After remove(3): " << std::endl;
      sut.print();

      THEN("it should remove node with data:3, should return true, and list with size 3 "
           "(front: 4, back 1)")
      {
        REQUIRE(sut.size() == 3);
        REQUIRE(sut.back()->data == 1);
        REQUIRE(sut.front()->data == 4);
        REQUIRE(result == true);
      }
    }

    WHEN("remove data: 4 from the list")
    {
      auto result = sut.remove(4);

      std::cout << "UnorderedList After remove(4): " << std::endl;
      sut.print();

      THEN("it should remove node with data:4, should return true, and list with size 3 "
           "(front: 3, back 1)")
      {
        REQUIRE(sut.size() == 3);
        REQUIRE(sut.back()->data == 1);
        REQUIRE(sut.front()->data == 3);
        REQUIRE(result == true);
      }
    }
  }
}

SCENARIO("testing UnorderedList front method with int as data")
{
  GIVEN("empty list")
  {
    auto sut = UnorderedList<int>();

    WHEN("push data:1 into list")
    {
      sut.push(1);
      auto result = sut.front();

      THEN("front should return node with data = 1") { REQUIRE(result->data == 1); }
    }

    WHEN("push data:1 and then data:2 into list")
    {
      sut.push(1);
      sut.push(2);
      auto result = sut.front();

      THEN("front should return node with data = 2") { REQUIRE(result->data == 2); }
    }

    WHEN("push data:1, then data:2 and then data:3 into list")
    {
      sut.push(1);
      sut.push(2);
      sut.push(3);
      auto result = sut.front();

      THEN("front should return node with data = 3") { REQUIRE(result->data == 3); }
    }
  }
}

SCENARIO("testing UnorderedList back method with int as data")
{
  GIVEN("empty list")
  {
    auto sut = UnorderedList<int>();

    WHEN("push data:1 into list")
    {
      sut.push(1);
      auto result = sut.back();

      THEN("back should return node with data = 1") { REQUIRE(result->data == 1); }
    }

    WHEN("push data:1 and then data:2 into list")
    {
      sut.push(1);
      sut.push(2);
      auto result = sut.back();

      THEN("back should return node with data = 1") { REQUIRE(result->data == 1); }
    }

    WHEN("push data:1, then data:2 and then data:3 into list")
    {
      sut.push(1);
      sut.push(2);
      sut.push(3);
      auto result = sut.back();

      THEN("front should return node with data = 1") { REQUIRE(result->data == 1); }
    }
  }
}

SCENARIO("testing UnorderedList front and back methods with int as data")
{
  GIVEN("empty list")
  {
    auto sut = UnorderedList<int>();

    WHEN("push data:1 into list")
    {
      sut.push(1);
      auto resultFront = sut.front();
      auto resultBack  = sut.back();

      THEN("back and front should return node with data = 1")
      {
        REQUIRE(resultFront->data == 1);
        REQUIRE(resultBack->data == 1);
      }
    }

    WHEN("push data:1 and then data:2 into list")
    {
      sut.push(1);
      sut.push(2);
      auto resultFront = sut.front();
      auto resultBack  = sut.back();

      THEN("back should return node with data = 1 and front with data = 2")
      {
        REQUIRE(resultFront->data == 2);
        REQUIRE(resultBack->data == 1);
      }
    }

    WHEN("push data:1, then data:2 and then data:3 into list")
    {
      sut.push(1);
      sut.push(2);
      sut.push(3);
      auto resultFront = sut.front();
      auto resultBack  = sut.back();

      THEN("back should return node with data = 1 and front with data = 3")
      {
        REQUIRE(resultFront->data == 3);
        REQUIRE(resultBack->data == 1);
      }
    }
  }
}

SCENARIO("testing UnorderedList reverse method with int as data")
{
  GIVEN("empty list")
  {
    auto sut = UnorderedList<int>();

    WHEN("reverse list")
    {
      sut.reverse();

      THEN("list should have size 0") { REQUIRE(sut.size() == 0); }
    }
  }

  GIVEN(" list: 1->")
  {
    auto sut = UnorderedList<int>();
    sut.push(1);

    WHEN("reverse list")
    {
      sut.reverse();

      THEN("list should have size 1, front is 1 and back is 1")
      {
        REQUIRE(sut.size() == 1);
        REQUIRE(sut.front()->data == 1);
        REQUIRE(sut.back()->data == 1);
      }
    }
  }

  GIVEN(" list: 1->2")
  {
    auto sut = UnorderedList<int>();
    sut.push(2);
    sut.push(1);

    WHEN("reverse list")
    {
      sut.reverse();

      THEN("list should have size 2, front is 2 and back is 1")
      {
        REQUIRE(sut.size() == 2);
        REQUIRE(sut.front()->data == 2);
        REQUIRE(sut.back()->data == 1);
      }
    }
  }

  GIVEN(" list: 1->2->3")
  {
    auto sut = UnorderedList<int>();
    sut.push(3);
    sut.push(2);
    sut.push(1);

    WHEN("reverse list")
    {
      sut.reverse();

      THEN("list should have size 3, front is 3 and back is 1")
      {
        REQUIRE(sut.size() == 3);
        REQUIRE(sut.front()->data == 3);
        REQUIRE(sut.back()->data == 1);
      }
    }
  }

  GIVEN(" list: 1->2->3->4")
  {
    auto sut = UnorderedList<int>();
    sut.push(4);
    sut.push(3);
    sut.push(2);
    sut.push(1);

    WHEN("reverse list")
    {
      sut.reverse();

      THEN("list should have size 4, front is 4 and back is 1")
      {
        REQUIRE(sut.size() == 4);
        REQUIRE(sut.front()->data == 4);
        REQUIRE(sut.back()->data == 1);
      }
    }
  }

  GIVEN(" list: 1->2->3->4->5")
  {
    auto sut = UnorderedList<int>();
    sut.push(5);
    sut.push(4);
    sut.push(3);
    sut.push(2);
    sut.push(1);
    std::cout << "UnorderedList Before REVERSE: " << std::endl;
    sut.print();

    WHEN("reverse list")
    {
      sut.reverse();
      std::cout << "UnorderedList After REVERSE: " << std::endl;
      sut.print();

      THEN("list should have size 5, front is 5 and back is 1")
      {
        REQUIRE(sut.size() == 5);
        REQUIRE(sut.front()->data == 5);
        REQUIRE(sut.back()->data == 1);
      }
    }
  }
}

struct TestObject {
  TestObject(int scalar = 0) : X(scalar)
  {
    std::cout << "TestObject Constructor" << std::endl;
    m_data = new int[5];
  }
  TestObject(const TestObject& other)
  {
    std::cout << "TestObject Copy Constructor" << std::endl;
    m_data = other.m_data;
    X      = other.X;
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
    delete[] m_data;
    std::cout << "TestObject Destroyed" << std::endl;
  }

  int  X;
  int* m_data = nullptr;
};

// SCENARIO("testing OrderedList with TestObject as data")
// {
//   GIVEN("empty list")
//   {
//     auto sut = UnorderedList<TestObject>();

//     WHEN("push 3 test objects")
//     {
//       TestObject t1;
//       sut.push(t1);
//       // sut.push(TestObject(1));
//       // sut.push(TestObject(2));

//       // sut.pop();
//       // sut.pop();
//       // sut.pop();
//     }
//   }
// }

} // namespace dsc::tests
