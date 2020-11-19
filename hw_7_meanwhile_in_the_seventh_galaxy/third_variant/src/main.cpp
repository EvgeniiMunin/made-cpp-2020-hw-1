#include <iostream>
#include "graph.h"
#include "dfs.h"


int main() {
  const Graph<Vertex<0, Edge<0, 2>>,
              Vertex<1, Edge<1, 2>, Edge<1, 5>>,
              Vertex<2, Edge<2, 3>>,
              Vertex<3, Edge<3, 4>>,
              Vertex<4, Edge<4, 1>>,
              Vertex<5, Edge<5, 4>>>
      graph;

  std::cout << "Path exists: " <<
            (PathExists<decltype(graph), 5, 0>::value ? "true" : "false") << std::endl;


  return 0;
}
