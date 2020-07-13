colors.o: colors.c
	gcc -c colors.c -o colors.o

board.o: board.c
	gcc -c board.c -o board.o

blocks.o: blocks.c
	gcc -c blocks.c -o blocks.o

players.o: players.c
	gcc -c players.c -o players.o

output.o: output.c
	gcc -c output.c -o output.o

buffer.o: buffer.c
	gcc -c buffer.c -o buffer.o

game.o: game.c 
	gcc -c game.c -o game.o

pontuacao.o: pontuacao.c
	gcc -c pontuacao.c -o pontuacao.o

main.o: main.c
	gcc -c main.c -o main.o

qwirkle: colors.o board.o output.o main.o buffer.o players.o blocks.o game.o pontuacao.o
	gcc colors.o board.o output.o main.o buffer.o players.o blocks.o game.o pontuacao.o -o qwirkle

all: qwirkle
	
clean:
	rm *.o

run: all
	./qwirkle && make clean
