#ifndef Graphs_IncidenceMatrix_h
#define Graphs_IncidenceMatrix_h

#include <iostream>
#include <vector>


namespace dsc {
namespace graphs {
namespace incmatrix {

// =============================================================================
// GRAPH INCIDENCE MATRIX
// =============================================================================

template<typename T, typename M>
class Graph {
public:
    // -------------------------------------------------------------------------
	// CONSTRUCTORS
	// -------------------------------------------------------------------------
	Graph() noexcept :
		m_adjecentMatrix(0, std::vector<bool>(0)),
		m_edgeValueMatrix(0, std::vector<M>(0)),
		m_vertices(std::vector<T>(0))
	{
    }

    // -------------------------------------------------------------------------
	// METHODS
	// -------------------------------------------------------------------------
    // tests whether there is an edge from the vertex x to the vertex y
    const bool adjacent(const int x, const int y) const;
    // lists all vertices y such that there is an edge from the vertex x to the vertex y
    std::vector<T> neighbors(const int x) const;
    // adds the vertex x, if it is not there
    bool add_vertex(const T& x, bool withEdgeToItself = false);
    // removes the vertex x, if it is there
    bool remove_vertex(const int x);
    // adds the edge from the vertex x to the vertex y, if it is not there
    bool add_edge(const int x, const int y, bool inBothDirection = false);
    // removes the edge from the vertex x to the vertex y, if it is there
    bool remove_edge(const int x, const int y, bool inBothDirection = false);
    // returns the value as sociated with the vertex x
    const T get_vertex_value(const int x) const;
    // sets the value associated with the vertex x to v
    bool set_vertex_value(const int x, const T& v);
    // returns the value associated with the edge (x, y)
    const M get_edge_value(const int x, const int y) const;
    // sets the value associated with the edge (x, y) to v
    bool set_edge_value(const int x, const int y, const M& v);
	// prints adjacentMatrix
	void printMatrix();

	const size_t size() const
	{
		return m_vertices.size();
	}

private:
    std::vector<std::vector<bool>> m_adjecentMatrix;
	std::vector<std::vector<M>> m_edgeValueMatrix;
	std::vector<T> m_vertices;
};

}  // namespace incmatrix
}  // namespace graphs
}  // namespace dsc

#include "graph.cpp"

#endif  // Graphs_IncidenceMatrix_h
