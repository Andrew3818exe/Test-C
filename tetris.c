#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 5 // List size that will appear.
#define SIZE 100 // List size that's waiting.

// Structs creations:
typedef struct{
    char name[2];
    int ID;
} Piece;

typedef struct {
    Piece items[MAX];
    int start;
    int final;
    int total;
} PiecesList;

// Tetris pieces base creation:
Piece BasePieces[7] = {
    {"O",0},{"I",0},{"T",0},{"L",0},{"J",0},{"S",0},{"Z",0}
};

// Waiting pieces list:
Piece GlobalList[SIZE];
int top = 0;

// IDs identification for random pieces:
Piece NextPiece(){
    Piece p = GlobalList [top];
    p.ID = top + 1;
    top++;
    return p;
}

// Value checking:
int FullList(PiecesList *l){ return l->total == MAX; }
int EmptyList(PiecesList *l){ return l->total == 0; }

// Functions:
void StartList(PiecesList *l){
    l->start = 0; l->final = 0; l->total = 0;
}

void CreateList(){
    for(int i = 0; i < SIZE; i++){
        GlobalList[i] = BasePieces[i % 7];
    }

    for(int i = SIZE - 1; i > 0; i--){
        int j = rand() % (i + 1);
        Piece temp = GlobalList[i];
        GlobalList[i] = GlobalList[j];
        GlobalList[j] = temp;
    }

    top = 0;
}

void InsertPiece(PiecesList *l, Piece p){
    if(FullList(l)) return;
    l->items[l->final] = p;
    l->final = (l->final + 1) % MAX;
    l->total++;
}

void RemovePiece(PiecesList *l, Piece *p){
    if(EmptyList(l)) return;
    *p = l->items[l->start];
    l->start = (l->start + 1) % MAX;
    l->total--;
}

void UsePiece(PiecesList *l){
    Piece p;
    RemovePiece(l, &p);
    InsertPiece(l, NextPiece());
}

void ShowList(const PiecesList *l){
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

    PiecesList list;
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

    } while(option != 0);

    return 0;
}
