#include <stdio.h>

typedef struct{
    int key;
    char name[20];
}Data;
typedef struct{
    Data data;
    struct Node *next;
}Node;
Node *NodeAdd(Node *head,Data data){
    Node *htmp,*node;
    if(!(node=(Node*)malloc(sizeof(Node)))){
        printf("Error!");
        return 0;
    }else{
        node->data=data;
        node->next=NULL;
        if(head==NULL){
            head=node;
            return head;
        }
        htmp=head;
        while(htmp->next)
            htmp->next=node;
        return htmp;
    }
}
int main(int argc,char *argv[])
{
    Node *head=NULL;
    Data d={1,"abcd"};
    head=NodeAdd(head,d);
    printf("%s\n",head->data.name);
    return 0;
}
