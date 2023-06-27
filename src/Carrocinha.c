#include <pthread.h>
#include "Geradora.h"
#include "Monitor.h"
#include "Uteis.h"
#include <time.h>
#include "Cliente.h"
#include <stdio.h>
#include <sys/time.h>
#include "Carrocinha.h"
#include <stdbool.h>

#define MAXIMO_INGREDIENTES 10

static pthread_mutex_t mutexCarrocinha;

double tempoTotalEspera = 0;
int numeroAtendimentos = 0;

Ingredientes *ingredientes; // Ingredientes disponíveis
Ingredientes *falta;        // Quantidade de vezes que cada ingrediente faltou

// Tempo de fim do atendimento
struct timeval fimAtendimento;

// rotina de consumo de clientes da fila
void *consumirClientes(void *dado)
{
    (void)dado; // não utilizado

    // flag controlada pela thread de parada
    while (estaExecutando())
    {
        // tenta consumir um cliente da fila
        // se não houver cliente, retorna NULL
        Cliente *cliente = desenfileirarCliente();
        if (cliente != NULL)
        {

            // verifica se há ingredientes suficientes para o atendimento
            // se houver, consome os ingredientes e demora um tempo para preparar o kikão 
            // se não houver, contabiliza a falta de ingredientes
            if (kikaoPossivel())
            {
                consumirIngredientes();

                dormir(faixaRandomica(100, 500));


                // calcula o tempo de fim do atendimento em milissegundos
                gettimeofday(&fimAtendimento, NULL);
                double fimAtendimentoMilis = (fimAtendimento.tv_sec) * 1000.0;
                fimAtendimentoMilis += (fimAtendimento.tv_usec) / 1000.0;

                // contabiliza o tempo de espera do cliente
                // e o número de atendimentos
                tempoTotalEspera += fimAtendimentoMilis - cliente->chegada;
                numeroAtendimentos++;
            }
        }
    }
}

double mediaTempoEspera()
{
    return tempoTotalEspera / numeroAtendimentos;
}

int totalAtendimentos()
{
    return numeroAtendimentos;
}

void criarThreadCarrocinha(pthread_t *threadCarrocinha)
{
    pthread_mutex_init(&mutexCarrocinha, NULL);
    ingredientes = criarIngredientes();
    pthread_create(threadCarrocinha, NULL, consumirClientes, NULL);
}

Ingredientes *criarIngredientes()
{
    ingredientes = malloc(sizeof(Ingredientes));
    ingredientes->pao = MAXIMO_INGREDIENTES;
    ingredientes->salsicha = MAXIMO_INGREDIENTES;
    ingredientes->molho = MAXIMO_INGREDIENTES;

    falta = malloc(sizeof(Ingredientes));
    falta->pao = 0;
    falta->salsicha = 0;
    falta->molho = 0;

    return ingredientes;
}

void consumirIngredientes()
{
    pthread_mutex_lock(&mutexCarrocinha);
    ingredientes->pao--;
    ingredientes->salsicha--;
    ingredientes->molho--;
    pthread_mutex_unlock(&mutexCarrocinha);
}

bool kikaoPossivel()
{
    int pao, salsicha, molho;
    pthread_mutex_lock(&mutexCarrocinha);

    pao = ingredientes->pao;
    salsicha = ingredientes->salsicha;
    molho = ingredientes->molho;
    // printf("Ingredientes: %d pães, %d salsichas, %d molhos\n", pao, salsicha, molho);

    if (pao == 0)
        falta->pao++;
    if (salsicha == 0)
        falta->salsicha++;
    if (molho == 0)
        falta->molho++;
    pthread_mutex_unlock(&mutexCarrocinha);

    return pao > 0 && salsicha > 0 && molho > 0;
}

void reabastecerIngrediente(TipoIngrediente ingrediente)
{
    pthread_mutex_lock(&mutexCarrocinha);
    switch (ingrediente)
    {
    case PAO:
        ingredientes->pao = MAXIMO_INGREDIENTES;
        break;
    case SALSICHA:
        ingredientes->salsicha = MAXIMO_INGREDIENTES;
        break;
    case MOLHO:
        ingredientes->molho = MAXIMO_INGREDIENTES;
        break;
    }
    pthread_mutex_unlock(&mutexCarrocinha);
}

Ingredientes faltaIngredientes()
{
    return *falta;
}