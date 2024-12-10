#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Sonda_espacial/Sonda_espacial.h"
#include "Lista_sondas_espaciais/Lista_sonda_espacial.h"
#include <time.h>

#define N_sonda 3
#define max_peso_compartimento 40

FILE *leitura_arq(int argc, char **argv);
void combinacao(RochaMineral lista_rochas[], RochaMineral lista_temp[], Sonda_espacial * sonda, int inicio, int fim, int indice, int r, int * maior_valor, int * peso_maior, int * qnt_rochas_maior, RochaMineral lista_melhor_comb[]);
void problema_do_compartimento(RochaMineral lista_rochas[],Sonda_espacial * sonda,int sonda_atual, int *N_rochas);
int qtdCombinacoes(int n, int p);
int arranjo(int n, int p);
int permutacao(int n);

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
            insere_item_lista_sonda_espacial(&lista_de_sondas_file,&sonda_i);
        }

        //le o numero de rochas
        int N_rochas = 0;
        fscanf(file,"%d",&N_rochas);
        fgetc(file);

        //pega as rochas e coloca em uma lista
        int Id_rocha=0;

        RochaMineral* lista_rochas = (RochaMineral*) malloc(N_rochas * sizeof(RochaMineral)); //faz lista de rochas para redistribuir depois

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
        Celula * celula_sonda = lista_de_sondas_file.pPrimeiro->pProx;
        int sonda_atual = 1;
        while(celula_sonda != NULL){
            problema_do_compartimento(lista_rochas, &celula_sonda->item_sonda, sonda_atual, &N_rochas);
            sonda_atual++;
            celula_sonda = celula_sonda->pProx;
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
    }else{
        return 0;
    }
}

void problema_do_compartimento(RochaMineral lista_rochas[],Sonda_espacial * sonda,int sonda_atual, int *N_rochas){
    //DECLARAR LISTA DE COMBINAÇÕES
    RochaMineral matriz[*N_rochas][*N_rochas];
    for(int r = 1; r <= *N_rochas; r++){
        RochaMineral lista_temp[r];
        RochaMineral lista_melhor_combinacao[r];
        //ADICIONA A MELHOR COMBINAÇÃO DO TAMANHO R À LISTA DE COMBINAÇÕES USANDO O RETURN:
        //listaCombinacoes[i] = combinacao(...);
        int maior_valor = 0, peso_maior = 0, qnt_rochas_maior = 0;
        combinacao(lista_rochas, lista_temp, sonda, 0, *N_rochas-1, 0, r,&maior_valor, &peso_maior, &qnt_rochas_maior, lista_melhor_combinacao);
        for (int count = 0; count < r; count++){
            matriz[r-1][count] = lista_melhor_combinacao[count];
        }
    }
      for(int i = 0; i <*N_rochas; i++){
        for(int j = 0; j<i+1; j++){
          printf("%d ", matriz[i][j].valor);
        }
        printf("\n");
      }
      printf("-----------------------------------\n");
    int melhor_comb_valores = 0;
    int melhor_atual = 0;
    RochaMineral melhor_comb[*N_rochas];
    // printf("%d\n", *N_rochas);
    int aux=0;
    for(int i = 0; i <*N_rochas; i++){
      for(int j = 0; j<i+1; j++){
        melhor_atual += matriz[i][j].valor;
      }
      if (melhor_atual >= melhor_comb_valores){
        aux = i+1;
        melhor_comb_valores = melhor_atual;
        for(int k = 0;  k<aux; k++){
          melhor_comb[k] = matriz[i][k];
        }
      }
      melhor_atual = 0;
    }
    for(int i= 0; i<aux; i++){
    //   printf("%d ", melhor_comb[i].valor);
      inserir_rocha(&sonda->Compartimento,&melhor_comb[i]);
      for(int j=0;j<*N_rochas; j++){
        if(melhor_comb[i].id == lista_rochas[j].id){
          lista_rochas[j] = lista_rochas[*N_rochas-1];
          *N_rochas = *N_rochas-1;
        }
        
      }
    }
    printf("\n");
    printf("Sonda %d: Peso %d, Valor %d , Solucao [",sonda_atual, sonda->Compartimento.peso_atual, sonda->Compartimento.valor);
    for(int i = 0; i<aux;i++){
        printf("%d", melhor_comb[i].id);
        if(!(i == aux-1)){
            printf(",");
        }
    }
    printf("]\n");
  //comparar qual é a melhor combinacao dentre as melhores combinações de cada tamanho
  //ou seja, comaparar cada elemento da lista de combinacoes pra ver qual é a melhor de todas, e adicionar à sonda 1

  //fazer a mesma coisa pra sonda 2, removendo da lista_rochas as rochas já adicionadas na sonda 1
  //fazer fazer a mesma coisa pra sonda 3, removendo da lista_rochas as rochas já adicionadas na sonda 2


}


