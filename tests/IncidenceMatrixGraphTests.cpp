#include "catch.hpp"
#include "Graphs/IncidenceMatrixGraph.h"
#include <stdio.h>

namespace dsc::tests {

SCENARIO("testing Graph add_vertex with int as verticies")
{
  GIVEN("graph")
  {
    auto sut = IncidenceMatrixGraph<int, int>();

    WHEN("do nothing")
    {
      THEN("size of vertices in graph should be 0") { REQUIRE(sut.size() == 0); }
    }

    WHEN("add_vertex 0")
    {
      sut.add_vertex(0);

      THEN("size of vertices in graph should be 1") { REQUIRE(sut.size() == 1); }
    }

    WHEN("add_vertex 0 and 1")
    {
      sut.add_vertex(0);
      sut.add_vertex(1);

      THEN("size of vertices in graph should be 2") { REQUIRE(sut.size() == 2); }
    }

    WHEN("add_vertex 0 and 1 with edgesToItself")
    {
      sut.add_vertex(0, true);
      sut.add_vertex(1, true);

      THEN("size of vertices in graph should be 2") { REQUIRE(sut.size() == 2); }
    }

    WHEN("add_vertex 0, 1, 2 with edgesToItself false for vertice 2")
    {
      sut.add_vertex(0, true);
      sut.add_vertex(1, true);
      sut.add_vertex(2);

      THEN("size of vertices in graph should be 3") { REQUIRE(sut.size() == 3); }
    }
  }
}

SCENARIO("testing Graph remove_vertex with int as verticies")
{
  GIVEN("graph with 4 vertices")
  {
    auto sut = IncidenceMatrixGraph<int, int>();
    sut.add_vertex(0, true);
    sut.add_vertex(1, true);
    sut.add_vertex(2, true);
    sut.add_vertex(3, true);

    WHEN("remove vertex 4")
    {
      auto result = sut.remove_vertex(4);

      THEN("nothing should be removed")
      {
        REQUIRE_FALSE(result);
        REQUIRE(sut.size() == 4);
      }
    }

    WHEN("remove vertex 0")
    {
      sut.remove_vertex(0);

      THEN("size of vertices in graph should be 3") { REQUIRE(sut.size() == 3); }
    }

    WHEN("remove vertex 1 and then 2")
    {
      sut.remove_vertex(1);
      sut.remove_vertex(2);

      THEN("size of vertices in graph should be 2") { REQUIRE(sut.size() == 2); }
    }
  }
}

SCENARIO("testing Graph methods: add_edge and neighbors with int as verticies")
{
  GIVEN("graph with 4 vertices")
  {
    auto sut = IncidenceMatrixGraph<int, int>();
    sut.add_vertex(0, true);
    sut.add_vertex(1, true);
    sut.add_vertex(2, true);
    sut.add_vertex(3, true);

    WHEN("add single edge between 0 and 1")
    {
      sut.add_edge(0, 1);
      auto neighbors_Node0 = sut.neighbors(0);
      auto neighbors_Node1 = sut.neighbors(1);

      THEN("node 0 should have 2 neighbors and node 1 should have only itself")
      {
        REQUIRE(neighbors_Node0.size() == 2);
        REQUIRE(neighbors_Node0[0] == 0);
        REQUIRE(neighbors_Node0[1] == 1);
        REQUIRE(neighbors_Node1.size() == 1);
        REQUIRE(neighbors_Node1[0] == 1);
      }
    }

    WHEN("add double edge between 0 and 1")
    {
      sut.add_edge(0, 1, true);
      auto neighbors_Node0 = sut.neighbors(0);
      auto neighbors_Node1 = sut.neighbors(1);

      THEN("node 0 should have 2 neighbors (0,1) and node 1 should have 2 neighbors (0,1)")
      {
        REQUIRE(neighbors_Node0.size() == 2);
        REQUIRE(neighbors_Node0[0] == 0);
        REQUIRE(neighbors_Node0[1] == 1);
        REQUIRE(neighbors_Node1.size() == 2);
        REQUIRE(neighbors_Node1[0] == 0);
        REQUIRE(neighbors_Node1[1] == 1);
      }
    }

    WHEN("add double edge between 0 and 2, single 0 and 1")
    {
      sut.add_edge(0, 1);
      sut.add_edge(0, 2, true);
      auto neighbors_Node0 = sut.neighbors(0);
      auto neighbors_Node1 = sut.neighbors(1);
      auto neighbors_Node2 = sut.neighbors(2);

      THEN("node 0 should have 3 neighbors (0,1,2) and node 1 should have 1 neighbor (1) and node "
           "2 should have 2 neighbors (0,2)")
      {
        REQUIRE(neighbors_Node0.size() == 3);
        REQUIRE(neighbors_Node0[0] == 0);
        REQUIRE(neighbors_Node0[1] == 1);
        REQUIRE(neighbors_Node0[2] == 2);
        REQUIRE(neighbors_Node1.size() == 1);
        REQUIRE(neighbors_Node1[0] == 1);
        REQUIRE(neighbors_Node2.size() == 2);
        REQUIRE(neighbors_Node2[0] == 0);
        REQUIRE(neighbors_Node2[1] == 2);
      }
    }

    WHEN("add double edge between 0 and 2, single 0 and 1 and then remove vertex 2")
    {
      sut.add_edge(0, 1);
      sut.add_edge(0, 2, true);
      sut.remove_vertex(2);
      auto neighbors_Node0 = sut.neighbors(0);
      auto neighbors_Node1 = sut.neighbors(1);

      THEN("node 0 should have 2 neighbors (0,1) and node 1 should have 1 neighbor (1)")
      {
        REQUIRE(neighbors_Node0.size() == 2);
        REQUIRE(neighbors_Node0[0] == 0);
        REQUIRE(neighbors_Node0[1] == 1);
        REQUIRE(neighbors_Node1.size() == 1);
        REQUIRE(neighbors_Node1[0] == 1);
      }
    }
  }
}

SCENARIO("testing Graph method adjacent with int as verticies")
{
  GIVEN("graph with 4 vertices ")
  {
    auto sut = IncidenceMatrixGraph<int, int>();
    sut.add_vertex(0, false);
    sut.add_vertex(1, true);
    sut.add_vertex(2, false);
    sut.add_vertex(3, false);

    WHEN("edges (0-1, 0-2, 2-3, 3-2, 1-1)")
    {
      sut.add_edge(0, 1);
      sut.add_edge(0, 2);
      sut.add_edge(2, 3, true);

      THEN("(0-1, 0-2, 2-3, 3-2, 1-1) should be adjacent and rest not")
      {
        REQUIRE(sut.adjacent(0, 1));
        REQUIRE(sut.adjacent(0, 2));
        REQUIRE_FALSE(sut.adjacent(0, 3));
        REQUIRE_FALSE(sut.adjacent(1, 0));
        REQUIRE_FALSE(sut.adjacent(2, 0));
        REQUIRE_FALSE(sut.adjacent(3, 0));
        REQUIRE(sut.adjacent(2, 3));
        REQUIRE(sut.adjacent(3, 2));
        REQUIRE(sut.adjacent(1, 1));
      }
    }
  }
}

SCENARIO("testing Graph methods: remove_edge and neighbors with int as verticies")
{
  GIVEN("graph with 4 vertices and edges to itself and edges (0,1),(0,2),(2,0)")
  {
    auto sut = IncidenceMatrixGraph<int, int>();
    sut.add_vertex(0, true);
    sut.add_vertex(1, true);
    sut.add_vertex(2, true);
    sut.add_vertex(3, true);
    sut.add_edge(0, 1);
    sut.add_edge(0, 2, true);

    WHEN("remove edge (1,1)")
    {
      sut.remove_edge(1, 1);
      auto neighbors_Node1 = sut.neighbors(1);

      THEN("node 1 has no neighbors") { REQUIRE(neighbors_Node1.size() == 0); }
    }

    WHEN("remove edge (0, 1)")
    {
      sut.remove_edge(0, 1);
      auto neighbors_Node0 = sut.neighbors(0);

      THEN("node 0 should have 2 neighbors (0,2)")
      {
        REQUIRE(neighbors_Node0.size() == 2);
        REQUIRE(neighbors_Node0[0] == 0);
        REQUIRE(neighbors_Node0[1] == 2);
      }
    }

    WHEN("remove edge (2, 0)")
    {
      sut.remove_edge(2, 0);
      auto neighbors_Node0 = sut.neighbors(0);
      auto neighbors_Node2 = sut.neighbors(2);

      THEN("node 0 should have 3 neighbors (0,1,2) and node 2 should have 1 neighbor (2)")
      {
        REQUIRE(neighbors_Node0.size() == 3);
        REQUIRE(neighbors_Node0[0] == 0);
        REQUIRE(neighbors_Node0[1] == 1);
        REQUIRE(neighbors_Node0[2] == 2);
        REQUIRE(neighbors_Node2.size() == 1);
        REQUIRE(neighbors_Node2[0] == 2);
      }
    }

    WHEN("remove edge (2, 0) in both directions")
    {
      sut.remove_edge(2, 0, true);
      auto neighbors_Node0 = sut.neighbors(0);
      auto neighbors_Node2 = sut.neighbors(2);

      THEN("node 0 should have 2 neighbors (0,1) and node 2 should have 1 neighbor (2)")
      {
        REQUIRE(neighbors_Node0.size() == 2);
        REQUIRE(neighbors_Node0[0] == 0);
        REQUIRE(neighbors_Node0[1] == 1);
        REQUIRE(neighbors_Node2.size() == 1);
        REQUIRE(neighbors_Node2[0] == 2);
      }
    }
  }
}

SCENARIO("testing Graph methods: get_vertex_value with int as verticies")
{
  GIVEN("graph with 3 vertices")
  {
    auto sut = IncidenceMatrixGraph<int, int>();
    sut.add_vertex(0);
    sut.add_vertex(1);
    sut.add_vertex(2);

    WHEN("get vertex value of node 0")
    {
      auto result = sut.get_vertex_value(0);

      THEN("node 0 value is 0") { REQUIRE(result == 0); }
    }

    WHEN("get vertex value of node 1")
    {
      auto result = sut.get_vertex_value(1);

      THEN("node 1 value is 1") { REQUIRE(result == 1); }
    }

    WHEN("get vertex value of node 2")
    {
      auto result = sut.get_vertex_value(2);

      THEN("node 2 value is 2") { REQUIRE(result == 2); }
    }
  }
}

SCENARIO("testing Graph methods: set_vertex_value with int as verticies")
{
  GIVEN("graph with 3 vertices")
  {
    auto sut = IncidenceMatrixGraph<int, int>();
    sut.add_vertex(0);
    sut.add_vertex(1);
    sut.add_vertex(2);

    WHEN("set vertex value of node 0 to 100")
    {
      sut.set_vertex_value(0, 100);
      auto result = sut.get_vertex_value(0);

      THEN("node 0 value is 100") { REQUIRE(result == 100); }
    }

    WHEN("set vertex value of node 1 to 200")
    {
      sut.set_vertex_value(1, 200);
      auto result = sut.get_vertex_value(1);

      THEN("node 1 value is 200") { REQUIRE(result == 200); }
    }

    WHEN("set vertex value of node 2 to 300")
    {
      sut.set_vertex_value(2, 300);
      auto result = sut.get_vertex_value(2);

      THEN("node 2 value is 300") { REQUIRE(result == 300); }
    }
  }
}

SCENARIO("testing Graph methods: set_edge_value and get_edge_value with int as verticies")
{
  GIVEN("graph with 3 vertices with edges (0,1),(0,2),(2,1)")
  {
    auto sut = IncidenceMatrixGraph<int, int>();
    sut.add_vertex(0, true);
    sut.add_vertex(1, true);
    sut.add_vertex(2, true);
    sut.add_edge(0, 1);
    sut.add_edge(0, 2);
    sut.add_edge(2, 1);

    WHEN("set edge values between node itself to -1,-2,-3")
    {
      sut.set_edge_value(0, 0, -1);
      sut.set_edge_value(1, 1, -2);
      sut.set_edge_value(2, 2, -3);
      auto result0 = sut.get_edge_value(0, 0);
      auto result1 = sut.get_edge_value(1, 1);
      auto result2 = sut.get_edge_value(2, 2);

      THEN("result0,1,2 should be -1,-2,-3")
      {
        REQUIRE(result0 == -1);
        REQUIRE(result1 == -2);
        REQUIRE(result2 == -3);
      }
    }

    WHEN("set edge values between (0,1) to 100")
    {
      sut.set_edge_value(0, 1, 100);
      auto result0 = sut.get_edge_value(0, 1);

      THEN("result should be 100") { REQUIRE(result0 == 100); }
    }

    WHEN("set edge values between (0,2) to 200")
    {
      sut.set_edge_value(0, 2, 200);
      auto result0 = sut.get_edge_value(0, 2);

      THEN("result should be 200") { REQUIRE(result0 == 200); }
    }

    WHEN("set edge values between (2,1) to 300")
    {
      sut.set_edge_value(2, 1, 300);
      auto result0 = sut.get_edge_value(2, 1);

      THEN("result should be 300") { REQUIRE(result0 == 300); }
    }
  }
}

} // namespace dsc::tests
