#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./Compartimento.h"


void faz_compartimento_vazio(Compartimento* compartimento, int peso_maximo){ //cria um compartimento vazio com um peso maximo fornecido pelo usuario
    compartimento->primeiro = (Ccelula*) malloc(sizeof(Ccelula));
    compartimento->ultimo = compartimento->primeiro;
    compartimento->primeiro->prox = NULL;
    compartimento->tamanho = 0;
    compartimento->peso_atual = 0;
    compartimento->peso_maximo = peso_maximo;
    compartimento->valor = 0;

}

int tamanho_do_compartimento(Compartimento* compartimento){//retorna o tamanho do compartimento
    return compartimento->tamanho;
}

int compartimento_eh_vazio(Compartimento* compartimento){//verifica se o compartimento é vazio
    return (compartimento->tamanho == 0);
}

int imprime_compartimento(Compartimento* compartimento){  //imprime as rochas presentes no compartimento com o seu peso e valor
    Ccelula* celula;
    //verifica se é vazio antes de fazer qualquer impressão
    if (compartimento_eh_vazio(compartimento)){
        printf("compartimento vazio!\n");
        return 0;
    }
    //percorre todas as rochas, imprimindo-as
    celula = compartimento->primeiro->prox;
    while(celula != NULL){
        printf("%d %d\n", celula->rocha.peso, celula->rocha.valor);  
        celula = celula->prox;
    };
    return 1;
}

float retorna_peso_atual(Compartimento* compartimento){ //retorna o peso atual
    return compartimento->peso_atual;
}

int inserir_rocha(Compartimento* compartimento, RochaMineral* rocha){ //adiciona rocha ao compartimento
    compartimento->ultimo->prox = (Ccelula*) malloc(sizeof(Ccelula));
    compartimento->ultimo = compartimento->ultimo->prox;
    compartimento->ultimo->rocha = *rocha;
    compartimento->ultimo->prox = NULL;
    compartimento->tamanho++;
    compartimento->peso_atual += rocha->peso;
    compartimento->valor += rocha->valor;
    return 1;
}
