.PHONY: clean

PROGRAM = graph-algortithm
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g

$(PROGRAM) : main.o
	$(CXX) $(CXXFLAGS) -o $(PROGRAM) main.o

clean:
	rm -f *.o
	rm -f ~*
	rm -f $(PROGRAM)
