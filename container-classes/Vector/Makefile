CXX 		= g++
STANDARD	= -std=c++17
DEBUG 		= -g
CXXFLAGS 	= -Wall -Wextra $(STANDARD) $(DEBUG)
SRC 		= main.cpp
HEADER 		= ./include/Vector.hpp \
			  ./cppunit/vector.test.hpp \
			  ./cppunit/test_info/color.hpp \
			  ./cppunit/test_info/info.hpp
OBJ 		= $(SRC:.cpp=.o)
LDFAGS 		= -lcppunit
TARGET 		= main

.PHONY: clean zip

$(TARGET): $(OBJ) $(HEADER)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFAGS)

$(OBJ): $(SRC)
	$(CXX) $(CXXFLAGS) -o $@ -c $< $(LDFAGS)


clean:
	rm -f *.o
	rm -f ~*
	rm -f $(TARGET)

zip:
	zip -r $(TARGET).zip ./
