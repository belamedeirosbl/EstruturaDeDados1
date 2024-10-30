#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

typedef struct noPilha {
    int info;
    struct noPilha* prox;
} TNoPilha;
typedef TNoPilha* Stack;

void inicializar(Stack* pilha) {
    *pilha = NULL;
}

void push(Stack* pilha, int valor) {
    TNoPilha* novoNo = (TNoPilha*)malloc(sizeof(TNoPilha));
    novoNo->info = valor;
    novoNo->prox = *pilha;
    *pilha = novoNo;
}

int pop(Stack* pilha) {
    TNoPilha* aux = *pilha;
    *pilha = (*pilha)->prox;
    int valorretirado = aux->info;
    free(aux);
    return valorretirado;
}

int top(Stack pilha) {
    return pilha->info;
}

int isEmpty(Stack pilha) {
    return pilha == NULL;
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
        getchar();

        switch (op) {
        case 1:
            printf("Informe o valor: ");
            scanf("%d", &num);
            push(&minhaPilha, num);
            printf("Valor empilhado!\n");
            break;
        case 2:
            if (!isEmpty(minhaPilha)) {
                int valorRetirado = pop(&minhaPilha);
                printf("O valor %d foi removido", valorRetirado);
            } else {
                printf("Stack Empty\n");
            }
            break;
        case 3:
            if (!isEmpty(minhaPilha)) {
                int topo = top(minhaPilha);
                printf("O valor do topo é %d\n", topo);
            } else {
                printf("Stack Empty\n");
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
