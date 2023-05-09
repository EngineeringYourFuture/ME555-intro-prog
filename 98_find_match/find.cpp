#include <cstdlib>
#include <fstream>
#include <iostream>
#include <unordered_set>

#include "profile.hpp"

// returns next comma-separated substring in str
// beginning at startp, storing location of next comma in endp
std::string nextSubstr(const std::string & str, size_t * startp, size_t * endp) {
  if (*startp == std::string::npos) {
    return "";
  }
  *endp = str.find(',', *startp);
  std::string ans;
  if (*endp == std::string::npos) {
    ans = str.substr(*startp);
    *startp = *endp;
  }
  else {
    ans = str.substr(*startp, *endp - *startp);
    *startp = *endp + 1;
  }
  return ans;
}

// reads from file stream f and returns unordered_set of Profiles in file
std::unordered_set<Profile> readProfiles(std::ifstream & f) {
  std::unordered_set<Profile> ans;
  std::string line;
  while (std::getline(f, line)) {
    size_t start = 0;
    size_t end;
    std::string uname = nextSubstr(line, &start, &end);
    int age = std::stoi(nextSubstr(line, &start, &end));
    double height = std::stod(nextSubstr(line, &start, &end));
    int attr = std::stoi(nextSubstr(line, &start, &end));
    Profile p(uname, age, height, attr);
    std::string i;
    while ((i = nextSubstr(line, &start, &end)).compare("")) {
      p.addInterest(i);
    }
    ans.insert(p);
  }
  return ans;
}

// reads from file stream f and returns a Qualities object
// describing the desired qualities to make a match
Qualities getQuals(std::ifstream & f) {
  std::string line;
  std::getline(f, line);
  size_t start = 0;
  size_t end;
  int a_min = std::stoi(nextSubstr(line, &start, &end));
  int a_max = std::stoi(nextSubstr(line, &start, &end));
  std::getline(f, line);
  start = 0;
  double h_min = std::stod(nextSubstr(line, &start, &end));
  double h_max = std::stod(nextSubstr(line, &start, &end));
  std::getline(f, line);
  start = 0;
  int at_min = std::stoi(nextSubstr(line, &start, &end));
  int at_max = std::stoi(nextSubstr(line, &start, &end));
  std::getline(f, line);
  start = 0;
  std::set<std::string> i_req;
  std::string i;
  while ((i = nextSubstr(line, &start, &end)).compare("")) {
    i_req.insert(i);
  }
  return Qualities(a_min, a_max, h_min, h_max, at_min, at_max, i_req);
}

int main(int argc, char ** argv) {
  if (argc != 3) {
    std::cerr << "Wrong # arguments" << std::endl;
    exit(EXIT_FAILURE);
  }
  // open files for reading
  std::ifstream inputFile(argv[1]);
  std::ifstream qualsFile(argv[2]);
  if (!inputFile.is_open() || !qualsFile.is_open()) {
    std::cerr << "Error opening file" << std::endl;
    exit(EXIT_FAILURE);
  }
  // read all profiles
  std::unordered_set<Profile> profiles = readProfiles(inputFile);
  // read quals
  Qualities quals = getQuals(qualsFile);
  inputFile.close();
  qualsFile.close();
  // remove profiles that don't match qualities
  // print profiles that match
  for (const auto & profile : profiles) {
    if (profile.isMatch(quals)) {
      std::cout << profile;
    }
  }
  return EXIT_SUCCESS;
}
