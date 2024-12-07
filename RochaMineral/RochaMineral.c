#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./RochaMineral.h"

//função para inicializar uma rocha
void inicializaRochaMineral(RochaMineral *rocha, int id, float peso, MLista *lista, LocalRochaMineral local, char *dataColeta){
       
    setId(rocha, id);
    setPeso(rocha, peso);
    setListaMinerais(rocha, lista);  
    escolheCategoria(rocha);
    setLatitude(rocha, local.latitude);
    setLongitude(rocha, local.longitude);
    setDataColeta(rocha, dataColeta);

}

//obtenção de valores (gets)
int getId(RochaMineral* rocha){
    return rocha->id;
}
float getPeso(RochaMineral* rocha){
    return rocha->peso;
}
char *getCategoria(RochaMineral* rocha){
    return rocha->categoria;
}
MLista *getListaMinerais(RochaMineral* rocha){
    return rocha->lista;
}
float getLatitude(RochaMineral* rocha){
    return rocha->local.latitude;
}
float getLongitude(RochaMineral* rocha){
    return rocha->local.longitude;
}
char *getDataColeta(RochaMineral* rocha){
    return rocha->dataColeta;
}

//definição de valores (sets)
void setId(RochaMineral* rocha, int id){
    rocha->id = id;
}
void setPeso(RochaMineral* rocha, float peso){
    rocha->peso = peso;
}
void setListaMinerais(RochaMineral* rocha, MLista* lista){
    rocha->lista = lista;
}
void setCategoria(RochaMineral* rocha, char *categoria){
    strcpy(rocha->categoria, categoria);
}
void setLatitude(RochaMineral* rocha, float latitude){
    rocha->local.latitude = latitude;
}
void setLongitude(RochaMineral* rocha, float longitude){
    rocha->local.longitude = longitude;
}
void setDataColeta(RochaMineral* rocha, char *data){
    strcpy(rocha->dataColeta, data);
}

//função que define a categoria da rocha a partir da lista de minerais
void escolheCategoria(RochaMineral *rocha){
    
    //definindo variáveis booleanas para verificar se existe cada mineral na lista
    int tFerrolita = 0, tSolarium = 0, tAquavitae = 0, tTerranita = 0, tCalaris = 0;
    //imprimeListaMinerais(rocha->lista);  
    //passando por todas as posições da lista de minerais
    for(int i = rocha->lista->Primeiro; i < rocha->lista->Ultimo; i++){
        TChave m = rocha->lista->minerais[i].Chave;
        //printf("%s\n", m.nome);
        //verificando, a partir do nome do mineral, qual mineral está na posição i
        if(strcmp(m.nome, "Ferrolita") == 0){
            tFerrolita = 1;
        }else if(strcmp(m.nome, "Solarium") == 0){
            tSolarium = 1;
        }else if(strcmp(m.nome, "Aquavitae") == 0){
            tAquavitae = 1;
        }else if(strcmp(m.nome, "Terranita") == 0){
            tTerranita = 1;
        }else if (strcmp(m.nome, "Calaris") == 0){
            tCalaris = 1;
        } 
    }
    
    //definindo a categoria da rocha de acordo com os minerais que estão presentes na lista
    if(tAquavitae && tCalaris && tFerrolita){
        setCategoria(rocha, "AQUACALIS"); 
    }else if(tTerranita && tFerrolita){
        setCategoria(rocha, "TERRALIS");

    }else if(tSolarium && tFerrolita){
        setCategoria(rocha, "SOLARISFER");

    }else if(tCalaris && tAquavitae){
        setCategoria(rocha, "CALQUER");

    }else if(tAquavitae && tTerranita){
        setCategoria(rocha, "AQUATERRA");

    }else if(tTerranita && tSolarium){
        setCategoria(rocha, "TERRASOL");

    }else if(tTerranita && tCalaris){
        setCategoria(rocha, "TERROLIS");

    }else if (tFerrolita && tAquavitae){
        setCategoria(rocha,"AQUAFERRO");

    }else if (tSolarium){
        setCategoria(rocha, "SOLARIS");

    }else if (tFerrolita){
        setCategoria(rocha, "FERROM");
    }
}
