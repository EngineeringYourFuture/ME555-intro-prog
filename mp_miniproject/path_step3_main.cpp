#include "path_planning.hpp"
int main(int argc, char ** argv) {
  //check the # arguments
  checkArg(argc, 5);

  Graph graph;
  std::string gridmap(argv[1]);
  std::string obstacle(argv[2]);
  //parse the grid map
  parseGridMap(gridmap, graph);

  //parse the obstacle file
  std::vector<std::vector<unsigned> > obstacles = readObstacles(obstacle);

  //remove edges that have obstacles
  graph.removeObstructedEdges(obstacles);

  //get the node arguments
  unsigned startNode = convertNode(argv[3]);
  unsigned goalNode = convertNode(argv[4]);

  //find the shortes path with obstacles
  Path shortestPath = graph.findShortestPath(startNode, goalNode, 1);
  std::cout << shortestPath << std::endl;
  return EXIT_SUCCESS;
}
