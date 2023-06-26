#include <time.h>

#ifndef _CLIENTE_H_
#define _CLIENTE_H_

typedef struct {
    time_t chegada;
    time_t inicioAtendimento;
    time_t fimAtendimento;
} Cliente;

void imprimirCliente(Cliente cliente);

#endif