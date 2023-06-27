#ifndef _CLIENTE_H_
#define _CLIENTE_H_

// Representa um cliente
typedef struct
{
    double chegada; // tempo de chegada do cliente na fila
} Cliente;

// imprime os dados do cliente
void imprimirCliente(Cliente cliente);

#endif