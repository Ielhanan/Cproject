/*Created by Elhanan Ilganiv and Halel Gabber
 *Last update: 17/08/2021*/

#include "Labels.h"
#include "stdlib.h"
#include <stdio.h>
#include <string.h>
#include "entry.h"
/*we will represent the lable table as link list of nodes, each node contain lable struck*/
/* A linked list node*/
typedef struct label {     /*LABEL TABLE*/
    char* symbol ;
    int IC;
    int isEntry;
    int isExtern;
    int isData;
}label;
typedef struct Node {
    label* data ;
    struct Node* next;
}Node;

Node* creatLablesList()/*creat link list*/
{
    Node* head;
    head=( Node*)calloc(1,sizeof (Node));
    if(head==NULL){
        perror("ERROR: Cant creat lable list -");
        return NULL;
    }
    head->data=(label*) calloc(1,sizeof (label));
    if(head->data==NULL){
        perror("ERROR: Cant creat lable list ");
        return NULL;
    }
    head->data->symbol=(char*) calloc(80,sizeof (char));/*lable is max 80 chars*/
    if(head->data->symbol==NULL){
        perror("ERROR: cant creat lable list");
        return NULL;
    }
    return head;
}
int addLableToTable( int lineNum,Node* newLable,Node* head)/*add the new node to link list*/
{
    if(head==NULL)/*checking if calloc succsess*/
        return ERROR;
    if(checkLableInTable(newLable,head)!=ERROR){/*check if the current lable exist*/
        printf("%d:     ERROR: This lable already exist\n ",lineNum);
        return ERROR;}
    while ((head!=NULL)&&(head->next!=NULL))/*pass the link list until you reach end of list*/
    {
    head=head->next;
    }
    head->next=newLable;/*add new node to list*/
    return SUCCESS;
}
int creatNewNode(char* symbol, int IC,int lineNum,int isEntry,int isExtern,int isData,Node* head)/*creat new node*/ /*I ADDED IS DATA ID CODE*/
{
    Node* newLable= calloc(1,sizeof (struct Node));
    if(newLable==NULL){
        printf("%d:     ",lineNum);
        perror("ERROR: ");
        return ERROR;}
    newLable->data= calloc(1,sizeof(label));
    if(newLable->data==NULL){
        printf("%d:     ",lineNum);
        perror("ERROR: ");
        return ERROR;}

    newLable->data->IC=IC;
    newLable->data->isEntry=isEntry;
    newLable->data->isExtern=isExtern;
    newLable->data->symbol=symbol;
    newLable->data->isData=isData;
    return addLableToTable(lineNum,newLable,head);/*connect the new node to list*/
}
int checkLableInTable(char* lable, Node* head) {
    while (head != NULL){
        if (strcmp(lable, head->data->symbol) == 0)/*if it 0 seems the lable is exist*/
            return head->data->IC;/*return his IC for ICommand or JCommand*/
    head = head->next;
}
    return ERROR;/*the lable dosnt exist in table*/
}


/*this function checks if the lable is extern acording to the lable name.*/
int checkIfLableIsExtern(char* lable, Node* head) {
    while (head != NULL){
        if (strcmp(lable, head->data->symbol) == 0)/*if it 0 seems the lable is exist*/
            return head->data->isExtern;/*return his IC for ICommand or JCommand*/
        head = head->next;
    }
    return ERROR;/*the lable dosnt exist in table*/
}


/*this function change the value of isExtern in the lable node acording to the lable name. in case of failure function return ERROR*/
int makeLableToExtern(char* lable, Node* head) {
    while (head != NULL){
        if (strcmp(lable, head->data->symbol) == 0)/*if it 0 seems the lable is exist*/
        {
            head->data->isExtern=1;/*return his IC for ICommand or JCommand*/
            return SUCCESS;
        }
        head = head->next;
    }
    return ERROR;
}


/*this function checks if the lable is entry acording to the lable name.*/
int checkIfLableIsEntry(char* lable, Node* head) {
    while (head != NULL){
        if (strcmp(lable, head->data->symbol) == 0)/*if it 0 seems the lable is exist*/
            return head->data->isEntry;/*return his IC for ICommand or JCommand*/
        head = head->next;
    }
    return ERROR;/*the lable dosnt exist in table*/
}


/*this function change the value of isEntry in the lable node acording to the lable name. in case of failure function return ERROR*/
int makeLableToEntry(char* lable, Node* head) {
    while (head != NULL){
        if (strcmp(lable, head->data->symbol) == 0)/*if it 0 seems the lable is exist*/
        {
            head->data->isEntry=1;/*return his IC for ICommand or JCommand*/
            return SUCCESS;
        }
        head = head->next;
    }
    return ERROR;
}


int fixDataLables (Node* lableHead,int ICF)
    {
        if(lableHead==NULL)/*CHECK IF LIST EXIST*/
        {
            printf("ERROR: No exist lable list \n");
            return ERROR;
        }
        while(lableHead!=NULL)
        {
                if(lableHead->data->isData==1)/*the current node is data we need to add to his IC the ICF*/
                    lableHead->data->IC+=ICF;
                lableHead=lableHead->next;
        }

        return SUCCESS;


}

Node* getNextNode (Node* head)
{
    return head->next;
}
char* getLableName(Node * head)
{
    return head->data->symbol;
}
int getICLable(Node* head)
{
    return head->data->IC;
}
label* getLableStruct (Node* head)
{
   return head->data;
}