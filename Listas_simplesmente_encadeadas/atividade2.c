#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Contato {
    char nome[50];
    int telefone;
    char email[50];
    struct Contato* prox;
} contato;

typedef struct Fila {
    contato* inicio, * fim;
} fila;

void inicializar(fila* mf) {
    mf->inicio = NULL;
    mf->fim = NULL;
}

int isfull(fila mf) {
    return 0;
}

int isempty(fila mf) {
    return (mf.inicio == NULL);
}

void preencher(contato* novocontato) {
    printf("Informe o telefone: ");
    scanf("%d", &novocontato->telefone);
    getchar();
    printf("Informe o email: ");
    fgets(novocontato->email, 50, stdin);
    novocontato->email[strcspn(novocontato->email, "\n")] = 0;
}

void adicionar(fila* mf) {
    contato* novo = (contato*)malloc(sizeof(contato));
    novo->prox = NULL;
    char nome[50];
    getchar();
    printf("Qual o nome do contato que deseja adicionar? ");
    fgets(nome, 50, stdin);
    nome[strcspn(nome, "\n")] = 0;

    if (isempty(*mf)) {
        strcpy(novo->nome, nome);
        preencher(novo);
        mf->inicio = novo;
        mf->fim = novo;
        printf("Valor adicionado!\n");
        return;
    } else {
        contato* aux1 = mf->inicio;
        contato* aux2 = NULL;
        while (aux1 != NULL) {
            if (strcmp(nome, aux1->nome) == 0) {
                free(novo);
                printf("Não é permitido nomes iguais! o contato não vai ser adicionado.\n");
                return;
            }
            if (nome[0] < aux1->nome[0]) {
                if (aux2 == NULL) {
                    strcpy(novo->nome, nome);
                    preencher(novo);
                    novo->prox = mf->inicio;
                    mf->inicio = novo;
                    printf("Valor adicionado!\n");
                    return;
                } else {
                    strcpy(novo->nome, nome);
                    preencher(novo);
                    novo->prox = aux1;
                    aux2->prox = novo;
                    printf("Valor adicionado!\n");
                    return;
                }
            } else if (aux1->prox == NULL) {
                strcpy(novo->nome, nome);
                preencher(novo);
                aux1->prox = novo;
                mf->fim = novo;
                printf("Valor adicionado!\n");
                return;
            }
            aux2 = aux1;
            aux1 = aux1->prox;
        }
    }
}

void remover(fila* mf, char nome[]) {
    contato* aux1 = mf->inicio;
    contato* aux2 = NULL;
    while (aux1 != NULL) {
        if (strcmp(nome, aux1->nome) == 0) {
            if (aux2 == NULL) {
                if (aux1->prox == NULL) {
                    mf->inicio = NULL;
                    mf->fim = NULL;
                    free(aux1);
                    printf("Valor removido!\n");
                    return;
                } else {
                    mf->inicio = aux1->prox;
                    free(aux1);
                    printf("Valor removido!\n");
                    return;
                }
            } else if (aux1->prox == NULL) {
                mf->fim = aux2;
                aux2->prox = NULL;
                free(aux1);
                printf("Valor removido!\n");
                return;
            } else {
                aux2->prox = aux1->prox;
                free(aux1);
                printf("Nome removido!\n");
                return;
            }
        }
        aux2 = aux1;
        aux1 = aux1->prox;
    }
    printf("O nome não está na lista!\n");
}

void exibir(fila mf) {
    contato* aux = mf.inicio;
    int cont = 1;
    while (aux != NULL) {
        printf("XXXXXX CONTATO %d XXXXXX\n", cont);
        printf("nome: %s\n", aux->nome);
        printf("telefone: %d\n", aux->telefone);
        printf("email: %s\n", aux->email);
        aux = aux->prox;
        cont++;
    }
}

contato* buscar(fila* mf, char nome[]) {
    contato* aux = mf->inicio;
    while (aux != NULL) {
        if (strcmp(nome, aux->nome) == 0) {
            return aux;
        }
        aux = aux->prox;
    }
    return NULL;
}

