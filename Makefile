#
# Makefile para o projeto do Compilador
#

# Compilador e flags
CC = gcc
CFLAGS = -Wall -g -I.

# Arquivos fonte
SRCS = exp.c \
       lexico/lexico.c \
       lexico/tabela_transicao.c \
       tabela_simbolos/tabela_simbolos.c

# Arquivos objeto (gerados a partir dos fontes)
OBJS = $(SRCS:.c=.o)

# Nome do executável
EXEC = compilador

# Alvo principal: compila o projeto
all: $(EXEC)

# Regra para linkar os arquivos objeto e criar o executável
$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJS)

# Regra para compilar os arquivos fonte (.c) em arquivos objeto (.o)
# O -I. é adicionado para que os includes como "exp.h" sejam encontrados
# a partir do diretório raiz do projeto.
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Alvo para limpar os arquivos gerados (objetos e executável)
clean:
	rm -f $(OBJS) $(EXEC)

# Alvo para executar o compilador com o arquivo de teste correto
run: all
	./$(EXEC) testeCorreto.txt

# Alvo para executar o compilador com o arquivo de teste com erros
run_error: all
	./$(EXEC) testeErrado.txt

# Phony targets não representam arquivos
.PHONY: all clean run run_error