#include "path_planning.hpp"

//check the number of arguments
void checkArg(int argc, int expected_argc) {
  if (argc != expected_argc) {
    std::cerr << "Wrong # arguments" << std::endl;
    exit(EXIT_FAILURE);
  }
}

//implement the constructor in Point class
Point::Point(double x, double y) : x(x), y(y) {
}
Point::Point() : x(0), y(0) {
}

//implement distanceFrom method in Point class
double Point::distanceFrom(const Point & rhs) const {
  return std::sqrt(std::pow(x - rhs.x, 2) + std::pow(y - rhs.y, 2));
}

//implement addNode method in Graph class
void Graph::addNode(unsigned id, double x, double y) {
  nodes.resize(id + 1);
  adj_list.resize(id + 1);
  nodes[id] = Point(x, y);
}

//implement addEdge method in Graph class
void Graph::addEdge(unsigned node1, unsigned node2) {
  if (node1 >= nodes.size() || node2 >= nodes.size()) {
    std::cerr << "Invalid node IDs in edge: " << node1 << " " << node2 << std::endl;
    exit(EXIT_FAILURE);
  }
  double distance = nodes[node1].distanceFrom(nodes[node2]);
  adj_list[node1][node2] = distance;
  adj_list[node2][node1] = distance;
};

//implement the overloaded operator<<
std::ostream & operator<<(std::ostream & os, const Graph & graph) {
  for (const auto & node : graph.nodes) {
    os << "(" << node.x << "," << node.y << ") ";
  }
  os << std::endl;
  for (unsigned i = 0; i < graph.adj_list.size(); i++) {
    os << i << ": ";
    for (const auto & adj : graph.adj_list[i]) {
      os << adj.first << "," << adj.second << " ";
    }
    os << std::endl;
  }
  return os;
};

//implement the parseGridMap function
void parseGridMap(const std::string & filename, Graph & graph) {
  // Read the grid map file check if it can be opened
  std::ifstream grid_map_file(filename);
  if (!grid_map_file.is_open()) {
    std::cerr << "Cannot open grid map file: " << filename << std::endl;
    exit(EXIT_FAILURE);
  }

  // Check if the file is empty
  if (grid_map_file.peek() == std::ifstream::traits_type::eof()) {
    std::cerr << "Grid map file is empty." << std::endl;
    exit(EXIT_FAILURE);
  }

  std::string line;

  //create three situations which will be handled later
  enum class Section { NONE, NODES, EDGES };
  Section current_section = Section::NONE;

  // Flags to check if both sections were processed
  bool nodes_section_found = false;
  bool edges_section_found = false;

  //read the line by line in grid map
  while (std::getline(grid_map_file, line)) {
    std::stringstream ss(line);
    std::string token;
    ss >> token;

    //check if there is $nodes or $edges at beginning
    if (token == "$nodes") {
      current_section = Section::NODES;
      nodes_section_found = true;
      continue;
    }
    else if (token == "$edges") {
      current_section = Section::EDGES;
      edges_section_found = true;
      continue;
    }

    //switch the condition to add nodes or edges
    switch (current_section) {
      case Section::NODES: {
        unsigned id = 0;
        double x = 0, y = 0;
        std::stringstream ssnodes(line);
        ssnodes >> id >> x >> y;

        //check whether the coordinate is correct or not
        if (ssnodes.fail() || !ssnodes.eof()) {
          std::cerr << "Invalid input line: " << line << std::endl;
          exit(EXIT_FAILURE);
        }
        graph.addNode(id, x, y);
        break;
      }
      case Section::EDGES: {
        int temp_node1 = 0, temp_node2 = 0;
        std::stringstream ssedges(line);
        ssedges >> temp_node1 >> temp_node2;

        //The node ID should be non-negative integer
        if (temp_node1 < 0 || temp_node2 < 0) {
          std::cerr << "The node ID should be non-negative in $edges: " << temp_node1
                    << " " << temp_node2 << std::endl;
          exit(EXIT_FAILURE);
        }

        //check if the nodes is in correct format
        if (ssedges.fail() || !ssedges.eof()) {
          std::cerr << "The type of the node is incorrect: " << temp_node1 << " "
                    << temp_node2 << std::endl;
          exit(EXIT_FAILURE);
        }
        unsigned node1 = static_cast<unsigned>(temp_node1);
        unsigned node2 = static_cast<unsigned>(temp_node2);
        graph.addEdge(node1, node2);
        break;
      }

        //this indicates that there is no $nodes or $edges at the beginning
      default:
        std::cerr << "Invalid section in the grid map file" << std::endl;
        exit(EXIT_FAILURE);
    }
  }

  // Check if both sections were processed
  if (!nodes_section_found || !edges_section_found) {
    std::cerr << "Grid map file is missing one or both sections: $nodes and $edges."
              << std::endl;
    exit(EXIT_FAILURE);
  }
  grid_map_file.close();
};

