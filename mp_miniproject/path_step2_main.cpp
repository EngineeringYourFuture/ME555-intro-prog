#include "path_planning.hpp"
int main(int argc, char ** argv) {
  // Check the number of arguments
  checkArg(argc, 4);

  Graph graph;
  std::string gridmap(argv[1]);

  //parse the grid map
  parseGridMap(gridmap, graph);

  //get the node arguments
  unsigned startNode = convertNode(argv[2]);
  unsigned goalNode = convertNode(argv[3]);

  //find the shortest path
  Path shortestPath = graph.findShortestPath(startNode, goalNode, 1);
  std::cout << shortestPath << std::endl;
  return EXIT_SUCCESS;
}
