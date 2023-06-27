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

    while (estaExecutando())
    {
        Cliente *cliente = desenfileirarCliente();
        if (cliente != NULL)
        {
            if (kikaoPossivel())
            {
                consumirIngredientes();

                dormir(faixaRandomica(100, 500));

                gettimeofday(&fimAtendimento, NULL);

                double fimAtendimentoMilis = (fimAtendimento.tv_sec) * 1000.0; // sec to ms
                fimAtendimentoMilis += (fimAtendimento.tv_usec) / 1000.0;      // us to ms
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