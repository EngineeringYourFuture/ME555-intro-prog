CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic

todo_list: todo_list.o
	$(CXX) $(CXXFLAGS) -o todo_list todo_list.o

todo_list.o: todo_list.cpp task.hpp
	$(CXX) $(CXXFLAGS) -c todo_list.cpp

clean:
	rm -f todo_list todo_list.o

.PHONY: clean
