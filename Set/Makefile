.PHONY: clean

set: main.o
	g++ -std=c++1z -o set main.cpp -g

main.o: main.cpp
	g++ -std=c++1z -c -o main.o main.cpp -g

clean:
	rm -f ~*
	rm -f *.o
	rm -f set
