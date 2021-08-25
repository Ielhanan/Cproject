/*Created by Elhanan Ilganiv and Halel Gabber
 *Last update: 17/08/2021*/

#include "entry.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "Labels.h"

typedef struct ent{
    int IC;
    char* lable;
}ent;
typedef struct entryNode {
    ent* data;
    entryNode * next;
}entryNode;

char * getEntryLableName(entryNode* head)
{
    if(head!=NULL)
        return head->data->lable;
    else
        return ERROR;
}
int getLableIC(entryNode* head)
{
    if(head!=NULL)
        return head->data->IC;
    else
        return ERROR;
}
entryNode* getNextEntryNode (entryNode* head)
{
    return head->next;
}
ent* getEntStruct(entryNode* head)
{
    return head->data;
}



entryNode* creatEntryLinkList()
{
    entryNode* head;
    head=(entryNode* ) calloc(1,sizeof (entryNode));
    if(head==NULL)
    {
        perror("ERROR: Cant creat entry list - ");
    return NULL;
    }
    head->data=(ent*) calloc(1,sizeof (ent));
    if(head->data==NULL)
    {
        perror("ERROR: Cant creat entry list - ");
        return NULL;
    }
    return head;
}
int insertEntry(ent* new,entryNode* head)
{
    entryNode* newEntryNode;
    newEntryNode=(entryNode*) calloc(1,sizeof (entryNode));
    if(newEntryNode==NULL)
    {
        perror("ERROR: There is an error with entry list: ");
        return ERROR;
    }
    if(head==NULL)
        return ERROR;
    newEntryNode->data= (ent*)calloc(1,sizeof (ent));
    if(newEntryNode->data==NULL)
    {
        perror("ERROR: There is an error with entry list: ");
        return ERROR;
    }
    newEntryNode->data=new;
    while((head->next)!=NULL)/* continue the list until reach empty space*/
        head=head->next;
    head->next=newEntryNode;
    head=head->next;
    head->next=NULL;
    return SUCCESS;
}
int creatNewEntry(int IC,char* lable,entryNode* head)
{
    ent* newEntry;
    newEntry=(ent*) calloc(1,sizeof (ent));
    if(newEntry==NULL)
    {
        perror("ERROR: There is an error with entry list:  ");
        return ERROR;
    }
    newEntry->IC=IC;
    newEntry->lable=lable;
    return insertEntry(newEntry,head);
}
