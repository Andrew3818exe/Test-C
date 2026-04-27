#include <stdio.h>
#include <stdlib.h>

#define MAX 5

typedef struct {
    char nome[2];
    int ID;
} Peca;

typedef struct {
    Peca itens[MAX];
    int inicio;
    int final;
    int total;
} FilaDePecas;

void inicializarFila(FilaDePecas *f) {
    f->inicio = 0;
    f->final = 0;
    f->total = 0;
}

int filaCheia(FilaDePecas *f) {
    return f->total == MAX;
}

int filaVazia(FilaDePecas *f) {
    return f->total == 0;
}

void inserir(FilaDePecas *f, Peca p) {
    if(filaCheia(f)) {
        printf("Fila cheia. Não é possível inserir mais peças.");
        return;
    }

    f->itens[f->final] = p;
    f->final = (f->final + 1) % MAX;
    f->total++;
}

void remover(FilaDePecas *f, Peca *p) {
    if(filaVazia(f)) {
        printf("Fila vazia. Não é possível remover mais peças.");
        return;
    }

    *p = f->itens[f->inicio];
    f->inicio = (f->inicio + 1) % MAX;
    f->total--;
}

void mostrarFila(FilaDePecas *f) {
    printf("Pecas: ");
    for(int i = 0, idx = f->inicio; i < f->total; i++, idx = (idx + 1) % MAX) {
        printf("[%s %d] ", f->itens[idx].nome, f->itens[idx].ID);
    }
    printf("\n");
}

int main() {

    FilaDePecas f;
    inicializarFila(&f);

    Peca p1 = {"O", 1};
    Peca p2 = {"T", 2};
    Peca p3 = {"I", 3};
    Peca p4 = {"O", 4};
    Peca p5 = {"S", 5};
    Peca p6 = {"Z", 6};
    Peca p7 = {"I", 7};
    inserir(&f, p1);
    inserir(&f, p2);
    inserir(&f, p3);
    inserir(&f, p4);
    inserir(&f, p5);

    mostrarFila(&f);

    Peca removida;
    remover(&f, &removida);
    inserir(&f, p6);

    printf("Peca removida: %s %d\n", removida.nome, removida.ID);
    printf("Peca inserida: %s %d\n", p6.nome, p6.ID);

    mostrarFila(&f);

    remover(&f, &removida);
    inserir(&f, p7);

    printf("Peca removida: %s %d\n", removida.nome, removida.ID);
    printf("Peca inserida: %s %d\n", p7.nome, p7.ID);

    mostrarFila(&f);

    return 0;
}