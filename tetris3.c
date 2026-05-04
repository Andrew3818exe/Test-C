#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_LIST 5 // List size of pieces that appear to play.
#define MAX_PILE 3 // Pile size of pieces to hold (not necessarily always filled).
#define SIZE 100 // List size of pieces that will be waiting to come to the list.

// Structs creation:
typedef struct {
    char name[2];
    int ID;
} Piece;

typedef struct {
    Piece items[MAX_LIST];
    int start, end, total;
} PiecesList;

typedef struct {
    Piece items[MAX_PILE];
    int top;
} PiecesPile;

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

// List related functions:
// Value checking:
int EmptyList(PiecesList *p) {
    return p->total == 0;
}
int FullList(PiecesList *p) {
    return p->total == MAX_LIST;
}

// Functions:
void StartList(PiecesList *p) {
    p->start = 0;
    p->end = 0;
    p->total = 0;
}

void CreateList() {
    for(int i = 0; i < SIZE; i++) {
        GlobalList[i] = BasePieces[i % 7];
    }

    for(int i = SIZE - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        Piece temp = GlobalList[i];
        GlobalList[i] = GlobalList[j];
        GlobalList[j] = temp;
    }

    top = 0;
}

void InsertPiece(PiecesList *l, Piece p) {
    if(FullList(l)) {
        return;
    }
    l->items[l->end] = p;
    l->end = (l->end + 1) % MAX_LIST;
    l->total++;
}

void RemovePiece(PiecesList *l, Piece *p) {
    if(EmptyList(l)) {
        return;
    }
    *p = l->items[l->start];
    l->start = (l->start + 1) % MAX_LIST;
    l->total--;
}

void UsePiece(PiecesList *l) {
    Piece p;
    RemovePiece(l, &p);
    InsertPiece(l, NextPiece());
}

void ShowList(const PiecesList *l) {
    printf("\nPieces: ");
    for(int i = 0, idx = l->start; i < l->total; i++) {
        printf("[%s %d] ", l->items[idx].name, l->items[idx].ID);
        idx = (idx + 1) % MAX_LIST;
    }
    printf("\n");
}

// Pile related functions:
// Value checking:
int EmptyPile(PiecesPile *p) {
    return p->top == -1;
}
int FullPile(PiecesPile *p) {
    return p->top == MAX_PILE - 1;
}

// Functions:
void StartPile(PiecesPile *p) {
    p->top = -1;
}

void Push(PiecesList *list, PiecesPile *pile) {
    if(EmptyList(list)) {
        return;
    } else if(FullPile(pile)) {
        printf("You cannot hold any more pieces.\n");
        return;
    }

    Piece p;
    RemovePiece(list, &p);

    pile->top++;
    pile->items[pile->top] = p;

    InsertPiece(list, NextPiece());
}

void Pop(PiecesPile *p) {
    if(EmptyPile(p)) {
        return;
    }

    p->top--;
}

void ShowPile(PiecesPile *p) {
    if(EmptyPile(p)) {
        printf("You're not holding any pieces.\n");
        return;
    }
    printf("Hold: ");
    for(int i = p->top; i >= 0; i--) {
        printf("[%s, %d] ", p->items[i].name, p->items[i].ID);
    }
    printf("\n");
}

// Functions to swap Pile and List:
void SwapOne(PiecesList *list, PiecesPile *pile) {
    if(EmptyPile(pile) || list->total == 0) {
        printf("There's no pieces to swap.\n");
        return;
    }

    int listidx = list->start; // First piece of the list.
    int pileidx = pile->top; // Last piece of the pile.

    Piece temp = list->items[listidx]; // Temporary list.

    // Swapping:
    list->items[listidx] = pile->items[pileidx];
    pile->items[pileidx] = temp;
}

void SwapAll(PiecesList *list, PiecesPile *pile) {
    if(EmptyPile(pile) || list->total == 0) {
        printf("There's no pieces to swap.\n");
        return;
    }

    int k = pile->top +1; // Number of current held pieces.

    // Auxiliar structs to swap pieces:
    Piece tempList[MAX_PILE];
    Piece tempPile[MAX_PILE];

    // Copy first k pieces from list:
    for(int i = 0; i < k; i++) {
        int idx = (list->start + i) % MAX_LIST;
        tempList[i] = list->items[idx];
    }

    // Copy k pieces from pile:
    for(int i = 0; i < k; i++) {
        tempPile[i] = pile->items[pile->top - i];
    }

    // Swapping:
    // Pile into list:
    for(int i = 0; i < k; i++) {
        int idx = (list->start + i) % MAX_LIST;
        list->items[idx] = tempPile[i];
    }

    // List into pile:
    for(int i = 0; i < k; i++) {
        pile->items[pile->top - i] = tempList[i];
    }
}

// Menu:
void ShowMenu() {
    printf("\n==============================\n");
    printf("    Tetris Stack - Part 3\n");
    printf("==============================\n");
    printf("1 - Play a piece\n");
    printf("2 - Hold a piece\n");
    printf("3 - Use a hold piece\n");
    printf("4 - Swap 1 piece\n");
    printf("5 - Swap all pieces\n");
    printf("0 - Exit game\n");
    printf("------------------------------\n");
    printf("Choose an option: ");
}

int HandleMenu(PiecesList *list, PiecesPile *pile) {
    int option;
    scanf("%d", &option);

    switch(option) {
            case 1: // Play a piece.
                UsePiece(list);
                ShowList(list);
                ShowPile(pile);
                break;
            case 2: // Hold a piece.
                Push(list, pile);
                ShowList(list);
                ShowPile(pile);
                break;
            case 3: // Use a hold piece.
                Pop(pile);
                ShowList(list);
                ShowPile(pile);
                break;
            case 4: // Swap 1 piece.
                SwapOne(list, pile);
                ShowList(list);
                ShowPile(pile);
                break;
            case 5: // Swap all pieces.
                SwapAll(list, pile);
                ShowList(list);
                ShowPile(pile);
                break;
            case 0: // Exit game;
                printf("\nExiting Game...\n");
                break;
            default:
                printf("\nInvalid option.\n");
        }

    return option;
}

int main() {
    srand(time(NULL));

    PiecesList list;
    PiecesPile pile;

    StartList(&list);
    StartPile(&pile);
    CreateList();

    int option;

    // Inserting pieces from the global list (with random pieces):
    for(int i = 0; i < MAX_LIST; i++) {
        InsertPiece(&list, NextPiece());
    }

    do {
        ShowMenu();
        option = HandleMenu(&list, &pile);
    } while(option != 0);

    return 0;
}