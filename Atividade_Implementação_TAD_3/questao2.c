#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct nofila {
    char nome[50];
    int num;
    struct nofila* prox;
} Tnofila;

typedef struct Fila {
    Tnofila* inicio;
    Tnofila* fim;
} fila;

void inicializar(fila* md) {
    md->fim = NULL;
    md->inicio = NULL;
}

int isfull(fila md) {
    return 0;
}

int isempty(fila md) {
    return (md.inicio == NULL);
}

void enfileirar(fila* md, char nome[], int num) {
    Tnofila* aux = (Tnofila*)malloc(sizeof(Tnofila));
    strcpy(aux->nome, nome);
    aux->num = num;
    aux->prox = NULL;

    if (isempty(*md) == 1) {
        md->inicio = aux;
    } else {
        md->fim->prox = aux;
    }
    md->fim = aux;
}

char* desenfileirar(fila* md) {
    char* name = malloc(50 * sizeof(char));
    strcpy(name, md->inicio->nome);
    Tnofila* aux = md->inicio;
    md->inicio = md->inicio->prox;

    if (md->inicio == NULL) md->fim = NULL;

    free(aux);
    return name;
}

void exibirOpcoes() {
    printf("Opções: \n");
    printf("1 - Enqueue \n");
    printf("2 - Dequeue \n");
    printf("0 - Encerrar programa \n");
    printf("Informe a opção desejada: ");
}

int main() {
    fila minhaFila;
    inicializar(&minhaFila);
    int op, num;
    char nome[50];

    do {
        exibirOpcoes();
        scanf("%d", &op);
        getchar();
        switch (op) {
            case 1:
                printf("Informe a descrição do pedido: ");
                fgets(nome, 50, stdin);
                nome[strcspn(nome, "\n")] = 0;
                printf("Informe o numero do pedido: ");
                scanf("%d", &num);
                getchar();
                if (isfull(minhaFila) == 0) {
                    enfileirar(&minhaFila, nome, num);
                    printf("Pedido enfileirado! \n");
                } else {
                    printf("Queue full!\n");
                }
                break;
            case 2:
                if (isempty(minhaFila) == 0) {
                    printf("Pedido de descrição '%s' pronto \n", desenfileirar(&minhaFila));
                } else {
                    printf("Queue empty! \n");
                }
                break;
            case 0:
                printf("Fim de programa! \n");
                break;
            default:
                printf("Opção inválida! \n");
        }
    } while (op != 0);

    return 0;
}
