CC=clang
# to be replaced by your own file
TARGET=main
CFLAGS=-g -W -Wall -Wextra
LDFLAGS=-lgraph -lSDL -lSDL_ttf -LGraphique

default: ${TARGET}

list.o: ListeChainee/list.h ListeChainee/list.c
	clang $(CFLAGS) -c ListeChainee/list.c

alea.o: Random/alea.h Random/alea.c
	clang $(CFLAGS) -c Random/alea.c

main.o: main.c ListeChainee/list.h Random/alea.h
	clang $(CFLAGS) -c main.c

${TARGET}: main.o list.o alea.o
	clang *.o -o $(TARGET) $(LDFLAGS)
	
.PHONY: clean

clean:
	rm -f ${TARGET}
	rm -f *.o
