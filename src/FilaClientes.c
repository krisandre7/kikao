#include "FilaClientes.h"
#include <stdlib.h>
#include "Cliente.h"
#include <pthread.h>

static pthread_mutex_t mutexFilaClientes;

FilaClientes *FilaClientesNew()
{
    pthread_mutex_init(&mutexFilaClientes, NULL);
    printf("Mutex iniciado!\n");
    filaClientes = malloc(sizeof(FilaClientes));
    filaClientes->tamanho = 0;
    filaClientes->frente = 0;
    return filaClientes;
}

void FilaClientesDelete()
{
    free(filaClientes);
}

void enfileirarCliente(Cliente cliente)
{
    pthread_mutex_lock(&mutexFilaClientes);
    if (filaClientes->tamanho == MAXIMO_CLIENTES)
    {
        pthread_mutex_unlock(&mutexFilaClientes);
        return;
    }

    int indiceEscrita = (filaClientes->frente + filaClientes->tamanho) % MAXIMO_CLIENTES;
    filaClientes->clientes[indiceEscrita] = cliente;

    filaClientes->tamanho++;
    pthread_mutex_unlock(&mutexFilaClientes);
}

Cliente *desenfileirarCliente()
{
    pthread_mutex_lock(&mutexFilaClientes);
    if (filaClientes->tamanho == 0)
    {
        pthread_mutex_unlock(&mutexFilaClientes);
        return NULL;
    }

    Cliente *cliente = &filaClientes->clientes[filaClientes->frente];

    filaClientes->frente = (filaClientes->frente + 1) % MAXIMO_CLIENTES;

    filaClientes->tamanho--;

    pthread_mutex_unlock(&mutexFilaClientes);
    return cliente;
}

Cliente *clienteFrente()
{
    pthread_mutex_lock(&mutexFilaClientes);
    if (filaClientes->tamanho == 0)
    {
        pthread_mutex_unlock(&mutexFilaClientes);
        return NULL;
    }

    Cliente *cliente = &filaClientes->clientes[filaClientes->frente];

    pthread_mutex_unlock(&mutexFilaClientes);

    return cliente;
}

Cliente *clienteFinal()
{
    pthread_mutex_lock(&mutexFilaClientes);
    if (filaClientes->tamanho == 0)
    {
        pthread_mutex_unlock(&mutexFilaClientes);
        return NULL;
    }

    Cliente *cliente = &filaClientes->clientes[(filaClientes->frente + filaClientes->tamanho - 1) % MAXIMO_CLIENTES];
    pthread_mutex_unlock(&mutexFilaClientes);
    return cliente;
}