#include "FilaClientes.h"
#include <pthread.h>
#include "Cliente.h"
#include <stdlib.h>
#include "Uteis.h"
#include "time.h"
#include "Monitor.h"

void configurarClientes()
{
    filaClientes = FilaClientesNew();
}

void *gerarClientes(void *dado)
{
    (void)dado; // Top 10 truques

    while (estaExecutando())
    {
        Cliente *cliente = malloc(sizeof(Cliente));

        cliente->chegada = milissegundos();
        cliente->inicioAtendimento = 0;
        cliente->fimAtendimento = 0;

        enfileirarCliente(*cliente);
        printf("Adicionado! ");
        imprimirCliente(*clienteFinal());

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
