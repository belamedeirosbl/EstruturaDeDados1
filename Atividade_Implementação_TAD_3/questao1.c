#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct nofila {
    char nome[50];
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

void cancel(fila* md, char nome[]) {
    Tnofila *aux1 = md->inicio;
    Tnofila *aux2 = NULL;

    while (aux1 != NULL && strcmp(aux1->nome, nome) != 0) {
        aux2 = aux1;
        aux1 = aux1->prox;
    }

    if (aux1 == NULL) {
        printf("Arquivo '%s' não encontrado na fila.\n", nome);
        return;
    }

    if (aux2 == NULL) {
        md->inicio = aux1->prox;
    } else {
        aux2->prox = aux1->prox;
    }

    if (aux1 == md->fim) {
        md->fim = aux2;
    }

    free(aux1);
    printf("Arquivo '%s' cancelado.\n", nome);
}

void list(fila md) {
    Tnofila* aux = md.inicio;
    if (isempty(md)) {
        printf("Fila vazia.\n");
        return;
    }
    printf("Arquivos na fila:\n");
    while (aux != NULL) {
        printf("%s\n", aux->nome);
        aux = aux->prox;
    }
}

void enfileirar(fila* md, char nome[]) {
    Tnofila* aux = (Tnofila*)malloc(sizeof(Tnofila));
    strcpy(aux->nome, nome);
    aux->prox = NULL;

    if (isempty(*md)) {
        md->inicio = aux;
    } else {
        md->fim->prox = aux;
    }
    md->fim = aux;
}

char* desenfileirar(fila* md) {
    if (isempty(*md)) {
        printf("Fila vazia. Não é possível desenfileirar.\n");
        return NULL;
    }

    char* name = (char*)malloc(50 * sizeof(char));
    strcpy(name, md->inicio->nome);
    Tnofila* aux = md->inicio;
    md->inicio = md->inicio->prox;

    if (md->inicio == NULL) {
        md->fim = NULL;
    }

    free(aux);
    return name;
}

char* head(fila md) {
    if (isempty(md)) {
        printf("Fila vazia. Não há arquivos.\n");
        return NULL;
    }
    return md.inicio->nome;
}

void exibirOpcoes() {
    printf("Opções:\n");
    printf("1 - Enfileirar\n");
    printf("2 - Desenfileirar\n");
    printf("3 - Cancelar\n");
    printf("4 - Listar\n");
    printf("0 - Encerrar programa\n");
    printf("Informe a opção desejada: ");
}

int main() {
    fila minhaFila;
    inicializar(&minhaFila);
    int op;
    char nome[50];

    do {
        exibirOpcoes();
        scanf("%d", &op);
        getchar();
        switch (op) {
            case 1:
                printf("Informe o nome do arquivo: ");
                fgets(nome, 50, stdin);
                nome[strcspn(nome, "\n")] = 0; // Remove newline character
                if (isfull(minhaFila) == 0) {
                    enfileirar(&minhaFila, nome);
                    printf("Arquivo '%s' enfileirado!\n", nome);
                } else {
                    printf("Fila cheia!\n");
                }
                break;
            case 2:
                if (!isempty(minhaFila)) {
                    char* arquivoPronto = desenfileirar(&minhaFila);
                    if (arquivoPronto != NULL) {
                        printf("Arquivo '%s' desenfileirado!\n", arquivoPronto);
                        free(arquivoPronto);
                    }
                } else {
                    printf("Fila vazia!\n");
                }
                break;
            case 3:
                printf("Informe o nome do arquivo a cancelar: ");
                fgets(nome, 50, stdin);
                nome[strcspn(nome, "\n")] = 0; // Remove newline character
                cancel(&minhaFila, nome);
                break;
            case 4:
                list(minhaFila);
                break;
            case 0:
                printf("Fim de programa!\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (op != 0);

    return 0;
}
