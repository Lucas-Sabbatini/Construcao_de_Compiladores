CC = gcc
CFLAGS = -Wall -g -I. 
TARGET = analisador

SOURCES = $(wildcard *.c) $(wildcard lexico/*.c) $(wildcard tabela_simbolos/*.c) $(wildcard sintatico/*.c)
OBJECTS = $(SOURCES:.c=.o)
DEPS = $(wildcard *.h) $(wildcard lexico/*.h) $(wildcard tabela_simbolos/*.h) $(wildcard sintatico/*.h)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS)

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

run: all
	./$(TARGET) testeCorreto.txt

run_sintatico: all
	./$(TARGET) testeErroSintatico.txt

run_errado: all
	./$(TARGET) testeErroLexico.txt

clean:
	rm -f $(TARGET) $(OBJECTS)