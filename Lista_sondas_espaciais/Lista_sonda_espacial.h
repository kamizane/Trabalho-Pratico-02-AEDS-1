#ifndef LISTA_SONDA_ESPACIAL_H
#define LISTA_SONDA_ESPACIAL_H

#include "../Sonda_espacial/Sonda_espacial.h"


//implementação da lista usando lista encadeada de acordo com a implementação do ziviane
typedef struct Celula {
    Sonda_espacial item_sonda;
    struct Celula* pProx;
}Celula;

typedef struct {
    Celula* pPrimeiro;
    Celula* pUltimo;
    int QntItens;//única diferença é que adicionamos um atributo que contém o número de itens na lista
}Lista_sonda_espacial;


void inicializa_lista_sonda_espacial(Lista_sonda_espacial * lista_sonda);
int verifica_lista_vazia(Lista_sonda_espacial * lista_sonda);
void insere_item_lista_sonda_espacial(Lista_sonda_espacial * lista_sonda, Sonda_espacial* pItem);
int retira_item_lista_sonda_espacial(Lista_sonda_espacial* lista_sonda, char * id, Sonda_espacial * pitem);
int imprime_lista_sonda_espacial(Lista_sonda_espacial* lista_sonda);


#endif