#include "estrutura.h"
#include "paralelo.h"

//Criar noh da arvore
//@param valor: serah o valor da resistencia do resistor
//@param tipo: qual o tipo de assossiacao (serie ou paralelo)
//Caso a funcao apresente algum erro ela retornarah NULL
//Futuramente a variavel tipo tambem informarah se serah um resistor, capacitor ou indutor
Tree* criar_tree(double valor, char tipo){
    //Alocacao
    Tree* arvore = (Tree*)malloc(sizeof(Tree));

    //Verificacao de seguranca
    if( arvore != NULL){
        arvore->res.valor = valor;
        arvore->res.tipo = tipo;
        arvore->dir = arvore->esq = NULL; //Tanto o lado esquerdo quanto o direito sao setados como NULL

        return arvore;
    }else{
        printf("Erro na criacao do noh da arvore, funcao criar_tree");
        return NULL;
    }
}

//Funcao para calcular a resistencia total
//Observacao: Ver a possibilidade de colocar os valores do noh esquerdo e direito numa fila e depois chamar a funcao "paralelo_req" para calcular a resistencia em paralelo
//@param arvore: serah o noh raiz da arvore para podermos navegar

double res_misto(Tree* arvore){
    if( arvore == NULL){
        return 0;
    }

    //Caso seja um resistor
    if( arvore->res.tipo == 'R'){
        return arvore->res.valor;
    }

    //Chamada recursiva para a direita e para a esquerda da arvore
    double resist_esq = res_misto(arvore->esq);
    double resist_dir = res_misto(arvore->dir);

    //Espacao para adicionar o enfileirar

    //Verificar o tipo da associacao (serie ou paralelo)
    if( arvore->res.tipo == 'S'){
        return resist_dir + resist_esq;
    }else if( arvore->res.tipo == 'P'){
        return (resist_dir * resist_esq) / (resist_dir + resist_esq);
    }

    return 0;

}

/* ----- Funcoes responsaveis pelo empilhamento da expressao de entrada para jogarmos na arvore*/


//Empilhar
//Caso esta funcao apresente algum erro ela retornarah NULL
//@param topo: receberemos o endereco do topo da pilha
//@param raiz: receberemos a raiz da arvore(topo da arvore) para inserir na pilha
Pilha* push(Pilha* topo, Tree* raiz){
    //Alocacao
    Pilha* stack = (Pilha*)malloc(sizeof(Pilha));

    //Verificacao de seguranca
    if( stack != NULL){
        stack->arvore = raiz;
        stack->prox = topo;

        return stack;
    }else{
        printf("Erro na alocacao de memoria da pilha,funcao push\n");
        return NULL;
    }
}

//Desempilhar
Pilha* pop(Pilha** topo){
    //Pilha vazia
    if( *topo == NULL) return NULL;

    //Criamos um auxiliar para nao perdermos a referencia original da pilha
    Pilha* aux = *topo;
    *topo = (*topo)->prox;
    return aux;
}

//Funcao responsavel por ler e construir a arvore
//Caso esta funcao apresente erro ela retornarah NULL
//Esta funcao irah analisar a expressao e no final retornah um ponteiro para o endereco da raiz da arvore
Tree* processar_expressao(char* expressao){
    Pilha* stack = NULL;
    char* palavra = strtok(expressao, " ()");

    while( palavra != NULL){
        if( strcmp( palavra, "S") == 0 || strcmp(palavra, "P") == 0){
            Tree* raiz = criar_tree(0,palavra[0]);
            //Verificacao de seguranca
            if( raiz != NULL){
                stack = push(stack,raiz);
            }else{
                printf("Erro na alocacao da raiz, funcao processar_expressao");
                return NULL;
            }
        }else if( strcmp(palavra, "R") == 0){
            palavra = strtok(NULL, " ()");
            double valor = atof(palavra);
            Tree* raiz = criar_tree(valor, 'R');
            //Verificacao de seguranca
            if( raiz != NULL){
                stack = push(stack,raiz);
            }else{
                printf("Erro na alocacao da raiz, funcao processar_expressao");
                return NULL;
            }
        }else if( strcmp(palavra, ")") == 0){
            Pilha* dir_node = pop(&stack);
            Pilha* esq_node = pop(&stack);
            Pilha* op_node = pop(&stack);

            if (dir_node == NULL || esq_node == NULL || op_node == NULL) {
                printf("Erro ao processar a expressão: pilha vazia\n");
                return NULL;
            }

            Tree* op = op_node->arvore;
            op->esq = esq_node->arvore;
            op->dir = dir_node->arvore;

            free(dir_node);
            free(esq_node);
            free(op_node);

            stack = push(stack, op);
        }

        palavra = strtok(NULL, " ()");
    }
    /*
    if( stack == NULL){
        printf("Erro: Expressão malformada\n");
        return NULL;
    }
*/
    Tree* raiz = pop(&stack)->arvore;

    return raiz;
}

//Funcao para liberar a memoria alocada da arvore
void liberar_arvore(Tree* raiz) {
    if (raiz == NULL) return;
    liberar_arvore(raiz->esq);
    liberar_arvore(raiz->dir);
    free(raiz);
}


void imprimir_arvore(Tree* arvore, int nivel) {
    if (arvore == NULL) return;

    for (int i = 0; i < nivel; i++) printf("  ");
    if (arvore->res.tipo == 'R') {
        printf("[R: %.2lf ohms]\n", arvore->res.valor);
    } else {
        printf("[%c]\n", arvore->res.tipo);
    }
    imprimir_arvore(arvore->esq, nivel + 1);
    imprimir_arvore(arvore->dir, nivel + 1);
}
