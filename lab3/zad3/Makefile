CCOMP = gcc
LOADER = gcc

OPT = -g -DDEBUG

TARGET = zad3
SRC = zad3.c

all: $(TARGET)

$(TARGET): $(SRC:.c=.o)
	$(LOADER) $(OPT) $(SRC:.c=.o) -o $(TARGET)

$(SRC:.c=.o): $(SRC)
	$(CCOMP) $(OPT) -c $(SRC) -o $(SRC:.c=.o)

clean:
	rm -f $(TARGET) $(SRC:.c=.o)

run:
	./$(TARGET)
