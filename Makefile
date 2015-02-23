NAME=zentwm

CFLAGS	+=-Wall -Ilibswc --std=c++11
LDFLAGS	+=-lm

CFLAGS	+= $(shell pkg-config --cflags swc)
LDFLAGS	+= $(shell pkg-config --libs swc)

SRCN=wm
SRCF=$(patsubst %,src/%,$(SRCN))
SRC=$(patsubst %,%.cpp,$(SRCF))
OBJ=$(patsubst %,%.o,$(SRCF))

.PHONY: all
all: $(NAME)

.PHONY: $(NAME)
$(NAME): $(OBJ)
	$(CXX) $(LDFLAGS) $(CFLAGS) $(OBJ) -o $(NAME)
