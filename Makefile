CC = gcc
CFLAGS = -Wall -g

TARGET = analisador

SOURCES = exp.c parser.c tabela_simbolos.c token_string.c

FLEX = flex

all: $(TARGET)

$(TARGET): $(SOURCES) lex.yy.c
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCES) lex.yy.c

lex.yy.c: exp.lex exp.h
	$(FLEX) -o lex.yy.c exp.lex

exp.o: exp.c exp.h parser.h tabela_simbolos.h
	$(CC) $(CFLAGS) -c exp.c

parser.o: parser.c parser.h exp.h
	$(CC) $(CFLAGS) -c parser.c

tabela_simbolos.o: tabela_simbolos.c tabela_simbolos.h exp.h
	$(CC) $(CFLAGS) -c tabela_simbolos.c

token_string.o: token_string.c exp.h parser.h
	$(CC) $(CFLAGS) -c token_string.c

.PHONY: run clean

run: all
	./$(TARGET) testeCorreto.txt

clean:
	rm -f $(TARGET) lex.yy.c *.o