void combinacao(RochaMineral lista_rochas[], RochaMineral lista_temp[], Sonda_espacial * sonda, int inicio, int fim, int indice, int r, int * maior_valor, int * peso_maior, int * qnt_rochas_maior, RochaMineral lista_melhor_comb[]){
    int maior_valor_atual = 0, peso_atual = 0, qnt_rochas_atual = 0, peso_max = 40, N_rochas = fim+1;
    static int combinacoesFeitas = 0;
    if(indice == r){
        printf("maior valor: %d\n" ,*maior_valor);
        combinacoesFeitas++;
        // for (int j = 0; j < r; j++)
        //     printf("%d ", lista_temp[j].valor);
        // printf("\n");

        for (int j = 0; j < r; j++){
            maior_valor_atual += lista_temp[j].valor;
            qnt_rochas_atual++;
            peso_atual += lista_temp[j].peso;
        }
        if((maior_valor_atual > *maior_valor) && !(peso_atual > peso_max)){

            *maior_valor = maior_valor_atual;
            *qnt_rochas_maior = qnt_rochas_atual;
            *peso_maior = peso_atual;
            for (int k = 0; k < r; k++){
              lista_melhor_comb[k] = lista_temp[k];
            }

        }
        int combinacoesTotais = qtdCombinacoes(N_rochas, r);
        //SE TODAS AS COMBINAÇÕES FORAM GERADAS E VERIFICADAS, PODEMOS RETORNAR A MELHOR COMBINAÇÃO DO TAMANHO R
        // printf("combinacoes feitas:\n %d\n", combinacoesFeitas);
        if(combinacoesFeitas == combinacoesTotais){
            if (*maior_valor == 0){
                for (int j = 0; j < r; j++)
                lista_melhor_comb[j].valor = 0;
            }
            //retornar melhor combinacao de tamanho r
            printf("teste: ");
            for (int j = 0; j < r; j++)
                printf("%d ", lista_melhor_comb[j].valor);
            printf("\n");
            //return &lista_melhor_combinacao;

        combinacoesFeitas = 0;
        }
        return;
    }
  
    for (int i = inicio; i <= fim && fim-i+1 >= r - indice; i++){
        lista_temp[indice] = lista_rochas[i];
        combinacao(lista_rochas, lista_temp, sonda, i+1, fim, indice + 1, r, maior_valor, peso_maior, qnt_rochas_maior, lista_melhor_comb);
    }

  /*Compartimento * aux = &sonda->Compartimento;
  for (int k = 0; k < qnt_rochas_maior; k++){
    inserir_rocha(&aux,&lista_melhor_combinacao[k]);
  }*/
}




int arranjo(int n, int p){
    if (p>1)
        return n*arranjo(n-1,p-1);
    else
        return n;
}

int fatorial(int n){
    if (n > 0){
        return n*fatorial(n-1);
    }else{
        return 1;
    }
}

int qtdCombinacoes(int n, int p){
    return arranjo(n,p)/fatorial(p);
}
