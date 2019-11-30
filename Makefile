CXX=g++
LD=g++
CFLAGS=-std=c++11 -Wall -pedantic -Wno-long-long -O0 -ggdb

all: hruskraj doc

hruskraj: matrixType.o sparseMatrix.o denseMatrix.o matrix.o gem.o main.o matrixException.o handler.o
	$(LD) -o hruskraj matrixType.o sparseMatrix.o denseMatrix.o matrix.o gem.o matrixException.o handler.o main.o

handler.o: src/handler.cpp src/handler.hpp
	$(CXX) $(CFLAGS) -c -o handler.o src/handler.cpp

matrixException.o: src/matrixException.hpp src/matrixException.cpp
	$(CXX) $(CFLAGS) -c -o matrixException.o src/matrixException.cpp

gem.o: src/matrixType.hpp src/gem.hpp src/gem.cpp
	$(CXX) $(CFLAGS) -c -o gem.o src/gem.cpp

matrixType.o: src/matrixType.hpp src/matrixType.cpp
	$(CXX) $(CFLAGS) -c -o matrixType.o src/matrixType.cpp

sparseMatrix.o: src/matrixType.hpp src/sparseMatrix.hpp src/sparseMatrix.cpp
	$(CXX) $(CFLAGS) -c -o sparseMatrix.o src/sparseMatrix.cpp

denseMatrix.o: src/matrixType.hpp src/denseMatrix.hpp src/denseMatrix.cpp
	$(CXX) $(CFLAGS) -c -o denseMatrix.o src/denseMatrix.cpp

matrix.o: src/matrix.hpp src/matrixType.hpp src/denseMatrix.hpp src/sparseMatrix.hpp src/matrixException.hpp src/matrix.cpp
	$(CXX) $(CFLAGS) -c -o matrix.o src/matrix.cpp

main.o: src/main.cpp src/matrix.hpp
	$(CXX) $(CFLAGS) -c -o main.o src/main.cpp

clean:
	rm -f *.o hruskraj
	rm -f -r doc

doc: src/matrix.hpp src/matrixType.hpp src/denseMatrix.hpp src/sparseMatrix.hpp src/matrixException.hpp src/gem.hpp src/handler.hpp src/matrix.cpp src/matrixType.cpp src/denseMatrix.cpp src/sparseMatrix.cpp src/matrixException.cpp src/gem.cpp src/handler.cpp
	doxygen

compile: hruskraj	

run: hruskraj
	valgrind ./hruskraj

	
	

	
