#include <stdio.h>
#include <string.h>
#include "./Sonda_espacial.h"

//inicializa uma sonda e preenche os seus campos usando sets
void inicializa_Sonda_Espacial(Sonda_espacial * sonda, char * id, float latitude,float longitude, float capacidade, float velocidade, float combustivel){
    set_Identificador(sonda, id);
    set_Compartimento(sonda);
}

void set_Identificador(Sonda_espacial*sonda, char * id){
    strcpy(sonda->Identificador, id);
}

void set_Compartimento(Sonda_espacial*sonda){
    faz_compartimento_vazio(&sonda->Compartimento);
}
