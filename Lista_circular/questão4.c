#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct EstruturaFila{
    int valor;
    struct EstruturaFila* proximo;
}estrutura;

typedef struct ControleFila{
    estrutura* inicio;
    estrutura* fim;
    int qtd;
}fila;

void inicializar(fila* mf){
    mf->inicio = NULL;
    mf->fim = NULL;
    mf->qtd = 0;
}

int isEmpty(fila mf){
    if(mf.qtd == 0){
        return 1;
    }else{
        return 0;
    }
}

void inserirOrdenado(fila* mf,int valor){
    estrutura* novo = malloc(sizeof(estrutura));
    novo->proximo = NULL;
    novo->valor = valor;
    if(mf->inicio == NULL){
        mf->inicio = novo;
        mf->fim = novo;
        novo->proximo = novo;
        mf->qtd++;
    }else if(valor < mf->inicio->valor){
        novo->proximo = mf->inicio;
        mf->fim->proximo = novo;
        mf->inicio = novo;
        mf->qtd++;
    }else if(valor > mf->fim->valor){
        novo->proximo = mf->inicio;
        mf->fim->proximo = novo;
        mf->fim = novo;
        mf->qtd++;
    }else{
        estrutura* aux = mf->inicio->proximo;
        estrutura* aux2 = mf->inicio;
        do{
            if(valor < aux->valor){
                novo->proximo = aux;
                aux2->proximo = novo;
                mf->qtd++;
                return;
            }    
            aux2 = aux;
            aux = aux->proximo;
        }while(aux != mf->inicio);
    }
    
}

int remover(fila* mf, int valor){
    estrutura* aux = mf->inicio;
    estrutura* aux2 = mf->fim;
    estrutura* remover;
    int contador = 0;
    do{
        if(aux->valor == valor){
            contador++;
            mf->qtd--;
            if(aux == mf->inicio){
                remover = aux;
                aux2->proximo = aux->proximo;
                mf->inicio = aux->proximo;
                
            }else if(aux == mf->fim){
                remover = aux;
                mf->fim = aux2;
                mf->fim->proximo = mf->inicio;
            }else{
                remover = aux;
                aux2->proximo = aux->proximo;
                aux = aux2;
            }
            free(remover);
            if(aux->proximo->valor != valor){
                return contador;
            }
            if(isEmpty(*mf) == 1){
                mf->inicio = NULL;
                mf->fim = NULL;
                return contador;
            }
        }
        aux2 = aux;
        aux = aux->proximo;
    }while(aux != mf->inicio);
    
}

void exibir(fila lista){
    estrutura* aux = lista.inicio;
    if(isEmpty(lista) == 1){
        printf("\nLista vazia.");
    } else {
        printf("\n[%d] ",aux->valor);
        aux = aux->proximo;
        while(aux != lista.inicio){
            printf("[%d] ",aux->valor);
            aux = aux->proximo;
        }
    }
    printf("\n");
}

void exibirOpcoes(){
    printf("\nOpcoes:\n");
    printf("1 - Inserir valor\n");
    printf("2 - Exibir lista\n");
    printf("3 - Remover valores repetidos\n");
    printf("0 - Encerrar programa\n");
    printf("Informe a opcao desejada: ");
}

int main(){
    fila mf;
    inicializar(&mf);
    int op, num;
    do{
        exibirOpcoes();
        scanf("%d",&op);
        switch (op){
        case 1:
            printf("Informe o valor a ser inserido: ");
            scanf("%d",&num);
            inserirOrdenado(&mf, num);
            break;
        case 2:
            exibir(mf);
            break;
        case 3:
            if(isEmpty(mf) == 1){
                printf("Lista vazia.\n");
            } else {
                printf("Informe o valor a ser removido: ");
                scanf("%d",&num);
                int cont = remover(&mf,num);
                printf("Foram removidos %d valores %d.",cont,num);
            }
        case 0:
            printf("\nFim de programa!\n");
            break;
        default:
            printf("\nOpcao inválida!\n");
            break;
        }
    } while(op != 0);
    return 0;
}