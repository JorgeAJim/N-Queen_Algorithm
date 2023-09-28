queens: queens.o coordinate.o
	g++ -g queens.o coordinate.o -o queens
queens.o: queens.cpp coordinate.h
	g++ -g -c queens.cpp
coordinate.o: coordinate.cpp coordinate.h
	g++ -g -c coordinate.cpp
clean:
	rm *.o
	rm queens
run: queens
	./queens
debug: queens
	gdb queens