#include <stdio.h>
#include "listase.h"
#include <time.h>

int main (int argc, char *argv[]){
    time_t start, end;
    start = time(NULL);
    int num_pages = 5, op=0, id_pagina, pag_atual=0;

    tp_listase *l, *atu;
    tp_item e;
    int n, m;
    l = inicializa_listase();

    for (int i = 0; i < num_pages; i++){
        e.id_pagina = i;
        //scanf("%d", &m);
        end = time(NULL);
        e.ultimo_uso = difftime(end, start);
        e.bit_R = 1;
        e.bit_M = 1;
        insere_listase_no_fim(&l, e);
    }
    n = 4;
    while (op < 3){
        n++;
        wsclock(l, difftime(end, start), n,start);
        op++;
        //scanf("%d", &op);
        
        //switch (op)
        //{
        //case 1: printf("adcionar uma nova pagina:\n"); break;
        //case 2: printf("op 2\n"); break;
        //case 3: printf("op 3\n"); break;
        //default: printf("Opção inválida escolha novamente\n");break;
        //}
    }
    end = time(NULL);
    double tempo = difftime(end, start);
    printf("Tempo de execucao do Codigo:%.1lf\n", tempo);
    printf("Lista circular de paginas encerrou assim:\n");
    imprime_listase(l);
    return 0;
}
