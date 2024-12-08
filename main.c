#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Sonda_espacial/Sonda_espacial.h"
#include "Lista_sondas_espaciais/Lista_sonda_espacial.h"
#include <time.h>

FILE *leitura_arq(int argc, char **argv);
void combinacao(int lista[], int listaTemp[], int inicio, int fim, int indice, int r);

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

        //inicializa as 3 sondas sondas
        for(int i = 0; i<3; i++){
            char id[20];
            sprintf(id, "%d", i+1);
            Sonda_espacial sonda_i;
            inicializa_Sonda_Espacial(&sonda_i,id);
        }

        //le o numero de rochas
        int N_rochas = 0;
        fscanf(file,"%d",&N_rochas);
        fgetc(file);

        //pega as rochas e coloca em uma lista
        int Id_rocha;
        Compartimento compartimento_rochas;
        faz_compartimento_vazio(&compartimento_rochas, N_rochas*255);

        for (int i = 0; i < N_rochas; i++){
            int peso = 0, valor = 0;
            RochaMineral rocha;
            fscanf(file,"%d", &peso);
            fgetc(file);
            fscanf(file, "%d", &valor);
            fgetc(file);
            inicializaRochaMineral(&rocha,Id_rocha,peso,valor);
            Id_rocha++;
            inserir_rocha(&compartimento_rochas, &rocha);
        }
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
void combinacao(int lista[], int listaTemp[], int inicio, int fim, int indice, int r){
  if (indice == r){
    for (int j = 0; j < r; j++)
      printf("%d ", listaTemp[j]);
    printf("\n");
    return;
  }
 
  for (int i = inicio; i <= fim && fim-i+1 >= r - indice; i++){
    listaTemp[indice] = lista[i];
    combinacao(lista, listaTemp, i+1, fim, indice + 1, r);
  }
}