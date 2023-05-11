CC=clang
# to be replaced by your own file
TARGET=main
CFLAGS=-g -W -Wall -Wextra
LDFLAGS=-lgraph -lSDL -lSDL_ttf -LGraphique
ALLH=ListeChainee/list.h Random/alea.h Deplacement/move.h Collision/collide.h
ALLCH=main.c ListeChainee/list.* Random/alea.* Deplacement/move.* Collision/collide.*


all: ${TARGET}	$(MAKE) -C Graphique $@

list.o: ListeChainee/list.h ListeChainee/list.c
	clang $(CFLAGS) -c ListeChainee/list.c

alea.o: Random/alea.h Random/alea.c
	clang $(CFLAGS) -c Random/alea.c

move.o: Deplacement/move.h Deplacement/move.c
	clang $(CFLAGS) -c Deplacement/move.c
	
collide.o: Collision/collide.h Collision/collide.c
	clang $(CFLAGS) -c Collision/collide.c

main.o: main.c $(ALLH)
	clang $(CFLAGS) -c main.c

${TARGET}: main.o list.o alea.o move.o collide.o
	clang *.o -o $(TARGET) $(LDFLAGS)
	
.PHONY: clean

clean:
	rm -f ${TARGET}
	rm -f *.o

format:
	clang-format -i -style="Webkit" $(ALLCH)

tidy:
	clang-tidy $(ALLCH) --checks="readability-*"
	clang-tidy $(ALLCH) --checks="cppcoreguidelines-init-variables”

