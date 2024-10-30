#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define TAM 10
typedef struct queue {
    int dados[TAM];
    int inicio, fim;
} Queue;

void inicializar(Queue* fila) {
    int i;
    fila->inicio = 0;
    fila->fim = -1;
    for (i = 0; i < TAM; i++) {
        fila->dados[i] = 0;
    }
}

void enqueue(Queue* fila, int valor) {
    fila->fim++;
    fila->dados[fila->fim] = valor;
}

int dequeue(Queue* fila) {
    int num = fila->dados[fila->inicio];
    for (int i = 0; i < fila->fim; i++) {
        fila->dados[i] = fila->dados[i + 1];
    }
    fila->fim--;
    return num;
}

int head(Queue fila) {
    return fila.dados[0];
}

int isFull(Queue fila) {
    return fila.fim == (TAM - 1);
}

int isEmpty(Queue fila) {
    return fila.fim == -1;
}

void exibirOpcoes() {
    printf("Opções: \n");
    printf("1 - Enqueue \n");
    printf("2 - Dequeue \n");
    printf("3 - Head \n");
    printf("0 - Encerrar programa \n");
    printf("Informe a opção desejada: ");
}

int main() {
    Queue minhaFila;
    inicializar(&minhaFila);
    int op, num;

    do {
        exibirOpcoes();
        scanf("%d", &op);
        getchar();

        switch (op) {
        case 1:
            if (!isFull(minhaFila)) {
                printf("Informe o valor: ");
                scanf("%d", &num);
                enqueue(&minhaFila, num);
                printf("Valor enfileirado!\n");
            } else {
                printf("Queue full!\n");
            }
            break;
        case 2:
            if (!isEmpty(minhaFila)) {
                int retirado = dequeue(&minhaFila);
                printf("O valor retirado foi: %d\n", retirado);
            } else {
                printf("A fila está vazia!\n");
            }
            break;
        case 3:
            if (!isEmpty(minhaFila)) {
                int comeco = head(minhaFila);
                printf("HEAD:%d\n", comeco);
            } else {
                printf("A fila está vazia!\n");
            }
            break;
        case 0:
            printf("Fim de programa!");
            break;
        default:
            printf("Opção inválida!");
        }
    } while (op != 0);

    return 0;
}
