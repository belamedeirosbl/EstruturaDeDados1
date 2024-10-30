#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 53

typedef struct carro {
    char placa[8];
    char marca[15];
    char modelo[15];
    char cor[15];
    int status;  
} CARRO;

typedef struct noTabela {
    char placa[8];
    int posicao;
    struct noTabela* prox;
} NO;

FILE* prepararArquivo(char nome[]);
void fecharArquivo(FILE* arq);
int buscar(NO* tabelaHashing[], char placa[]);
void cadastrar(FILE* arq, NO* tabelaHashing[]);
void consultar(FILE* arq, NO* tabelaHashing[]);
void alterar(FILE* arq, NO* tabelaHashing[]);
void remover(FILE* arq, NO* tabelaHashing[]);
void exibirCadastro(FILE* arq);
void criarIndice(FILE* arq, NO* tabelaHashing[]);
void inserirTabelaHash(NO* tabelaHashing[], char placa[], int pos);
int hashing(char placa[]);
void exibirOpcoes();
void desalocarIndice(NO* tabelaHashing[]);

int main() {
    char nomeArq[] = "carros.dat";
    int op;
    FILE* cadastro;
    NO* tabelaHashing[N] = { NULL };
    cadastro = prepararArquivo(nomeArq);
    if (cadastro == NULL)
        printf("Erro na abertura do arquivo. Programa encerrado \n");
    else {
        criarIndice(cadastro, tabelaHashing);
        do {
            exibirOpcoes();
            scanf("%d", &op); fflush(stdin);
            switch (op) {
                case 1: cadastrar(cadastro, tabelaHashing);
                    break;
                case 2: consultar(cadastro, tabelaHashing);
                    break;
                case 3: alterar(cadastro, tabelaHashing);
                    break;
                case 4: remover(cadastro, tabelaHashing);
                    break;
                case 5: exibirCadastro(cadastro);
                    break;
                case 0: fecharArquivo(cadastro);
                    desalocarIndice(tabelaHashing);
                    break;
                default: printf("Opcao invalida \n");
            }
        } while (op != 0);
    }
    return 0;
}

FILE* prepararArquivo(char nome[]) {
    FILE* aux;
    aux = fopen(nome, "r+t"); 
    if (aux == NULL)
        aux = fopen(nome, "w+t");
    return aux;          
}

void fecharArquivo(FILE* arq) {
    FILE* novoArq = fopen("carros_temp.dat", "w+t");
    CARRO carro;                                    
    rewind(arq);
    while (fread(&carro, sizeof(CARRO), 1, arq) == 1) {
        if (carro.status == 1) {                        
            fwrite(&carro, sizeof(CARRO), 1, novoArq);
        }
    }

    fclose(arq);
    fclose(novoArq);
    remove("carros.dat");
    rename("carros_temp.dat", "carros.dat");
}

void criarIndice(FILE* arq, NO* tabelaHashing[]) {
    CARRO carro;
    int pos = 0;

    rewind(arq);
    while (fread(&carro, sizeof(CARRO), 1, arq) == 1) {
        if (carro.status == 1) {
            inserirTabelaHash(tabelaHashing, carro.placa, pos);
        }
        pos++;
    }
}

void desalocarIndice(NO* tabelaHashing[]) {
    for (int i = 0; i < N; i++) {
        NO* atual = tabelaHashing[i];
        while (atual != NULL) {
            NO* aux = atual;
            atual = atual->prox;
            free(aux);
        }
        tabelaHashing[i] = NULL;
    }
}

void exibirOpcoes() {
    printf("Opções \n");
    printf("1 - Cadastrar um carro \n");
    printf("2 - Consultar carro \n");
    printf("3 - Alterar dados do carro \n");
    printf("4 - Remover carro \n");
    printf("5 - Exibir carros cadastrados \n");
    printf("0 - Encerrar programa \n");
    printf("Informe a opcao: ");
}

