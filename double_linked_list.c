#include<stdio.h>
#include<stdlib.h>

typedef struct line{
    struct line * prior;
    int data;
    struct line * next;
}line;

line * initLine(line * head);
line * insertLine(line * head, int data, int add);
line * delLine(line * head, int data);
int selectElem(line * head, int elem);
line * amendElem(line * p, int add, int newElem);
void display(line * head);

int main(){
    line * head=NULL;
    //����˫����
    head=initLine(head);
    display(head);
    //�ڱ��е� 3 ��λ�ò���Ԫ�� 7
    head=insertLine(head, 7, 3);
    display(head);
    //����ɾ��Ԫ�� 2
    head=delLine(head, 2);
    display(head);
    printf("Ԫ�� 3 ��λ���ǣ�%d\n",selectElem(head,3));
    //���е� 3 ���ڵ��е����ݸ�Ϊ�洢 6
    head = amendElem(head,3,6);
    display(head);
    return 0;
}

line * initLine(line * head){
    head = (line*)malloc(sizeof(line));
    head->prior = NULL;
    head->next = NULL;
    head->data = 1;
    line * list = head;
    for(int i = 1; i <= 5; i++){
        line * body = (line*)malloc(sizeof(line));
        body->prior = NULL;
        body->next = NULL;
        body->data = i;
        list->next = body;
        body->prior = list;
        list = list->next;
    }
    return head;
}
line * insertLine(line * head, int data, int add){
    line * temp = (line*)malloc(sizeof(line));
    temp->data = data;
    temp->prior = NULL;
    temp->next = NULL;
    if(add == 1){
        temp->next = head;
        head->prior = temp;
        head = temp;
    }
    else{
        line * body = head;
        for(int i = 1; i <= add - 1; i++){
            body = body->next;
        }
        if(body->next = NULL){
            body->next = temp;
            temp->prior = body;
        }
        else{
            body->next->prior = temp;
            temp->next = body->next;
            body->next = temp;
            temp->prior = body;
        }
    }
    return head;
}

line * delLine(line * head, int data){
    line * temp = head;
    while(temp){
        if(temp->data == data){
            temp->prior->next = temp->next;
            temp->next->prior = temp->prior;
            free(temp);
            return head;
        }
        temp = temp->next;
    }
    printf("�������޸�����Ԫ��");
    return head;
}
int selectElem(line * head, int elem){
    line *t = head;
    int i = 1;
    while(t){
        if(t->data = elem){
            return i;
        }
        i++;
        t = t->next;
    }
    return -1;
}

line * amendElem(line * p, int add, int newElem){
    line * temp = p;
    for(int i = 1; i < add; i++){
        temp = temp->next;
    }
    temp->data = newElem;
    return p;
}

void display(line * head){
    line * temp = head;
    while(temp){
        if(temp->next == NULL){
            printf("%d\n", temp->data);
        }
        else{
            printf("%d->",temp->data);
        }
        temp = temp->next;
    }
}
