#include <stdio.h> 
#include <stdlib.h>  

typedef struct TnoFila { 
    int num; 
    struct TnoFila* prox; 
} TnoFila; 

typedef struct fila { 
    struct TnoFila *inicio, *fim; 
} fila; 

void inicializar(fila *minhafila) { 
    minhafila->inicio = NULL; 
    minhafila->fim = NULL; 
} 

int gerarsenha(int senha) { 
    return senha + 1; 
} 

int IsFull(fila minhafila) { 
    return 0; 
} 

int IsEmpty(fila minhafila) { 
    return minhafila.inicio == NULL; 
} 

void enfileirar(fila* minhafila, int valor) { 
    TnoFila *aux = (TnoFila*)malloc(sizeof(TnoFila)); 
    aux->num = valor; 
    aux->prox = NULL; 
    if (IsEmpty(*minhafila)) { 
        minhafila->inicio = aux; 
    } else { 
        minhafila->fim->prox = aux; 
    } 
    minhafila->fim = aux; 
} 

int desenfileirar(fila* minhafila) { 
    int valor = minhafila->inicio->num; 
    TnoFila* aux = minhafila->inicio; 
    minhafila->inicio = minhafila->inicio->prox; 
    if (minhafila->inicio == NULL) minhafila->fim = NULL; 
    free(aux); 
    return valor; 
} 

int main() { 
    int senha = 0; 
    fila minhafila; 
    inicializar(&minhafila); 
    int resposta = 1; 
    while (resposta != 0) { 
        printf("ESCOLHA A OPÇÃO DESEJADA:\n1)gerar senha\n2)chamar senha para atendimento\n"); 
        scanf("%d", &resposta); 
        if (resposta == 1) { 
            if (!IsFull(minhafila)) { 
                senha = gerarsenha(senha); 
                enfileirar(&minhafila, senha); 
                printf("A senha de número %d foi gerada\n", senha); 
            } else printf("Fila cheia!\n"); 
        } else if (resposta == 2) { 
            if (!IsEmpty(minhafila)) { 
                int valor = desenfileirar(&minhafila); 
                printf("A senha %d foi chamada!\n", valor); 
            } else printf("A fila está vazia\n"); 
        } 
        if (IsEmpty(minhafila)) break; 
    } 
    printf("Não há clientes esperando por atendimento.\n"); 
   
