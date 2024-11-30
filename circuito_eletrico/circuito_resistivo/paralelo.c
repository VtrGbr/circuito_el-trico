#include "estrutura.h"

/*
Funcoes que serao implementadas neste arquivo:
    - Criacao do noh da fila
    - Enfileirar (fila de prioridade, do menor para o maior valor)
    - Desenfileirar
    - Calculo da resistencia em resitores paralelos
    - Calculo da corrente total do circuito
    - Calculo da tensao total do circuito 
    - Funcao para ir adicionando os resistores na fila
*/

//Criar noh da fila
//Observacao: Inicialmente a criacao do noh adicionarah apenas o valor da resistencia, mas futuramente esta funcao serah modificida para adicionar os outros valores necessarios, como corrente, tensao e o tipo. Então, lembre-se de modificar nas funcoes que usaram esta
//@param resistencia: Valor do resistor que serah colocado na fila
//Caso ocorra algum problema na alocacao do noh, a funcao retornarah "NULL" para indicar que houve um erro
Fila* criar_noh( double resistencia){
    //Alocacao do noh
    Fila* noh = (Fila*)malloc(sizeof(Fila));

    //Verificacao de seguranca
    if( noh != NULL){
        noh->res.valor = resistencia;
        noh->res.tipo = 'p';
        noh->res.corrente = 0.0;
        noh->res.tensao = 0.0;
        noh->prox = NULL;

        return noh;
    }else{
        printf("Erro na alocacao de memoria do noh, funcao criar_noh");
        return NULL;
    }
}

//Enfileirar
//@param queue: Fila que construiremos
//@param fila: Fila que receberemos
//@param resistor: struct do resistor que adicionaremos na fila
void enfileirar(Fila** fila,Resistor resistor){
    //Alocacao do noh
    Fila* queue = (Fila*)malloc(sizeof(Fila));
    Fila* aux;

    //Verificacao de seguranca
    if( queue != NULL){
        queue->res = resistor;
        queue->prox = NULL;

        //Fila vazia
        if( *fila == NULL || resistor.valor < (*fila)->res.valor){
            queue->prox = *fila;
            *fila = queue;
        }else{
            aux = *fila;
            // Percorrer a fila
            while( aux->prox != NULL && aux->prox->res.valor <= resistor.valor){
                aux = aux->prox;
            }

            queue->prox = aux->prox;
            aux->prox = queue;

        }

    }else{
        printf(" Houve erro na alocacao do noh da fila, funcao enfileirar");
        return; // Houve erro na alocacao do noh da fila
    }


}

//Desenfileirar
//@param remover: serah a estrutura que removeremos
Fila* dequeue( Fila** fila){
    Fila* remover = NULL; // Noh que serah removido
    
    if( *fila != NULL){
        remover = *fila;
        *fila = remover->prox;
    }else{
        printf("Fila vazia!\n");
    }

    return remover;
}

//Resistencia equivalente de resistores paralelos
//@param res1, res2: serao ponteiros que usarmos para guardar os valores dos menores resistores
//@param ra: serah o noh que iremos inserir na fila com o valor da resistencia equivalente entre dois resistores
//@param temporario: serah a variavel que usaremos para guardar o valor da resistencia equivalente entre dois resistores para colocarmos na funcao criar noh, para fins praticos
//Condicao de parada serah quando "prox" apontar para NULL
//Caso a funcao apresente algum erro na parte de criar o noh ra, ele retornarah "NULL"

Fila* paralelo_req(Fila* queue){
    Fila* res1, *res2,*ra;
    double temporario;

    while( queue != NULL && queue->prox != NULL){
        res1 = dequeue(&queue);
        res2 = dequeue(&queue);

        temporario = (res1->res.valor * res2->res.valor) / (res1->res.valor + res2->res.valor);
        //Chamar a funcao criar noh
        ra = criar_noh(temporario);

        //Verificacao de seguranca
        if( ra != NULL){
            enfileirar(&queue,ra->res);
        }else{
            printf("Erro na alocacao do noh ra, funcao paralelo_req\n");
            return NULL;
        }
    }

    //Quando o processo terminar retorne a estrutura que estah na fila
    return dequeue(&queue);
}

//Corrente total 
double corrente_total( double tensao, double resistencia){
    return tensao / resistencia;
}

//Tensao total
double tensao_total( double corrente, double resistencia){
    return corrente * resistencia;
}

//Adicionar os resistores ( servirah para ser posto na main)
//@param valor: valor da resistencia que serah pedido que o usuario digite
//@param resistencia: serah o noh que usaremos para colocar na funcao enfileirar
//Observacao: Futuramente podemos mudar esta funcao para que ao inves do usuario ter que informar a quantidade de resistores, o programa peca que seja inserido ate ser "EOF"
void adicionar_resistor(Fila** queue, int qtd){
    double valor;
    Fila* resistencia;

    for( int i = 0; i < qtd; i++){
        printf("Digite o valor da resistencia: \n");
        scanf("%lf",&valor);

        //Criar noh
        resistencia = criar_noh(valor);
        //Verificacao de seguranca
        if( resistencia != NULL){
            enfileirar(queue,resistencia->res);
        }else{
            printf("Houve erro na criacao do noh resistencia");
            return; // Houve erro na criacao do noh "resistencia"
        }
    }


}

//Funcao para calcular tensao total, corrente total ou algum outro calculo de resultado equivalente total
//@param valor1,valor2: estas duas variaveis podem vir a ser resistencia, tensao ou corrente
//Caso deseje calcular a corrente total, valor1 = tensao, valor2 = resistencia;
//Caso deseje a tensao total valor1 = corrente, valor2 = resistencia;
double calculo_total( double (*Funcao)(double,double),double valor1,double valor2){
    return Funcao(valor1,valor2);
}