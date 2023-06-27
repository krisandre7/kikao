#include <stdio.h>
#include <pthread.h>
#include <stdbool.h>

#ifndef _MONITOR_H_
#define _MONITOR_H_

// variável que indica se o programa está executando
bool estaExecutando();

// define se o programa está executando
void definirExecutando(bool valor);

// thread que para o programa ao receber uma entrada do teclado
void *threadParadaRotina(void *dado);

// inicia as threads do programa
void iniciarThreads();

#endif