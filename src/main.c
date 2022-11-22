#include <stdio.h>
#include "listase.h"
#include <time.h>

int main (int argc, char *argv[]){
    time_t start, end;
    start = time(NULL);
    int num_pages = 5, op;

    tp_listase *l, *atu;
    tp_item e;
    int n, m;
    l = inicializa_listase();

    for (int i = 0; i < num_pages; i++){
        scanf("%d", &m);
        end = time(NULL);
            //tp = difftime(end, start);
            //printf("Tempo de execucao do Codigo: %.1f segundos com funcao de tempo", tp);

        e.ultimo_uso = difftime(end, start);
        e.bit_R = 1;
        e.bit_M = 1;
        insere_listase_no_fim(&l, e);
    }

    while (op == 4){
        /* code */
    }
    
        
    imprime_listase(l);
    time(&end);
    double tempo = (end - start);
    printf("%lf\n", tempo);

    return 0;
}