int buscar(NO* tabelaHashing[], char placa[]) {
    int indice = hashing(placa); 
    NO* atual = tabelaHashing[indice];

    while (atual != NULL) {
        if (strcmp(atual->placa, placa) == 0) {
            return atual->posicao; 
        }
        atual = atual->prox;
    }
    return -1;
}

void inserirTabelaHash(NO* tabelaHashing[], char placa[], int pos) {
    int indice = hashing(placa); 
    NO* novoNo = (NO*)malloc(sizeof(NO)); 
    strcpy(novoNo->placa, placa); 
    novoNo->posicao = pos; 
    novoNo->prox = NULL; 

    if (tabelaHashing[indice] == NULL) {
        tabelaHashing[indice] = novoNo;
    } else {
        NO* atual = tabelaHashing[indice];
        NO* anterior = NULL;

        while (atual != NULL && strcmp(atual->placa, placa) < 0) {
            anterior = atual;
            atual = atual->prox;
        }

        if (anterior == NULL) { 
            novoNo->prox = tabelaHashing[indice];
            tabelaHashing[indice] = novoNo;
        } else { 
            anterior->prox = novoNo;
            novoNo->prox = atual;
        }
    }
}

int hashing(char placa[]) {
    int hash = 0;
    for (int i = 0; i < strlen(placa); i++) {
        hash = (hash * 31 + placa[i]) % N;
    }
    return hash;
}

void cadastrar(FILE* arq, NO* tabelaHashing[]) {
    char placa[9]; 

    printf("Informe a placa do carro a ser cadastrado: ");
    fgets(placa, sizeof(placa), stdin);
    placa[strcspn(placa, "\n")] = '\0'; 

    int pos = buscar(tabelaHashing, placa);
    if (pos != -1) {
        printf("Carro já está no cadastro.\n");
        return;
    }

    CARRO novoCarro;
    strcpy(novoCarro.placa, placa);

    printf("Informe a marca do carro: ");
    fgets(novoCarro.marca, sizeof(novoCarro.marca), stdin);
    novoCarro.marca[strcspn(novoCarro.marca, "\n")] = '\0'; 

    printf("Informe o modelo do carro: ");
    fgets(novoCarro.modelo, sizeof(novoCarro.modelo), stdin);
    novoCarro.modelo[strcspn(novoCarro.modelo, "\n")] = '\0'; 

    printf("Informe a cor do carro: ");
    fgets(novoCarro.cor, sizeof(novoCarro.cor), stdin);
    novoCarro.cor[strcspn(novoCarro.cor, "\n")] = '\0'; 

    novoCarro.status = 1;

    fseek(arq, 0, SEEK_END);
    pos = ftell(arq)/ sizeof(CARRO); 
    fwrite(&novoCarro, sizeof(CARRO), 1, arq); 
    inserirTabelaHash(tabelaHashing, novoCarro.placa, pos); 
    printf("Carro cadastrado com sucesso.\n");
}

void consultar(FILE* arq, NO* tabelaHashing[]) {

    CARRO carro;
    char placa[8];
    int pos;

    printf("Informe a placa do carro a ser consultado: ");
    scanf("%7s", placa);
    fflush(stdin);

    pos = buscar(tabelaHashing, placa);
    if (pos == -1) {
        printf("Carro não está no cadastro.\n");
        return;
    }

    fseek(arq, pos * sizeof(CARRO), SEEK_SET);
    fread(&carro, sizeof(CARRO), 1, arq);

    printf("Placa: %s\n", carro.placa);
    printf("Marca: %s\n", carro.marca);
    printf("Modelo: %s\n", carro.modelo);
    printf("Cor: %s\n", carro.cor);
    if (carro.status == 1) {
        printf("Status: Ativo\n");
    } else {
        printf("Status: Removido\n");
    }

}

