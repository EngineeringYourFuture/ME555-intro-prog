#include <map>
#include <string>
#include <vector>
class Story {
 private:
  std::string storyTemplate;
  std::map<std::string, std::vector<std::string> > categoryMap;
  std::string readStory(const std::string & storyFile);
  std::map<std::string, std::vector<std::string> > generateCategoryMap(
      const std::string & wordFile);
  std::string replaceCategory(const std::string & category, unsigned int index);

 public:
  Story(const std::string & storyFile, const std::string & wordFile);
  void tellStory(unsigned int seed);
};
