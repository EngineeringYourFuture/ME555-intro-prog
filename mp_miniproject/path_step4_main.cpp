#include "path_planning.hpp"
int main(int argc, char ** argv) {
  //check the # arguments
  if (argc < 5 || argc > 6) {
    std::cerr << "Wrong # arguments" << std::endl;
    exit(EXIT_FAILURE);
  }

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
  if (argc == 5) {
    Path shortestPath = graph.findShortestPath(startNode, goalNode, 1);
    std::cout << shortestPath << std::endl;
  }
  else {
    std::string option(argv[5]);
    bool _a = optional(option);
    if (_a == true) {
      Path shortestPath = graph.findShortestPath(startNode, goalNode, 2);
      std::cout << shortestPath << std::endl;
    }
  }

  return EXIT_SUCCESS;
}
