#include<stdio.h>
#include<stdlib.h>

typedef struct node{
    int number;
    struct node * next;
}person;

person * initLink(int n){
    person * head = (person*)malloc(sizeof(person));
    head->number = 1;
    head->next = NULL;
    person * cyclic = head;
    for(int i = 2; i <= n; i++){
        person * body = (person*)malloc(sizeof(person));
        body->number = i;
        body->next = NULL;
        cyclic->next = body;
        cyclic = cyclic->next;
    }
    cyclic->next = head;
    return head;
}

void findAndKillK(person * head, int k, int m){
    person *tail = head;
    while(tail->next != head){
        tail = tail->next;
    }
    person * p = head;
    while(p->number != k){
        tail = p;
        p = p->next;
    }
    while(p->next != p){
        for(int i = 1; i < m; i++){
            tail = p;
            p = p->next;
        }
        tail->next = p->next;
        printf("The number of the eliminated is:%d\n", p->number);
        free(p);
        p = tail->next;
    }
    printf("The number of the winner is:%d\n", p->number);
    free(p);
}

int main() {
    printf("Input the number of the people on the round table(n):");
    int n;
    scanf("%d",&n);
    person * head=initLink(n);
    printf("Start counting from the k-th person:(k)(k>1 && k<%d)£º",n);
    int k;
    scanf("%d",&k);
    printf("Input the number which they count make them stand out(m)£º");
    int m;
    scanf("%d",&m);
    findAndKillK(head, k, m);
    return 0;
}
