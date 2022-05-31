cmake_minimum_required(VERSION 3.19)

set(CMAKE_CXX_STANDARD 20)

set(UNIT_TEST_LIST
#  Array
#  BinarySearchTree
#  BinaryTree
#  Heap
#  IncidenceMatrixGraph
#  OrderedList
#  UnorderedList
#  Queue
#  Stack
  DynamicStack
  Vector)
 
foreach(NAME IN LISTS UNIT_TEST_LIST)
  list(APPEND UNIT_TEST_SOURCE_LIST
    ${NAME}Tests.cpp)
endforeach()
 
set(TARGET_NAME dsc_tests)
 
add_executable(${TARGET_NAME}
  main.cpp
  ${UNIT_TEST_SOURCE_LIST})
 
target_link_libraries(${TARGET_NAME}
  PRIVATE dsclib)
 
target_include_directories(${TARGET_NAME}
  PUBLIC ../externals/catch2/)
 
add_test(
  NAME ${TARGET_NAME}
  COMMAND ${TARGET_NAME} -o report.xml -r junit)