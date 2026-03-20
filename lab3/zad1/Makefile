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

TARGET = pthreads_detach_kill
SRC = pthreads_detach_kill.c

all: $(TARGET)

$(TARGET): $(SRC:.c=.o)
	$(LOADER) $(OPT) $(SRC:.c=.o) -o $(TARGET)

$(SRC:.c=.o): $(SRC)
	$(CCOMP) -c $(OPT) $(SRC) -o $(SRC:.c=.o)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(SRC:.c=.o) $(TARGET)

