#ifndef ROCHA_MINERAL_H
#define ROCHA_MINERAL_H

//definição do tipo RochaMineral
typedef struct RochaMineral{
    int id;
    int peso;
    int valor;
}RochaMineral;

//cabeçalho das funções

void inicializaRochaMineral(RochaMineral *rocha, int id, int peso, int valor);

int getId(RochaMineral* rocha);
int getPeso(RochaMineral* rocha);
int getValor(RochaMineral* rocha);

void setId(RochaMineral* rocha, int id);
void setPeso(RochaMineral* rocha, int peso);
void setValor(RochaMineral* rocha, int valor);

#endif
