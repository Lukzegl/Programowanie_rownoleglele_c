# kompilator c
CCOMP = gcc

# konsolidator
LOADER = gcc

# opcje optymalizacji:
# wersja do debugowania
OPT = -g -DDEBUG
# wersja zoptymalizowana do mierzenia czasu
#OPT = -O3

# pliki naglowkowe
#INC = -I../pomiar_czasu

# biblioteki
#LIB = -L../pomiar_czasu -lpomiar_czasu -lm

# zaleznosci i komendy

TARGET = zad2
SRC = zad2.c

all: $(TARGET)

$(TARGET): $(SRC:.c=.o)
	$(LOADER) $(OPT) $(SRC:.c=.o) -o $(TARGET)

$(SRC:.c=.o): $(SRC)
	$(CCOMP) $(OPT) -c $(SRC) -o $(SRC:.c=.o)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET) $(SRC:.c=.o)