#include <stdlib.h>
#include "Cliente.h"
#include <stdbool.h>

#ifndef _FILA_CIRCULAR_H_
#define _FILA_CIRCULAR_H_

#define MAXIMO_CLIENTES 100

typedef struct
{
	Cliente clientes[MAXIMO_CLIENTES];
	int tamanho;
	int frente;
} FilaClientes;

static FilaClientes *filaClientes = NULL;

FilaClientes *FilaClientesNew();
void FilaClientesDelete();

bool enfileirarCliente(Cliente cliente);

Cliente *desenfileirarCliente();

Cliente *clienteFrente();

Cliente *clienteFinal();

#endif