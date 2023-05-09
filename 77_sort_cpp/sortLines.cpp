#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;
void printVec(vector<string> vec) {
  vector<string>::iterator it = vec.begin();
  while (it != vec.end()) {
    cout << *it << endl;
    ++it;
  }
}
int main(int argc, char ** argv) {
  string str;
  vector<string> vec;
  if (argc == 1) {
    while (!cin.eof()) {
      getline(cin, str);
      vec.push_back(str);
    }
    sort(vec.begin(), vec.end());
    printVec(vec);
    vec.clear();
  }
  else {
    for (int i = 1; i < argc; i++) {
      ifstream ifs;
      ifs.open(argv[i]);
      if (ifs.fail()) {
        cerr << "fail to open file: " << argv[i] << endl;
        exit(EXIT_FAILURE);
      }
      while (!ifs.eof()) {
        getline(ifs, str);
        vec.push_back(str);
      }
      sort(vec.begin(), vec.end());
      printVec(vec);
      vec.clear();
      ifs.close();
    }
  }
  return EXIT_FAILURE;
}
