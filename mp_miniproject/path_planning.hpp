#include <cmath>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <functional>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <unordered_set>
#include <vector>
//declare the checkArg function which check whether the number of argument is correct
void checkArg(int argc, int expected_argc);

//The Point class
class Point {
 public:
  double x, y;
  Point();
  Point(double x, double y);
  double distanceFrom(const Point & rhs) const;
};

//declare the Path class
class Path;

//The Graph class
class Graph {
 private:
  std::vector<Point> nodes;
  std::vector<std::map<unsigned, double> > adj_list;

 public:
  void addNode(unsigned id, double x, double y);
  void addEdge(unsigned node1, unsigned node2);
  Path findShortestPath(unsigned startNode, unsigned goalNode, int mode);
  void removeObstructedEdges(const std::vector<std::vector<unsigned> > & obstacles);
  friend std::ostream & operator<<(std::ostream & os, const Graph & graph);
};

//declare the parseGridMap function which parse the input grid map file
void parseGridMap(const std::string & filename, Graph & graph);

//declare the convertNode function which convert the node argument into unsigned integer, and exit with error if it is not
unsigned convertNode(char * node);

//The path class
class Path {
 private:
  double cost;
  std::vector<unsigned> nodes;
  double priority;

 public:
  Path(unsigned startNode);
  void addNode(unsigned node, double cost);
  double getCost() const;
  double getPriority() const;
  void setPriority(double newPriority);
  const std::vector<unsigned> getNodes() const;
  friend std::ostream & operator<<(std::ostream & os, const Path & path);
  friend bool operator<(const Path & lhs, const Path & rhs);
  friend bool operator>(const Path & lhs, const Path & rhs);
};

//declare the readObstacles function which read and parse the input obstacles file
std::vector<std::vector<unsigned> > readObstacles(const std::string & filename);

//The Edge class
class Edge {
 private:
  Point point1;
  Point point2;

 public:
  Edge(const Point & p1, const Point & p2);
  int orientation(const Point & p1, const Point & p2, const Point & p3) const;
  bool onSegment(const Point & p, const Point & q, const Point & r) const;
  bool intersect(const Edge & other) const;
};

//declare the optional function which determines whether the optional -a format is correct
bool optional(const std::string & option);
