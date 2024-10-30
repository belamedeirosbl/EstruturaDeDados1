#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>  
#include <stdlib.h>  

typedef struct NoQueue { 
    int info; 
    struct NoQueue* prox; 
} TNoQueue; 

typedef TNoQueue* Queue; 

void inicializar(Queue* fila) { 
    *fila = NULL; 
} 

int isEmpty(Queue fila) {  
    return fila == NULL;
} 

void enqueue(Queue* fila, int valor) { 
    TNoQueue* novo = (TNoQueue*)malloc(sizeof(TNoQueue)); 
    novo->info = valor; 
    novo->prox = NULL; 
    if (isEmpty(*fila)) { 
        *fila = novo; 
    } else { 
        TNoQueue* aux = *fila; 
        while (aux->prox != NULL) { 
            aux = aux->prox; 
        } 
        aux->prox = novo; 
    } 
} 

int dequeue(Queue* fila) {  
    Queue aux = *fila; 
    int valor = (*fila)->info; 
    *fila = (*fila)->prox; 
    free(aux); 
    return valor; 
} 

int head(Queue fila) {   
    return fila->info; 
} 

int isFull(Queue fila) {  
    return 0; 
} 

void exibirOpcoes() { 
    printf("Opções:\n1 - Enqueue\n2 - Dequeue\n3 - Head\n0 - Encerrar programa\nInforme a opção desejada: "); 
} 

int main() { 
    Queue minhaFila; 
    inicializar(&minhaFila); 
    int op, num; 
    do { 
        exibirOpcoes(); 
        scanf("%d", &op); 
        switch (op) { 
            case 1: printf("Informe o valor: "); 
                scanf("%d", &num); 
                if (!isFull(minhaFila)) { 
                    enqueue(&minhaFila, num); 
                    printf("Valor enfileirado!\n"); 
                } else { 
                    printf("Queue full!\n"); 
                } 
                break; 
            case 2: if (!isEmpty(minhaFila)) { 
                        num = dequeue(&minhaFila); 
                        printf("Valor desenfileirado: %d\n", num); 
                    } else { 
                        printf("Queue empty!\n"); 
                    } 
                    break; 
            case 3: if (!isEmpty(minhaFila)) { 
                        num = head(minhaFila); 
                        printf("Valor no início da fila: %d\n", num); 
                    } else { 
                        printf("Queue empty!\n"); 
                    } 
                    break; 
            case 0: printf("Fim de programa!\n"); 
                break; 
            default: printf("Opção inválida!\n"); 
        } 
    } while (op != 0); 
    return 0; 
} 
