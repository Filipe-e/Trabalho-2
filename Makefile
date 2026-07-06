CC = gcc
RM = rm
TARGET = industria

all: objetos
	$(CC) main.o menus.o functions.o -o $(TARGET)

objetos: main.c ./src/menus.c ./src/functions.c
	$(CC) -c main.c
	$(CC) -c ./src/menus.c
	$(CC) -c ./src/functions.c

clean:
	$(RM) *.o 
	$(RM) $(TARGET)		
