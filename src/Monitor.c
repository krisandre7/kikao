#include <stdio.h>
#include <pthread.h>
#include <stdbool.h>
#include "Geradora.h"
#include "Carrocinha.h"
#include "Reabastecedor.h"

static pthread_mutex_t mutexExecutando;

static bool executando = true;

bool estaExecutando()
{
    pthread_mutex_lock(&mutexExecutando);

    bool retorno = executando;

    pthread_mutex_unlock(&mutexExecutando);

    return retorno;
}

void definirExecutando(bool valor)
{
    pthread_mutex_lock(&mutexExecutando);

    executando = valor;

    pthread_mutex_unlock(&mutexExecutando);
}

void *threadParada(void *dado)
{
    (void)dado; // não utilizado

    getchar();

    definirExecutando(false);

    printf("Tempo de Espera Médio: %.0lf\n", mediaTempoEspera());
    printf("Número de clientes atendidos: %d\n", totalAtendimentos());

    Ingredientes faltas = faltaIngredientes();
    printf("Número de faltas de pao: %d\n", faltas.pao);
    printf("Número de faltas de salsicha: %d\n", faltas.salsicha);
    printf("Número de faltas de molho: %d\n", faltas.molho);

    return NULL;
}

void iniciarThreads()
{
    pthread_mutex_init(&mutexExecutando, NULL);
    pthread_t threadParada, threadGeradora, threadCarrocinha, threadPao, threadSalsicha, threadMolho;
    executando = true;

    printf("Simulação iniciada! Aperte ENTER para interromper e mostrar estatísticas.\n");
    criarThreadGeradora(&threadGeradora);
    pthread_create(&threadParada, NULL, threadParada, NULL);
    criarThreadCarrocinha(&threadCarrocinha);
    criarThreadReabastecedor(&threadPao, &threadSalsicha, &threadMolho);

    pthread_join(threadGeradora, NULL);
    pthread_join(threadParada, NULL);
    pthread_join(threadCarrocinha, NULL);
    pthread_join(threadPao, NULL);
    pthread_join(threadSalsicha, NULL);
    pthread_join(threadMolho, NULL);
}