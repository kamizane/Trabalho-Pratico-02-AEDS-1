#ifndef COMPARTIMENTO_H
#define COMPARTIMENTO_H

#include "../RochaMineral/RochaMineral.h"

//define a estrutura da celula que contem a rocha e um apontador para a proxima celula
typedef struct celula{

    RochaMineral rocha;
    struct celula* prox;

} Ccelula;

/*estrutura do compartimento, com o ponteiro primeiro (basico para lista encadeada),
um ultimo, o tamanho, o peso atual, o valor o peso máximo, que serao usados posteriormente*/
typedef struct{

    Ccelula * primeiro;
    Ccelula * ultimo;
    int tamanho;
    int valor;
    int peso_atual;
    int peso_maximo;

} Compartimento;


void faz_compartimento_vazio(Compartimento* compartimento, int peso_maximo);

int tamanho_do_compartimento(Compartimento* compartimento);

int compartimento_eh_vazio(Compartimento* compartimento);

int imprime_compartimento(Compartimento* compartimento);

float retorna_peso_atual(Compartimento* compartimento);

int trocar_rocha(Compartimento* compartimento, RochaMineral* rocha);

int inserir_rocha(Compartimento* compartimento, RochaMineral* rocha);



#endif