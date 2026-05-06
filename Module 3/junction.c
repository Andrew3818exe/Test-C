// Testing file that combines both Lists and Piles into one, for practicing.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 50

typedef struct {
    char name[30];
    int age;
} Person;

typedef struct {
    Person data[MAX];
    int start, end;
} List;

typedef struct {
    Person data[MAX];
    int top;
} Pile;

void StartList(List *l) {
    l->start = 0;
    l->end = 0;
}

void StartPileList(Pile *p) {
    p->top = -1;
}

void Insert(List *l, Person p) {
    if(l->end < MAX) {
        l->data[l->end++] = p;
    }
}

Person Remove(List *l) {
    return l->data[l->start++];
}

void Push(Pile *p, Person per) {
    if(p->top < MAX - 1) {
        p->data[++p->top] = per;
    }
}

Person Pop(Pile *p) {
    return p->data[p->top--];
}

Person Peek(Pile *p) {
    return p->data[p->top];
}

void ShowPile(Pile p) {
    while(p.top >= 0) {
        Person atual = Pop(&p);
        printf("Name: %s | Age: %d\n", atual.name, atual.age);
    }
}

int main() {

    List list;
    Pile PriorityPile;

    StartList(&list);
    StartPileList(&PriorityPile);

    Person People[] = {
        {"Carlos", 45}, {"Joana", 62}, {"Lucas", 30}, {"Maria", 75}
    };

    for(int i = 0; i < 4; i++) {
        Insert(&list, People[i]);
    }

    while(list.start < list.end) {
        Person atual = Remove(&list);
        if(atual.age > 60) {
            Push(&PriorityPile, atual);
        }
    }

    printf("Priority people:\n");
    ShowPile(PriorityPile);

    return 0;
}
