#include <pthread.h>
#include <stdbool.h>

#ifndef _CARROCINHA_H_
#define _CARROCINHA_H_

// representa o tipo de ingrediente
typedef enum TipoIngrediente
{
  PAO,
  SALSICHA,
  MOLHO
} TipoIngrediente;

// struct onde é armazenado a quantidade de ingredientes da carrocinha
// também é armazenado a quantidade de ingredientes que faltam para reabastecer
typedef struct
{
  int pao;
  int salsicha;
  int molho;
} Ingredientes;

// inicializa as structs de ingredientes e de falta de ingredientes
Ingredientes *criarIngredientes();

// consome um ingrediente de cada tipo para fazer um kikão
void consumirIngredientes();

// verifica se é possível fazer um kikão
bool kikaoPossivel();

// reabastece completamente um ingrediente da carrocinha, de acordo com o tipo
void reabastecerIngrediente(TipoIngrediente ingrediente);

// cria a thread da carrocinha
void criarThreadCarrocinha(pthread_t *threadCarrocinha);

// retorna o tempo médio de espera dos clientes
double mediaTempoEspera();

// retorna o tempo médio de espera dos clientes
int totalAtendimentos();

// retorna a quantidade de ingredientes que faltam para reabastecer
Ingredientes faltaIngredientes();

#endif