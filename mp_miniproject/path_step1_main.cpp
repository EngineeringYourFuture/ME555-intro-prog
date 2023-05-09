#include "path_planning.hpp"
int main(int argc, char ** argv) {
  //check the # arguments
  checkArg(argc, 2);

  Graph graph;
  std::string gridmap(argv[1]);

  //parse the grid map
  parseGridMap(gridmap, graph);

  std::cout << graph;
  return EXIT_SUCCESS;
}
