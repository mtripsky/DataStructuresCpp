#include <stdio.h>
#include <vector>
#include "../../libs/catch.hpp"
#include "../../libs/fakeit.hpp"
#include "../../src/Trees/node.h"
#include "../../src/Trees/BinaryTree.h"

namespace dsc {
namespace trees {
namespace tests {

SCENARIO("testing Binary Tree")
{
	GIVEN("empty Binary Tree of int")
	{
		auto sut = BinaryTree<int>();

		WHEN("inserting 1, 2, 4, 5, 6, 7, 8, 9")
		{
			sut.insert(1);
			// sut.printTreeStructure();
			sut.insert(2);
			// sut.printTreeStructure();
			sut.insert(3);
			// sut.printTreeStructure();
			sut.insert(4);
			// sut.printTreeStructure();
			sut.insert(5);
			// sut.printTreeStructure();
			sut.insert(6);
			// sut.printTreeStructure();
			sut.insert(7);
			// sut.printTreeStructure();
			sut.insert(8);
			//sut.printTreeStructure();
			sut.insert(9);
			//sut.printTreeStructure();
			sut.printBreadthFirst();

			THEN("size should be 9")
			{
				REQUIRE(sut.size() == 9);
			}
		}
    }

	GIVEN("empty Binary Tree of char")
	{
		auto sut = BinaryTree<char>();

		WHEN("inserting char from a text")
		{
			const std::string text = "This is testing text for breadth-first printing in Binary tree.";
			for(char const &c : text)
			{
				sut.insert(c);
			}
			sut.printBreadthFirst();

			THEN("size should be ")
			{
				REQUIRE(sut.size() == text.length());
			}
		}
    }
}

}
}
}
