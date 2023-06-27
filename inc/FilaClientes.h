#include <stdlib.h>
#include "Cliente.h"
#include <stdbool.h>

#ifndef _FILA_CIRCULAR_H_
#define _FILA_CIRCULAR_H_

#define MAXIMO_CLIENTES 100

// Fila circular de clientes da carrocinha
typedef struct
{
	Cliente clientes[MAXIMO_CLIENTES];
	int tamanho;
	int frente;
} FilaClientes;

static FilaClientes *filaClientes = NULL;

// inicializa a fila de clientes
FilaClientes *FilaClientesNew();

// libera a fila de clientes da memória
void FilaClientesDelete();

// insere um cliente na fila
bool enfileirarCliente(Cliente cliente);

// remove um cliente da fila
Cliente *desenfileirarCliente();

// retorna o cliente na frente da fila
Cliente *clienteFrente();

// retornao cliente no final da fila
Cliente *clienteFinal();

#endif