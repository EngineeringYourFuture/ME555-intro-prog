#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <list>
#include <sstream>
#include <string>

#include "task.hpp"
std::list<TaskDep> parse_file(const std::string & filename) {
  std::list<TaskDep> task_deps;
  std::string line;
  std::fstream fs(filename);
  while (std::getline(fs, line)) {
    if (line.find(':') == line.npos) {
      std::cerr << "Error: no colon in line" << std::endl;
      exit(EXIT_FAILURE);
    }
    task_t task = line.substr(0, line.find(':'));
    TaskDep task_dep(task);
    if (line.find(':') + 1 != line.size()) {
      task_t prede;
      std::istringstream predes_stream(line.substr(line.find(':') + 2));
      while (std::getline(predes_stream, prede, ',')) {
        if (prede[0] == ' ') {
          prede.erase(0, 1);
        }
        task_dep.addPredecessor(prede);
      }
    }
    task_deps.push_back(task_dep);
  }
  fs.close();
  return task_deps;
}
bool process_task(std::list<TaskDep> & task_deps, std::list<task_t> & answer) {
  for (auto it = task_deps.begin(); it != task_deps.end(); ++it) {
    bool all_predecessors_in_answer = true;
    std::list<task_t> predecessors = it->getPredecessors();
    task_t latest_predecessor;
    int max_predecessor_index = -1;

    for (const task_t & pred : predecessors) {
      auto found_pred = std::find(answer.begin(), answer.end(), pred);
      if (found_pred == answer.end()) {
        all_predecessors_in_answer = false;
        break;
      }
      else {
        int pred_index = std::distance(answer.begin(), found_pred);
        if (pred_index > max_predecessor_index) {
          max_predecessor_index = pred_index;
          latest_predecessor = pred;
        }
      }
    }

    if (all_predecessors_in_answer) {
      auto insert_pos = answer.begin();
      if (max_predecessor_index != -1) {
        insert_pos = std::find(answer.begin(), answer.end(), latest_predecessor);
        ++insert_pos;
      }
      answer.insert(insert_pos, it->getTask());
      task_deps.erase(it);
      return true;
    }
  }
  return false;
}
std::list<task_t> order_tasks(std::list<TaskDep> & task_deps) {
  std::list<task_t> answer;
  while (!task_deps.empty()) {
    if (!process_task(task_deps, answer)) {
      std::cerr << "Error: Unable to create a todo list with the provided dependencies."
                << std::endl;
      std::exit(EXIT_FAILURE);
    }
  }
  return answer;
}
void print_todo_list(const std::list<task_t> & todo_list) {
  for (auto it = todo_list.begin(); it != todo_list.end(); ++it) {
    if (it != todo_list.begin()) {
      std::cout << ", ";
    }
    std::cout << *it;
  }
  std::cout << std::endl;
}
int main(int argc, char ** argv) {
  // open file for reading
  if (argc != 2) {
    std::cerr << "Wrong # arguments" << std::endl;
    exit(EXIT_FAILURE);
  }
  std::fstream ifs(argv[1]);
  if (!ifs.is_open()) {
    std::cerr << "Error: Unable to open file" << std::endl;
    exit(EXIT_FAILURE);
  }
  // make dependency list of tasks from input file
  std::list<TaskDep> task_deps = parse_file(argv[1]);
  // order list according to dependencies
  std::list<task_t> ordered_tasks = order_tasks(task_deps);
  // print todo list
  print_todo_list(ordered_tasks);
  return EXIT_SUCCESS;
}