//implement the convertNode function
unsigned convertNode(char * node) {
  char * end;
  double n_double = std::strtod(node, &end);
  if (end != node + std::strlen(node) || n_double < 0 ||
      std::floor(n_double) != n_double) {
    std::cerr << "Invalid input for node ID: " << node << std::endl;
    exit(EXIT_FAILURE);
  }
  return n_double;
};

//implement the constructor in Path class
Path::Path(unsigned startNode) : cost(0.0), priority(0.0) {
  nodes.push_back(startNode);
}

//implement the addNode method in Path class
void Path::addNode(unsigned node, double cost) {
  nodes.push_back(node);
  this->cost += cost;
}

//implement the getCost method in Path class to get the cost
double Path::getCost() const {
  return cost;
}

//implement the getPriority method in Path class to get the cost+heristic_cost which is the priority
double Path::getPriority() const {
  return priority;
}

//implement the setPriority method in Path class to get the nodes to set the cost+heristic_cost to this priority
void Path::setPriority(double newPriority) {
  priority = newPriority;
}

//implement the getNodes method in Path class to get the nodes
const std::vector<unsigned> Path::getNodes() const {
  return nodes;
}

//implement the operator<< as a friend of Path class
std::ostream & operator<<(std::ostream & os, const Path & path) {
  for (const auto & node : path.nodes) {
    os << node << " ";
  }
  os << ": " << path.cost;
  return os;
}

//implement the overloaded operator< to compare two paths based on their priority in std::greater<Path>
//which implicilty compare two paths
bool operator<(const Path & lhs, const Path & rhs) {
  return lhs.getPriority() < rhs.getPriority();
}

//implement the overloaded operator> to compare two paths based on their priority in std::greater<Path>
//which implicilty compare two paths
bool operator>(const Path & lhs, const Path & rhs) {
  return lhs.getPriority() > rhs.getPriority();
}

//implement readObstacles function which read and parse the obstacle file.
std::vector<std::vector<unsigned> > readObstacles(const std::string & filename) {
  std::vector<std::vector<unsigned> > obstacles;
  // Read the obstacle file check if it can be opened
  std::ifstream obstacle_file(filename);
  if (!obstacle_file.is_open()) {
    std::cerr << "Cannot open obstacle file: " << filename << std::endl;
    exit(EXIT_FAILURE);
  }

  // Check if the file is empty
  if (obstacle_file.peek() == std::ifstream::traits_type::eof()) {
    std::cerr << "obstacle file is empty." << std::endl;
    exit(EXIT_FAILURE);
  }

  std::string line;
  //check for header
  std::getline(obstacle_file, line);
  if (line != "$obstacles") {
    std::cout << "Invalid format for the first line: " << line << std::endl;
    exit(EXIT_FAILURE);
  }

  //Read the obstacle
  while (getline(obstacle_file, line)) {
    std::vector<unsigned> obstacle_nodes;
    if (line.empty()) {
      continue;
    }
    std::stringstream ss(line);
    unsigned node;
    while (ss >> node) {
      obstacle_nodes.push_back(node);
    }

    //check the format of the nodes
    if (!ss.eof()) {
      std::cerr << "Invalid input line: " << line << std::endl;
      exit(EXIT_FAILURE);
    }

    //if the number of nodes in one line is greater than 2, then add it to obstacles.
    if (obstacle_nodes.size() >= 2) {
      obstacles.push_back(obstacle_nodes);
    }
    else {
      std::cerr << "The node number is incorrect on line: " << line << std::endl;
      exit(EXIT_FAILURE);
    }
  }
  obstacle_file.close();
  return obstacles;
}

//implement the constructor of Edge class
Edge::Edge(const Point & p1, const Point & p2) : point1(p1), point2(p2) {
}

//implement the orientation method in Edge class to find the orientation of three point
int Edge::orientation(const Point & p1, const Point & p2, const Point & p3) const {
  double z = (p2.y - p1.y) * (p3.x - p2.x) - (p2.x - p1.x) * (p3.y - p2.y);
  if (z > 0) {
    return 1;  //clockwise
  }
  else if (z < 0) {
    return -1;  //counter clockwise
  }
  else {
    return 0;  // collinear
  }
}

//implement the onSegment method in Edge class to check if a point 'q' lies on the line segment 'pr'
//when the three points are collinear
bool Edge::onSegment(const Point & p, const Point & q, const Point & r) const {
  if (q.x <= std::max(p.x, r.x) && q.x >= std::min(p.x, r.y) &&
      q.y <= std::max(p.y, r.y) && q.y >= std::min(p.y, r.y)) {
    return true;
  }
  return false;
}

