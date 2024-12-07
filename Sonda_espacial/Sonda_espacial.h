#ifndef SONDA_ESPACIAL_H
#define SONDA_ESPACIAL_H

#include "../Compartimento/Compartimento.h"

//usando uma estrutura para conter a localização
typedef struct{
    float Latitude;
    float Longitude;
}Localizacao;

//utilização do enum para indicar o estado atual da sonda
typedef enum{
    ON = 0,
    OFF = 1
}EstaLigada;


typedef struct {
    char Identificador[20];
    Compartimento Compartimento;
    Localizacao Localizacao_sonda;
    EstaLigada EstaLigada;
    float Velocidade_sonda;
    float Combustivel_sonda;
}Sonda_espacial;

void inicializa_Sonda_Espacial(Sonda_espacial * sonda, char * id, float latitude,float longitude, float capacidade, float velocidade, float combustivel);
int liga_Sonda_Espacial(Sonda_espacial * sonda);
int desliga_Sonda_Espacial(Sonda_espacial * sonda);
void move_Sonda_Espacial (Sonda_espacial * sonda, float latitude, float longitude);
void set_Identificador(Sonda_espacial*sonda, char * id);
void set_Compartimento(Sonda_espacial*sonda, float capacidade);

void set_Localizacao_sonda(Sonda_espacial * sonda, float latitude, float longitude);
void set_Velocidade(Sonda_espacial * sonda, float velocidade);
void set_Combustivel(Sonda_espacial * sonda, float combustivel);
void set_EstaLigada(Sonda_espacial *sonda, EstaLigada estado);

#endif