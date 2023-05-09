#include "parse.hpp"

#include <exception>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
// any other headers you need

class invalid_input : public std::exception {
  // override what() here
 private:
  std::string message_;

 public:
  invalid_input(const std::string & message) : message_(message) {}
  const char * what() const noexcept override { return message_.c_str(); }
};
item_t * parseLine(const std::string & line) {
  // write me
  if (line.find(":") == line.npos) {
    throw invalid_input("Does not have a colon on line ");
  }
  std::string key;
  std::vector<std::string> values;
  key = line.substr(0, line.find(":"));
  if (line.find(":") + 1 != line.size()) {
    std::string value;
    std::istringstream values_stream(line.substr(line.find(":") + 1));
    while (std::getline(values_stream, value, ',')) {
      values.push_back(value.substr(1));
    }
  }
  return new item_t(key, values);
}
std::vector<item_t *> itemsFromFile(const std::string & filename) {
  std::vector<item_t *> items;
  std::string line;
  std::fstream fs;
  try {
    fs.open(filename);
    if (!fs.is_open()) {
      throw std::runtime_error("Error opening the file");
    }
  }
  catch (std::runtime_error & e) {
    std::cerr << e.what() << std::endl;
    exit(EXIT_FAILURE);
  }
  size_t count = 0;
  while (std::getline(fs, line)) {
    count++;
    try {
      items.push_back(parseLine(line));
    }
    catch (invalid_input & e) {
      std::cerr << e.what() << count << "!" << std::endl;
    }
  }
  fs.close();
  return items;
}
void printItems(const std::vector<item_t *> & items) {
  for (const item_t * item : items) {
    std::cout << "key = " << item->first << std::endl;
    std::cout << "  values = ";
    for (size_t i = 0; i < item->second.size(); i++) {
      std::cout << item->second[i];
      if (i + 1 != item->second.size()) {
        std::cout << "; ";
      }
    }
    std::cout << std::endl;
  }
}
class invalid_argument_count : public std::exception {
  //public:
  const char * what() const noexcept override { return "Invalid # arguments\n"; }
};
int main(int argc, char ** argv) {
  std::ifstream fs;

  try {
    if (argc != 2) {
      throw invalid_argument_count();
    }
  }
  catch (std::exception & e) {
    std::cerr << e.what() << std::endl;
    exit(EXIT_FAILURE);
  }

  std::vector<item_t *> items = itemsFromFile(argv[1]);
  printItems(items);
  for (const item_t * item : items) {
    delete item;
  }
  return EXIT_SUCCESS;
}
