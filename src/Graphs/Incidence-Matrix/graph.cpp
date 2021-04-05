#include "graph.h"

template <typename T, typename M>
const bool dsc::graphs::incmatrix::Graph<T, M>::adjacent(const int x, const int y) const
{
  if (x < size() && y < size())
    return m_adjecentMatrix[x][y];

  return false;
}

template <typename T, typename M>
bool dsc::graphs::incmatrix::Graph<T, M>::add_vertex(const T& x, bool withEdgeToItself)
{
  for (auto i = 0; i < size(); ++i) {
    m_adjecentMatrix[i].push_back(false);
    m_edgeValueMatrix[i].resize(size() + 1);
  }

  m_vertices.push_back(x);
  m_adjecentMatrix.push_back(std::vector<bool>(size(), false));

  auto edgeValues = std::vector<M>();
  edgeValues.resize(size());
  m_edgeValueMatrix.push_back(edgeValues);

  if (withEdgeToItself) {
    m_adjecentMatrix.back()[m_vertices.size() - 1] = true;
  }

  return true;
}

template <typename T, typename M>
bool dsc::graphs::incmatrix::Graph<T, M>::remove_vertex(const int x)
{
  if (x < size()) {
    m_adjecentMatrix.erase(m_adjecentMatrix.begin() + x);
    m_edgeValueMatrix.erase(m_edgeValueMatrix.begin() + x);

    for (auto i = 0; i < size() - 1; ++i) {
      m_adjecentMatrix[i].erase(m_adjecentMatrix[i].begin() + x);
      m_edgeValueMatrix[i].erase(m_edgeValueMatrix[i].begin() + x);
    }

    m_vertices.erase(m_vertices.begin() + x);

    return true;
  }

  return false;
}

template <typename T, typename M>
std::vector<T> dsc::graphs::incmatrix::Graph<T, M>::neighbors(const int x) const
{
  auto result = std::vector<T>();

  for (auto i = 0; i < m_vertices.size(); ++i) {
    if (m_adjecentMatrix[x][i]) {
      result.push_back(m_vertices[i]);
    }
  }

  return result;
}

template <typename T, typename M>
bool dsc::graphs::incmatrix::Graph<T, M>::add_edge(const int x, const int y, bool inBothDirection)
{
  if (x < size() && y < size()) {
    m_adjecentMatrix[x][y] = true;
    if (inBothDirection) {
      m_adjecentMatrix[y][x] = true;
    }

    return true;
  }

  return false;
}

template <typename T, typename M>
bool dsc::graphs::incmatrix::Graph<T, M>::remove_edge(const int x, const int y,
                                                      bool inBothDirection)
{
  if (x < size() && y < size()) {
    m_adjecentMatrix[x][y] = false;
    if (inBothDirection) {
      m_adjecentMatrix[y][x] = false;
    }

    return true;
  }

  return false;
}

template <typename T, typename M>
const T dsc::graphs::incmatrix::Graph<T, M>::get_vertex_value(const int x) const
{
  if (x < size())
    return m_vertices[x];
  else
    throw std::invalid_argument("this node does not exist in graph");
}

template <typename T, typename M>
bool dsc::graphs::incmatrix::Graph<T, M>::set_vertex_value(const int x, const T& v)
{
  if (x < size()) {
    m_vertices[x] = v;
    return true;
  }

  return false;
}

template <typename T, typename M>
const M dsc::graphs::incmatrix::Graph<T, M>::get_edge_value(const int x, const int y) const
{
  if (x < size() && y < size())
    return m_edgeValueMatrix[x][y];
  else
    throw std::invalid_argument("this node does not exist in graph");
}

template <typename T, typename M>
bool dsc::graphs::incmatrix::Graph<T, M>::set_edge_value(const int x, const int y, const M& v)
{
  if (x < size() && y < size()) {
    m_edgeValueMatrix[x][y] = v;
    return true;
  }

  return false;
}

template <typename T, typename M>
void dsc::graphs::incmatrix::Graph<T, M>::printMatrix()
{
  for (auto row : m_adjecentMatrix) {
    for (auto elem : row) {
      std::cout << elem << " ";
    }
    std::cout << std::endl;
  }
}
