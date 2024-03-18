all: main.o radnik.o firma.o
	clang++ main.o radnik.o firma.o -o radnici

main.o: main.cpp
	clang++ -c main.cpp

radnik.o: radnik.cpp
	clang++ -c radnik.cpp

firma.o: firma.cpp
	clang++ -c firma.cpp

clean:
	rm -rf *.o radnici
