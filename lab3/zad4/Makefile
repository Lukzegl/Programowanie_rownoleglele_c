LOADER = gcc
CCOMP = gcc

TARGET = zad4
SRC = zad4.c

OPT = -g -DDEBUG

all:$(TARGET)

$(TARGET):$(SRC:.c=.o)
	$(LOADER) $(OPT) $(SRC:.c=.o) -o $(TARGET)

$(SRC:.c=.o):$(SRC)
	$(CCOMP) $(OPT) -c $(SRC) -o $(SRC:.c=.o)

clean:
	rm -f $(TARGET) $(SRC:.c=.o)

run:
	./$(TARGET)