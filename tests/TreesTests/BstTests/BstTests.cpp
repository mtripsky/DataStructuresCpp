#include <stdio.h>
#include <vector>
#include "../../../libs/catch.hpp"
#include "../../../libs/fakeit.hpp"
#include "../../../src/Trees/node.h"
#include "../../../src/Trees/Bst/bst.cpp"


namespace dsc {
namespace trees {
namespace bst {
namespace tests {

SCENARIO("testing BST insert method with int key and int data")
{
	GIVEN("empty BST")
	{
		auto sut = BST<int, int>();

		WHEN("not inserting anything")
		{
			THEN("size should be 0")
			{
				REQUIRE(sut.size() == 0);
			}
		}

		WHEN("inserting 10 (key and data are same)")
		{
			sut.insert(10,10);

			THEN("size should be 1")
			{
				REQUIRE(sut.size() == 1);
			}
		}

		WHEN("inserting 10 and 5 (key and data are same)")
		{
			sut.insert(10,10);
			sut.insert(5,5);

			THEN("size should be 2")
			{
				REQUIRE(sut.size() == 2);
			}
		}

		WHEN("inserting 10, 5 and 12 (key and data are same)")
		{
			sut.insert(10,10);
			sut.insert(5,5);
			sut.insert(12,12);

			THEN("size should be 3")
			{
				REQUIRE(sut.size() == 3);
			}
		}

		WHEN("inserting 10, 5, 12 and 1 (key and data are same)")
		{
			sut.insert(10,10);
			sut.insert(5,5);
			sut.insert(12,12);
			sut.insert(1,1);

			THEN("size should be 4")
			{
				REQUIRE(sut.size() == 4);
			}
		}
	}
}

SCENARIO("testing BST findMaxKey and findMinKey methods with int key and int data")
{
	GIVEN("empty BST")
	{
		auto sut = BST<int, int>();

		WHEN("findMaxKey in empty BST")
		{
			THEN("it should throw: Tree is empty")
			{
				REQUIRE_THROWS_WITH(sut.findMaxKey(), "Tree is empty");
			}
		}

		WHEN("findMinKey in empty BST")
		{
			THEN("it should throw: Tree is empty")
			{
				REQUIRE_THROWS_WITH(sut.findMinKey(), "Tree is empty");
			}
		}

		WHEN("inserting 5 into tree to findMinKey and findMaxKey")
		{
			sut.insert(5,5);

			THEN("it minKey and maxKey should be same")
			{
				REQUIRE(sut.findMaxKey() == 5);
				REQUIRE(sut.findMinKey() == 5);
			}
		}

		WHEN("inserting 5 and 12 into tree to findMinKey and findMaxKey")
		{
			sut.insert(5,5);
			sut.insert(12,12);

			THEN("minKey should be 5 and maxKey should be 12")
			{
				REQUIRE(sut.findMaxKey() == 12);
				REQUIRE(sut.findMinKey() == 5);
			}
		}

		WHEN("inserting 5, 3 and 12 into tree to findMinKey and findMaxKey")
		{
			sut.insert(5,5);
			sut.insert(3,3);
			sut.insert(12,12);

			THEN("minKey should be 3 and maxKey should be 12")
			{
				REQUIRE(sut.findMaxKey() == 12);
				REQUIRE(sut.findMinKey() == 3);
			}
		}
	}
}

SCENARIO("testing BST find method with int key and int data")
{
	GIVEN("empty BST")
	{
		auto sut = BST<int, int>();

		WHEN("find node with key 10")
		{
			auto result = sut.findNode(10);

			THEN("it should not found any node")
			{
				REQUIRE(result == nullptr);
			}
		}
	}

	GIVEN("BST with 10 as root and 5 and 12 as children")
	{
		auto sut = BST<int, int>();
		sut.insert(10,10);
		sut.insert(5,5);
		sut.insert(12,12);

		WHEN("find node with key 10")
		{
			auto result = sut.findNode(10);

			THEN("data of found node should be 10")
			{
				REQUIRE(result->data == 10);
			}
		}

		WHEN("find node with key 5")
		{
			auto result = sut.findNode(5);

			THEN("data of found node should be 5")
			{
				REQUIRE(result->data == 5);
			}
		}

		WHEN("find node with key 12")
		{
			auto result = sut.findNode(12);

			THEN("data of found node should be 12")
			{
				REQUIRE(result->data == 12);
			}
		}

		WHEN("find node with key 13")
		{
			auto result = sut.findNode(13);

			THEN("it should not found any node")
			{
				REQUIRE(result == nullptr);
			}
		}
	}
}

SCENARIO("testing BST remove method with int key and int data")
{
	GIVEN("BST with 10 as root and 5 and 12 as children")
	{
		auto sut = BST<int, int>();
		sut.insert(10,10);
		sut.insert(5,5);
		sut.insert(12,12);

		WHEN("remove node with key 5")
		{
			std::cout << "BEFORE: " << std::endl;
			sut.printInOrder();
			sut.remove(5);
			std::cout << "REMOVE (5): " << std::endl;
			sut.printInOrder();

			THEN("size of BST should be 2 and minKey should be 10")
			{
				REQUIRE(sut.size() == 2);
				REQUIRE(sut.findMinKey() == 10);
			}
		}

		WHEN("remove node with key 12 and maxKey should be 10")
		{
			std::cout << "BEFORE: " << std::endl;
			sut.printInOrder();
			sut.remove(12);
			std::cout << "REMOVE (12): " << std::endl;
			sut.printInOrder();

			THEN("size of BST should be 2")
			{
				REQUIRE(sut.size() == 2);
				REQUIRE(sut.findMaxKey() == 10);
			}
		}
	}

	GIVEN("BST with 10 as root and 5 and 12, 9, 3, 4, 2, 1")
	{
		auto sut = BST<int, int>();
		sut.insert(10,10);		//					10
		sut.insert(5,5);		//				5		12
		sut.insert(12,12);		//			3		9
		sut.insert(9,9);		//		2		4
		sut.insert(3,3);		//	1
		sut.insert(4,4);		//
		sut.insert(2,2);		//
		sut.insert(1,1);		//

		WHEN("remove node with key 5")
		{
			std::cout << "BEFORE: " << std::endl;
			sut.printInOrder();
			sut.remove(5);
			std::cout << "REMOVE (5): " << std::endl;
			sut.printInOrder();

			THEN("size of BST should be 7 and it should not find node with key 5, maxKey=12 and minKey=1")
			{
				REQUIRE(sut.size() == 7);
				REQUIRE(sut.findNode(5) == nullptr);
				REQUIRE(sut.findMaxKey() == 12);
				REQUIRE(sut.findMinKey() == 1);
			}
		}

		WHEN("remove node with key 1")
		{
			std::cout << "BEFORE: " << std::endl;
			sut.printInOrder();
			sut.remove(1);
			std::cout << "REMOVE (1): " << std::endl;
			sut.printInOrder();

			THEN("size of BST should be 7 and it should not find node with key 1, maxKey=12 and minKey=2")
			{
				REQUIRE(sut.size() == 7);
				REQUIRE(sut.findNode(1) == nullptr);
				REQUIRE(sut.findMaxKey() == 12);
				REQUIRE(sut.findMinKey() == 2);
			}
		}

		WHEN("remove node with key 10")
		{
			std::cout << "BEFORE: " << std::endl;
			sut.printInOrder();
			sut.remove(10);
			std::cout << "REMOVE (10): " << std::endl;
			sut.printInOrder();

			THEN("size of BST should be 7 and it should not find node with key 10, maxKey=12 and minKey=1")
			{
				REQUIRE(sut.size() == 7);
				REQUIRE(sut.findNode(10) == nullptr);
				REQUIRE(sut.findMaxKey() == 12);
				REQUIRE(sut.findMinKey() == 1);
			}
		}
	}
}

SCENARIO("testing BST depth method with int key and int data")
{
	GIVEN("empty BST")
	{
		auto sut = BST<int, int>();

		WHEN("not inserting anything")
		{
			THEN("depth of tree should be 0")
			{
				REQUIRE(sut.depth() == 0);
			}
		}

		WHEN("insert 10")
		{
			sut.insert(10, 10);

			THEN("depth of tree should be 1")
			{
				REQUIRE(sut.depth() == 1);
			}
		}

		WHEN("insert 10,9")
		{
			sut.insert(10,10);
			sut.insert(9,9);

			THEN("depth of tree should be 2")
			{
				REQUIRE(sut.depth() == 2);
			}
		}

		WHEN("insert 10,9,8,7,6,5,4,3,2,1")
		{
			sut.insert(10,10);
			sut.insert(9,9);
			sut.insert(8,8);
			sut.insert(7,7);
			sut.insert(6,6);
			sut.insert(5,5);
			sut.insert(4,4);
			sut.insert(3,3);
			sut.insert(2,2);
			sut.insert(1,1);

			THEN("depth of tree should be 10")
			{
				REQUIRE(sut.depth() == 10);
			}
		}

		WHEN("insert 10,5,12,9,3,4,2,1")
		{
			sut.insert(10,10);		//					10
			sut.insert(5,5);		//				5		12
			sut.insert(12,12);		//			3		9
			sut.insert(9,9);		//		2		4
			sut.insert(3,3);		//	1
			sut.insert(4,4);		//
			sut.insert(2,2);		//
			sut.insert(1,1);		//

			THEN("depth of tree should be 5")
			{
				REQUIRE(sut.depth() == 5);
			}
		}
	}
}

SCENARIO("testing BST constructor using algorithm Minimal Tree from Cracking Coding Interview")
{
	GIVEN("ordered array of 5 numbers")
	{
		int array[5] = {1,2,3,4,5};
		auto size = sizeof(array)/sizeof(array[0]);
		auto tree = BST<int, int>(array, size);

		WHEN("calling the algorithm")
		{
			std::cout << "tree should be 1,2,3,4,5" << std::endl;
			tree.printInOrder();

			THEN("depth of tree should be 3")
			{
				REQUIRE(tree.depth() == 3);
			}
		}
	}

	GIVEN("ordered array of 7 numbers")
	{
		int array[7] = {3,5,9,10,11,12,13};
		auto size = sizeof(array)/sizeof(array[0]);
		auto tree = BST<int, int>(array, size);

		WHEN("calling the algorithm")
		{
			std::cout << "tree should be 3,5,9,10,11,12,13" << std::endl;
			tree.printInOrder();

			THEN("depth of tree should be 3")
			{
				REQUIRE(tree.depth() == 3);
			}
		}
	}

	GIVEN("ordered array of 1 number")
	{
		int array[1] = {3};
		auto size = sizeof(array)/sizeof(array[0]);
		auto tree = BST<int, int>(array, size);

		WHEN("calling the algorithm")
		{
			std::cout << "tree should be 3" << std::endl;
			tree.printInOrder();

			THEN("depth of tree should be 1")
			{
				REQUIRE(tree.depth() == 1);
			}
		}
	}

	GIVEN("ordered array of 3 numbers")
	{
		int array[3] = {1,2,3};
		auto size = sizeof(array)/sizeof(array[0]);
		auto tree = BST<int, int>(array, size);

		WHEN("calling the algorithm")
		{
			std::cout << "tree should be 1,2,3" << std::endl;
			tree.printInOrder();

			THEN("depth of tree should be 2")
			{
				REQUIRE(tree.depth() == 2);
			}
		}
	}

	GIVEN("empty array")
	{
		int array[0] = {};
		auto size = sizeof(array)/sizeof(array[0]);
		auto tree = BST<int, int>(array, size);

		WHEN("calling the algorithm")
		{
			std::cout << "tree should be empty" << std::endl;
			tree.printInOrder();

			THEN("depth of tree should be 0")
			{
				REQUIRE(tree.depth() == 0);
			}
		}
	}
}

}  // namespace tests
}  // namespace bst
}  // namespace trees
}  // namespace dsc
