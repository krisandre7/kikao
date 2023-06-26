#include <stdio.h>
#include <pthread.h>
#include <stdbool.h>
#include "Geradora.h"
#include "Carrocinha.h"

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

void *threadParadaRotina(void *dado)
{
    (void)dado;

    getchar();

    definirExecutando(false);

    return NULL;
}

void iniciarThreads()
{
    pthread_mutex_init(&mutexExecutando, NULL);
    pthread_t threadParada, threadGeradora, threadCarrocinha;
    executando = true;

    criarThreadGeradora(&threadGeradora);
    pthread_create(&threadParada, NULL, threadParadaRotina, NULL);
    criarThreadCarrocinha(&threadCarrocinha);

    pthread_join(threadGeradora, NULL);
    pthread_join(threadParada, NULL);
    pthread_join(threadCarrocinha, NULL);
}