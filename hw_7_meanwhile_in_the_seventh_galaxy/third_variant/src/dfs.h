#ifndef MEANWHILE_IN_THE_SEVENTH_GALAXY_THIRD_VARIANT_DFS_H
#define MEANWHILE_IN_THE_SEVENTH_GALAXY_THIRD_VARIANT_DFS_H

#include "graph.h"
#include "type_list.h"
#include "value_list.h"

template <typename Graph, size_t from, size_t to, typename ValueList>
struct DFS;

template <Type visited, typename Graph, size_t from, size_t to,
          typename ValueList>
struct IF_VISITED {};

template <typename Graph, size_t from, size_t to, typename ValueList>
struct IF_VISITED<true, Graph, from, to, ValueList> {
  static constexpr Type value = false;
};

template <typename Graph, size_t from, size_t to, typename ValueList>
struct IF_VISITED<false, Graph, from, to, ValueList> {
  static constexpr Type value = DFS<Graph, from, to, ValueList>::value;
};

template <typename Graph, size_t from, size_t to, typename ValueList,
          size_t current_edge_id>
struct LOOP_DFS;


// Call it from DFS
template <typename Graph, size_t from, size_t to, typename ValueList,
          size_t edge_id>
struct LOOP_DFS {
public:
  using current_vertex = typename TypeAt<from, typename Graph::Vertices>::type;
  static_assert(current_vertex::index == from);
  using edges = typename current_vertex ::Edges;
  static_assert(edge_id - 1 >= 0);
  using current_edge = typename TypeAt<edge_id - 1, edges>::type;
  static_assert(current_edge::from == from);

  static constexpr Type is_visited_value =
      Get<current_edge::to, ValueList>::value;

  static constexpr Type value =
      IF_VISITED<is_visited_value, Graph, current_edge::to, to,
                 ValueList>::value ||
      LOOP_DFS<Graph, from, to, ValueList, edge_id - 1>::value;
};

template <typename Graph, size_t from, size_t to, typename ValueList>
struct LOOP_DFS<Graph, from, to, ValueList, 0> {
public:
  static constexpr Type value = false;
};

template <typename Graph, size_t from, size_t to, typename ValueList>
struct DFS {
private:
  using current_vertex = typename TypeAt<from, typename Graph::Vertices>::type;
  static_assert(current_vertex::index == from);
  using edges = typename current_vertex ::Edges;

  static constexpr size_t count_of_edges = Length<edges>::value;

public:
  static constexpr Type value =
      (from == to) ||
      LOOP_DFS<Graph, from, to, typename Set<from, true, ValueList>::type,
               count_of_edges>::value;
};

template <typename Graph, size_t start, size_t end> struct PathExists {
private:
  static constexpr size_t n = Length<typename Graph::Vertices>::value;

public:
  static constexpr bool value =
      DFS<Graph, start, end, typename Construct<false, n>::type>::value;
};

#endif /// MEANWHILE_IN_THE_SEVENTH_GALAXY_THIRD_VARIANT_DFS_H.
