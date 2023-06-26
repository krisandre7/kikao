#include <pthread.h>
#include "Geradora.h"
#include "Monitor.h"
#include "Uteis.h"
#include <time.h>
#include "Cliente.h"

void *consumirClientes(void *dado)
{
    (void)dado; // Top 10 truques

    while (estaExecutando())
    {
        Cliente *cliente = desenfileirarCliente();

        if (cliente != NULL)
        {
            printf("Removido! ");
            imprimirCliente(*cliente);
            dormir(faixaRandomica(100,300));
        } else {
            dormir(10);
        }
    }
}

void criarThreadCarrocinha(pthread_t *threadCarrocinha)
{
    pthread_create(threadCarrocinha, NULL, consumirClientes, NULL);
}
