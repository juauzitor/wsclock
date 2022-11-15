#include <stdio.h>
#include "listase.h"

int main (int argc, char *argv[]){
    tp_listase *l, *atu;
    tp_item e;
    int n, m;
    l = inicializa_listase();

    scanf("%d %d", &e.ultimo_uso, &e.bit_referencia);
    insere_listase_no_fim(&l, e);
    
    imprime_listase(l);

    return 0;
}
