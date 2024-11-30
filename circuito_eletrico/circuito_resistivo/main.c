#include "paralelo.h"

int main(){
    Fila* queue = NULL;
    Fila* resistencia_equivalente;
    int qtd,opcao;
    double corrente, tensao,i_total;

    printf("Digite a quantidade de resistores: \n");
    scanf("%d",&qtd);

    adicionar_resistor(&queue,qtd);

    resistencia_equivalente = paralelo_req(queue);
    if (resistencia_equivalente != NULL) {
        printf("Resistencia total do circuito: %.2lf ohm.\n", resistencia_equivalente->res.valor);
    } else {
        printf("Erro ao calcular a resistência equivalente.\n");
        return 1;
    }

    printf("\nQual calculo total voce deseja?\nDigite:\n 1 - Corrente;\n 2- Tensao.\n");
    scanf("%d",&opcao);

    if( opcao == 1){
        printf("Digite o valor da tensao total: \n");
        scanf("%lf",&tensao);
        i_total = calculo_total(corrente_total,tensao,resistencia_equivalente->res.valor);
        printf("Corrente total do circuito: %.2lf A.",i_total);

    }else if(opcao == 2){
        printf("Digite o valor da corrente total: \n");
        scanf("%lf",&corrente);
        i_total = calculo_total(tensao_total,corrente,resistencia_equivalente->res.valor);
        printf("Tensao total do circuito: %.2lf V.",i_total);

    }

    // Liberação de memória (recomenda-se implementar uma função para isso)
    while (queue != NULL) {
        Fila* temp = dequeue(&queue);
        free(temp);
    }
    free(resistencia_equivalente);

    return 0;

}