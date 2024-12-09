#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Sonda_espacial/Sonda_espacial.h"
#include "Lista_sondas_espaciais/Lista_sonda_espacial.h"
#include <time.h>

#define N_sonda 3
#define max_peso_compartimento 40

FILE *leitura_arq(int argc, char **argv);
void combinacao(RochaMineral lista_rochas[], RochaMineral lista_temp[], Sonda_espacial * sonda, int inicio, int fim, int indice, int r);
void problema_do_compartimento(RochaMineral lista_rochas[], Lista_sonda_espacial * Lista_sonda_espacial, int N_rochas);

int main(int argc, char **argv){

  //registra o tempo de início
  clock_t inicio = clock();

  if(leitura_arq(argc, argv) != 0){
    FILE *file = leitura_arq(argc,argv);
    if( file == NULL){
        printf("arquivo inválido!\n");
        return 0;
    }

    //cria e inicializa lista sonda espacial
    Lista_sonda_espacial lista_de_sondas_file;
    inicializa_lista_sonda_espacial(&lista_de_sondas_file);

    //inicializa as sondas de acordo com o máximo de sondas
    for(int i = 0; i<N_sonda; i++){
        char id[20];
        sprintf(id, "%d", i+1);
        Sonda_espacial sonda_i;
        inicializa_Sonda_Espacial(&sonda_i,id, max_peso_compartimento);
    }

    //le o numero de rochas
    int N_rochas = 0;
    fscanf(file,"%d",&N_rochas);
    fgetc(file);

    //pega as rochas e coloca em uma lista
    int Id_rocha=0;

    RochaMineral* lista_rochas= (RochaMineral*) malloc(N_rochas * sizeof(RochaMineral)); //faz lista de rochas para redistribuir depois

    for (int i = 0; i < N_rochas; i++){
        int peso = 0, valor = 0;
        RochaMineral rocha;
        fscanf(file,"%d", &peso);
        fgetc(file);
        fscanf(file, "%d", &valor);
        fgetc(file);
        inicializaRochaMineral(&rocha,Id_rocha,peso,valor);
        Id_rocha++;
        lista_rochas[i] = rocha;
    }
    problema_do_compartimento(lista_rochas, &lista_de_sondas_file, N_rochas);

    //registra o tempo de término
    clock_t fim = clock();

    //calcula o tempo total
    double tempoTotal = (double)(fim - inicio)/CLOCKS_PER_SEC;

    printf("Tempo gasto: %f segundos\n", tempoTotal);
  }

  return 0;
}

FILE *leitura_arq(int argc, char **argv){
    //verifica se existe argumentos validos para iniciar leitura por arquivo
    if(argc > 1 && strcmp(argv[1], "-f") == 0){
        FILE *file = fopen(argv[2],"r");

    return file;
    }
    else{
        return 0;
    }
}

void problema_do_compartimento(RochaMineral lista_rochas[], Lista_sonda_espacial * Lista_sonda_espacial, int N_rochas){
  for(int r=1; r<N_rochas; r++){
    RochaMineral lista_temp[r];
    combinacao(lista_rochas, lista_temp, &Lista_sonda_espacial->pPrimeiro->pProx->item_sonda, 0, N_rochas-1, 0, r);
  }

}


void combinacao(RochaMineral lista_rochas[], RochaMineral lista_temp[], Sonda_espacial * sonda, int inicio, int fim, int indice, int r){
  int maior_valor_atual = 0, maior_valor=0, peso_maior = 0, peso_atual = 0, qnt_rochas_atual = 0,qnt_rochas_maior = 0, peso_max = 40, N_rochas = fim+1;
  RochaMineral lista_melhor_combinacao[r];
  for(int r=1; r<N_rochas; r++){
    if (indice == r){
      for (int j = 0; j < r; j++){
        maior_valor_atual += lista_temp[j].valor;
        qnt_rochas_atual++;
        peso_atual += lista_temp[j].peso;
      }
      if (peso_atual > peso_max){
        return;
      }
      else if(maior_valor_atual > maior_valor){
        maior_valor = maior_valor_atual;
        qnt_rochas_maior = qnt_rochas_atual;
        peso_maior = peso_atual;
        for (int k = 0; k < r; k++){
          RochaMineral lista_melhor_combinacao[r];
          lista_melhor_combinacao[k] = lista_temp[k];
        }

      }
      printf("\n");
      return;
    }
  
    for (int i = inicio; i <= fim && fim-i+1 >= r - indice; i++){
      lista_temp[indice] = lista_rochas[i];
      combinacao(lista_rochas, lista_temp, sonda, i+1, fim, indice + 1, r);
    }
  }
  Compartimento * aux = &sonda->Compartimento;
  for (int k = 0; k < qnt_rochas_maior; k++){
    inserir_rocha(&aux,&lista_melhor_combinacao[k]);
  }
}
