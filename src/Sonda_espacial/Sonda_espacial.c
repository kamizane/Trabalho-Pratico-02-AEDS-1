#include <stdio.h>
#include <string.h>
#include "./Sonda_espacial.h"

//inicializa uma sonda e preenche os seus campos usando sets
void inicializa_Sonda_Espacial(Sonda_espacial * sonda, char * id, int peso){
    set_Identificador(sonda, id);
    set_Compartimento(sonda, peso);
}

void set_Identificador(Sonda_espacial*sonda, char * id){
    strcpy(sonda->Identificador, id);
}

void set_Compartimento(Sonda_espacial*sonda, int peso){
    faz_compartimento_vazio(&sonda->Compartimento, peso);
}