#include "Cliente.h"
#include <stdio.h>

void imprimirCliente(Cliente cliente)
{
    printf("chegada: %d, inicio: %d, fim %d\n", cliente.chegada, cliente.inicioAtendimento, cliente.fimAtendimento);
}