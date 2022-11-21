#include <stdio.h>
#include "listase.h"
#include <time.h>

int main (int argc, char *argv[]){
    time_t start, end;
    time(&start);
    tp_listase *l, *atu;
    tp_item e;
    int n, m;
    l = inicializa_listase();
    
    scanf("%d %d", &e.ultimo_uso, &e.bit_R);
    insere_listase_no_fim(&l, e);
    
    imprime_listase(l);
    time(&end);
    double tempo = (end - start);
    printf("%lf\n", tempo);

    return 0;
}
