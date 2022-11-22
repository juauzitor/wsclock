#ifndef LISTASE_H
#define LISTASE_H
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAU 1000

typedef struct{
		int id_pagina;
        double ultimo_uso;
        int bit_R; // Bit de referencia
        int bit_M; // Bit de sujeira
	}pagina;
	
typedef pagina tp_item;

typedef struct tp_no{
tp_item info;
struct tp_no *ant;
struct tp_no *prox;
}tp_listase;


tp_listase * inicializa_listase(){
        return NULL;
}

int listase_vazia(tp_listase *lista){
    if(lista == NULL) return 1;
    return 0;
}

tp_listase *aloca_listase(){
    tp_listase *novo_no;
    novo_no=(tp_listase*) malloc(sizeof(tp_listase));
    return novo_no;
}

int insere_listase_no_fim(tp_listase **l, tp_item e){
    tp_listase *novo_no, *atu;
    novo_no=aloca_listase();
    if(novo_no==NULL) return 0;
    //atribuir valores para o novo nó;
    novo_no->info= e;
    novo_no->prox=NULL;
    //finaliza o encadeamento do nó
    if(listase_vazia(*l)){
	    novo_no->ant = NULL;
        *l=novo_no;
    } else{
    	atu = *l;
	    while(atu->prox!=NULL){
		    atu=atu->prox;
	    }
        novo_no->ant = atu;
        atu->prox=novo_no;
    }
    return 1; 
}


void imprime_listase(tp_listase *lista){
	tp_listase *atu;
	atu=lista;
	while (atu!=NULL){
	    printf("[id: %i|ultimo uso: %.1lf|bit R: %i] ", atu->info.id_pagina,atu->info.ultimo_uso,atu->info.bit_R);
        atu=atu->prox;
	}
    printf("\n");
}


tp_listase *busca_listase(tp_listase *lista,tp_item e){
    tp_listase *atu;
    atu=lista;
    while((atu!=NULL) && (atu->info.id_pagina!=e.id_pagina)){
        atu=atu-> prox;
    }
    if(atu == NULL)return NULL;
    return atu;
}

int tamanho_listase(tp_listase *lista){
    int cont=0;
    tp_listase *atu;
    atu =lista;
    while(atu!=NULL){
        cont++;
        atu=atu->prox;
    }
    return cont;
}

void clean_bit_r(tp_listase *lista){
    tp_listase *atu;
    atu=lista;
    atu->info.bit_R = 0;    
}

void clean_bit_m(tp_listase *lista){
    tp_listase *atu;
    atu=lista;
    atu->info.bit_M = 0;    
}

void wsclock(tp_listase *lista, double tempo_total, int id, time_t start){
    tp_listase *ant, *atu;
    time_t end;
    atu=lista;
    int count_clean=0;
    while (atu!=NULL){
        if (atu->info.bit_R == 1){
            clean_bit_r(atu);
            ant = atu;
            atu = atu->prox;
        } else if(atu->info.bit_R == 0){
            if ((tempo_total-atu->info.ultimo_uso)>TAU){
                if (atu->info.bit_M == 1){
                    clean_bit_m(atu);
                    count_clean++;
                    ant = atu;
                    atu = atu->prox;
                } else {
                    end = time(NULL);
                    atu->info.id_pagina = id;
                    atu->info.ultimo_uso = difftime(end, start);
                    atu->info.bit_M = 1;
                    atu->info.bit_R = 1;
                    return;
                }
            } else {
                ant = atu;
                atu = atu->prox;
            }
        }
    }
    atu=lista;
    if (count_clean > 0){
        while (atu!=NULL){
            if (atu->info.bit_M == 0){
                end = time(NULL);
                atu->info.id_pagina = id;
                atu->info.ultimo_uso = difftime(end, start);
                atu->info.bit_M = 1;
                atu->info.bit_R = 1;
                return;
            }
            atu = atu->prox;
        }
    } else {
        end = time(NULL);
        atu->info.id_pagina = id;
        atu->info.ultimo_uso = difftime(end, start);
        atu->info.bit_M = 1;
        atu->info.bit_R = 1;
        return;
    }
}
    void wsclockt(tp_listase *lista){
    tp_listase *ant, *atu;
    atu=lista;
    int count_dirty;
    while (atu!=NULL){
        if (atu->info.bit_R == 1){
            clean_bit_r(atu);
            ant = atu;
            atu = atu->prox;    
        }
    }
    atu=lista;
    printf("%d", atu->info.id_pagina);
    while (atu!=NULL)
    {
        if (atu->info.bit_M == 1){
            clean_bit_m(atu);
            ant = atu;
            atu = atu->prox;    
        }
    }
    
}

#endif
