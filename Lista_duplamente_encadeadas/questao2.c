#include <stdio.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct EstruturaLista{
    int valor;
    struct EstruturaLista* proximo;
    struct EstruturaLista* anterior;
}Estrutura;

typedef struct ControleDeFila{
    Estrutura* inicio;
    Estrutura* fim;
    int quantidade;
}Fila;

void inicializar(Fila* mf){
    mf->inicio = NULL;
    mf->fim = NULL;
    mf->quantidade = 0;
}

int isFull(Fila mf){
    return 0;
}

int isEmpty(Fila mf){
    if(mf.inicio == NULL){
        return 1;
    }else{
        return 0;
    }
}

void inserir(Fila* mf, int valor){
    Estrutura* novo = (Estrutura*)malloc(sizeof(Estrutura));
    novo->proximo = NULL;
    novo->anterior= NULL;
    novo->valor = valor;
    if(isEmpty(*mf) == 1){//fila vazia
        mf->inicio = novo;
        mf->fim = novo;
        mf->quantidade++;
        return;
    }else{
        if(valor <= mf->inicio->valor){//inserir no inicio
            mf->inicio->anterior = novo;
            novo->proximo = mf->inicio;
            mf->inicio = novo;
            mf->quantidade++;
            return;
        }else if(valor > mf->fim->valor){
            mf->fim->proximo = novo;
            novo->anterior = mf->fim;
            mf->fim = novo;
            mf->quantidade++;
            return;
        }else{
            Estrutura* aux1 = mf->inicio->proximo;
            Estrutura* aux2 = mf->inicio;
            while(aux1!=NULL){
                if(valor <= aux1->valor){//achou o ponto
                    novo->anterior = aux2;
                    novo->proximo = aux1;
                    aux2->proximo = novo;
                    aux1->anterior = novo;
                    mf->quantidade++;
                    return;
                }else{
                    aux2 = aux1;
                    aux1 = aux1->proximo;
                }
            }         
        }
    }
}

void removerValor(Fila* mf, int valor){
    Estrutura* aux = mf->inicio;
    while(aux != NULL){
        Estrutura* auxiliar2 = NULL;
        if(aux->valor == valor){//encontrou o valor
            while(aux->valor == valor){
                if(mf->inicio == mf->fim){//so tem um elemento
                    mf->inicio = NULL;
                    mf->fim = NULL;
                    free(aux);
                    printf("A fila esta vazia agora!\n");
                    return;
                    mf->quantidade--;
                }else if(aux == mf->inicio){//removendo o primeiro
                    auxiliar2 = aux->proximo;
                    mf->inicio = mf->inicio->proximo;
                    mf->inicio->anterior = NULL;
                    free(aux);
                    mf->quantidade--;
                }else if(aux == mf->fim){//removendo o ultimo
                    mf->fim = mf->fim->anterior;
                    mf->fim->proximo = NULL;
                    free(aux);
                    mf->quantidade--;
                    return;
                }else{
                    auxiliar2 = aux->proximo;
                    aux->anterior->proximo = aux->proximo;
                    aux->proximo->anterior = aux->anterior;
                    free(aux);
                    mf->quantidade--;
                }
                aux = auxiliar2;
            }
            return;
        }else{
            aux = aux->proximo;
        }
    }
    printf("Valor não está na lista!\n");
}

void exibirFila(Fila mf){
    Estrutura* aux = mf.inicio;
    while(aux!=NULL){
        printf("[%d] ",aux->valor);
        aux = aux->proximo;
    }
    printf("\n");
    return;
}

void exibirOpc(){
    printf("1- Inserir valor\n");
    printf("2- Remover valor\n");
    printf("3- Exibir fila\n");
}

int main(){
    int op, valor;
    Fila mf;
    inicializar(&mf);
    do{
        exibirOpc();
        printf("Escolha a opção desejada: ");
        scanf("%d", &op);
        switch(op){
            case 1:
                if(isFull(mf) == 1){
                    printf("Fila cheia!\n");
                }else{
                    printf("Informe o valor que deseja adicionar: ");
                    scanf("%d", &valor);
                    inserir(&mf,valor);
                }
                break;
            case 2:
                    if(isEmpty(mf) == 1){
                        printf("Fila vazia!\n");
                    }else{
                        printf("Informe o valor que deseja remover: ");
                        scanf("%d",&valor);
                        removerValor(&mf, valor);
                    }
                break;
            
            case 3:
                if(isEmpty(mf) == 1){
                    printf("Fila vazia!\n");
                }else{
                    exibirFila(mf);
                }
                break;
                
            default: printf("TENTE NOVAMENTE!\n");
        }
    }while(op!=0);

    return 0;
}
