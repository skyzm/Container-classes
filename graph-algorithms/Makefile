CXX 		= g++
STANDARD	= -std=c++17
DEBUG 		= -g
CXXFLAGS 	= -Wall -Wextra $(STANDARD) $(DEBUG)
SRC 		= main.cpp
HEADER 		= graph.hpp \
			  graph_algorithm.hpp \
			  graph_algorithm_detail.hpp
OBJ 		= $(SRC:.cpp=.o)
TARGET 		= main

.PHONY: clean zip

$(TARGET): $(OBJ) $(HEADER)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(OBJ): $(SRC)
	$(CXX) $(CXXFLAGS) -o $@ -c $<


clean:
	rm -f *.o
	rm -f ~*
	rm -f $(TARGET)

zip:
	zip -r $(TARGET).zip ./
