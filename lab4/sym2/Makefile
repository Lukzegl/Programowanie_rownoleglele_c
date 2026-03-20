CCOMP = gcc
LOADER = gcc
#OPT = -g -DDEBUG
TARGET = sym2
SRC = pub_sym2.c

all: $(TARGET)

all: $(TARGET)

$(TARGET): $(SRC:.c=.o)
	$(LOADER) $(SRC:.c=.o) -o $(TARGET)

$(SRC:.c=.o): $(SRC)
	$(CCOMP) -c $(SRC) -o $(SRC:.c=.o)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(SRC:.c=.o) $(TARGET)