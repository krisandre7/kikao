#include "Monitor.h"
#include <stdlib.h>
#include <time.h>

int main()
{
    srand(time(NULL)); // seed para gerar números aleatórios
    iniciarThreads();
    return 0;
}
