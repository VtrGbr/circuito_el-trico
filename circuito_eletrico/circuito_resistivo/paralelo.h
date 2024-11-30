#ifndef paralelo_h
#define paralelo_h

#include "estrutura.h"

//Observacao: Inicialmente a criacao do noh adicionarah apenas o valor da resistencia, mas futuramente esta funcao serah modificida para adicionar os outros valores necessarios, como corrente, tensao e o tipo. Então, lembre-se de modificar nas funcoes que usaram esta
//@param resistencia: Valor do resistor que serah colocado na fila
//Caso ocorra algum problema na alocacao do noh, a funcao retornarah "NULL" para indicar que houve um erro
Fila* criar_noh( double resistencia);

//@param queue: Fila que construiremos
//@param fila: Fila que receberemos
//@param resistor: struct do resistor que adicionaremos na fila
void enfileirar(Fila** fila,Resistor resistor);

//@param remover: serah a estrutura que removeremos
Fila* dequeue( Fila** fila);

//Resistencia equivalente de resistores paralelos
//@param res1, res2: serao ponteiros que usarmos para guardar os valores dos menores resistores
//@param ra: serah o noh que iremos inserir na fila com o valor da resistencia equivalente entre dois resistores
//@param temporario: serah a variavel que usaremos para guardar o valor da resistencia equivalente entre dois resistores para colocarmos na funcao criar noh, para fins praticos
//Condicao de parada serah quando "prox" apontar para NULL
//Caso a funcao apresente algum erro na parte de criar o noh ra, ele retornarah "NULL"

Fila* paralelo_req(Fila* queue);

//Corrente total 
double corrente_total( double tensao, double resistencia);

//Tensao total
double tensao_total( double corrente, double resistencia);

//Adicionar os resistores ( servirah para ser posto na main)
//@param valor: valor da resistencia que serah pedido que o usuario digite
//@param resistencia: serah o noh que usaremos para colocar na funcao enfileirar
//Observacao: Futuramente podemos mudar esta funcao para que ao inves do usuario ter que informar a quantidade de resistores, o programa peca que seja inserido ate ser "EOF"
void adicionar_resistor(Fila** queue, int qtd);

//Funcao para calcular tensao total, corrente total ou algum outro calculo de resultado equivalente total
//@param valor1,valor2: estas duas variaveis podem vir a ser resistencia, tensao ou corrente
//Caso deseje calcular a corrente total, valor1 = tensao, valor2 = resistencia;
//Caso deseje a tensao total valor1 = corrente, valor2 = resistencia;
double calculo_total( double (*Funcao)(double,double),double valor1,double valor2);

#endif
