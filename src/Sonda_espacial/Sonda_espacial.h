#ifndef SONDA_ESPACIAL_H
#define SONDA_ESPACIAL_H

#include "../Compartimento/Compartimento.h"

typedef struct {
    char Identificador[20];
    Compartimento Compartimento;
}Sonda_espacial;

void inicializa_Sonda_Espacial(Sonda_espacial * sonda, char * id, int peso);
void set_Identificador(Sonda_espacial*sonda, char * id);
void set_Compartimento(Sonda_espacial*sonda, int peso);

#endif