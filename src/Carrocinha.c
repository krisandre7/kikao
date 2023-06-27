#include <pthread.h>
#include "Geradora.h"
#include "Monitor.h"
#include "Uteis.h"
#include <time.h>
#include "Cliente.h"
#include <stdio.h>
#include <sys/time.h>

double tempoTotalEspera = 0;
int numeroAtendimentos = 0;

struct timeval fimAtendimento;
void *consumirClientes(void *dado)
{
    (void)dado; // Top 10 truques

    while (estaExecutando())
    {
        if (tamanhoFila() != 0) {
            Cliente *cliente = desenfileirarCliente();

            if (cliente != NULL)
            {
                // printf("Removido! ");

                dormir(faixaRandomica(100,300));

                gettimeofday(&fimAtendimento, NULL);

                double fimAtendimentoMilis = (fimAtendimento.tv_sec) * 1000.0; //sec to ms
                fimAtendimentoMilis += (fimAtendimento.tv_usec) / 1000.0; // us to ms
                tempoTotalEspera += fimAtendimentoMilis - cliente->chegada;
                numeroAtendimentos++;
            }
        }
    }
}

double mediaTempoEspera() {
    return tempoTotalEspera / numeroAtendimentos;
}

int totalAtendimentos() {
    return numeroAtendimentos;
}

void criarThreadCarrocinha(pthread_t *threadCarrocinha)
{
    pthread_create(threadCarrocinha, NULL, consumirClientes, NULL);
}
