#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 

typedef struct Tnopilha { 
    char letra; 
    struct Tnopilha* prox; 
} stack; 

typedef stack* Stack; 

void inicializar(Stack* pilha) { 
    *pilha = NULL; 
} 

void push(Stack* pilha, char caractere) { 
    stack* aux = (stack*)malloc(sizeof(stack)); 
    aux->letra = caractere; 
    aux->prox = *pilha; 
    *pilha = aux; 
} 

char pop(Stack* pilha) { 
    char caractere = (*pilha)->letra; 
    stack* aux = *pilha; 
    *pilha = (*pilha)->prox; 
    free(aux); 
    return caractere; 
} 

int comparar(Stack* pilha, char nome[], int tamanho) { 
    int cont = 0, resposta = 0; 
    while (cont < tamanho) { 
        push(pilha, nome[cont++]); 
    } 
    cont = 0; 
    while (cont < tamanho) { 
        if (nome[cont++] != pop(pilha)) { 
            resposta = 1; 
            break; 
        } 
    } 
    return resposta; 
} 

int main() { 
    char nome[50]; 
    Stack minhapilha; 
    inicializar(&minhapilha); 
    printf("Digite sua String: "); 
    fgets(nome, 50, stdin); 
    int tam = strlen(nome) - 1; 
    if (!comparar(&minhapilha, nome, tam)) { 
        printf("SIM"); 
    } else printf("NAO"); 
    return 0; 
} 
