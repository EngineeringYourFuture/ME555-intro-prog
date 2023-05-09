#include <cmath>
#include <cstring>
#include <iostream>

#include "rand_story.hpp"
int main(int argc, char ** argv) {
  if (argc != 4) {
    std::cerr << "Wrong # arguments" << std::endl;
    exit(EXIT_FAILURE);
  }
  std::string storyFile = argv[1];
  std::string wordFile = argv[2];
  Story story(storyFile, wordFile);
  //convert the last argument into positive integer, exit error if it is not.
  char * end;
  double n_double = std::strtod(argv[3], &end);
  if (end != argv[3] + std::strlen(argv[3]) || n_double < 1 ||
      std::floor(n_double) != n_double) {
    std::cerr << "Invalid input for n: " << argv[3] << std::endl;
    exit(EXIT_FAILURE);
  }
  size_t seed = n_double;
  story.tellStory(seed);

  return EXIT_SUCCESS;
}
