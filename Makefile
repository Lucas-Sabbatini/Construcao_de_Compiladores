CC = gcc

CFLAGS = -Wall -g

TARGET = analisador

SOURCES = exp.c lex.yy.c tabela_simbolos.c

FLEX = flex

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCES)

lex.yy.c: exp.lex exp.h
	$(FLEX) -o lex.yy.c exp.lex

run: all
	./$(TARGET) teste.txt

clean:
	rm -f $(TARGET) lex.yy.c *.o