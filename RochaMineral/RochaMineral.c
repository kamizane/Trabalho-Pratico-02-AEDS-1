#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./RochaMineral.h"

//função para inicializar uma rocha
void inicializaRochaMineral(RochaMineral *rocha, int id, int peso, int valor){
       
    setId(rocha, id);
    setPeso(rocha, peso);
    setValor(rocha, valor);

}

//obtenção de valores (gets)
int getId(RochaMineral* rocha){
    return rocha->id;
}
int getPeso(RochaMineral* rocha){
    return rocha->peso;
}
int getValor(RochaMineral* rocha){
    return rocha->valor;
}

//definição de valores (sets)
void setId(RochaMineral* rocha, int id){
    rocha->id = id;
}
void setPeso(RochaMineral* rocha, int peso){
    rocha->peso = peso;
}
void serValor(RochaMineral* rocha, int valor){
    rocha->valor = valor;
}