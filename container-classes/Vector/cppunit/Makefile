.PHONY: clean

PROGRAM = vector
CXX = g++
CXXFLAGS =  -std=c++17 -Wall -Wextra -g
LDFLAGS = -lcppunit

$(PROGRAM) : main.o
	$(CXX) $(CXXFLAGS) -o $(PROGRAM) main.o $(LDFLAGS)

clean:
	rm -f $(PROGRAM)
	rm -f *.o
