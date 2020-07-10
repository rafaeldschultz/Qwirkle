colors.o: colors.c
	gcc -c colors.c -o colors.o

board.o: board.c
	gcc -c board.c -o board.o

output.o: output.c
	gcc -c output.c -o output.o

game.o: game.c
	gcc -c game.c -o game.o

buffer.o: buffer.c
	gcc -c buffer.c -o buffer.o

main.o: main.c
	gcc -c main.c -o main.o

qwirkle: colors.o board.o output.o main.o game.o buffer.o
	gcc colors.o board.o output.o main.o game.o buffer.o -o qwirkle

all: qwirkle
	
clean:
	rm *.o

run: all
	./qwirkle && make clean
