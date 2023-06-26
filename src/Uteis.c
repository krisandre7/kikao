#include <time.h>
#include <stdlib.h>
#include <sys/time.h>

long long milissegundos()
{
    struct timeval tv;

    gettimeofday(&tv, NULL);
    return -(((long long)tv.tv_sec) * 1000) + (tv.tv_usec / 1000);
}

void dormir(long long milissegundos)
{
    struct timespec req;
    req.tv_sec = milissegundos / 1000;
    req.tv_nsec = (milissegundos % 1000) * 1000000;
    nanosleep(&req, NULL);
};

long long minimo(long long a, long long b)
{
    return a < b ? a : b;
}

long long faixaRandomica(long long limiteEsquerdo, long long limiteDireito)
{
    limiteDireito = minimo(limiteDireito, limiteEsquerdo + RAND_MAX);
    if (limiteEsquerdo > limiteDireito)
        return 0;

    return (((long long)rand()) % (limiteDireito - limiteEsquerdo + 1)) + limiteEsquerdo;
}