void procurar(fila mf, char nome[]) {
    contato* aux = buscar(&mf, nome);
    if (aux == NULL) {
        printf("O nome não está nos contatos!\n");
    } else {
        printf("Dados de %s\n", nome);
        printf("nome: %s\n", aux->nome);
        printf("telefone: %d\n", aux->telefone);
        printf("email: %s\n", aux->email);
    }
}

void alterar(fila* mf, char name[]) {
    contato* aux = buscar(mf, name);
    if (aux == NULL) {
        printf("O nome não está nos contatos!\n");
    } else {
        int opc;
        printf("DADOS ATUAIS:\n");
        printf("telefone: %d\n", aux->telefone);
        printf("email: %s\n", aux->email);
        printf("1- alterar telefone\n2- alterar email\n3- alterar ambos\n");
        printf("Escolha a opção desejada: ");
        scanf("%d", &opc);
        int telefone;
        char email[50];
        switch (opc) {
            case 1:
                printf("Informe o novo telefone: ");
                scanf("%d", &telefone);
                aux->telefone = telefone;
                break;
            case 2:
                getchar();
                printf("Informe o novo email: ");
                fgets(email, 50, stdin);
                email[strcspn(email, "\n")] = 0;
                strcpy(aux->email, email);
                break;
            case 3:
                printf("Informe o novo telefone: ");
                scanf("%d", &telefone);
                aux->telefone = telefone;
                getchar();
                printf("Informe o novo email: ");
                fgets(email, 50, stdin);
                email[strcspn(email, "\n")] = 0;
                strcpy(aux->email, email);
                break;
            default:
                printf("Opção inválida!\n");
        }
        if (opc >= 1 && opc <= 3) {
            printf("Dados atualizados:\n");
            printf("nome: %s\n", aux->nome);
            printf("telefone: %d\n", aux->telefone);
            printf("email: %s\n", aux->email);
        }
    }
}

void mostrarop() {
    printf("1- adicionar\n");
    printf("2- remover\n");
    printf("3- exibir\n");
    printf("4- procurar\n");
    printf("5- alterar\n");
    printf("0- sair\n");
}

int main() {
    fila minhafila;
    inicializar(&minhafila);
    int op;

    do {
        mostrarop();
        printf("Qual a opção desejada? ");
        scanf("%d", &op);
        char nome[50];
        switch (op) {
            case 1:
                if (isfull(minhafila) == 0) {
                    adicionar(&minhafila);
                } else {
                    printf("Fila cheia!\n");
                }
                break;

            case 2:
                if (isempty(minhafila) == 0) {
                    getchar();
                    printf("Qual nome deseja remover? ");
                    fgets(nome, 50, stdin);
                    nome[strcspn(nome, "\n")] = 0;
                    remover(&minhafila, nome);
                } else {
                    printf("A fila está vazia!\n");
                }
                break;

            case 3:
                if (isempty(minhafila) == 0) {
                    exibir(minhafila);
                } else {
                    printf("A fila está vazia!\n");
                }
                break;

            case 4:
                if (isempty(minhafila) == 0) {
                    getchar();
                    printf("Qual nome deseja procurar? ");
                    fgets(nome, 50, stdin);
                    nome[strcspn(nome, "\n")] = 0;
                    procurar(minhafila, nome);
                } else {
                    printf("Fila vazia!\n");
                }
                break;

            case 5:
                if (isempty(minhafila) == 0) {
                    getchar();
                    printf("Qual o nome do contato que deseja alterar? ");
                    fgets(nome, 50, stdin);
                    nome[strcspn(nome, "\n")] = 0;
                    alterar(&minhafila, nome);
                } else {
                    printf("Fila vazia!\n");
                }
                break;

            case 0:
                printf("Fechando programa...\n");
                break;

            default:
                printf("Opção inválida!\n");
        }
    } while (op != 0);

    return 0;
}
