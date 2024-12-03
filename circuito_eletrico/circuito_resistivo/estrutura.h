#ifndef estrutura_h
#define estrutura_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <complex.h> // Para uso dos numeros complexos

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

//Estrutura da arvore
typedef struct arvore{
    Resistor res;
    struct arvore* dir,*esq;
}Tree;

//Estrutura para a pilha
typedef struct pilha {
    Tree* arvore;
    struct pilha* prox;
} Pilha;
#endif