# Makefile

CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11

COMMON_SRC = path_planning.cpp
COMMON_OBJ = $(COMMON_SRC:.cpp=.o)

# Add more programs here
PROGRAMS = path-step1 path-step2 path-step3 path-step4

all: $(PROGRAMS)

# Rule for path-step1
path-step1_SRC = path_step1_main.cpp
path-step1_OBJ = $(path-step1_SRC:.cpp=.o)

# Rule for path-step2
path-step2_SRC = path_step2_main.cpp
path-step2_OBJ = $(path-step2_SRC:.cpp=.o)

# Rule for path-step3
path-step3_SRC = path_step3_main.cpp
path-step3_OBJ = $(path-step3_SRC:.cpp=.o)

# Rule for path-step4
path-step4_SRC = path_step4_main.cpp
path-step4_OBJ = $(path-step4_SRC:.cpp=.o)

path-step1: $(COMMON_OBJ) $(path-step1_OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

path-step2: $(COMMON_OBJ) $(path-step2_OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

path-step3: $(COMMON_OBJ) $(path-step3_OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

path-step4: $(COMMON_OBJ) $(path-step4_OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp path_planning.hpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f $(COMMON_OBJ) $(path-step1_OBJ) $(PROGRAMS)
