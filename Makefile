NAME=zentwm

CC=g++
CFLAGS=-Ilibswc --std=c++11
LDFLAGS=-lm

SRCF=wm.cpp

CFLAGS	+= `pkg-config --cflags swc`
LDFLAGS	+= `pkg-config --libs swc`

SRC=$(patsubst %,src/%,$(SRCF))
OBJ = obj/$(NAME).o

all:
	mkdir -p obj
	echo $(LDFLAGS)
	$(CC) $(CFLAGS) $(SRC) -c -o obj/$(NAME).o
	$(CC) $(LDFLAGS) $(OBJ) -o $(NAME)

clean:
	rm -rf obj bin
