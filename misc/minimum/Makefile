CXX 		= g++
STANDARD	= -std=c++14
DEBUG 		= -ggdb
CXXFLAGS 	= -Wall -Wextra $(STANDARD) $(DEBUG)
LDFLAGS 	= #link-flags
SRC 		= main.cpp
HEADER 		= #headers
OBJ 		= $(SRC:.cpp=.o)
TARGET 		= min.out

.PHONY: clean zip

$(TARGET): $(OBJ) $(HEADER)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.cpp %.hpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f *.o
	rm -f ~*
	rm -f $(TARGET)

zip:
	zip -r $(TARGET).zip ./
