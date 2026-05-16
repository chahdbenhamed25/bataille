CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c99 -pedantic
OBJ = main.o liste.o file.o pile.o jeu.o
TARGET = bataille

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

main.o: main.c jeu.h
liste.o: liste.c liste.h carte.h jeu.h
file.o: file.c file.h carte.h jeu.h
pile.o: pile.c pile.h carte.h file.h
jeu.o: jeu.c jeu.h liste.h file.h pile.h

clean:
	rm -f $(OBJ) $(TARGET)

run: $(TARGET)
	./$(TARGET)
