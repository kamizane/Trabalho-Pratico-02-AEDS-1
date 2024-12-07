#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./Compartimento.h"




void faz_compartimento_vazio(Compartimento* compartimento, float peso_max){ //cria um compartimento vazio com um peso maximo fornecido pelo usuario
    compartimento->primeiro = (Ccelula*) malloc(sizeof(Ccelula));
    compartimento->ultimo = compartimento->primeiro;
    compartimento->primeiro->prox = NULL;
    compartimento->tamanho = 0;
    compartimento->peso_atual = 0;
    compartimento->peso_maximo = peso_max;

}

int tamanho_do_compartimento(Compartimento* compartimento){
    return compartimento->tamanho;
}

int compartimento_eh_vazio(Compartimento* compartimento){
    return (compartimento->tamanho == 0);
}

int imprime_compartimento(Compartimento* compartimento){  //imprime as rochas presentes no compartimento com a sua categoria e peso  
    Ccelula* celula;
    
    //verifica se é vazio antes de fazer qualquer impressão
    if (compartimento_eh_vazio(compartimento)){
        printf("compartimento vazio!\n");
        return 0;
    }
    
    //percorre todas as rochas, imprimindo-as
    celula = compartimento->primeiro->prox;
    do{
   

        printf("%s %.2f\n",celula->rocha.categoria, celula->rocha.peso);
        
        
        celula = celula->prox;
      
    }while(celula != NULL);
  
    return 1;
}

float retorna_peso_atual(Compartimento* compartimento){
    return compartimento->peso_atual;
}

//troca rochas de lugar pela categoria, caso o peso da previamente armazenada seja superior ao da nova
int trocar_rocha(Compartimento* compartimento, RochaMineral* rocha){
    Ccelula* celula = compartimento->primeiro->prox;
    
    if (!compartimento_eh_vazio(compartimento)){
        while (celula != NULL) {
            if (strcmp(celula->rocha.categoria, rocha->categoria) == 0) { //compara primeiro a categoria para achar a rocha a ser trocada
                if (celula->rocha.peso > rocha->peso) { //compara o peso para fazer a troca se necessário
                        compartimento->peso_atual -= celula->rocha.peso;
                        celula->rocha = *rocha;
                        compartimento->peso_atual += celula->rocha.peso;
                        return 1;
                }
            }
            celula = celula->prox;
        }

        return 0;

    }

    return 0;
}



int inserir_rocha(Compartimento* compartimento, RochaMineral* rocha){ //adiciona rocha ao compartimento
    if((compartimento->peso_atual + rocha->peso) <= compartimento->peso_maximo){
        compartimento->ultimo->prox = (Ccelula*) malloc(sizeof(Ccelula));
        compartimento->ultimo = compartimento->ultimo->prox;
        compartimento->ultimo->rocha = *rocha;
        compartimento->ultimo->prox = NULL;
        compartimento->tamanho++;
        compartimento->peso_atual += rocha->peso;
        return 1;
    }

    return 0;
}
 //remove rocha do compartimento por categoria, e entrega a rocha para o usuario, caso ele precise
int remover_rocha(Compartimento* compartimento, char categoria[], RochaMineral* rocha_retirada){
    Ccelula* anterior = compartimento->primeiro;
    Ccelula* celula = compartimento->primeiro->prox;

    while (celula != NULL) {

        if(strcmp(categoria, celula->rocha.categoria) == 0){ //procura pela rocha da categoria certa e faz a remoção
            
            anterior->prox = celula->prox;
            compartimento->peso_atual -= celula->rocha.peso;
            *rocha_retirada = celula->rocha;

            if (celula->prox == NULL) compartimento->ultimo = anterior;
            compartimento->tamanho--;

            free(celula);
            return 1; 
        }
        
        anterior = celula;
        celula = celula->prox;
    }

    return 0;
}