CC = g++
target = img
sources = $(wildcard *.c)
objects = main.o IO.o filter.o matrix.o

$(target) : $(objects)
	$(CC) $(objects) -o img
	mkdir -p output

main.o : main.cpp
	$(CC) -c main.cpp

IO.o : IO.cpp hdrs/IO.hh
	$(CC) -c IO.cpp

filter.o : filter.cpp hdrs/filter.hh
	$(CC) -c filter.cpp

matrix.o : matrix.cpp hdrs/matrix.hh
	$(CC) -c matrix.cpp

clean: 
	rm *.o $(target)
	rm -rf output/