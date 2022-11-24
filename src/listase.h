#ifndef LISTASE_H
#define LISTASE_H
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAU 10

typedef struct{
		int id_pagina; // Numero de identificação da pagina
        double ultimo_uso; // Ultimo momento que a pagina foi referênciada
        int bit_R; // Bit de referencia
        int bit_M; // Bit de sujeira~
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

tp_listase *busca_listase(tp_listase *lista,int e){
    tp_listase *atu;
    atu=lista;
    while((atu!=NULL) && (atu->info.id_pagina!=e)){
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

void clean_bit_r(tp_listase *lista){ // Funça para limpar o  bit referênciação
    tp_listase *atu;
    atu=lista;
    atu->info.bit_R = 0;    
}

void clean_bit_m(tp_listase *lista){ // Função para limpar o bit de sujeira
    tp_listase *atu;
    atu=lista;
    atu->info.bit_M = 0;    
}

void wsclock(tp_listase *lista, double tempo_total, int *pag_atual,int id, time_t start){
    tp_listase *atu;
    time_t end;
    atu=busca_listase(lista, *pag_atual); // Alocar o nó em que o ponteiro está
    int count_clean=0, saida=0;
    while (saida == 0 || atu->info.id_pagina != *pag_atual){// Laço para substituição das páginas
        if (atu->info.bit_R == 1){// Condicional para verificar se o bit referêncial é igual a 1
            printf("Pagina atual:\n[id: %i|ultimo uso: %.1lf|bit R: %i]\n", atu->info.id_pagina,atu->info.ultimo_uso,atu->info.bit_R);
            clean_bit_r(atu);// Lipando o bit de referência da pagina
            if (atu->prox!=NULL){//Condicional para verificar se o próximo nó é diferênte de nulo
                atu = atu->prox;// Avançando a lista para o proximo nó
            } else {
                atu = lista;// Voltando a lista para o primeiro nó 
            }            
            saida = 1;// Variavel para funcionamento correto do laço condicional
        } else if(atu->info.bit_R == 0){// Caso bit de refência esteja zerado
            if ((tempo_total-atu->info.ultimo_uso)>TAU){// Verificação da idade da pagina em relação a TAU
                if (atu->info.bit_M == 1){// Condicional para verificar se a pagina ainda está suja
                    printf("Pagina atual:\n[id: %i|ultimo uso: %.1lf|bit R: %i]\n", atu->info.id_pagina,atu->info.ultimo_uso,atu->info.bit_R);
                    clean_bit_m(atu);// Limpando a sujeira da pagina
                    count_clean++; // Variavel que indica se alguma pagina foi limpa nessa passada
                    if (atu->prox!=NULL){//Condicional para verificar se o próximo nó é diferênte de nulo
                        atu = atu->prox;// Avançando a lista para o proximo nó
                    } else {
                        atu = lista;// Voltando a lista para o primeiro nó 
                    }
                    saida = 1; // Variavel para funcionamento correto do laço condicional
                saida = 1;
                } else {// Caso a pagina esteja limpa ela será substituida
                    printf("--------------------------------------\n");
                    printf("Pagina substituida:\n[id: %i|ultimo uso: %.1lf|bit R: %i]\n", atu->info.id_pagina,atu->info.ultimo_uso,atu->info.bit_R);
                    printf("--------------------------------------\n");
                    end = time(NULL);// Zerando o final do cronometro
                    // Sustituição dos valores da pagina para os valores das novas paginas
                    atu->info.id_pagina = id;
                    atu->info.ultimo_uso = difftime(end, start);
                    atu->info.bit_M = 1;
                    atu->info.bit_R = 1;
                    if (atu->prox!=NULL){//Condicional para verificar se o próximo nó é diferênte de nulo
                        atu = atu->prox;// Avançando a lista para o proximo nó
                    } else {
                        atu = lista;// Voltando a lista para o primeiro nó 
                    }
                    *pag_atual = atu->info.id_pagina; // Pegando o valor do id da proxima pagina
                    return;// Encerramento da função
                }
            } else {// Caso a idade da pagina seja menor que o TAU
                printf("Pagina atual:\n[id: %i|ultimo uso: %.1lf|bit R: %i]\n", atu->info.id_pagina,atu->info.ultimo_uso,atu->info.bit_R);
                if (atu->prox!=NULL){//Condicional para verificar se o próximo nó é diferênte de nulo
                    atu = atu->prox;// Avançando a lista para o proximo nó
                } else {
                    atu = lista;// Voltando a lista para o primeiro nó 
                }            
                saida = 1;// Variavel para funcionamento correto do laço condicional
            }
        }
    }
    atu=busca_listase(lista, *pag_atual);// Resetando a lista para o começo de onde estava o ponteiro inicialmente
    saida=0;
    if (count_clean > 0){// Verificando se ouve a limpeza de alguma pagina
        while (saida == 0 || atu->info.id_pagina != *pag_atual){// Busca a pagina até substituila
            if (atu->info.bit_M == 0){
                printf("--------------------------------------\n");
                printf("Pagina substituida:\n[id: %i|ultimo uso: %.1lf|bit R: %i]\n", atu->info.id_pagina,atu->info.ultimo_uso,atu->info.bit_R);
                printf("--------------------------------------\n");
                end = time(NULL);
                // Sustituição dos valores da pagina para os valores das novas paginas
                atu->info.id_pagina = id;
                atu->info.ultimo_uso = difftime(end, start);
                atu->info.bit_M = 1;
                atu->info.bit_R = 1;
                if (atu->prox!=NULL){//Condicional para verificar se o próximo nó é diferênte de nulo
                        atu = atu->prox;// Avançando a lista para o proximo nó
                    } else {
                        atu = lista;// Voltando a lista para o primeiro nó 
                    }
                    *pag_atual = atu->info.id_pagina; // Pegando o valor do id da proxima pagina
                return;
            }
            printf("Pagina atual:\n[id: %i|ultimo uso: %.1lf|bit R: %i]\n", atu->info.id_pagina,atu->info.ultimo_uso,atu->info.bit_R);
            if (atu->prox!=NULL){
                atu = atu->prox;
            } else {
                atu = lista;
            } 
        }
    } else {// Caso não tenha sido possivel substituir nenhuma pagina com as exigencias, forçando a substituir a primeira pagina que aparecer
        printf("--------------------------------------\n");
        printf("Pagina substituida:\n[id: %i|ultimo uso: %.1lf|bit R: %i]\n", atu->info.id_pagina,atu->info.ultimo_uso,atu->info.bit_R);
        printf("--------------------------------------\n");
        end = time(NULL);
        // Sustituição dos valores da pagina para os valores das novas paginas
        atu->info.id_pagina = id;
        atu->info.ultimo_uso = difftime(end, start);
        atu->info.bit_M = 1;
        atu->info.bit_R = 1;
        if (atu->prox!=NULL){//Condicional para verificar se o próximo nó é diferênte de nulo
            atu = atu->prox;// Avançando a lista para o proximo nó
        } else {
            atu = lista;// Voltando a lista para o primeiro nó 
        }
        *pag_atual = atu->info.id_pagina; // Pegando o valor do id da proxima pagina
        return;
    }
}

#endif
