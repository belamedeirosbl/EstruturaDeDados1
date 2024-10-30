#include <stdlib.h>
#include <stdio.h>

typedef struct estruturaFila{
    struct estruturaFila* proximo;
    struct estruturaFila* anterior;
    int valor;
}estrutura;

typedef struct controleFila{
    estrutura* inicio;
    estrutura* fim;
    int quantidade;
}fila;

void inicializar(fila *mf){
    mf->fim = NULL;
    mf->inicio = NULL;
    mf->quantidade = 0;
}

int isFull(fila mf){
    return 0;
}

int isEmpty(fila mf){
    if(mf.inicio == NULL){
        return 1;
    }else{
        return 0;
    }
}

int buscarRepetido(fila mf, int valor){
    estrutura* aux = mf.inicio;
    while(aux != NULL){
        int valorAtual = aux->valor;  
        if(valorAtual == valor){
            return 0;//achou
        }else{
            aux = aux->proximo;
        }
    }
    return 1;//nao tem
}

void inserir(fila* mf, int valor){
    estrutura* novo = (estrutura*)malloc(sizeof(estrutura));
    novo->proximo = NULL;
    novo->anterior = NULL;
    novo->valor = valor;
    if(isEmpty(*mf) == 1){
        mf->inicio = novo;
        mf->fim = novo;
        mf->quantidade++;
        return;
    }else{
        if(valor < mf->inicio->valor){//inserir no inicio
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
            estrutura* aux = mf->inicio;
            while(aux!= NULL){
                if(aux->valor == valor){
                    free(novo);
                    printf("Essa fila não aceita valores repetidos!\n");
                    return; 
                }
                if(aux->valor > valor){//achou
                    novo->anterior = aux->anterior;
                    novo->proximo = aux;
                    aux->anterior->proximo = novo;
                    aux->anterior = novo;
                    mf->quantidade++;
                    return;
                }else{
                    aux = aux->proximo;
                }
            }
            return;
        }
    }
}

void intersecao(fila a, fila b, fila* intersecao){
    estrutura* aux = a.inicio;
    while(aux != NULL){
        int valor = aux->valor;
        if(buscarRepetido(b, valor) == 0){//achou um valor igual
            inserir(intersecao,valor);
        }
        aux = aux->proximo;
        
    }
}

void uniao(fila a, fila b, fila* uniao){
    estrutura* aux = a.inicio;
    while(aux != NULL){
        int valor = aux->valor;
        inserir(uniao,valor);//insere toda a fila a
        aux = aux->proximo;
    }
    aux = b.inicio;
    while(aux != NULL){
        int valor = aux->valor;
        if(buscarRepetido(*uniao,valor) == 1){
            inserir(uniao,valor);
        }
        aux = aux->proximo;
    }
}

void diferenca(fila a, fila b, fila* diferenca){
    estrutura* aux = a.inicio;
    while(aux!=NULL){
        int valor = aux->valor;
        if(buscarRepetido(b,valor) == 1){
            inserir(diferenca,valor);
        }
        aux = aux->proximo;
    }
}

void exibirFila(fila mf){
    estrutura* aux = mf.inicio;
    while(aux != NULL){
        printf("[%d] ",aux->valor);
        aux = aux->proximo;
    }
    printf("\n");
}


int main(){
    fila A,B,filaIntersecao, filaUniao, filaDiferenca;
    int tamanho, valor;
    inicializar(&A);
    inicializar(&B);
    inicializar(&filaIntersecao);
    inicializar(&filaUniao);
    inicializar(&filaDiferenca);
    printf("Qual vai ser o tamanho de A? ");
    scanf("%d", &tamanho);
    while(A.quantidade < tamanho){
        printf("Informe o valor que deseja adicionar em A: ");
        scanf("%d", &valor);
        inserir(&A,valor);
    }

    printf("Qual vai ser o tamanho de B? ");
    scanf("%d", &tamanho);
    while(B.quantidade < tamanho){
        printf("Informe o valor que deseja adicionar em B: ");
        scanf("%d", &valor);
        inserir(&B,valor);
    }
    
    printf("FILA A: ");
    exibirFila(A);
    
    printf("FILA B: ");
    exibirFila(B);
    
    printf("FILA intersecao: ");
    intersecao(A, B, &filaIntersecao);
    exibirFila(filaIntersecao);
    
    printf("FILA UNIÃO: ");
    uniao(A, B, &filaUniao);
    exibirFila(filaUniao);
    
    printf("FILA DIFERENÇA: ");
    diferenca(A, B, &filaDiferenca);
    exibirFila(filaDiferenca);

    return 0;
}
