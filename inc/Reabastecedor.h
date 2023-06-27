#include <pthread.h>

#ifndef _REABASTECEDOR_H_
#define _REABASTECEDOR_H_

// Inicia três threads, uma para cada tipo de ingrediente: pão, molho e salsicha
void criarThreadReabastecedor(pthread_t *threadPao, pthread_t *threadMolho, pthread_t *threadSalsicha);

#endif


