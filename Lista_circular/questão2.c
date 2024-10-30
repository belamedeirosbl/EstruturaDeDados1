#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

typedef struct NoListaDupla {
    char nome[40];
    float media;
    int faltas;
    struct NoListaDupla* proximo;
    struct NoListaDupla* anterior;
} NoListaDupla;

typedef struct ListaDuplaEncadeada {
    NoListaDupla* inicio;
    NoListaDupla* fim;
    int tamanho;
} ListaDuplaEncadeada;

void inicializarLista(ListaDuplaEncadeada* lista) {
    lista->inicio = NULL;
    lista->fim = NULL;
    lista->tamanho = 0;
}

int estaVazia(ListaDuplaEncadeada* lista) {
    return lista->tamanho == 0 ? TRUE : FALSE;
}

void cadastrarAluno(ListaDuplaEncadeada* lista, char nomeAluno[40]) {
    float mediaAluno;
    int faltasAluno;

    if (estaVazia(lista)) {
        NoListaDupla* novoAluno = (NoListaDupla*)malloc(sizeof(NoListaDupla));
        strcpy(novoAluno->nome, nomeAluno);
        printf("Media final: ");
        scanf("%f", &mediaAluno);
        while (mediaAluno < 0 || mediaAluno > 10) {
            printf("A media do aluno deve estar entre 0-10. Tente novamente: ");
            scanf("%f", &mediaAluno);
        }
        novoAluno->media = mediaAluno;
        printf("Faltas: ");
        scanf("%d", &faltasAluno);
        novoAluno->faltas = faltasAluno;
        lista->inicio = novoAluno;
        lista->fim = novoAluno;
        novoAluno->proximo = novoAluno;
        novoAluno->anterior = novoAluno;
        lista->tamanho = 1;
        printf("Cadastro vazio realizado!\n");

    } else {
        NoListaDupla* atual = lista->inicio;
        do {
            if (strcmp(atual->nome, nomeAluno) == 0) {
                printf("Nome já existente na lista.\n");
                return;
            }
            atual = atual->proximo;
        } while (atual != lista->inicio);

        NoListaDupla* novoAluno = (NoListaDupla*)malloc(sizeof(NoListaDupla));
        strcpy(novoAluno->nome, nomeAluno);
        printf("Media final: ");
        scanf("%f", &mediaAluno);
        while (mediaAluno < 0 || mediaAluno > 10) {
            printf("A media do aluno deve estar entre 0-10. Tente novamente: ");
            scanf("%f", &mediaAluno);
        }
        novoAluno->media = mediaAluno;
        printf("Faltas: ");
        scanf("%d", &faltasAluno);
        novoAluno->faltas = faltasAluno;

        novoAluno->proximo = lista->inicio;
        novoAluno->anterior = lista->fim;
        lista->inicio->anterior = novoAluno;
        lista->fim->proximo = novoAluno;
        lista->fim = novoAluno;
        lista->tamanho++;

        printf("Cadastro realizado!\n");
    }
}


void listarAlunos(ListaDuplaEncadeada* lista) {
    if (estaVazia(lista)) {
        printf("Lista vazia.\n");
    } else {
        NoListaDupla* atual = lista->inicio;
        do {
            printf("Nome: %s\n", atual->nome);
            printf("Media: %.1f\n", atual->media);
            printf("Faltas: %d\n", atual->faltas);
            printf("\n");
            atual = atual->proximo;
        } while (atual != lista->inicio);
    }
}

NoListaDupla* buscarAluno(ListaDuplaEncadeada* lista, char nomeAluno[40]) {
    if (estaVazia(lista)) {
        return NULL;
    } else {
        NoListaDupla* atual = lista->inicio;
        do {
            if (strcmp(atual->nome, nomeAluno) == 0) {
                return atual;
            }
            atual = atual->proximo;
        } while (atual != lista->inicio);
        return NULL;
    }
}

void alterarMediaAluno(ListaDuplaEncadeada* lista, char nomeAluno[40]) {
    NoListaDupla* aluno = buscarAluno(lista, nomeAluno);
    if (aluno == NULL) {
        printf("Aluno nao encontrado.\n");
    } else {
        float novaMedia;
        printf("Nova media: ");
        scanf("%f", &novaMedia);
        aluno->media = novaMedia;
        printf("Media do aluno '%s' alterada com sucesso.\n", nomeAluno);
    }
}

void alterarFaltasAluno(ListaDuplaEncadeada* lista, char nomeAluno[40]) {
    NoListaDupla* aluno = buscarAluno(lista, nomeAluno);
    if (aluno == NULL) {
        printf("Aluno nao encontrado.\n");
    } else {
        int novasFaltas;
        printf("Novas faltas: ");
        scanf("%d", &novasFaltas);
        aluno->faltas = novasFaltas;
        printf("Faltas do aluno '%s' alteradas com sucesso.\n", nomeAluno);
    }
}

void removerAluno(ListaDuplaEncadeada* lista, char nomeAluno[40]) {
    NoListaDupla* aluno = buscarAluno(lista, nomeAluno);
    if (aluno == NULL) {
        printf("Aluno nao encontrado.\n");
    } else {
        if (lista->tamanho == 1) {
            free(aluno);
            lista->inicio = NULL;
            lista->fim = NULL;
            lista->tamanho = 0;
        } else {
            aluno->anterior->proximo = aluno->proximo;
            aluno->proximo->anterior = aluno->anterior;
            if (aluno == lista->inicio) {
                lista->inicio = aluno->proximo;
            } else if (aluno == lista->fim) {
                lista->fim = aluno->anterior;
            }
            free(aluno);
            lista->tamanho--;
        }
        printf("Aluno '%s' removido com sucesso.\n", nomeAluno);
    }
}

