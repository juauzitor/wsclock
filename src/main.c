#include <stdio.h>
#include "listase.h"
#include <time.h>
#include <unistd.h> // acho que tem trocar para uma chamada Windows.h pra rodar no windows.

int main (int argc, char *argv[]){
    time_t start, end;
    start = time(NULL);
    int num_pages = 0, op=0, id_pagina, pag_atual=0;
    tp_listase *l, *atu;
    tp_item e;
    l = inicializa_listase();
    
    printf("Digite o numéro de pagnias que deseja: ");
    scanf("%d", &num_pages);
    for (int i = 0; i < num_pages; i++){
        sleep(.7);
        e.id_pagina = i;
        end = time(NULL);
        e.ultimo_uso = difftime(end, start);
        e.bit_R = 1;
        e.bit_M = 1;
        insere_listase_no_fim(&l, e);
    }
    while (op != 2){

        end = time(NULL);
        printf("--------------------------------------\n");
        printf("Tempo total de execução: %.1lf\n", difftime(end, start));
        printf("--------------------------------------\n");
        printf("Digite 1 para adicinar uma nova pagina ou 2 para encerrar o programa\n");
        scanf("%d", &op);
        
        switch (op)
        {
        case 1: 
            time_t start_evento, end_evento;
            start_evento = time(NULL);
            printf("adcionar uma nova pagina:\n");
            printf("--------------------------------------\n");
            sleep(1);
            end = time(NULL);
            wsclock(l, difftime(end, start), num_pages, start);
            printf("--------------------------------------\n");
            end_evento = time(NULL);
            printf("Tempo de execução da troca: %.1lf\n", difftime(end_evento, start_evento));
            printf("Lista das paginas:\n");
            imprime_listase(l);
            printf("--------------------------------------\n");
            num_pages++;
            break;
        case 2: printf("O programa irá se encerrar obrigado pelo uso!!\n"); break;
        default: printf("Opção inválida escolha novamente\n");break;
        }
    }
    
    end = time(NULL);
    double tempo = difftime(end, start);
    printf("--------------------------------------\n");
    printf("Tempo de execucao do Codigo:%.1lf\n", tempo);
    printf("Lista circular de paginas encerrou assim:\n");
    imprime_listase(l);
    printf("--------------------------------------\n");
    return 0;
}
