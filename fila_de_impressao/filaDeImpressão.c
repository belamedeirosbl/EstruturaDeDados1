#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct TNofila {
    char info[50];
    struct TNofila *prox;
} TNofila;

typedef struct Queue {
    TNofila *inicio, *fim;
} Queue;

void inicializar(Queue *fila) {
    fila->inicio = NULL;
    fila->fim = NULL;
}

int isEmpty(Queue *fila) {
    return (fila->inicio == NULL);
}

void enqueue(Queue *fila, const char *nomeArquivo) {
    TNofila *novo = (TNofila*)malloc(sizeof(TNofila));
    strcpy(novo->info, nomeArquivo);
    novo->prox = NULL;

    if (isEmpty(fila)) {
        fila->inicio = novo;
        fila->fim = novo;
    } else {
        fila->fim->prox = novo;
        fila->fim = novo;
    }
}

void dequeue(Queue *fila) {
    if (isEmpty(fila)) {
        printf("A fila está vazia.\n");
        return;
    }

    TNofila *aux = fila->inicio;
    fila->inicio = fila->inicio->prox;

    if (fila->inicio == NULL) {
        fila->fim = NULL;
    }

    free(aux);
}

char* head(Queue *fila) {
    if (isEmpty(fila)) {
        printf("A fila está vazia.\n");
        return NULL;
    }
    return fila->inicio->info;
}

int isFull(Queue *fila) {
    return 0;
}

void cancel(Queue *fila, const char *nomeArquivo) {
    if (isEmpty(fila)) {
        printf("A fila está vazia.\n");
        return;
    }

    TNofila *aux = fila->inicio;
    TNofila *anterior = NULL;

    while (aux != NULL && strcmp(aux->info, nomeArquivo) != 0) {
        anterior = aux;
        aux = aux->prox;
    }

    if (aux == NULL) {
        printf("Arquivo %s não encontrado na fila.\n", nomeArquivo);
        return;
    }

    if (anterior == NULL) {
        fila->inicio = aux->prox;
    } else {
        anterior->prox = aux->prox;
    }

    if (aux == fila->fim) {
        fila->fim = anterior;
    }

    free(aux);
    printf("Arquivo %s removido da fila.\n", nomeArquivo);
}

void list(Queue *fila) {
    if (isEmpty(fila)) {
        printf("A fila está vazia.\n");
        return;
    }

    TNofila *aux = fila->inicio;
    printf("Arquivos na fila de impressão:\n");

    while (aux != NULL) {
        printf("- %s\n", aux->info);
        aux = aux->prox;
    }
}

int main() {
    Queue fila;
    inicializar(&fila);

    enqueue(&fila, "arquivo1.pdf");
    enqueue(&fila, "arquivo2.docx");
    enqueue(&fila, "arquivo3.jpg");

    list(&fila);

    cancel(&fila, "arquivo2.docx");
    list(&fila);

    dequeue(&fila);
    list(&fila);

    printf("Primeiro arquivo da fila: %s\n", head(&fila));

    return 0;
}