void limparLista(ListaDuplaEncadeada* lista) {
    NoListaDupla* atual = lista->inicio;
    while (atual != NULL) {
        NoListaDupla* proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }
    lista->inicio = NULL;
    lista->fim = NULL;
    lista->tamanho = 0;
    printf("Lista limpa.\n");
}

void exibirOpcoes() {
    printf("\nOpcoes:\n");
    printf("1 - Cadastrar aluno\n");
    printf("2 - Listar alunos\n");
    printf("3 - Alterar media de um aluno\n");
    printf("4 - Alterar faltas de um aluno\n");
    printf("5 - Remover aluno\n");
    printf("6 - Limpar lista de alunos\n");
    printf("0 - Encerrar programa\n");
    printf("Escolha: ");
}

int main(){
    ListaDuplaEncadeada listaUm;
    ListaDuplaEncadeada listaDois;
    inicializar(&listaUm);
    inicializar(&listaDois);
    char nome[40];
    int op, turma;

    do{
        exibirOpcoes();
        scanf("%d",&op);
        switch(op){
            case 1:
                printf("Em que turma? (1/2): ");
                scanf("%d",&turma);
                while(turma != 1 && turma != 2){
                    printf("Opcao invalida. Tente novamente: ");
                    scanf("%d",&turma);
                }
                
                if(turma == 1){
                    printf("\nNome: ");
                    scanf("%s",nome);
                    cadastrar(&listaUm,nome);
                } else {
                    printf("\nNome: ");
                    scanf("%s",nome);
                    cadastrar(&listaDois,nome);
                }
                
                break;
            case 2:
                printf("Que turma? (1/2): ");
                scanf("%d",&turma);
                while(turma != 1 && turma != 2){
                    printf("Opcao invalida. Tente novamente: ");
                    scanf("%d",&turma);
                }
                
                if(turma == 1){
                    if(isEmpty(&listaUm) == TRUE){
                        printf("\nTurma vazia.\n");
                    } else {
                        listar(&listaUm);
                    }
                } else {
                    if(isEmpty(&listaDois) == TRUE){
                        printf("\nTurma vazia.\n");
                    } else {
                        listar(&listaDois);
                    }
                }
                break;
            case 3:
                printf("Que turma? (1/2): ");
                scanf("%d",&turma);
                while(turma != 1 && turma != 2){
                    printf("Opcao invalida. Tente novamente: ");
                    scanf("%d",&turma);
                }

                if(turma == 1){
                    if(isEmpty(&listaUm) == TRUE){
                        printf("\nTurma vazia.\n");
                    } else {
                        alterarMedia(&listaUm);
                    }
                } else {
                    if(isEmpty(&listaDois) == TRUE){
                        printf("\nTurma vazia.\n");
                    } else {
                        alterarMedia(&listaDois);
                    }
                }
                break;
            case 4:
                printf("Que turma? (1/2): ");
                scanf("%d",&turma);
                while(turma != 1 && turma != 2){
                    printf("Opcao invalida. Tente novamente: ");
                    scanf("%d",&turma);
                }

                if(turma == 1){
                    if(isEmpty(&listaUm) == TRUE){
                        printf("\nTurma vazia.\n");
                    } else {
                        alterarfaltas(&listaUm);
                    }
                } else {
                    if(isEmpty(&listaDois) == TRUE){
                        printf("\nTurma vazia.\n");
                    } else {
                        alterarfaltas(&listaDois);
                    }
                }
                break;
            case 5:
                printf("Que turma? (1/2): ");
                scanf("%d",&turma);
                while(turma != 1 && turma != 2){
                    printf("Opcao invalida. Tente novamente: ");
                    scanf("%d",&turma);
                }

                if(turma == 1){
                    if(isEmpty(&listaUm) == TRUE){
                        printf("\nTurma vazia.\n");
                    } else {
                        exibirAlunoEspecifico(&listaUm);
                    }
                } else {
                    if(isEmpty(&listaDois) == TRUE){
                        printf("\nTurma vazia.\n");
                    } else {
                        exibirAlunoEspecifico(&listaDois);
                    }
                }
                break;
            case 6:
                printf("Que turma? (1/2): ");
                scanf("%d",&turma);
                while(turma != 1 && turma != 2){
                    printf("Opcao invalida. Tente novamente: ");
                    scanf("%d",&turma);
                }

                if(turma == 1){
                    if(isEmpty(&listaUm) == TRUE){
                        printf("\nTurma vazia.\n");
                    } else {
                        remover(&listaUm);
                    }
                } else {
                    if(isEmpty(&listaDois) == TRUE){
                        printf("\nTurma vazia.\n");
                    } else {
                        remover(&listaDois);
                    }
                }
                break;
            case 7:
                printf("Que turma? (1/2): ");
                scanf("%d",&turma);
                while(turma != 1 && turma != 2){
                    printf("Opcao invalida. Tente novamente: ");
                    scanf("%d",&turma);
                }

                if(turma == 1){
                    if(isEmpty(&listaUm) == TRUE){
                        printf("\nTurma vazia.\n");
                    } else {
                        limparTurma(&listaUm);
                    }
                } else {
                    if(isEmpty(&listaDois) == TRUE){
                        printf("\nTurma vazia.\n");
                    } else {
                        limparTurma(&listaDois);
                    }
                }
                break;
            case 0:
                printf("\nEncerrando programa...\n");
                break;
        }

    } while (op != 0);
}