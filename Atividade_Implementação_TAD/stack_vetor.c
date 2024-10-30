#define _CRT_SECURE_NO_WARNINGS
#define TAM 10

#include <stdio.h>

typedef struct stack {
    int dados[TAM];
    int topo;
} Stack;

void inicializar(Stack* pilha) {
    int i;
    for (i = 0; i < TAM; i++) {
        pilha->dados[i] = 0;
    }
    pilha->topo = -1;
}

void push(Stack* pilha, int valor) {
    (pilha->topo)++;
    pilha->dados[pilha->topo] = valor;
}

void pop(Stack* pilha) {
    pilha->dados[pilha->topo] = 0;
    pilha->topo -= 1;
}

void top(Stack pilha) {
    printf("O valor no topo da pilha esta na posição %d e é igual a %d\n", pilha.topo + 1, pilha.dados[pilha.topo]);
}

int isFull(Stack pilha) {
    return pilha.topo == TAM - 1;
}

int isEmpty(Stack* pilha) {
    return pilha->topo == -1 ? -1 : 0;
}

void exibirOpcoes() {
    printf("Opções: \n");
    printf("1 - Push \n");
    printf("2 - Pop \n");
    printf("3 - Top \n");
    printf("0 - Encerrar programa \n");
    printf("Informe a opção desejada: ");
}

int main() {
    Stack minhaPilha;
    inicializar(&minhaPilha);
    int op, num;

    do {
        exibirOpcoes();
        scanf("%d", &op);

        switch (op) {
        case 1:
            printf("Informe o valor: ");
            scanf("%d", &num);
            if (!isFull(minhaPilha)) {
                push(&minhaPilha, num);
                printf("Valor empilhado!\n");
            } else {
                printf("Stack full\n");
            }
            break;
        case 2:
            if (!isEmpty(&minhaPilha)) {
                printf("O valor %d ", minhaPilha.dados[minhaPilha.topo]);
                pop(&minhaPilha);
                printf("foi removido com sucesso\n");
            } else {
                printf("A PILHA ESTA VAZIA\n");
            }
            break;
        case 3:
            top(minhaPilha);
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
