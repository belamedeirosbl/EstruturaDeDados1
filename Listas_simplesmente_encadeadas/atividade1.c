/*lista simplesmente encadeada ordenada crescente e sem repetição*/

#include <stdio.h>
#include <stdlib.h>

typedef struct nofila {
    int numero;
    struct nofila* prox;
} Tnofila;

typedef struct Fila {
    Tnofila* inicio, *fim;
    int quantidade;
} fila;

void inicializar(fila* md) {
    md->fim = NULL;
    md->inicio = NULL;
    md->quantidade = 0;
}

int isfull(fila md) {
    return 0;
}

int isempty(fila md) {
    if (md.inicio == NULL) return 1;
    else return 0;
}

void inserir(fila* mf, int num){
    mf->quantidade += 1;
    Tnofila* aux = (Tnofila*)malloc(sizeof(Tnofila));
    aux->numero = num;
    aux->prox = NULL;
    if(isempty(*mf)==1){
        mf->inicio = aux;
        mf->fim = aux;
    }else{
        if(num < mf->inicio->numero){
            aux->prox = mf->inicio;
            mf->inicio = aux;
        }
        if(num > mf->fim->numero){
            mf->fim->prox = aux;
            mf->fim = aux;
        }
        else{
            Tnofila* aux1;
            Tnofila* aux2;
            aux1 = mf->inicio;//teoricamente poderiamos começar pulando o inicio e terminar no penultimo
            aux2 = NULL;
            for(int i=0; i < mf->quantidade; i++){
                if(aux1->numero == num){
                    printf("Essa lista não aceita números repetidos!\n");
                    break;
                }
                if(aux1->numero > num){//ou seja > aux->num, dupla checagem: &&aux2<num
                    aux->prox = aux1;
                    aux2->prox = aux;
                    break;
                }else{
                    aux2 = aux1;
                    aux1 = aux1->prox;
                }
            }
        }
    }
    mf->quantidade += 1;
}

int remover(fila *mf,int num){
    Tnofila* aux1 = mf->inicio;
    Tnofila* aux2 = NULL;
    int estanafila = 1;
    if(mf->inicio == mf->fim && mf->inicio->numero != num){//estava dando falha de segmentaçao quando so tem um valor a fila
                                                           //e ele não é o que deve ser removido
        return 1;
    }
    for(int i = 0; i < mf->quantidade; i++){
        if(aux1->numero == num){
            estanafila = 0;
            break;
        }else{
            aux2 = aux1;
            aux1 = aux1->prox;
        }
    }
    if(estanafila == 1){
        return 1;
    }else{
        if(mf->inicio == mf->fim){//a lista so tem um valor
            mf->inicio = NULL;
            mf->fim = NULL;
        }
        else{
            if(aux2 == NULL){//se o valor a ser retirado for o primeiro da fila
                mf->inicio = aux1->prox;
                aux2 = aux1->prox;
            }
            else{
                aux2->prox = aux1->prox;
                if(aux2->prox == NULL){
                    mf->fim = aux2;
                }
            }
        }
        free (aux1);
        return 0;
    }
    
}

void list(fila md) {
    Tnofila* aux = md.inicio;
    printf("xxxxxxxxx FILA ATUAL xxxxxxxxx\n");
    while (aux != NULL) {
        printf("[%d] ", aux->numero);
        aux = aux->prox;
    }
    printf("\n");
}


int main(){
    fila minhaFila;
    inicializar(&minhaFila);
    int op, num;
    do{
        printf("1 - inserir valor\n2 - remover valor\n3 - listar valores enfileirados\n0 - fechar programa\nSELECIONE SUA OPÇÃO: ");
        scanf("%d", &op);
        switch(op){
            case 1:
            printf("Informe o valor que deseja inserir: ");
            scanf("%d", &num);
                if(isfull(minhaFila)==0){
                    inserir(&minhaFila,num);
                }
            break;

            case 2:
                if(isempty(minhaFila) == 1){
                    printf("Fila vazia\n");
                }
                else{
                    int valor;
                    printf("Qual valor deseja remover? ");
                    scanf("%d", &num);
                    valor = remover(&minhaFila, num);
                    if(valor == 1){
                        printf("O valor %d não está na fila\n", num);
                    }
                    else{
                        printf("Valor removido!\n");
                    }
                }
            break;

            case 3:
                if(isempty(minhaFila)==1){
                    printf("Fila vazia\n");
                }
                else{
                    list(minhaFila);
                }
            break;
            default: printf("Opção inválida! \n");
        }
    }while(op!=0);
    
    return 0;
}