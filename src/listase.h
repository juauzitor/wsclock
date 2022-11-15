#ifndef LISTASE_H
#define LISTASE_H
#include<stdio.h>
#include <stdlib.h>


typedef struct{
		int valores[2];
	}peca;
	
typedef peca tp_item;

typedef struct tp_no{
tp_item info;
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
	*l=novo_no;
} else{
	atu = *l;
	while(atu->prox!=NULL){
		atu=atu->prox;
	}
	atu->prox=novo_no;
}
return 1; 
}


void imprime_listase(tp_listase *lista){
	tp_listase *atu;
	atu=lista;
	while (atu!=NULL){
		printf("[%i|%i] ",atu->info.valores[0],atu->info.valores[1]);
		atu=atu->prox;
	}
}


tp_listase *busca_listase(tp_listase *lista,tp_item e){
    tp_listase *atu;
    atu=lista;
    while((atu!=NULL) && (atu->info.valores[0]!=e.valores[0]) && (atu->info.valores[1]!=e.valores[1])){
        atu=atu-> prox;
    }
    if(atu ==NULL)return NULL;
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

int remove_listase_do_fim(tp_listase **lista, tp_item *e){
    tp_listase *atu;
    tp_listase *ant;
    if(listase_vazia(*lista)) return 0;
	atu=*lista;
    
    while(atu->prox != NULL){
        ant = atu;
		atu = atu ->prox;
    }
    
	*e = atu->info;
    ant->prox=NULL;
    
    free(atu);
    atu = NULL;
    return 1;
}
 
 
 
 int remove_listase_n(tp_listase **lista, tp_item e){
    tp_listase * ant, *atu;
    atu=*lista;
    ant=NULL;
    while((atu->info.valores[0]!=e.valores[0]) || (atu->info.valores[1]!=e.valores[1])){
        ant = atu;
        atu = atu ->prox;
    }
    if(atu == NULL)return 0;
    if(ant == NULL){
        *lista = atu -> prox;
    }else{
        ant -> prox = atu -> prox;
    }
    free(atu);
    atu = NULL;
    return 1;
} 

#endif