void alterar(FILE* arq, NO* tabelaHashing[]) {
    char placa[8];

    printf("Informe a placa do carro a ser alterado: ");
    scanf("%7s", placa);
    fflush(stdin);

    int pos = buscar(tabelaHashing, placa);
    if (pos == -1) {
        printf("Carro não está no cadastro.\n");
        return;
    }

    CARRO carro;
    fseek(arq, pos * sizeof(CARRO), SEEK_SET);
    fread(&carro, sizeof(CARRO), 1, arq);

    printf("Dados atuais do carro:\n");
    printf("Placa: %s\n", carro.placa);
    printf("Marca: %s\n", carro.marca);
    printf("Modelo: %s\n", carro.modelo);
    printf("Cor: %s\n", carro.cor);

    int resp=1;
    do{
        printf("1- Alterar marca\n2- Alterar modelo\n3- Alterar cor\n0- Encerrar alterações\n");
        printf("Qual dado deseja alterar? ");
        scanf("%d", &resp);
        switch (resp)
        {
        case 1:
            printf("Informe a nova marca:\n");
            scanf("%14s", carro.marca);
            break;
        case 2:
            printf("Informe o novo modelo:\n");
            scanf("%14s", carro.modelo);
            break;
        case 3:
            printf("Informe a nova cor: ");
            scanf("%14s", carro.cor);
            break;

        case 0:
            printf("Alterações concluídas!\n");
        
        default:
            printf("Opção inválida!\n");
            break;
        }
        fflush(stdin);
    }while(resp != 0);

    
    fseek(arq, pos * sizeof(CARRO), SEEK_SET);//posiciona ponteiro
    fwrite(&carro, sizeof(CARRO), 1, arq);//escreve 
    printf("Dados do carro alterados com sucesso.\n");
}


void removerTabelaHash(NO* tabelaHashing[], char placa[], int posTabela) {
    int hashIndex = hashing(placa);
    NO* atual = tabelaHashing[hashIndex];
    NO* anterior = NULL;

    while (atual != NULL && strcmp(atual->placa, placa) != 0) {
        anterior = atual;
        atual = atual->prox;
    }

    if (atual != NULL) {
        if (anterior == NULL) {
            tabelaHashing[hashIndex] = atual->prox;
        } else {
            anterior->prox = atual->prox;
        }
        free(atual);
    }
}

void remover(FILE* arq, NO* tabelaHashing[]) {

    char placa[8];

    printf("Informe a placa do carro a ser removido: ");
    scanf("%7s", placa);
    fflush(stdin);

    int pos = buscar(tabelaHashing, placa);
    if (pos == -1) {
        printf("Carro não está no cadastro.\n");
        return;
    }

    fseek(arq, pos * sizeof(CARRO), SEEK_SET);
    CARRO carro;
    fread(&carro, sizeof(CARRO), 1, arq);
    printf("Dados do carro:\n");
    printf("Placa: %s\n", carro.placa);
    printf("Marca: %s\n", carro.marca);
    printf("Modelo: %s\n", carro.modelo);
    printf("Cor: %s\n", carro.cor);

    int resp;
    printf("Deseja realmente remover este carro? (1 - Sim / 0 - Não): ");
    scanf("%d", &resp);
    while(resp != 1 && resp !=0){
        printf("Resposta inválida!\n");
        printf("Deseja realmente remover este carro? (1 - Sim / 0 - Não): ");
        scanf("%d", &resp);
    }
    fflush(stdin);

    if (resp == 0) {
        printf("Remoção cancelada.\n");
    } else {
        carro.status = 0;
        fseek(arq, pos * sizeof(CARRO), SEEK_SET);
        fwrite(&carro, sizeof(CARRO), 1, arq);//att dados

        removerTabelaHash(tabelaHashing, placa, pos);

        printf("Carro removido com sucesso.\n");
    }
    return;
}




void exibirCadastro(FILE* arq) {

    CARRO carro;

    rewind(arq);
    printf("Carros cadastrados:\n");
    while (fread(&carro, sizeof(CARRO), 1, arq) == 1) {
        if (carro.status == 1) {
            printf("Placa: %s\n", carro.placa);
            printf("Marca: %s\n", carro.marca);
            printf("Modelo: %s\n", carro.modelo);
            printf("Cor: %s\n", carro.cor);
            printf("Status: %s\n", carro.status == 1 ? "Ativo" : "Removido");
            printf("-------------------------------\n");
        }
    }
}