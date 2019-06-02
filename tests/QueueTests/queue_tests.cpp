#include <stdio.h>
#include <vector>
#include "../../libs/catch.hpp"
#include "../../libs/fakeit.hpp"
#include "../../src/Queue/queue.h"


namespace dsc {
namespace fifo {
namespace tests {

SCENARIO("testing Queue constructor with int as data")
{
	GIVEN("constructing  queue of maxSize 2")
	{
		auto sut = Queue<int>(2);

		WHEN("do nothing")
		{
			THEN("size should be 0")
			{
				REQUIRE(sut.size() == 0);
			}
		}
	}
}

SCENARIO("testing Queue enqueue with int as data")
{
	GIVEN("constructing  queue of size 2")
	{
		auto sut = Queue<int>(2);

		WHEN("enqueue 1")
		{
			auto result1 = sut.enqueue(1);

			THEN("size should be 1 and front element should be 1")
			{
				REQUIRE(sut.size() == 1);
				REQUIRE(sut.front() == 1);
				REQUIRE(result1);
			}
		}

		WHEN("enqueue 1 and then 2")
		{
			auto result1 = sut.enqueue(1);
			auto result2 = sut.enqueue(2);

			THEN("size should be 2 and front element should be 1")
			{
				REQUIRE(sut.size() == 2);
				REQUIRE(sut.front() == 1);
				REQUIRE(result1);
				REQUIRE(result2);
			}
		}

		WHEN("enqueue 1, 2 and then 3")
		{
			auto result1 = sut.enqueue(1);
			auto result2 = sut.enqueue(2);
			auto result3 = sut.enqueue(3);

			THEN("size should be 2 and front element should be 1 and last enqueue should be false "
				 "and queue should be full")
			{
				REQUIRE(sut.size() == 2);
				REQUIRE(sut.front() == 1);
				REQUIRE(result1);
				REQUIRE(result2);
				REQUIRE_FALSE(result3);
				REQUIRE(sut.isFull());
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
			auto result1 = sut.dequeue();

			THEN("dequeue methods should return false size should be 0")
			{
				REQUIRE(sut.size() == 0);
				REQUIRE_FALSE(result1);
			}
		}

		WHEN("enqueue from queue containing 1 and 2 (in order)")
		{
			sut.enqueue(1);
			sut.enqueue(2);
			auto result1 = sut.dequeue();

			THEN("size should be 1 and front element should be 2")
			{
				REQUIRE(sut.size() == 1);
				REQUIRE(sut.front() == 2);
				REQUIRE(result1);
			}
		}

		WHEN("enqueue three times from queue containing 1 and 2 (in order)")
		{
			sut.enqueue(1);
			sut.enqueue(2);
			auto result1 = sut.dequeue();
			auto result2 = sut.dequeue();
			auto result3 = sut.dequeue();

			THEN("size should be 0 and front should throw exception and last enqueue should be "
				 "false and queue should be empty")
			{
				REQUIRE(sut.size() == 0);
				REQUIRE_THROWS_WITH(sut.front(), "Queue is empty");
				REQUIRE(result1);
				REQUIRE(result2);
				REQUIRE_FALSE(result3);
				REQUIRE(sut.isEmpty());
			}
		}
	}
}

SCENARIO("testing Queue dequeue and enqueue to test circular buffer with int as data")
{
	GIVEN("constructing  queue of size 4 containing 1, 2, 3, 4 (in order)")
	{
		auto sut = Queue<int>(4);
		sut.enqueue(1);
		sut.enqueue(2);
		sut.enqueue(3);
		sut.enqueue(4);
		std::cout << "Queue BEFORE: " << std::endl;
		sut.print();

		WHEN("dequeue from queue and then queue 5 ")
		{
			sut.dequeue();
			sut.enqueue(5);
			std::cout << "Queue AFTER dequeue and enqueu(5): " << std::endl;
			sut.print();

			THEN("size should be 4, queue is full and front element should be 2")
			{
				REQUIRE(sut.size() == 4);
				REQUIRE(sut.isFull());
				REQUIRE_FALSE(sut.isEmpty());
				REQUIRE(sut.front() == 2);
			}
		}

		WHEN("dequeue from queue twice and then queue 5 and 6")
		{
			sut.dequeue();
			sut.enqueue(5);
			sut.dequeue();
			sut.enqueue(6);

			std::cout << "Queue AFTER twice dequeue and enqueu(5) and enqueu(6): " << std::endl;
			sut.print();

			THEN("size should be 4, queue is full and front element should be 3")
			{
				REQUIRE(sut.size() == 4);
				REQUIRE(sut.isFull());
				REQUIRE_FALSE(sut.isEmpty());
				REQUIRE(sut.front() == 3);
			}
		}

		WHEN("dequeue from queue three times and then queue 5 and 6")
		{
			sut.dequeue();
			sut.enqueue(5);
			sut.dequeue();
			sut.dequeue();
			sut.enqueue(6);

			std::cout << "Queue AFTER three times dequeue and enqueu(5, 6): " << std::endl;
			sut.print();

			THEN("size should be 3, queue is not full and front element should be 4")
			{
				REQUIRE(sut.size() == 3);
				REQUIRE_FALSE(sut.isFull());
				REQUIRE_FALSE(sut.isEmpty());
				REQUIRE(sut.front() == 4);
			}
		}

		WHEN("dequeue from queue four times and then queue 5, 6, 7, 8")
		{
			sut.dequeue();
			sut.dequeue();
			sut.dequeue();
			sut.dequeue();
			sut.enqueue(5);
			sut.enqueue(6);
			sut.enqueue(7);
			sut.enqueue(8);

			std::cout << "Queue AFTER four times dequeue and enqueu(5, 6, 7, 8): " << std::endl;
			sut.print();

			THEN("size should be 4, queue is full and front element should be 5")
			{
				REQUIRE(sut.size() == 4);
				REQUIRE(sut.isFull());
				REQUIRE_FALSE(sut.isEmpty());
				REQUIRE(sut.front() == 5);
			}
		}
	}
}

SCENARIO("testing Queue dequeue and enqueue and order of front elements")
{
	GIVEN("constructing  queue of size 4 containing 1, 2, 3, 4 (in order)")
	{
		auto sut = Queue<int>(4);
		sut.enqueue(1);
		sut.enqueue(2);
		sut.enqueue(3);
		sut.enqueue(4);
		auto testOrderVector = std::vector<int>();

		WHEN("dequeue from queue and then queue 5 ")
		{
			sut.dequeue();
			sut.enqueue(5);

			while(!sut.isEmpty()) {
				testOrderVector.push_back(sut.front());
				sut.dequeue();
			}

			auto expectedOrderVector = std::vector<int>{2, 3, 4, 5};

			THEN("testOrderVector should match expectedOrderVector {2,3,4,5}")
			{
				REQUIRE(testOrderVector == expectedOrderVector);
			}
		}

		WHEN("dequeue from queue twice and then queue 5 and 6")
		{
			sut.dequeue();
			sut.enqueue(5);
			sut.dequeue();
			sut.enqueue(6);

			while(!sut.isEmpty()) {
				testOrderVector.push_back(sut.front());
				sut.dequeue();
			}

			auto expectedOrderVector = std::vector<int>{3, 4, 5, 6};

			THEN("testOrderVector should match expectedOrderVector {3,4,5,6}")
			{
				REQUIRE(testOrderVector == expectedOrderVector);
			}
		}

		WHEN("dequeue from queue three times and then queue 5 and 6")
		{
			sut.dequeue();
			sut.enqueue(5);
			sut.dequeue();
			sut.dequeue();
			sut.enqueue(6);

			while(!sut.isEmpty()) {
				testOrderVector.push_back(sut.front());
				sut.dequeue();
			}

			auto expectedOrderVector = std::vector<int>{4, 5, 6};

			THEN("testOrderVector should match expectedOrderVector {4,5,6}")
			{
				REQUIRE(testOrderVector == expectedOrderVector);
			}
		}

		WHEN("dequeue from queue four times and then queue 5, 6, 7, 8")
		{
			sut.dequeue();
			sut.dequeue();
			sut.dequeue();
			sut.dequeue();
			sut.enqueue(5);
			sut.enqueue(6);
			sut.enqueue(7);
			sut.enqueue(8);

			while(!sut.isEmpty()) {
				testOrderVector.push_back(sut.front());
				sut.dequeue();
			}

			auto expectedOrderVector = std::vector<int>{5, 6, 7, 8};

			THEN("testOrderVector should match expectedOrderVector {5,6,7,8}")
			{
				REQUIRE(testOrderVector == expectedOrderVector);
			}
		}
	}
}

}  // namespace tests
}  // namespace fifo
}  // namespace dsc
