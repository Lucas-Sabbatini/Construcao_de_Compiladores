# Projeto de Compilador

Este é um projeto de compilador desenvolvido como parte do trabalho da disciplina de Construção de Compiladores. O projeto implementa um analisador léxico e sintático para uma linguagem de programação simples, definida no decorrer do projeto.

## Funcionalidades

O compilador é capaz de realizar as seguintes análises:

  * **Análise Léxica**: Reconhece os tokens da linguagem a partir de um código-fonte de entrada, utilizando uma tabela de transição para identificar palavras reservadas, identificadores, constantes, operadores e separadores.
  * **Análise Sintática**: Verifica se a sequência de tokens do código-fonte obedece às regras gramaticais da linguagem, construindo uma Árvore Sintática Abstrata (AST) para representar a estrutura do programa.
  * **Tabela de Símbolos**: Gerencia os identificadores (variáveis e nome do programa) encontrados no código, armazenando informações como o lexema e o tipo do token.
  * **Tratamento de Erros**: O compilador é capaz de identificar e reportar erros léxicos e sintáticos encontrados no código-fonte.



## Como Compilar e Executar

Para compilar o projeto, basta utilizar o comando `make` no terminal, dentro do diretório do projeto. Isso irá gerar o executável `analisador`.

```bash
make
```

### Executando os Testes

O `Makefile` fornecido contém regras para executar o compilador com diferentes arquivos de teste:

  * **Teste com código correto**: Para analisar um arquivo com a sintaxe correta da linguagem (`testeCorreto.txt`), execute:

    ```bash
    make run
    ```

  * **Teste com erro sintático**: Para analisar um arquivo com um erro sintático (`testeErroSintatico.txt`), execute:

    ```bash
    make run_sintatico
    ```

  * **Teste com erro léxico**: Para analisar um arquivo com um erro léxico (`testeErroLexico.txt`), execute:

    ```bash
    make run_errado
    ```

### Limpando os arquivos

Para remover os arquivos objeto e o executável gerados pela compilação, utilize o comando:

```bash
make clean
```