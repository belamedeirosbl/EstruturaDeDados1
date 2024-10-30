#include <stdlib.h>
#include <stdio.h>

typedef struct EstruturaLista{
    int valor;
    struct EstruturaLista* proximo;
    struct EstruturaLista* anterior;
}Estrutura;

typedef struct ControleDaFila{
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

Estrutura* buscar(Fila* mf, int valor){
    Estrutura* aux = mf->inicio;
    while(aux!=NULL){
        if(aux->valor == valor){
            return aux;
        }else{
            aux = aux->proximo;
        }
    }
    return aux;//aux == NULL
}

void inserir(Fila* mf, int valor){
    if(buscar(mf,valor) != NULL){
        printf("Essa fila não aceita valores repetidos!\n");
        return;
    }else{
        Estrutura* novo = (Estrutura*)malloc(sizeof(Estrutura));
        novo->proximo = NULL;
        novo->anterior = NULL;
        novo->valor = valor;
        if(isEmpty(*mf) == 1){//so um elemento
            mf->inicio = novo;
            mf->fim = novo;
            mf->quantidade++;
            return;
        }
        if(valor > mf->inicio->valor){//adc inicio
            mf->inicio->anterior = novo;
            novo->proximo = mf->inicio;
            mf->inicio = novo;
            mf->quantidade++;
            return;
        }else if(valor < mf->inicio->valor){//adc fim
            mf->fim->proximo = novo;
            novo->anterior = mf->fim;
            mf->fim = novo;
            mf->quantidade++;
            return; 
        }
        Estrutura* aux = mf->inicio;
        while(aux != NULL){
            if(valor > aux->valor){
                novo->proximo = aux;
                novo->anterior = aux->anterior;
                aux->anterior->proximo = novo;
                aux->anterior = novo;
                mf->quantidade++;
                return;
            }else{
                aux = aux->proximo;
            }
        }
    }
}

void remover(Fila* mf, int valor){
    Estrutura* removerValor = buscar(mf,valor);
    if(removerValor == NULL){
        printf("Valor não está na lista\n");
        return;
    }else{
        if(mf->inicio == mf->fim){
            mf->inicio = NULL;
            mf->fim = NULL;
            free(removerValor);
            mf->quantidade = 0;
            printf("A fila agora esta vazia!\n");
            return;
        }
        if(removerValor == mf->inicio){//é o primeiro
            mf->inicio = mf->inicio->proximo;
            mf->inicio->anterior = NULL;
            free(removerValor);
            mf->quantidade--;
            return;
        }else if(removerValor == mf->fim){
            mf->fim = mf->fim->anterior;
            mf->fim->proximo = NULL;
            free(removerValor);
            mf->quantidade--;
            return;
        }else{
            removerValor->anterior->proximo = removerValor->proximo;
            removerValor->proximo->anterior = removerValor->anterior;
            free(removerValor);
            mf->quantidade--;
            return;
        }
    }
}

void exibirFila(Fila mf){
    Estrutura* aux = mf.inicio;
    while(aux!=NULL){
        printf("[%d]", aux->valor);
        aux = aux->proximo;
    }
    printf("\n");
    return;
}

void exibirOpc(){
    printf("1- Inserir valor\n");
    printf("2- Remover valor\n");
    printf("3- Exibir fila\n");
    printf("0- Finalizar programa\n");
}

int main(){
    int op, valor;
    Fila mf;
    inicializar(&mf);
    do{
        exibirOpc();
        printf("Informe a opção desejada: ");
        scanf("%d", &op);
        switch(op){
            case 1:
                if(isFull(mf) == 1){
                    printf("Fila cheia!\n");
                }else{
                    printf("Informe o valor que deseja adicionar na fila: ");
                    scanf("%d", &valor);
                    inserir(&mf,valor);
                }
            break;

            case 2:
                if(isEmpty(mf) == 1){
                    printf("Fila vazia!\n");
                }else{
                    printf("Informe o valor que deseja remover da fila: ");
                    scanf("%d", &valor);
                    remover(&mf,valor);
                }
            break;

            case 3:
                if(isEmpty(mf) == 1){
                    printf("Fila vazia\n");
                }else{
                    exibirFila(mf);
                }
            break;

        }
    }while(op!=0);
    printf("Fechando programa...");
    return 0;
}