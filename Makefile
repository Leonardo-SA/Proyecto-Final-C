all: p1 p2 p3 run clean

p1: proyecto1.c
	gcc proyecto1.c -o exe 

p2: proyecto2.c
	gcc proyecto2.c -o exe -lm

p3: proyecto3.c
	gcc proyecto3.c -o exe

run:
	./exe

clean:
	rm -f exe
	
