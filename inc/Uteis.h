#ifndef _UTEIS_H_
#define _UTEIS_H

// Faz a thread dormir por milissegundos
void dormir(long long milissegundos);

// Retorna o tempo atual em milissegundos
long long milissegundos();

// Se a < b, retorna a, senão retorna b
long long minimo(long long a, long long b);

// Retorna um número aleatório entre limiteEsquerdo e limiteDireito
long long faixaRandomica(long long limiteEsquerdo, long long limiteDireito);

#endif