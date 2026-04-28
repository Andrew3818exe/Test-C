#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 5 // Tamanho da lista de peças que irá aparecer.
#define TAMANHO 100 // Tamanho da lista de peças em espera.

// Criação das structs:
struct Peca{
    char nome[2];
    int ID;
};

struct ListaDePecas{
    struct Peca itens[MAX];
    int inicio;
    int final;
    int total;
};

// Criação da base das peças de Tetris:
struct Peca PecasBase[7] = {
    {"O",0},{"I",0},{"T",0},{"L",0},{"J",0},{"S",0},{"Z",0}
};

// Lista de peças em espera:
struct Peca ListaGlobal[TAMANHO];
int topo = 0;

// Identação dos IDs para as peças aleatórias:
struct Peca ProximaPeca(){
    struct Peca p = ListaGlobal[topo];
    p.ID = topo + 1;
    topo++;
    return p;
}

// Checagem de valores
int ListaCheia(struct ListaDePecas *l){ return l->total == MAX; }
int ListaVazia(struct ListaDePecas *l){ return l->total == 0; }

// Funções:
void InicializarLista(struct ListaDePecas *l){
    l->inicio = 0; l->final = 0; l->total = 0;
}

void GerarLista(){
    for(int i = 0; i < TAMANHO; i++){
        ListaGlobal[i] = PecasBase[i % 7];
    }

    for(int i = TAMANHO - 1; i > 0; i--){
        int j = rand() % (i + 1);
        struct Peca temp = ListaGlobal[i];
        ListaGlobal[i] = ListaGlobal[j];
        ListaGlobal[j] = temp;
    }

    topo = 0;
}

void InserirPeca(struct ListaDePecas *l, struct Peca p){
    if(ListaCheia(l)) return;
    l->itens[l->final] = p;
    l->final = (l->final + 1) % MAX;
    l->total++;
}

void RemoverPeca(struct ListaDePecas *l, struct Peca *p){
    if(ListaVazia(l)) return;
    *p = l->itens[l->inicio];
    l->inicio = (l->inicio + 1) % MAX;
    l->total--;
}

void UtilizarPeca(struct ListaDePecas *l){
    struct Peca p;
    RemoverPeca(l, &p);
    InserirPeca(l, ProximaPeca());
}

void MostrarLista(const struct ListaDePecas *l){
    printf("\nPecas: ");
    for(int i = 0, idx = l->inicio; i < l->total; i++){
        printf("[%s %d] ", l->itens[idx].nome, l->itens[idx].ID);
        idx = (idx + 1) % MAX;
    }
    printf("\n");
}

void ExibirMenu(){
    printf("\n==============================\n");
    printf("    Tetris Stack - Parte 1\n");
    printf("==============================\n");
    printf("1 - Ver suas pecas\n");
    printf("2 - Utilizar uma peca\n");
    printf("0 - Sair do jogo\n");
    printf("------------------------------\n");
    printf("Escolha uma opcao: ");
}

int main(){
    srand(time(NULL));

    struct ListaDePecas lista;
    InicializarLista(&lista);
    GerarLista();

    for(int i = 0; i < MAX; i++)
        InserirPeca(&lista, ProximaPeca());

    int opcao;

    do{
        ExibirMenu();
        scanf("%d", &opcao);

        switch(opcao){
            case 1:
                MostrarLista(&lista);
                break;
            case 2:
                UtilizarPeca(&lista);
                MostrarLista(&lista);
                break;
            case 0:
                printf("\nEncerrando o jogo...\n");
                break;
            default:
                printf("\nOpcao invalida.\n");
        }

    } while(opcao != 0);

    return 0;
}
