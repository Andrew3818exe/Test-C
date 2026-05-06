// Based off junction.c where there was an integration of lists and piles,
// this file is about them again, but using piles to invert the list.
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

void ShowList(List p) {
    for(int i = p.start; i < p.end; i++) {
        printf("Name: %s | Age: %d\n", p.data[i].name, p.data[i].age);
    }
}

int main() {

    List OriginalList, InvertedList;
    Pile Aux;

    StartList(&OriginalList);
    StartList(&InvertedList);
    StartPileList(&Aux);

    Person People[] = {
        {"Carlos", 45}, {"Joana", 62}, {"Lucas", 30}, {"Maria", 75}
    };

    for(int i = 0; i < 4; i++) {
        Insert(&OriginalList, People[i]);
    }

    while(OriginalList.start < OriginalList.end) {
        Push(&Aux, Remove(&OriginalList));
    }

    while(Aux.top >= 0) {
        Insert(&InvertedList, Pop(&Aux));
    }

    printf("Inverted list\n");
    ShowList(InvertedList);

    return 0;
}
