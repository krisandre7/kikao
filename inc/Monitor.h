#include <stdio.h>
#include <pthread.h>
#include <stdbool.h>

#ifndef _MONITOR_H_
#define _MONITOR_H_

bool estaExecutando();

void definirExecutando(bool valor);

void *threadParada(void *dado);

void iniciarThreads();

#endif