#include <stdio.h>
#include <stdlib.h>

#define MAX 5 // List size.

// Structs creation:
typedef struct {
    char name[30];
    int age;
} Person;

typedef struct {
    Person items[MAX];
    int top;
} Pile;

// Value Checking:
int EmptyPile(Pile *p) {
    return p->top == -1;
}
int FullPile(Pile *p) {
    return p->top == MAX - 1;
}

// Functions:
void StartList(Pile *p) {
    p->top = -1;
}

void Push(Pile *p, Person new) {
    if(FullPile(p)) {
        printf("Full pile. It's not possible to insert.\n");
        return;
    }

    p->top++;
    p->items[p->top] = new;
}

void Pop(Pile *p, Person *remove) {
    if(EmptyPile(p)) {
        printf("Empty pile. It's not possible to remove.\n");
        return;
    }

    *remove = p->items[p->top];
    p->top--;
}

void Peek(Pile *p, Person *look) {
    if(EmptyPile(p)) {
        printf("Empty pile. Nothinng to peek");
        return;
    }

    *look = p->items[p->top];
}

void ShowPile(Pile *p) {
    printf("Pile [top -> base]:\n");
    for(int i = p->top; i>=0; i--) {
        printf("[%s, %d]\n", p->items[i].name, p->items[i].age);
    }
    printf("\n");
}

int main() {
    Pile p;
    StartList(&p);

    Person a = {"Anna", 20};
    Person b = {"Bruno", 35};
    Person c = {"Carlos", 28};

    Push(&p, a);
    Push(&p, b);
    Push(&p, c);

    ShowPile(&p);

    Person remove;
    Pop(&p, &remove);
    printf("Removed: %s, %d\n", remove.name, remove.age);

    ShowPile(&p);

    Person top;
    Peek(&p, &top);
    printf("Atual top: %s, %d\n", top.name, top.age);

    return 0;
}
