CC = gcc
CFLAGS = -Wall -g -I. 
TARGET = analisador

SOURCES = $(wildcard *.c) $(wildcard lexico/*.c) $(wildcard tabela_simbolos/*.c)

OBJECTS = $(SOURCES:.c=.o)

DEPS = $(wildcard *.h) $(wildcard lexico/*.h) $(wildcard tabela_simbolos/*.h)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS)

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

run: all
	./$(TARGET) testeCorreto.txt

run_sintatico: all
	./$(TARGET) testeSintaticoCorreto.txt

run_errado: all
	./$(TARGET) testeErrado.txt

clean:
	rm -f $(TARGET) $(OBJECTS)