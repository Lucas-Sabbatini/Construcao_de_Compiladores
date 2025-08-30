#ifndef AUTOMATO_H
#define AUTOMATO_H
#include "../exp.h"

// Retorna o índice do estado inicial (sempre 0 neste caso)
int estado_inicial(void);

// Verifica se o estado é final (1 = sim, 0 = não)
int eh_final(int estado);

// Retorna o tipo de token associado a um estado final
nome_token tipo_final(int estado);

// Retorna próximo estado para dado caractere ou -1 se não houver transição
int move(int estado, int c);

#endif
