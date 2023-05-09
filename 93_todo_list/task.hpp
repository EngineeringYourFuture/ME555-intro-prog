#include <list>
#include <string>

typedef std::string task_t;

class TaskDep {
 private:
  const task_t task;
  std::list<task_t> pres;

 public:
  // write these
  TaskDep(const task_t & t) : task(t) {}
  const task_t & getTask() const { return task; }
  void addPredecessor(const task_t & t) { pres.push_back(t); }
  std::list<task_t> getPredecessors() const { return pres; }
};
