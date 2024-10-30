#include <stdio.h>
#include <stdlib.h>

typedef struct NoStack {
    int info;
    struct NoStack* prox;
} TNoStack;

typedef TNoStack* Stack;

void inicializar(Stack* pilha) {
    *pilha = NULL;
}

int isEmpty(Stack pilha) {
    return (pilha == NULL);
}

void push(Stack* pilha, int valor) {
    TNoStack* novo = (TNoStack*)malloc(sizeof(TNoStack));
    novo->info = valor;
    novo->prox = *pilha;
    *pilha = novo;
}

int pop(Stack* pilha) {
    if (isEmpty(*pilha)) {
        printf("A pilha está vazia!\n");
        return -1;
    }
    TNoStack* aux = *pilha;
    int valor = aux->info;
    *pilha = aux->prox;
    free(aux);
    return valor;
}

void converterParaBinario(int numero) {
    Stack pilha;
    inicializar(&pilha);

    while (numero > 0) {
        push(&pilha, numero % 2);
        numero /= 2;
    }

    while (!isEmpty(pilha)) {
        printf("%d", pop(&pilha));
    }
    printf("\n");
}

int main() {
    int numero;
    printf("Informe um número decimal: ");
    scanf("%d", &numero);
    printf("Representação binária: ");
    converterParaBinario(numero);
    return 0;
}
