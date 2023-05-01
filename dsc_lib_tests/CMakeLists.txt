cmake_minimum_required(VERSION 3.23)

project("dsc_tests" VERSION 0.1 DESCRIPTION "Unit tests for dsc library")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED On)
set(CMAKE_CXX_EXTENSIONS Off)

set(UNIT_TEST_LIST
  Array
  BinarySearchTree
  BinaryTree
  Heap
  IncidenceMatrixGraph
  OrderedList
  UnorderedList
  Queue
  Stack
  DynamicStack
  Vector)

foreach(NAME IN LISTS UNIT_TEST_LIST)
  list(APPEND UNIT_TEST_SOURCE_LIST
    src/${NAME}Tests.cpp)
endforeach()

set(CMAKE_PREFIX_PATH "../dsc_lib/install/")
find_package(dsc CONFIG REQUIRED)

add_executable(${PROJECT_NAME}
  main.cpp
  ${UNIT_TEST_SOURCE_LIST})

target_sources(${PROJECT_NAME}
  PRIVATE
  main.cpp
)

# linking to the library, here you need to provide the namespace too
target_link_libraries(${PROJECT_NAME} PRIVATE dsc::dsc)

target_include_directories(${PROJECT_NAME}
  PUBLIC externals/catch2/)

add_test(
  NAME ${PROJECT_NAME}
  COMMAND ${PROJECT_NAME} -o report.xml -r junit)