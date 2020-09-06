#include <stdio.h>
#include "../../libs/catch.hpp"
#include "../../libs/fakeit.hpp"
#include "../../src/Array/array.h"


namespace dsc::tests {

SCENARIO("testing Array container")
{
	GIVEN("array of int of size 4")
	{
		auto sut = Array<int, 4>();

		WHEN("fill with ones as data")
		{
      sut.fill(1);

			THEN("size should be 4 and all data should be 1")
			{
				REQUIRE(sut.size()  == 4);
        REQUIRE(sut.front() == 1);
        REQUIRE(sut.back()  == 1);
        for(size_t i = 0; i < sut.size(); ++i) 
          REQUIRE(sut[i] == 1);
			}

      THEN("at should return 1 for indeces 0,1,2,3 and throw out of range for index 4")
      {
        for(size_t i = 0; i < sut.size(); ++i)
        {
          REQUIRE(sut.at(i) == 1);
        }

        REQUIRE_THROWS_AS( sut.at(4), std::logic_error);
      }
		}

    WHEN("fill with ones as data and fill first 2 elements with two")
		{
      sut.fill(1);
      sut.fill_n(2, 2);

			THEN("size should be 4 and first 2 elements should be equal to 2 and other elements to 1")
			{
				REQUIRE(sut.size()  == 4);
        REQUIRE(sut.front() == 2);
        REQUIRE(sut.back()  == 1);
        for(size_t i = 0; i < 2; ++i) 
          REQUIRE(sut[i] == 2);
        for(size_t i = 2; i < 4; ++i) 
          REQUIRE(sut[i] == 1);
			}
		}

    WHEN("fill with increasing numbers starting from 0")
		{
      for(size_t i = 0; i < sut.size(); ++i)
        sut[i] = i;

			THEN("range loop should gives numbers from 0 to Size - 1")
			{
        int testCounter = 0;
				for(const auto& elem : sut)
        {
          REQUIRE(elem == testCounter);
          ++testCounter;
        }
			}

      THEN("for loop should give numbers from 0 to Size - 1")
			{
        int testCounter = 0;
				for(size_t i = 0; i < sut.size(); ++i)
        {
          REQUIRE(sut.at(i) == testCounter);
          ++testCounter;
        }
			}
		}
	}
}

}  // namespace dsc::tests