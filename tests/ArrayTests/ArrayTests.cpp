#include <stdio.h>
#include "../../libs/catch.hpp"
#include "../../libs/fakeit.hpp"
#include "../../src/Array/Array.h"


namespace dsc::tests {

SCENARIO("testing Array container")
{
  GIVEN("int array of size 0")
  {
    auto sut = Array<int, 0>();

    THEN("size should be 0")
		{
			REQUIRE(sut.Size()  == 0);
    }
  }

	GIVEN("array of int of size 4")
	{
		auto sut = Array<int, 4>();

		WHEN("fill with ones as data")
		{
      sut.Fill(1);

			THEN("size should be 4 and all data should be 1")
			{
				REQUIRE(sut.Size()  == 4);
        REQUIRE(sut.Front() == 1);
        REQUIRE(sut.Back()  == 1);
        for(size_t i = 0; i < sut.Size(); ++i) 
          REQUIRE(sut[i] == 1);
			}

      THEN("at should return 1 for indeces 0,1,2,3 and throw out of range for index 4")
      {
        for(size_t i = 0; i < sut.Size(); ++i)
        {
          REQUIRE(sut.At(i) == 1);
        }

        REQUIRE_THROWS_AS( sut.At(4), std::logic_error);
      }
		}

    WHEN("fill with ones as data and fill first 2 elements with two")
		{
      sut.Fill(1);
      sut.Fill_n(2, 2);

			THEN("size should be 4 and first 2 elements should be equal to 2 and other elements to 1")
			{
				REQUIRE(sut.Size()  == 4);
        REQUIRE(sut.Front() == 2);
        REQUIRE(sut.Back()  == 1);
        for(size_t i = 0; i < 2; ++i) 
          REQUIRE(sut[i] == 2);
        for(size_t i = 2; i < 4; ++i) 
          REQUIRE(sut[i] == 1);
			}
		}

    WHEN("fill with increasing numbers starting from 0")
		{
      for(size_t i = 0; i < sut.Size(); ++i)
        sut[i] = i;

			THEN("range loop should gives numbers from 0 to Size - 1")
			{
        int testCounter = 0;
				for(auto elem : sut)
        {
          REQUIRE(elem == testCounter);
          ++testCounter;
        }
			}

      THEN("for loop should give numbers from 0 to Size - 1")
			{
        int testCounter = 0;
				for(size_t i = 0; i < sut.Size(); ++i)
        {
          REQUIRE(sut.At(i) == testCounter);
          ++testCounter;
        }
			}

      THEN("loop using iterators should give numbers from 0 to Size - 1")
			{
        int testCounter = 0;
				for(auto it = sut.begin(); it != sut.end(); ++it)
        {
          REQUIRE(*it == testCounter);
          ++testCounter;
        }
			}
		}
	}
}

}  // namespace dsc::tests