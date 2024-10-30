#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Tnofila{
    int num;
    struct Tnofila* prox;
}tnofila;

typedef struct controle{
    tnofila *inicio,*fim;
    int quantidade;
}fila;

void inicializar(fila *mf){
    mf->inicio = NULL;
    mf->fim = NULL;
    mf->quantidade = 0;
}

int isfull(fila mf){
    return 0;
}

int isempty(fila mf){
    if(mf.inicio == NULL){
        return 1;
    }
    else{
        return 0;
    }
}

void adicionar(fila* mf, int valor){
    tnofila *novo = (tnofila*)malloc(sizeof(tnofila));
    novo->num = valor;
    novo->prox = NULL;
    if(isempty(*mf)==1){
        mf->inicio = novo;
        mf->fim = novo;
    }else{
        mf->fim->prox = novo;
        mf->fim = novo;
    }
    mf->quantidade++;
}

void somar(fila lista1, fila lista2, fila *listaSoma){
    if(isempty(lista1)==1 && isempty(lista2) == 0){
        listaSoma->inicio = lista2.inicio;
        listaSoma->fim = lista2.fim;
        return;
    }else if(isempty(lista1) == 0 && isempty(lista2) == 1){
        listaSoma->inicio = lista1.inicio;
        listaSoma->fim = lista1.fim;
        return;
    }
    tnofila *auxl1 = lista1.inicio;
    tnofila *auxl2 = lista2.inicio;
    int quantidade;
    if(lista1.quantidade > lista2.quantidade){
        quantidade = lista1.quantidade;
    }else if(lista1.quantidade < lista2.quantidade){
        quantidade = lista2.quantidade;
    }else{
        quantidade = lista1.quantidade;
    }
    int cont = 0;
    while(cont < quantidade){
        tnofila* novo = (tnofila*)malloc(sizeof(tnofila));
        novo->prox = NULL;
        
        if(isempty(*listaSoma) == 1){
            listaSoma->inicio = novo;
            listaSoma->fim = novo;
        }
        if(auxl1 != NULL && auxl2 != NULL){
            novo->num = auxl1->num + auxl2->num;
            listaSoma->fim->prox = novo;
            listaSoma->fim = novo;
        }else if(auxl1 != NULL && auxl2 == NULL){
            novo->num = auxl1->num;
            listaSoma->fim->prox = novo;
            listaSoma->fim = novo;
        }else if(auxl1 == NULL && auxl2 != NULL){
            novo->num = auxl2->num;
            listaSoma->fim->prox = novo;
            listaSoma->fim = novo;
        }
        if(auxl1 != NULL){
            auxl1 = auxl1->prox;
        }
        if(auxl2 != NULL){
            auxl2 = auxl2->prox;
        }
        cont ++;
    }
}

void exibir(fila mf){   
  
    tnofila *aux = mf.inicio;
    while(aux != NULL){
        printf("[%d] ", aux->num);
        aux = aux->prox;
    }
    printf("\n");
}


int main(){
    fila fila1;
    fila fila2;
    fila filasoma;
    inicializar(&fila1);
    inicializar(&fila2);
    inicializar(&filasoma);
    int op,escolha,num;
    do{
        printf("1- Adicionar elemento na fila 1 ou 2\n2- Mostrar fila\n3-Somar fila 1 e 2\n0- Fechar programa\n");
        printf("Informe a opção desejada: ");
        scanf("%d", &op);
        switch(op){
            case 1:
                printf("Qual fila deseja adicionar um elemento? [1 ou 2] ");
                scanf("%d", &escolha);
                if(escolha == 1){
                    printf("Qual valor deseja adicionar na fila 1? ");
                    scanf("%d", &num);
                    adicionar(&fila1,num);
                    printf("Valor adicionado!\n");
                }else if (escolha == 2){
                    printf("Qual valor deseja adicionar na fila 2? ");
                    scanf("%d", &num);
                    adicionar(&fila2,num);
                    printf("Valor adicionado!\n");
                }
                break;
            case 2:
                printf("Qual fila deseja vizualizar? [1, 2, ou 3(soma)] ");
                scanf("%d", &escolha);
                if(escolha == 1){
                    if(isempty(fila1) == 0){
                        exibir(fila1);
                    }
                    else{
                        printf("Fila vazia\n");
                    }
                }
                else if (escolha == 2){
                    if(isempty(fila2) == 0){
                        exibir(fila2);
                    }
                    else{
                        printf("Fila vazia\n");
                    }
                }
                else if (escolha == 3){
                    if(isempty(filasoma) == 0){
                        exibir(filasoma);
                    }
                    else{
                        printf("Fila vazia\n");
                    }
                }
                
                break;
            case 3:
                inicializar(&filasoma);
                if(fila1.inicio != NULL || fila2.inicio != NULL){
                    somar(fila1, fila2, &filasoma);
                    printf("Filas somadas!\n");
                }
            break;
            default: printf("Opção invalida!\n");
        }
        
    }while(op!=0);
    
    return 0;
}