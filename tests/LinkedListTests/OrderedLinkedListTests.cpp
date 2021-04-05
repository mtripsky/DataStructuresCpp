#include "../../libs/catch.hpp"
#include "../../libs/fakeit.hpp"
#include "../../src/LinkedList/Ordered/linkedList.cpp"
#include "../../src/LinkedList/node.h"
#include <stdio.h>

namespace dsc {
namespace lists {
namespace ordered {
namespace tests {

SCENARIO("testing OrderedList push method with int as data")
{
  GIVEN("empty list")
  {
    auto sut = LinkedList<int>();

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

    WHEN("push data:2, 1, 3 into list")
    {
      sut.push(2);
      sut.push(1);
      sut.push(3);

      THEN("list size should be 3 and front should be 3 and back 1")
      {
        REQUIRE(sut.size() == 3);
        REQUIRE(sut.front()->data == 3);
        REQUIRE(sut.back()->data == 1);
      }
    }

    WHEN("push random data into list")
    {
      sut.push(2);
      sut.push(1);
      sut.push(3);
      sut.push(7);
      sut.push(4);
      sut.push(6);
      sut.push(9);
      sut.push(8);
      sut.push(5);

      std::cout << "Ordered list of data between 1-9" << std::endl;
      sut.print();
      THEN("list size should be 9 and front should be 9 and back 1")
      {
        REQUIRE(sut.size() == 9);
        REQUIRE(sut.front()->data == 9);
        REQUIRE(sut.back()->data == 1);
      }
    }
  }
}

SCENARIO("testing OrderedList reverse method with int as data")
{
  GIVEN("empty list")
  {
    auto sut = LinkedList<int>();

    WHEN("push random data into list")
    {
      sut.push(2);
      sut.push(1);
      sut.push(3);
      sut.push(7);
      sut.push(4);
      sut.push(6);
      sut.push(9);
      sut.push(8);
      sut.push(5);

      std::cout << "Ordered list of data between 1-9 before reverse" << std::endl;
      sut.print();
      sut.reverse();
      std::cout << "Ordered list of data between 1-9 after reverse" << std::endl;
      sut.print();

      THEN("list size should be 9 and front should be 1 and back 9")
      {
        REQUIRE(sut.size() == 9);
        REQUIRE(sut.front()->data == 1);
        REQUIRE(sut.back()->data == 9);
      }
    }
  }
}

// SCENARIO("testing UnorderedList push_back method with int as data")
// {
// 	GIVEN("empty list")
// 	{
// 		auto sut = LinkedList<int>();
//
// 		WHEN("push_back data:1 into list")
// 		{
// 			auto result = sut.push_back(1);
//
// 			THEN("list size should be 1 and front and back should be 1")
// 			{
// 				REQUIRE(sut.size() == 1);
// 				REQUIRE(result == true);
// 				REQUIRE(sut.front()->data == 1);
// 				REQUIRE(sut.back()->data == 1);
// 			}
// 		}
//
// 		WHEN("push_back data:1, 2 into list")
// 		{
// 			sut.push_back(1);
// 			sut.push_back(2);
//
// 			THEN("list size should be 2 and front should be 1 and back 2")
// 			{
// 				REQUIRE(sut.size() == 2);
// 				REQUIRE(sut.front()->data == 1);
// 				REQUIRE(sut.back()->data == 2);
// 			}
// 		}
//
// 		WHEN("push_back data:1, 2, 3 into list")
// 		{
// 			sut.push_back(1);
// 			sut.push_back(2);
// 			sut.push_back(3);
//
// 			THEN("list size should be 3 and front should be 1 and back 3")
// 			{
// 				REQUIRE(sut.size() == 3);
// 				REQUIRE(sut.front()->data == 1);
// 				REQUIRE(sut.back()->data == 3);
// 			}
// 		}
//
// 		WHEN("push_back data:1, 2, 3 into list and then remove 3")
// 		{
// 			sut.push_back(1);
// 			sut.push_back(2);
// 			sut.push_back(3);
// 			sut.remove(3);
//
// 			THEN("list size should be 2 and front should be 1 and back 2")
// 			{
// 				REQUIRE(sut.size() == 2);
// 				REQUIRE(sut.front()->data == 1);
// 				REQUIRE(sut.back()->data == 2);
// 			}
// 		}
// 	}
// }
//
// SCENARIO("testing UnorderedList push and push_back methods combination to create list with int as
// data")
// {
// 	GIVEN("empty list")
// 	{
// 		auto sut = LinkedList<int>();
//
// 		WHEN("push_back data:1, 2 and then push 3 into list")
// 		{
// 			sut.push_back(1);
// 			sut.push_back(2);
// 			sut.push(3);
//
// 			THEN("list size should be 3 and front=3 and back should be 2, list:
// 3->1->2")
// 			{
// 				REQUIRE(sut.size() == 3);
// 				REQUIRE(sut.front()->data == 3);
// 				REQUIRE(sut.back()->data == 2);
// 			}
// 		}
//
// 		WHEN("push data:1, 2 and then push_back 3 and then push 4 into list")
// 		{
// 			sut.push(1);
// 			sut.push(2);
// 			sut.push_back(3);
// 			sut.push(4);
//
// 			THEN("list size should be 4 and front should be 4 and back 3, list:
// 4->2->1->3")
// 			{
// 				REQUIRE(sut.size() == 4);
// 				REQUIRE(sut.front()->data == 4);
// 				REQUIRE(sut.back()->data == 3);
// 			}
// 		}
//
// 		WHEN("push_back data:1, push data:2, push_back data:3, push data:4 into list")
// 		{
// 			sut.push_back(1);
// 			sut.push(2);
// 			sut.push_back(3);
// 			sut.push(4);
//
// 			THEN("list size should be 4 and front should be 4 and back 3, list:
// 4->2->1->3")
// 			{
// 				REQUIRE(sut.size() == 4);
// 				REQUIRE(sut.front()->data == 4);
// 				REQUIRE(sut.back()->data == 3);
// 			}
// 		}
//
// 		WHEN("push_back data:1, push data:2, push_back data:3, push data:4 into list and
// remove 4 and 3")
// 		{
// 			sut.push_back(1);
// 			sut.push(2);
// 			sut.push_back(3);
// 			sut.push(4);
// 			sut.remove(4);
// 			sut.remove(3);
//
// 			THEN("list size should be 2 and front should be 2 and back 1, list: 2->1")
// 			{
// 				REQUIRE(sut.size() == 2);
// 				REQUIRE(sut.front()->data == 2);
// 				REQUIRE(sut.back()->data == 1);
// 			}
// 		}
// 	}
// }
//
// SCENARIO("testing UnorderedList pop method with int as data")
// {
// 	GIVEN("empty list")
// 	{
// 		auto sut = LinkedList<int>();
//
// 		WHEN("pop from the list")
// 		{
// 			auto result = sut.pop();
//
// 			THEN("it should not do anything")
// 			{
// 				REQUIRE(sut.size() == 0);
// 				REQUIRE(result == true);
// 			}
// 		}
// 	}
//
// 	GIVEN(" list with one node")
// 	{
// 		auto sut = LinkedList<int>();
// 		sut.push(1);
//
// 		WHEN("pop from the list")
// 		{
// 			auto result = sut.pop();
//
// 			THEN("it should create empty list")
// 			{
// 				REQUIRE(sut.size() == 0);
// 				REQUIRE(result == true);
// 			}
// 		}
// 	}
//
// 	GIVEN(" list with two nodes")
// 	{
// 		auto sut = LinkedList<int>();
// 		sut.push(1);
// 		sut.push(2);
//
// 		WHEN("pop from the list")
// 		{
// 			auto result = sut.pop();
//
// 			THEN("it should create list with one node (front: 1, back: 1)")
// 			{
// 				REQUIRE(sut.size() == 1);
// 				REQUIRE(sut.back()->data == 1);
// 				REQUIRE(sut.front()->data == 1);
// 				REQUIRE(result == true);
// 			}
// 		}
// 	}
//
// 	GIVEN(" list with three nodes")
// 	{
// 		auto sut = LinkedList<int>();
// 		sut.push(1);
// 		sut.push(2);
// 		sut.push(3);
//
// 		WHEN("pop from the list")
// 		{
// 			auto result = sut.pop();
//
// 			THEN("it should create list with two nodes (front: 2, back: 1)")
// 			{
// 				REQUIRE(sut.size() == 2);
// 				REQUIRE(sut.back()->data == 1);
// 				REQUIRE(sut.front()->data == 2);
// 				REQUIRE(result == true);
// 			}
// 		}
// 	}
// }
//
// SCENARIO("testing UnorderedList remove method with int as data")
// {
// 	GIVEN(" list with one node")
// 	{
// 		auto sut = LinkedList<int>();
// 		sut.push(1);
//
// 		WHEN("remove data: 2 from the list")
// 		{
// 			auto result = sut.remove(2);
//
// 			THEN("it should not remove anything and should return false")
// 			{
// 				REQUIRE(sut.size() == 1);
// 				REQUIRE(result == false);
// 			}
// 		}
//
// 		WHEN("remove data: 1 from the list")
// 		{
// 			auto result = sut.remove(1);
//
// 			THEN("it should remove node with data:1, should return true, and empty
// list")
// 			{
// 				REQUIRE(sut.size() == 0);
// 				REQUIRE(result == true);
// 			}
// 		}
// 	}
//
// 	GIVEN(" list with four nodes")
// 	{
// 		auto sut = LinkedList<int>();  // 4->3->2->1
// 		sut.push(1);
// 		sut.push(2);
// 		sut.push(3);
// 		sut.push(4);
//
// 		std::cout << "UnorderedList BEFORE: " << std::endl;
// 		sut.print();
//
// 		WHEN("remove data: 5 from the list")
// 		{
// 			auto result = sut.remove(5);
//
// 			std::cout << "UnorderedList After remove(5): " << std::endl;
// 			sut.print();
//
// 			THEN("it should not remove anything and should return false (front: 4, back
// 1)")
// 			{
// 				REQUIRE(sut.size() == 4);
// 				REQUIRE(sut.back()->data == 1);
// 				REQUIRE(sut.front()->data == 4);
// 				REQUIRE(result == false);
// 			}
// 		}
//
// 		WHEN("remove data: 1 from the list")
// 		{
// 			auto result = sut.remove(1);
//
// 			std::cout << "UnorderedList After remove(1): " << std::endl;
// 			sut.print();
//
// 			THEN("it should remove node with data:1, should return true, and list with size
// 3
// "
// 				 "(front: 4, back 2)")
// 			{
// 				REQUIRE(sut.size() == 3);
// 				REQUIRE(sut.back()->data == 2);
// 				REQUIRE(sut.front()->data == 4);
// 				REQUIRE(result == true);
// 			}
// 		}
//
// 		WHEN("remove data: 2 from the list")
// 		{
// 			auto result = sut.remove(2);
//
// 			std::cout << "UnorderedList After remove(2): " << std::endl;
// 			sut.print();
//
// 			THEN("it should remove node with data:2, should return true, and list with size
// 3
// "
// 				 "(front: 4, back 1)")
// 			{
// 				REQUIRE(sut.size() == 3);
// 				REQUIRE(sut.back()->data == 1);
// 				REQUIRE(sut.front()->data == 4);
// 				REQUIRE(result == true);
// 			}
// 		}
//
// 		WHEN("remove data: 3 from the list")
// 		{
// 			auto result = sut.remove(3);
//
// 			std::cout << "UnorderedList After remove(3): " << std::endl;
// 			sut.print();
//
// 			THEN("it should remove node with data:3, should return true, and list with size
// 3
// "
// 				 "(front: 4, back 1)")
// 			{
// 				REQUIRE(sut.size() == 3);
// 				REQUIRE(sut.back()->data == 1);
// 				REQUIRE(sut.front()->data == 4);
// 				REQUIRE(result == true);
// 			}
// 		}
//
// 		WHEN("remove data: 4 from the list")
// 		{
// 			auto result = sut.remove(4);
//
// 			std::cout << "UnorderedList After remove(4): " << std::endl;
// 			sut.print();
//
// 			THEN("it should remove node with data:4, should return true, and list with size
// 3
// "
// 				 "(front: 3, back 1)")
// 			{
// 				REQUIRE(sut.size() == 3);
// 				REQUIRE(sut.back()->data == 1);
// 				REQUIRE(sut.front()->data == 3);
// 				REQUIRE(result == true);
// 			}
// 		}
// 	}
// }
//
// SCENARIO("testing UnorderedList front method with int as data")
// {
// 	GIVEN("empty list")
// 	{
// 		auto sut = LinkedList<int>();
//
// 		WHEN("push data:1 into list")
// 		{
// 			sut.push(1);
// 			auto result = sut.front();
//
// 			THEN("front should return node with data = 1")
// 			{
// 				REQUIRE(result->data == 1);
// 			}
// 		}
//
// 		WHEN("push data:1 and then data:2 into list")
// 		{
// 			sut.push(1);
// 			sut.push(2);
// 			auto result = sut.front();
//
// 			THEN("front should return node with data = 2")
// 			{
// 				REQUIRE(result->data == 2);
// 			}
// 		}
//
// 		WHEN("push data:1, then data:2 and then data:3 into list")
// 		{
// 			sut.push(1);
// 			sut.push(2);
// 			sut.push(3);
// 			auto result = sut.front();
//
// 			THEN("front should return node with data = 3")
// 			{
// 				REQUIRE(result->data == 3);
// 			}
// 		}
// 	}
// }
//
// SCENARIO("testing UnorderedList back method with int as data")
// {
// 	GIVEN("empty list")
// 	{
// 		auto sut = LinkedList<int>();
//
// 		WHEN("push data:1 into list")
// 		{
// 			sut.push(1);
// 			auto result = sut.back();
//
// 			THEN("back should return node with data = 1")
// 			{
// 				REQUIRE(result->data == 1);
// 			}
// 		}
//
// 		WHEN("push data:1 and then data:2 into list")
// 		{
// 			sut.push(1);
// 			sut.push(2);
// 			auto result = sut.back();
//
// 			THEN("back should return node with data = 1")
// 			{
// 				REQUIRE(result->data == 1);
// 			}
// 		}
//
// 		WHEN("push data:1, then data:2 and then data:3 into list")
// 		{
// 			sut.push(1);
// 			sut.push(2);
// 			sut.push(3);
// 			auto result = sut.back();
//
// 			THEN("front should return node with data = 1")
// 			{
// 				REQUIRE(result->data == 1);
// 			}
// 		}
// 	}
// }
//
// SCENARIO("testing UnorderedList front and back methods with int as data")
// {
// 	GIVEN("empty list")
// 	{
// 		auto sut = LinkedList<int>();
//
// 		WHEN("push data:1 into list")
// 		{
// 			sut.push(1);
// 			auto resultFront = sut.front();
// 			auto resultBack = sut.back();
//
// 			THEN("back and front should return node with data = 1")
// 			{
// 				REQUIRE(resultFront->data == 1);
// 				REQUIRE(resultBack->data == 1);
// 			}
// 		}
//
// 		WHEN("push data:1 and then data:2 into list")
// 		{
// 			sut.push(1);
// 			sut.push(2);
// 			auto resultFront = sut.front();
// 			auto resultBack = sut.back();
//
// 			THEN("back should return node with data = 1 and front with data = 2")
// 			{
// 				REQUIRE(resultFront->data == 2);
// 				REQUIRE(resultBack->data == 1);
// 			}
// 		}
//
// 		WHEN("push data:1, then data:2 and then data:3 into list")
// 		{
// 			sut.push(1);
// 			sut.push(2);
// 			sut.push(3);
// 			auto resultFront = sut.front();
// 			auto resultBack = sut.back();
//
// 			THEN("back should return node with data = 1 and front with data = 3")
// 			{
// 				REQUIRE(resultFront->data == 3);
// 				REQUIRE(resultBack->data == 1);
// 			}
// 		}
// 	}
// }
//
// SCENARIO("testing UnorderedList reverse method with int as data")
// {
// 	GIVEN("empty list")
// 	{
// 		auto sut = LinkedList<int>();
//
// 		WHEN("reverse list")
// 		{
// 			sut.reverse();
//
// 			THEN("list should have size 0")
// 			{
// 				REQUIRE(sut.size() == 0);
// 			}
// 		}
// 	}
//
// 	GIVEN(" list: 1->")
// 	{
// 		auto sut = LinkedList<int>();
// 		sut.push(1);
//
// 		WHEN("reverse list")
// 		{
// 			sut.reverse();
//
// 			THEN("list should have size 1, front is 1 and back is 1")
// 			{
// 				REQUIRE(sut.size() == 1);
// 				REQUIRE(sut.front()->data == 1);
// 				REQUIRE(sut.back()->data == 1);
// 			}
// 		}
// 	}
//
// 	GIVEN(" list: 1->2")
// 	{
// 		auto sut = LinkedList<int>();
// 		sut.push(2);
// 		sut.push(1);
//
// 		WHEN("reverse list")
// 		{
// 			sut.reverse();
//
// 			THEN("list should have size 2, front is 2 and back is 1")
// 			{
// 				REQUIRE(sut.size() == 2);
// 				REQUIRE(sut.front()->data == 2);
// 				REQUIRE(sut.back()->data == 1);
// 			}
// 		}
// 	}
//
// 	GIVEN(" list: 1->2->3")
// 	{
// 		auto sut = LinkedList<int>();
// 		sut.push(3);
// 		sut.push(2);
// 		sut.push(1);
//
// 		WHEN("reverse list")
// 		{
// 			sut.reverse();
//
// 			THEN("list should have size 3, front is 3 and back is 1")
// 			{
// 				REQUIRE(sut.size() == 3);
// 				REQUIRE(sut.front()->data == 3);
// 				REQUIRE(sut.back()->data == 1);
// 			}
// 		}
// 	}
//
// 	GIVEN(" list: 1->2->3->4")
// 	{
// 		auto sut = LinkedList<int>();
// 		sut.push(4);
// 		sut.push(3);
// 		sut.push(2);
// 		sut.push(1);
//
// 		WHEN("reverse list")
// 		{
// 			sut.reverse();
//
// 			THEN("list should have size 4, front is 4 and back is 1")
// 			{
// 				REQUIRE(sut.size() == 4);
// 				REQUIRE(sut.front()->data == 4);
// 				REQUIRE(sut.back()->data == 1);
// 			}
// 		}
// 	}
//
// 	GIVEN(" list: 1->2->3->4->5")
// 	{
// 		auto sut = LinkedList<int>();
// 		sut.push(5);
// 		sut.push(4);
// 		sut.push(3);
// 		sut.push(2);
// 		sut.push(1);
// 		std::cout << "UnorderedList Before REVERSE: " << std::endl;
// 		sut.print();
//
// 		WHEN("reverse list")
// 		{
// 			sut.reverse();
// 			std::cout << "UnorderedList After REVERSE: " << std::endl;
// 			sut.print();
//
// 			THEN("list should have size 5, front is 5 and back is 1")
// 			{
// 				REQUIRE(sut.size() == 5);
// 				REQUIRE(sut.front()->data == 5);
// 				REQUIRE(sut.back()->data == 1);
// 			}
// 		}
// 	}
// }

} // namespace tests
} // namespace ordered
} // namespace lists
} // namespace dsc
