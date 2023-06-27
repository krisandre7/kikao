#include "FilaClientes.h"
#include <pthread.h>
#include "Cliente.h"
#include <stdlib.h>
#include "Uteis.h"
#include "Monitor.h"
#include <stdbool.h>
#include <sys/time.h>
struct timeval tempoChegada;

void configurarClientes()
{
    filaClientes = FilaClientesNew();
}

void *gerarClientes(void *dado)
{
    (void)dado; // não utilizado

    while (estaExecutando())
    {
        Cliente *cliente = malloc(sizeof(Cliente));

        gettimeofday(&tempoChegada, NULL);

        double tempoChegadaMilis = (tempoChegada.tv_sec) * 1000.0; // sec to ms
        tempoChegadaMilis += (tempoChegada.tv_usec) / 1000.0;      // us to ms
        cliente->chegada = tempoChegadaMilis;

        bool resposta = enfileirarCliente(*cliente);

        free(cliente);

        dormir(faixaRandomica(50, 500));
    }

    return NULL;
};

void criarThreadGeradora(pthread_t *threadGeradora)
{
    configurarClientes();
    pthread_create(threadGeradora, NULL, gerarClientes, NULL);
}
