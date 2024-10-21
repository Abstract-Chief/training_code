CC = gcc
FILES = game.c list.c vector.c rectangles.c

game_run: game
	./game

game: $(FILES)
	$(CC) $^  -C -o $@ -lncurses -lm

# $^ is the list of all dependencies
# $@ is the target file

