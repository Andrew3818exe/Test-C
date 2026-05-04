#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 5 // List size that will appear.
#define PUSH 1 // List size of the pieces you'll be holding.
#define SIZE 100 // List size that's for the waiting pieces.


// Structs creation:
typedef struct {
    char name[2];
    int ID;
} Piece;

typedef struct {
    Piece items[MAX];
    int start;
    int final;
    int total;
} PiecesList;

typedef struct {
    Piece items[PUSH];
    int top;
} PushPiecesList;

// Tetris pieces base creation:
Piece BasePieces[7] = {
    {"O",0},{"I",0},{"T",0},{"L",0},{"J",0},{"S",0},{"Z",0}
};

// Waiting pieces list:
Piece GlobalList[SIZE];
int top = 0;

// IDs identification for random pieces:
Piece NextPiece() {
    Piece p = GlobalList [top];
    p.ID = top + 1;
    top++;
    return p;
}

// Value Checking:
int EmptyList(PiecesList *p) {
    return p->total == 0;
}
int FullList(PiecesList *p) {
    return p->total == MAX;
}

// Functions:
void StartList(PiecesList *p) {
    p->start = 0;
    p->final = 0;
    p->total = 0;
}

void CreateList() {
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

void InsertPiece(PiecesList *l, Piece p) {
    if(FullList(l)) return;
    l->items[l->final] = p;
    l->final = (l->final + 1) % MAX;
    l->total++;
}

void RemovePiece(PiecesList *l, Piece *p) {
    if(EmptyList(l)) return;
    *p = l->items[l->start];
    l->start = (l->start + 1) % MAX;
    l->total--;
}

void UsePiece(PiecesList *l) {
    Piece p;
    RemovePiece(l, &p);
    InsertPiece(l, NextPiece());
}

void ShowList(const PiecesList *l) {
    printf("\nPieces: ");
    for(int i = 0, idx = l->start; i < l->total; i++){
        printf("[%s %d] ", l->items[idx].name, l->items[idx].ID);
        idx = (idx + 1) % MAX;
    }
    printf("\n");
}

// Value checking for the hold pieces:
int EmptyPushList(PushPiecesList *p) {
    return p->top == -1;
}
int FullPushList(PushPiecesList *p) {
    return p->top == PUSH - 1;
}

// Functions for the hold pieces:
void StartPushList(PushPiecesList *p) {
    p->top = -1;
}

void Push(PiecesList *list, PushPiecesList *hold) {
    if(EmptyList(list)) {
        return;
    } else if(FullPushList(hold)) {
        printf("You cannot hold more than one piece.\n");
        return;
    }

    Piece p;
    RemovePiece(list, &p);

    hold->top++;
    hold->items[hold->top] = p;

    InsertPiece(list, NextPiece());
}

void Pop(PushPiecesList *p) {
    if(EmptyPushList(p)) {
        printf("You don't hold any pieces.\n");
        return;
    }

    p->top--;
}

void ShowPushList(PushPiecesList *p) {
    printf("Hold: ");
    if(EmptyPushList(p)) {
        printf("You don't hold any pieces.\n");
    }
    for(int i = p->top; i >= 0; i--) {
        printf("[%s, %d]\n", p->items[i].name, p->items[i].ID);
    }
    printf("\n");
}

// Menu:
void ShowMenu() {
    printf("\n==============================\n");
    printf("    Tetris Stack - Part 2\n");
    printf("==============================\n");
    printf("1 - Play a piece\n");
    printf("2 - Hold a piece\n");
    printf("3 - Use a hold piece\n");
    printf("0 - Exit game\n");
    printf("------------------------------\n");
    printf("Choose an option: ");
}

int HandleMenu(PiecesList *list, PushPiecesList *hold) {
    int option;
    scanf("%d", &option);

    switch(option){
            case 1: // Play a piece.
                UsePiece(list);
                ShowList(list);
                ShowPushList(hold);
                break;
            case 2: // Hold a piece.
                Push(list, hold);
                ShowList(list);
                ShowPushList(hold);
                break;
            case 3: // Use a hold piece.
                Pop(hold);
                ShowList(list);
                ShowPushList(hold);
                break;
            case 0: // Exit game;
                printf("\nExiting Game...\n");
                break;
            default:
                printf("\nInvalid option.\n");
        }
}

int main () {
    srand(time(NULL));

    PiecesList list;
    PushPiecesList hold;

    StartList(&list);
    StartPushList(&hold);
    CreateList();

    int option;
    
    for(int i = 0; i < MAX; i++) {
        InsertPiece(&list, NextPiece());
    }
    do{
        ShowMenu();
        option = HandleMenu(&list, &hold);
    } while(option != 0);

    return 0;
}