//implement the intersect method in Edge class to find out whether two edges are intersect
bool Edge::intersect(const Edge & other) const {
  //Find the four orientations need for the general and special cases
  int o1 = orientation(point1, point2, other.point1);
  int o2 = orientation(point1, point2, other.point2);
  int o3 = orientation(other.point1, other.point2, point1);
  int o4 = orientation(other.point1, other.point2, point2);

  //general case
  if (o1 != o2 && o3 != o4) {
    return true;
  }

  //special cases
  if (o1 == 0 && onSegment(point1, other.point1, point2))
    return true;
  if (o2 == 0 && onSegment(point1, other.point2, point2))
    return true;
  if (o1 == 0 && onSegment(other.point1, point1, other.point2))
    return true;
  if (o1 == 0 && onSegment(other.point1, point2, other.point2))
    return true;

  // Doesn't fall in any of the above cases
  return false;
}

//implement the removeObstructedEdges method in Graph class which removes edges intersecting with obstacles
void Graph::removeObstructedEdges(const std::vector<std::vector<unsigned> > & obstacles) {
  for (const auto & obstacle_nodes : obstacles) {
    std::vector<Edge> obstacle_edges;

    //construct edges for each pair of nodes in the obstacle
    for (size_t i = 0; i < obstacle_nodes.size(); ++i) {
      size_t next = (i + 1) % obstacle_nodes.size();
      Edge obstacle_edge(nodes[obstacle_nodes[i]], nodes[obstacle_nodes[next]]);
      obstacle_edges.push_back(obstacle_edge);
    }
    // Iterate over all edges in the graph
    for (size_t i = 0; i < adj_list.size(); i++) {
      std::map<unsigned, double> & neighbors = adj_list[i];
      for (auto it = neighbors.begin(); it != neighbors.end();) {
        Edge graph_edge(nodes[i], nodes[it->first]);

        // Check if graph_edge intersects any of the obstacle_edges
        bool intersects = false;
        for (const Edge & obstacle_edge : obstacle_edges) {
          if (graph_edge.intersect(obstacle_edge)) {
            intersects = true;
            break;
          }
        }

        // Remove the graph edge if it intersects with an obstacle edge
        if (intersects) {
          it = neighbors.erase(it);
        }
        else {
          ++it;
        }
      }
    }
  }
}

//implement the optional function
bool optional(const std::string & option) {
  if (option == "-a") {
    return true;
  }
  std::cerr << "The format of the option is incorrect: " << option << std::endl;
  exit(EXIT_FAILURE);
}

//implement the findShortestPath method in Graph class which take two modes,
//mode 1 uses Dijkstra's algorithm, mode 2 uses A* algorithm
Path Graph::findShortestPath(unsigned int startNode, unsigned int goalNode, int mode) {
  //check whether the start node or goal node exist in nodes
  if (startNode >= nodes.size() || goalNode >= nodes.size()) {
    std::cerr << "Invalid node ID: " << startNode << " " << goalNode << std::endl;
    exit(EXIT_FAILURE);
  }

  //declare a priority queue which will store paths with the lowest priority (cost+heuristic) at the top
  std::priority_queue<Path, std::vector<Path>, std::greater<Path> > paths;
  std::unordered_set<unsigned> visited;

  //initialize the path with adding start node with 0 cost in the best path
  paths.push(Path(startNode));

  while (!paths.empty()) {
    Path current_path = paths.top();
    unsigned current_node = current_path.getNodes().back();
    paths.pop();

    //check if the current node is the goal node if it is, then return the path
    if (current_node == goalNode) {
      return current_path;
    }

    //check whether the current node is in the visited nodes
    if (visited.find(current_node) == visited.end()) {
      visited.insert(current_node);

      //find the current node's neigbors
      for (const auto & neighbor : adj_list[current_node]) {
        unsigned neighbor_node = neighbor.first;
        double edge_cost = neighbor.second;

        //check if the neighbor node is in the visited nodes
        if (visited.find(neighbor_node) == visited.end()) {
          Path new_path = current_path;
          new_path.addNode(neighbor_node, edge_cost);
          if (mode == 1) {  //Dijkstra's Algorithm
            new_path.setPriority(new_path.getCost());
          }
          else if (mode == 2) {  //A* Algorithm
            double heuristic = nodes[neighbor_node].distanceFrom(nodes[goalNode]);
            new_path.setPriority(new_path.getCost() + heuristic);
          }
          else {
            std::cerr
                << "Invalid mode. Use 1 for Dijkstra's algorithm or 2 for A* algorithm."
                << std::endl;
            exit(EXIT_FAILURE);
          }

          paths.push(new_path);
        }
      }
    }
  }
  //After the while loop where the paths is empty, return no path exist.
  std::cerr << "No path exists." << std::endl;
  exit(EXIT_FAILURE);
}
