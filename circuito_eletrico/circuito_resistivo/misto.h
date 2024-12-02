#ifndef misto_h
#define misto_h

#include "estrutura.h"
#include "paralelo.h"

//Criar noh da arvore
//@param valor: serah o valor da resistencia do resistor
//@param tipo: qual o tipo de assossiacao (serie ou paralelo)
//Caso a funcao apresente algum erro ela retornarah NULL
//Futuramente a variavel tipo tambem informarah se serah um resistor, capacitor ou indutor
Tree* criar_tree(double valor, char tipo);

//Funcao para calcular a resistencia total
//Observacao: Ver a possibilidade de colocar os valores do noh esquerdo e direito numa fila e depois chamar a funcao "paralelo_req" para calcular a resistencia em paralelo
//@param arvore: serah o noh raiz da arvore para podermos navegar

double res_misto(Tree* arvore);

//Empilhar
//Caso esta funcao apresente algum erro ela retornarah NULL
//@param topo: receberemos o endereco do topo da pilha
//@param raiz: receberemos a raiz da arvore(topo da arvore) para inserir na pilha
Pilha* push(Pilha* topo, Tree* raiz);

//Desempilhar
Pilha* pop(Pilha** topo);

//Funcao responsavel por ler e construir a arvore
//Caso esta funcao apresente erro ela retornarah NULL
//Esta funcao irah analisar a expressao e no final retornah um ponteiro para o endereco da raiz da arvore
Tree* processar_expressao(char* expressao);

//Funcao para liberar a memoria alocada da arvore
void liberar_arvore(Tree* raiz);

//Imprimir a arvore
void imprimir_arvore(Tree* arvore, int nivel);

#endif