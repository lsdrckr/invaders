CC=clang
# to be replaced by your own file
TARGET=main
CFLAGS=-g -W -Wall -Wextra
LDFLAGS=-lgraph -lSDL -lSDL_ttf -LGraphique

default: ${TARGET}

list.o: ListeChainee/list.h ListeChainee/list.c
	clang $(CFLAGS) -c ListeChainee/list.c

main.o: main.c ListeChainee/list.h
	clang $(CFLAGS) -c main.c

${TARGET}: main.o list.o
	clang main.o list.o -o $(TARGET) $(LDFLAGS)
	
.PHONY: clean

clean:
	rm -f ${TARGET}
	rm -f *.o
