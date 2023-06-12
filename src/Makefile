IDIR =../include
CC=std=c++11
CFLAGS=-I$(IDIR)

ODIR=obj
LDIR =../lib

_DEPS = deck.hpp card.hpp
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ =  main.o deck.o card.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

test: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(IDIR)/*~ 
