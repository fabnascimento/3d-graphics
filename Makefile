build:
	gcc -Wall -std=c99 -lSDL2 ./src/*.c -o renderer

run:
	./renderer

clean:
	rm renderer

