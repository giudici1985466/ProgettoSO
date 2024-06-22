all: test

csv_managing.o:	csv_managing.c csv_managing.h
	gcc -c -o csv_managing.o csv_managing.c

main.o:	main.c csv_managing.h
	gcc -c -o main.o main.c

test: main.o csv_managing.o
	gcc -o test main.o csv_managing.o

clean:
	rm *.o test ../record/*.csv