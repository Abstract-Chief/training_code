CC = gcc
FILES = game.c list.c vector.c triangles.c

game_run: game
	./game

game: $(FILES)
	$(CC) $^ -o $@ -lncurses -lm

# $^ is the list of all dependencies
# $@ is the target file

