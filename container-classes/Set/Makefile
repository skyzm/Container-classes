CXX 		= g++
STANDARD	= -std=c++17
DEBUG 		= -g
CXXFLAGS 	= -Wall -Wextra $(STANDARD) $(DEBUG)
SRC 		= main.cpp
HEADER 		= set.hpp \
			  set_node.hpp \
			  set_detail.hpp \
			  color.hpp
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
