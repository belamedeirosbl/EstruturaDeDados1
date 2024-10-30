#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct EstruturaLista{
    int prioridade;
    char descricao[50];
    struct EstruturaLista* proximo;
    struct EstruturaLista* anterior;
}Estrutura;

typedef struct ControleDeFila{
    Estrutura* inicio;
    Estrutura* fim;
    int quantidade;
}Fila;

void inicializar(Fila* mf){
    mf->inicio = NULL;
    mf->fim = NULL;
    mf->quantidade = 0;
}

int isFull(Fila mf){
    return 0;
}

int isEmpty(Fila mf){
    if(mf.inicio == NULL){
        return 1;
    }else{
        return 0;
    }
}

int repeticaoDescricao(Fila mf, char descricao[]){
    Estrutura* aux;
    aux = mf.inicio;
    while(aux != NULL){
        if(strcmp(aux->descricao, descricao) == 0){
            return 1;
        }else{
            aux = aux->proximo;
        }
    }
    return 0;
}

void inserir(Fila* mf, int prioridade,char descricao[]){
    int descrepetida = repeticaoDescricao(*mf, descricao);
    if(descrepetida){
        printf("Não são aceitas descrições repetidas!\n");
        return;
    }else{
        Estrutura* novo = (Estrutura*)malloc(sizeof(Estrutura));
        strcpy(novo->descricao, descricao);
        novo->proximo = NULL;
        novo->anterior = NULL;
        novo->prioridade = prioridade;
        
        if(isEmpty(*mf) == 1){//esta vazia
            mf->inicio = novo;
            mf->fim = novo;
            mf->quantidade++;
            return;
        }else if(mf->inicio->prioridade < prioridade){//colocar no inicio
            novo->proximo = mf->inicio;
            mf->inicio->anterior = novo;
            mf->inicio = novo;
            mf->quantidade++;
            return;
        }else if(mf->fim->prioridade >= prioridade){//colocar no fim
            novo->anterior = mf->fim;
            mf->fim->proximo = novo;
            mf->fim = novo;
            mf->quantidade++;
            return;
        }else{
            Estrutura* aux = mf->fim->anterior;
            if(aux == mf->inicio){//a fila so tem 2 elementos e o novo vai estar no meio
                novo->anterior = mf->inicio;
                novo->proximo = mf->fim;
                mf->inicio->proximo = novo;
                mf->fim->anterior = novo;
                return;
            }else{
                while(aux!= NULL){//buscar no meio
                    if(prioridade <= aux->prioridade){
                        novo->proximo = aux->proximo;
                        novo->anterior = aux;
                        aux->proximo->anterior = novo;
                        aux->proximo = novo;
                        mf->quantidade++;
                        return;
                    }else{
                        aux = aux->anterior;
                    }
                }
            }
        }
    }
}

void informarPosicaoDescricao(Fila mf, char descricao[]){
    if(repeticaoDescricao(mf,descricao) == 0) {
        printf("A descrição não foi encontrada na lista de tarefas.\n");
    }else{
        int contador = 0;
        Estrutura* aux = mf.inicio;
        while(aux!=NULL){
            if(strcmp(aux->descricao,descricao)==0){
                break;
            }
            contador++;
            aux = aux->proximo;
        }
        printf("Existem %d tarefas antes dessa.\n", contador);
    }
}

void exibir(Fila lista) {
    Estrutura* aux;
    aux = lista.inicio;
    while (aux != NULL) {
        printf("Prioridade: %d////", aux->prioridade);
        printf("Descrição: %s\n", aux->descricao);
        aux = aux->proximo;
    }
    printf("\n");
}

int prioridadeNoIntervaloCerto(int prioridade, char descricao[]){
    while(prioridade < 1 || prioridade > 10){
        printf("A prioridade deve estar entre 1-10. Tente novamente!\n");
        printf("Informe a nova prioridade para a tarefa de descrição %s ", descricao);
        scanf("%d", &prioridade);
    }
    return prioridade;
}

void executarTarefa(Fila* mf){
    Estrutura* aux = mf->inicio;
    char descricao[50];
    strcpy(descricao, aux->descricao);
    if(mf->inicio == mf->fim){//so tem uma tarefa
        free(aux);
        mf->inicio = NULL;
        mf->fim = NULL;
        mf->quantidade--;
    }else{
        mf->inicio = mf->inicio->proximo;
        mf->inicio->anterior = NULL;
        free(aux);
        mf->quantidade--;
    }
    printf("Tarefa executada:%s\n", descricao);
}

