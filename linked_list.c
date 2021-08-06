#include<stdio.h>
#include<stdlib.h>

typedef struct Link{
    char elem;
    struct Link * next;
}link;

link * initLink();

link * insertElem(link * p, int elem, int add);

link * delElem(link * p, int add);

int selectElem(link * p, int elem);

link * amendElem(link * p, int add, int newElem);

void display(link *p);


int main(){
    printf("Initialize linked list 1,2,3,4\n");
    link *p = initLink();
    display(p);

    printf("Insert 5 in the 4th position\n");
    insertElem(p, 5, 4);
    display(p);

    printf("del elem 3:\n");
    p = delElem(p, 3);
    display(p);
    printf("the position of 2：\n");
    int address = selectElem(p, 2);
    if (address == -1) {
        printf("element not found");
    }
    else {
        printf("the position of 2：%d\n", address);
    }
    printf("Change the data on position 3 to 7:\n");
    p = amendElem(p, 3, 7);
    display(p);

    return 0;
}


link * initLink(){//1 2 3 4
    link * p = (link*)malloc(sizeof(link));
    link * temp = p;
    for(int i = 1; i < 5; i++){
        link *a = (link*)malloc(sizeof(link));
        a->elem = i;
        a->next = NULL;
        temp->next = a;
        temp = temp->next;
    }
    return p;
}

link * insertElem(link * p, int elem, int add){
    link * temp = p;
    for(int i = 1; i < add; i++){
        temp = temp->next;
        if(temp == NULL){
            printf("插入位置无效。 \n");
            return p;
        }
    }
    link * c = (link *)malloc(sizeof(link));
    c->elem = elem;
    c->next = temp->next;
    temp->next = c;
    return p;
}

link * delElem(link * p, int add){
    link * temp = p;
    for(int i = 1; i < add; i++){
        temp = temp->next;
        if(temp->next == NULL){
            printf("没有该节点\n");
            return p;
        }
    }
    link * del = temp->next;
    temp->next = del->next;
    free(del);
    return p;
}

int selectElem(link * p, int elem){
    link * temp = p;
    int i = 1;
    while(temp->next){
        temp = temp->next;
        if(temp->elem == elem)
            return i;
        i++;
    }
    return -1;
}

link * amendElem(link * p, int add, int newElem){
    link * temp = p;
    temp = temp->next;//tamp指向首元结点
    //temp指向被删除结点
    for (int i = 1; i < add; i++) {
        temp = temp->next;
    }
    temp->elem = newElem;
    return p;
}


void display(link *p){
    link * temp = p;
    while(temp->next){
        temp = temp->next;
        printf("%d", temp->elem);
    }
    printf("\n");
}


