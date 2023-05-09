CXX = g++
CXXFLAGS = -Wall -std=c++11

rand_story: main.o rand_story.o
	$(CXX) $(CXXFLAGS) -o rand_story main.o rand_story.o

main.o: main.cpp rand_story.hpp
	$(CXX) $(CXXFLAGS) -c main.cpp

rand_story.o: rand_story.cpp rand_story.hpp
	$(CXX) $(CXXFLAGS) -c rand_story.cpp

clean:
	rm -f rand_story main.o rand_story.o
