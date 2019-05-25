//
//  UnorderedSingleListTests.cpp
//  DSCTests
//
//  Created by Matej Tripsky on 06/04/2019.
//  Copyright © 2019 Matej Tripsky. All rights reserved.
//

#include <stdio.h>
#include "../../libs/catch.hpp"
#include "../../libs/fakeit.hpp"
#include "../../src/UnorderedList/node.h"
#include "../../src/UnorderedList/unordered_list.h"


namespace dsc{
namespace lists{
namespace tests{

SCENARIO( "testing UnorderedList Push method with int as data" ) {
    GIVEN( "empty list" ) {
        auto sut = UnorderedList<int>();

        WHEN( "do nothing" ) {
            THEN( "list size should be 0" ) {
                REQUIRE( sut.size() == 0);
            }
        }

        WHEN( "push data:1 into list" ) {
            auto result = sut.push(1);

            THEN( "list size should be 1" ) {
                REQUIRE( sut.size() == 1);
                REQUIRE( result == true);
            }
        }

        WHEN( "push data:1 and then data:2 into list" ) {
            sut.push(1);
            sut.push(2);

            THEN( "list size should be 2" ) {
                REQUIRE( sut.size() == 2);
            }
        }
    }
}

SCENARIO( "testing UnorderedList Pop method with int as data" ) {
    GIVEN( "empty list" ) {
        auto sut = UnorderedList<int>();

        WHEN( "pop from the list" ) {
            auto result = sut.pop();

            THEN( "it should not do anything" ) {
                REQUIRE( sut.size() == 0);
                REQUIRE( result == true);
            }
        }
    }

    GIVEN( " list with one node" ) {
        auto sut = UnorderedList<int>();
        sut.push(1);

        WHEN( "pop from the list" ) {
            auto result = sut.pop();

            THEN( "it should create empty list" ) {
                REQUIRE( sut.size() == 0);
                REQUIRE( result == true);
            }
        }
    }

    GIVEN( " list with two nodes" ) {
        auto sut = UnorderedList<int>();
        sut.push(1);
        sut.push(2);

        WHEN( "pop from the list" ) {
            auto result = sut.pop();

            THEN( "it should create list with one node (front: 1, back: 1)" ) {
                REQUIRE( sut.size() == 1);
                REQUIRE( sut.back()->data == 1);
                REQUIRE( sut.front()->data == 1);
                REQUIRE( result == true);
            }
        }
    }

    GIVEN( " list with three nodes" ) {
        auto sut = UnorderedList<int>();
        sut.push(1);
        sut.push(2);
        sut.push(3);

        WHEN( "pop from the list" ) {
            auto result = sut.pop();

            THEN( "it should create list with two nodes (front: 2, back: 1)" ) {
                REQUIRE( sut.size() == 2);
                REQUIRE( sut.back()->data == 1);
                REQUIRE( sut.front()->data == 2);
                REQUIRE( result == true);
            }
        }
    }
}

SCENARIO( "testing UnorderedList Remove method with int as data" ) {
    GIVEN( " list with one node" ) {
        auto sut = UnorderedList<int>();
        sut.push(1);

        WHEN( "remove data: 2 from the list" ) {
            auto result = sut.remove(2);

            THEN( "it should not remove anything and should return false" ) {
                REQUIRE( sut.size() == 1);
                REQUIRE( result == false);
            }
        }

        WHEN( "remove data: 1 from the list" ) {
            auto result = sut.remove(1);

            THEN( "it should remove node with data:1, should return true, and empty list" ) {
                REQUIRE( sut.size() == 0);
                REQUIRE( result == true);
            }
        }
    }

    GIVEN( " list with four nodes" ) {
        auto sut = UnorderedList<int>();  // 4->3->2->1
        sut.push(1);
        sut.push(2);
        sut.push(3);
        sut.push(4);

        std::cout << "BEFORE: " << std::endl;
        sut.print();

        WHEN( "remove data: 5 from the list" ) {
            auto result = sut.remove(5);

            std::cout << "After remove(5): " << std::endl;
            sut.print();

            THEN( "it should not remove anything and should return false (front: 4, back 1)" ) {
                REQUIRE( sut.size() == 4);
                REQUIRE( sut.back()->data == 1);
                REQUIRE( sut.front()->data == 4);
                REQUIRE( result == false);
            }
        }

        WHEN( "remove data: 1 from the list" ) {
            auto result = sut.remove(1);

            std::cout << "After remove(1): " << std::endl;
            sut.print();

            THEN( "it should remove node with data:1, should return true, and list with size 3 (front: 4, back 2)" ) {
                REQUIRE( sut.size() == 3);
                REQUIRE( sut.back()->data == 2);
                REQUIRE( sut.front()->data == 4);
                REQUIRE( result == true);
            }
        }

        WHEN( "remove data: 2 from the list" ) {
            auto result = sut.remove(2);

            std::cout << "After remove(2): " << std::endl;
            sut.print();

            THEN( "it should remove node with data:2, should return true, and list with size 3 (front: 4, back 1)" ) {
                REQUIRE( sut.size() == 3);
                REQUIRE( sut.back()->data == 1);
                REQUIRE( sut.front()->data == 4);
                REQUIRE( result == true);
            }
        }

        WHEN( "remove data: 3 from the list" ) {
            auto result = sut.remove(3);

            std::cout << "After remove(3): " << std::endl;
            sut.print();

            THEN( "it should remove node with data:3, should return true, and list with size 3 (front: 4, back 1)" ) {
                REQUIRE( sut.size() == 3);
                REQUIRE( sut.back()->data == 1);
                REQUIRE( sut.front()->data == 4);
                REQUIRE( result == true);
            }
        }

        WHEN( "remove data: 4 from the list" ) {
            auto result = sut.remove(4);

            std::cout << "After remove(4): " << std::endl;
            sut.print();

            THEN( "it should remove node with data:4, should return true, and list with size 3 (front: 3, back 1)" ) {
                REQUIRE( sut.size() == 3);
                REQUIRE( sut.back()->data == 1);
                REQUIRE( sut.front()->data == 3);
                REQUIRE( result == true);
            }
        }
    }
}

SCENARIO( "testing UnorderedList Front method with int as data" ) {
    GIVEN( "empty list" ) {
        auto sut = UnorderedList<int>();

        WHEN( "push data:1 into list" ) {
            sut.push(1);
            auto result = sut.front();

            THEN( "front should return node with data = 1" ) {
                REQUIRE( result->data == 1);
            }
        }

        WHEN( "push data:1 and then data:2 into list" ) {
            sut.push(1);
            sut.push(2);
            auto result = sut.front();

            THEN( "front should return node with data = 2") {
                REQUIRE( result->data == 2);
            }
        }

        WHEN( "push data:1, then data:2 and then data:3 into list" ) {
            sut.push(1);
            sut.push(2);
            sut.push(3);
            auto result = sut.front();

            THEN( "front should return node with data = 3") {
                REQUIRE( result->data == 3);
            }
        }
    }
}

SCENARIO( "testing UnorderedList Back method with int as data" ) {
    GIVEN( "empty list" ) {
        auto sut = UnorderedList<int>();

        WHEN( "push data:1 into list" ) {
            sut.push(1);
            auto result = sut.back();

            THEN( "back should return node with data = 1" ) {
                REQUIRE( result->data == 1);
            }
        }

        WHEN( "push data:1 and then data:2 into list" ) {
            sut.push(1);
            sut.push(2);
            auto result = sut.back();

            THEN( "back should return node with data = 1") {
                REQUIRE( result->data == 1);
            }
        }

        WHEN( "push data:1, then data:2 and then data:3 into list" ) {
            sut.push(1);
            sut.push(2);
            sut.push(3);
            auto result = sut.back();

            THEN( "front should return node with data = 1") {
                REQUIRE( result->data == 1);
            }
        }
    }
}

SCENARIO( "testing UnorderedList Front and Back methods with int as data" ) {
    GIVEN( "empty list" ) {
        auto sut = UnorderedList<int>();

        WHEN( "push data:1 into list" ) {
            sut.push(1);
            auto resultFront = sut.front();
            auto resultBack = sut.back();

            THEN( "back and front should return node with data = 1" ) {
                REQUIRE( resultFront->data == 1);
                REQUIRE( resultBack->data == 1);
            }
        }

        WHEN( "push data:1 and then data:2 into list" ) {
            sut.push(1);
            sut.push(2);
            auto resultFront = sut.front();
            auto resultBack = sut.back();

            THEN( "back should return node with data = 1 and front with data = 2" ) {
                REQUIRE( resultFront->data == 2);
                REQUIRE( resultBack->data == 1);
            }
        }

        WHEN( "push data:1, then data:2 and then data:3 into list" ) {
            sut.push(1);
            sut.push(2);
            sut.push(3);
            auto resultFront = sut.front();
            auto resultBack = sut.back();

            THEN( "back should return node with data = 1 and front with data = 3" ) {
                REQUIRE( resultFront->data == 3);
                REQUIRE( resultBack->data == 1);
            }
        }
    }
}

}  // namespace tests
}  // namespace lists
}  // namespace dsc
