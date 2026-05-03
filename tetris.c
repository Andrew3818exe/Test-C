#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 5 // List size that will appear.
#define SIZE 100 // List size that's waiting.

// Structs creations:
struct Piece{
    char name[2];
    int ID;
};

struct PiecesList{
    struct Piece items[MAX];
    int start;
    int final;
    int total;
};

// Tetris pieces base creation:
struct Piece BasePieces[7] = {
    {"O",0},{"I",0},{"T",0},{"L",0},{"J",0},{"S",0},{"Z",0}
};

// Waiting pieces list:
struct Piece GlobalList[SIZE];
int top = 0;

// IDs identification for random pieces:
struct Piece NextPiece(){
    struct Piece p = GlobalPiece[top];
    p.ID = top + 1;
    top++;
    return p;
}

// Value checking:
int FullList(struct PiecesList *l){ return l->total == MAX; }
int EmptyList(struct PiecesList *l){ return l->total == 0; }

// Functions:
void StartList(struct PiecesList *l){
    l->start = 0; l->final = 0; l->total = 0;
}

void CreateList(){
    for(int i = 0; i < SIZE; i++){
        GlobalList[i] = BasePieces[i % 7];
    }

    for(int i = TAMANHO - 1; i > 0; i--){
        int j = rand() % (i + 1);
        struct Pieces temp = GlobalList[i];
        GlobalList[i] = GlobalList[j];
        GlobalList[j] = temp;
    }

    top = 0;
}

void InsertPiece(struct PiecesList *l, struct Piece p){
    if(FullList(l)) return;
    l->items[l->final] = p;
    l->final = (l->final + 1) % MAX;
    l->total++;
}

void RemovePiece(struct PiecesList *l, struct Piece *p){
    if(EmptyList(l)) return;
    *p = l->items[l->start];
    l->start = (l->start + 1) % MAX;
    l->total--;
}

void UsePiece(struct PiecesList *l){
    struct Piece p;
    RemovePiece(l, &p);
    InsertPiece(l, NextPiece());
}

void ShowList(const struct PiecesList *l){
    printf("\nPieces: ");
    for(int i = 0, idx = l->start; i < l->total; i++){
        printf("[%s %d] ", l->items[idx].name, l->items[idx].ID);
        idx = (idx + 1) % MAX;
    }
    printf("\n");
}

void ShowMenu(){
    printf("\n==============================\n");
    printf("    Tetris Stack - Part 1\n");
    printf("==============================\n");
    printf("1 - See your pieces\n");
    printf("2 - Use a piece\n");
    printf("0 - Exit game\n");
    printf("------------------------------\n");
    printf("Choose an option: ");
}

int main(){
    srand(time(NULL));

    struct PiecesList list;
    StartList(&list);
    CreateList();

    for(int i = 0; i < MAX; i++)
        InsertPiece(&list, NextPiece());

    int option;

    do{
        ShowMenu();
        scanf("%d", &option);

        switch(option){
            case 1:
                ShowList(&list);
                break;
            case 2:
                UsePiece(&list);
                ShowList(&list);
                break;
            case 0:
                printf("\nExiting Game...\n");
                break;
            default:
                printf("\nInvalid option.\n");
        }

    } while(opcao != 0);

    return 0;
}
