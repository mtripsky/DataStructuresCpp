cmake_minimum_required(VERSION 3.19)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS_DEBUG "-g -DDEBUG")

add_executable(dsc_tests main.cpp 
    ArrayTests.cpp 
    BinarySearchTreeTests.cpp 
    BinaryTreeTests.cpp 
    HeapTests.cpp 
    IncidenceMatrixGraphTests.cpp 
    OrderedListTests.cpp 
    UnorderedListTests.cpp 
    QueueTests.cpp 
    StackTests.cpp 
    DynamicStackTests.cpp
    VectorTests.cpp)
target_link_libraries(dsc_tests PRIVATE dsclib)
