#include <pthread.h>
#include "Carrocinha.h"
#include "Uteis.h"
#include "Monitor.h"

// rotina de reabastecimento de ingredientes
// reabastece o ingrediente passado como argumento, a cad certo tempo
void *reabastecerIngredientes(void *dado) {
    int ingrediente = (TipoIngrediente) dado;
    while (estaExecutando()) {
        dormir(faixaRandomica(1000, 2500));
        reabastecerIngrediente(ingrediente);
    }
    return NULL;
}

// inicia as threads de reabastecimento de ingredientes
// passando o tipo de ingrediente como argumento
void criarThreadReabastecedor(pthread_t *threadPao, pthread_t *threadSalsicha, pthread_t *threadMolho) {
    pthread_create(threadPao, NULL, reabastecerIngredientes, (void *) PAO);
    pthread_create(threadSalsicha, NULL, reabastecerIngredientes, (void *) SALSICHA);
    pthread_create(threadMolho, NULL, reabastecerIngredientes, (void *) MOLHO);
}