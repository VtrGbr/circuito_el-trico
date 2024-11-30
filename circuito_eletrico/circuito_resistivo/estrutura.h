#ifndef estrutura_h
#define estrutura_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
Arquivo responsavel pelas estruturas do programa
*/

//Estrutura do resistor
typedef struct resistor{
    double valor; // Valor da resistencia do resistor
    char tipo; // Se ele estah em serie ou em paralelo
    //Tanto "corrente" quanto "tensao" serao usadas para futuras aplicacoes, como queda de tensao individual em cada componente eletrico e corrente em cada componente eletrico
    double corrente;
    double tensao;
}Resistor;

//Estutura da fila
typedef struct fila{
    Resistor res;
    struct fila *prox;
}Fila;
#endif