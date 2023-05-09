#include "rand_story.hpp"

#include <cmath>
#include <cstring>
#include <ctime>
#include <deque>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
Story::Story(const std::string & storyFile, const std::string & wordFile) {
  storyTemplate = readStory(storyFile);
  categoryMap = generateCategoryMap(wordFile);
}
std::string Story::readStory(const std::string & storyFile) {
  std::ifstream file(storyFile);
  if (!file.is_open()) {
    std::cerr << "Error opening file:" << storyFile << std::endl;
    exit(EXIT_FAILURE);
  }
  std::stringstream buffer;
  buffer << file.rdbuf();
  return buffer.str();
}

std::map<std::string, std::vector<std::string> > Story::generateCategoryMap(
    const std::string & wordFile) {
  std::map<std::string, std::vector<std::string> > categoryMap;
  std::ifstream file(wordFile);
  if (!file.is_open()) {
    std::cerr << "Error opening file:" << wordFile << std::endl;
    exit(EXIT_FAILURE);
  }
  std::string line;
  while (std::getline(file, line)) {
    size_t colonPos = line.find(":");
    if (colonPos == std::string::npos) {
      std::cerr << "Invalid word entry: " << line << std::endl;
      exit(EXIT_FAILURE);
    }
    std::string category = line.substr(0, colonPos);
    std::string word = line.substr(colonPos + 1);
    categoryMap[category].push_back(word);
  }
  return categoryMap;
}

std::string Story::replaceCategory(const std::string & category, unsigned int index) {
  if (categoryMap.find(category) == categoryMap.end()) {
    std::cerr << "Invalid category: " << category << std::endl;
    exit(EXIT_FAILURE);
  }
  std::vector<std::string> & words = categoryMap[category];
  return words[index % words.size()];
}

void Story::tellStory(unsigned int seed) {
  srand(seed);
  std::deque<std::string> usedWords;
  size_t pos = 0;
  while ((pos = storyTemplate.find("_", pos)) != std::string::npos) {
    size_t endPos = storyTemplate.find("_", pos + 1);
    if (endPos == std::string::npos) {
      std::cerr << "Invalid format" << std::endl;
      exit(EXIT_FAILURE);
    }
    std::string category = storyTemplate.substr(pos + 1, endPos - pos - 1);
    std::string replacement;

    unsigned int index = 0;
    try {
      index = std::stoi(category);
      replacement = usedWords.at(index - 1);
      usedWords.push_front(replacement);
    }
    catch (const std::invalid_argument &) {
      replacement = replaceCategory(category, rand());
      usedWords.push_front(replacement);
    }
    catch (const std::out_of_range &) {
      std::cerr << "Invalid reference to previous word:" << category << std::endl;
      exit(EXIT_FAILURE);
    }
    storyTemplate.replace(pos, endPos - pos + 1, replacement);
    pos = pos + replacement.length();
  }
  if (!storyTemplate.empty() && storyTemplate.back() == '\n') {
    storyTemplate.pop_back();
  }
  std::cout << storyTemplate << std::endl;
}
