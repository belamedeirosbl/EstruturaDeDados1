#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int info;
    struct node* prox;
} Node;

typedef struct lseCircular {
    Node* inicio;
    Node* fim;
    int qtd;
} LSECircular;

void inicializar(LSECircular* lista) {
    lista->inicio = NULL;
    lista->fim = NULL;
    lista->qtd = 0;
}

int isEmpty(LSECircular mf){
    if(mf.inicio == NULL || mf.qtd == 0){
        return 1;
    }else{
        return 0;
    }
}

void inserirFinal(LSECircular* lista, int valor) {
    Node* novo = (Node*)malloc(sizeof(Node));
    novo->info = valor;
    if(isEmpty(*lista) == 1){
        lista->inicio = novo;
        lista->fim = novo;
        novo->prox = novo;
    }else{
        novo->prox = lista->inicio;
        lista->fim->prox = novo;
        lista->fim = novo;
    }
    lista->qtd++;
}

void inserirInicio(LSECircular* lista, int valor) {
    Node* novo = (Node*)malloc(sizeof(Node));
    novo->info = valor;
    if(isEmpty(*lista) == 1){
        lista->inicio = novo;
        lista->fim = novo;
        novo->prox = novo;
    }else{
        lista->fim->prox = novo;
        novo->prox = lista->inicio;
        lista->inicio = novo;
    }
    lista->qtd++;
}

void removerPrimeiro(LSECircular* lista){
    Node* remover = lista->inicio;
    if(remover->prox == lista->inicio){
        lista->inicio = NULL;
        lista->fim = NULL;
        lista->qtd = 0;
    }else{
        lista->inicio = lista->inicio->prox;
        lista->fim->prox = lista->inicio;
        lista->qtd--;
    }
    free(remover);
}

void removerFinal(LSECircular* lista){
    Node* remover = lista->fim;
    if(lista->fim == lista->inicio){
        lista->fim = NULL;
        lista->inicio = NULL;
        lista ->qtd = 0;
    }else{
        Node* aux = lista->inicio;
        while(aux -> prox != lista->fim){
            aux = aux->prox;
        }
        aux->prox = lista->inicio;
        lista->fim = aux;
        lista->qtd --;
    }
    free(remover);
}

void exibirLista(LSECircular lista){
    Node* aux = lista.inicio;
    do{
        printf("[%d] ",aux->info);
        aux = aux->prox;
    }while(aux != lista.inicio);
    printf("\n");
}

void exibirOpcoes() {
    printf("Opções: \n");
    printf("1 – Inserir valor no início da lista \n");
    printf("2 – Inserir valor no final da lista \n");
    printf("3 – Remover primeiro da lista \n");
    printf("4 – Remover último da lista \n");
    printf("5 – Exibir a lista \n");
    printf("0 - Encerrar programa \n");
    printf("Informe a opção desejada: ");
}

int main() {
    LSECircular listaInteiros;
    inicializar(&listaInteiros);
    int op, num;
    do {
        exibirOpcoes();
        scanf("%d", &op);
        switch (op) {
            case 1:
                printf("Informe o valor a ser inserido: ");
                scanf("%d", &num);
                inserirInicio(&listaInteiros, num);
                break;
            case 2:
                printf("Informe o valor a ser inserido: ");
                scanf("%d", &num);
                inserirFinal(&listaInteiros, num);
                break;
            case 3:
                removerPrimeiro(&listaInteiros);
                printf("Valor removido!\n");
                break;
            case 4:
                removerFinal(&listaInteiros);
                printf("Valor removido!\n");
                break;
            case 5:
                exibirLista(listaInteiros);
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
