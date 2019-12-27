all: test start clean

Lab_2.o:Lab_2.c
	gcc -c -o Lab_2.o Lab_2.c
test: Lab_2.o
	gcc -o test Lab_2.o
start:
	./test
clean: Lab_2.o
	rm -rf Lab_2.o test
