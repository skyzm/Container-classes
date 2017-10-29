.PHONY: clean

PROGRAM = set
CXX = g++
CXXFLAGS =  -std=c++17 -Wall -Wextra -g

$(PROGRAM) : main.o
	$(CXX) $(CXXFLAGS) -o $(PROGRAM) main.o

clean:
	rm -f $(PROGRAM)
	rm -f *.o