void removerTarefa(Fila* mf, char descricao[]){
    if(repeticaoDescricao(*mf,descricao) == 0){
        printf("Essa descrição não esta na lista!\n");
        return;
    }else{
        Estrutura* aux = mf->inicio;
        while(aux != NULL){
            if(strcmp(aux->descricao,descricao) == 0){
                char descricao[50];
                strcpy(descricao, aux->descricao);
                if(aux == mf->inicio){//é o primeiro elemento
                    if(aux == mf->fim){//so tem um elemento;
                        free(aux);
                        mf->inicio = NULL;
                        mf->fim = NULL;
                        mf->quantidade--;
                    }else{
                        mf->inicio = mf->inicio->proximo;
                        mf->inicio->anterior = NULL;
                        mf->quantidade--;
                        free(aux);
                    }
                }else if(aux == mf->fim){//é o ultimo elemento
                    mf->fim = mf->fim->anterior;
                    mf->fim->proximo = NULL;
                    mf->quantidade--;
                    free(aux);
                }else{
                    aux->anterior->proximo = aux->proximo;
                    aux->proximo->anterior = aux->anterior;
                    mf->quantidade--;
                    free(aux);
                }
                break;
            }else{
                aux = aux->proximo;
            }
        }
        printf("Removendo tarefa: %s\n", descricao);
    }
}

void prioridadeRepetida(Fila mf, int prioridade){
    Estrutura* aux1 = mf.inicio->proximo;
    Estrutura* aux2 = mf.inicio;
    
    while(aux1 != NULL){
        int cont = 0;
        if(aux1->prioridade == aux2->prioridade && aux1->prioridade == prioridade){
            while(aux2 != NULL && aux2->prioridade == prioridade){
                cont++;
                printf("Prioridade: %d//descrição:%s", aux2->prioridade, aux2->descricao);
                aux2 = aux2->proximo;
            }
            printf("Existem %d tarefas de prioridade %d\n", cont, prioridade);
            return;
        }else{
            aux2 = aux1;
            aux1 = aux1->proximo;
            
        }
    }
    printf("Não existe tarefa repetida de prioridade %d\n", prioridade);
}

void alterarPrioridade(Fila* mf, char descricao[]) {
    if(repeticaoDescricao(*mf,descricao) == 0){
        printf("Descrição não está presente na lista!\n");
        return;
    }else{
        removerTarefa(mf,descricao);//pq passa sem o &
        int prioridade;
        printf("Informe a nova prioridade da tarefa: %s",descricao);
        scanf("%d", &prioridade);
        prioridade = prioridadeNoIntervaloCerto(prioridade,descricao);
        inserir(mf,prioridade,descricao);
        return;
    }
}


void exibirop(){
    printf("1-Inserir\n");    
    printf("2-Exibir\n");    
    printf("3-Informar posição da tarefa\n");    
    printf("4-Executar tarefa\n");    
    printf("5-Remover tarefa\n");    
    printf("6-Mostrar descrição de tarefas com mesma prioridade\n");
    printf("7-Alterar prioridade de tarefa\n");
}


int main(){
    int op;
    Fila mf;
    char descricao[50];
    do{
        exibirop();
        printf("Escolha a opção desejada: ");
        scanf("%d", &op); 
        switch(op){
            case 1:
                if(isFull(mf) == 0){
                    int prioridade;
                    printf("Informe a prioridade: ");
                    scanf("%d", &prioridade);
                    prioridade = prioridadeNoIntervaloCerto(prioridade,descricao);
                    getchar();
                    printf("Informe a descrição da tarefa: ");
                    fgets(descricao, 50, stdin);
                    inserir(&mf,prioridade,descricao);
                }else{
                    printf("Fila cheia!\n");
                }
                break;
            case 2:
                if(isEmpty(mf) == 1){
                    printf("Fila vazia!");
                }else{
                    exibir(mf);
                }
                break;
            case 3:
                if(isEmpty(mf) == 1){
                    printf("Fila vazia!");
                }else{
                    getchar();
                    printf("Informe a descrição da tarefa que deseja saber a posição: ");
                    fgets(descricao, 50, stdin);
                    informarPosicaoDescricao(mf,descricao);
                }
                break;
            case 4:
                if(isEmpty(mf) == 1){
                    printf("Fila vazia!");
                }else{
                    executarTarefa(&mf);
                }
                break;
            case 5:
                if(isEmpty(mf) == 1){
                    printf("Fila vazia!");
                }else{
                    getchar();
                    printf("Informe a descrição da tarefa que deseja remover: ");
                    fgets(descricao, 50, stdin);
                    removerTarefa(&mf,descricao);
                }
                break;
            case 6:
                if(isEmpty(mf) == 1){
                    printf("Fila vazia!");
                }else{
                    int prioridade; 
                    printf("Informe a prioridade: ");
                    scanf("%d", &prioridade);
                    prioridade = prioridadeNoIntervaloCerto(prioridade,descricao);
                    prioridadeRepetida(mf,prioridade);
                }
                break;
            case 7:
                if(isEmpty(mf) == 1){
                    printf("Fila vazia!");
                }else{
                    getchar();
                    printf("Informe a descrição da tarefa que deseja alterar a prioridade: ");
                    fgets(descricao, 50, stdin);
                    alterarPrioridade(&mf, descricao);
                }
                break;
                
            default: printf("Esta opção é inválida!\n");
        }
    }while(op!=0);
    
    return 0;
}
