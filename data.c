/*Created by Elhanan Ilganiv and Halel Gabber
 *Last update: 17/08/2021*/
#include <string.h>
#include "Labels.h"
#include "stdio.h"
#include <ctype.h>
#include <stdlib.h>
#include "data.h"

typedef struct Data {     /*LABEL TABLE*/
    int DC;
    int value;
    int space;/*1 is db 2 is dh 4 is dw 0 ascizz*/
}Data;

typedef struct DataNode {
    Data * data ;
    struct DataNode* next;
}DataNode;


int getData(DataNode* head)
{
    if(head!=NULL)
        return head->data->value;
    else
        return ERROR;
}
int getDataIC(DataNode* head)
{
    if(head!=NULL)
        return head->data->DC;
    else
        return ERROR;
}
DataNode* getNextDataNode (DataNode* head)
{
    return head->next;
}
Data * getDataStruct(DataNode* head)
{
    return head->data;
}
int getDataSpace(DataNode* head)
{
    return head->data->space;
}
DataNode* creatDataList()/*creat link list*/
{
    DataNode* head;
    head=(DataNode*)calloc(1,sizeof (DataNode));
    if(head==NULL)
    {
        perror("ERROR: Cant creat data list-");
        return NULL;
    }
    head->data=(Data*) calloc(1,sizeof (Data));
    if(head->data==NULL)
    {
        perror("ERROR: Cant creat data list-");
        return NULL;
    }
    return head;
}
int addDataNodeToTable( DataNode* newData,DataNode* head)/*add the new node to data list*/
{
    if(newData==NULL) /*if the newData node isn't exist*/
        return ERROR;
    if((head->data) == NULL)/*if it the first Node in the list*/
        *head=*newData;
    while (head->next!=NULL)/*pass the link list until you reach end of list*/
    {
        head=head->next;
    }
    head->next=newData;/*add new node to list*/
    return SUCCESS;
}
int creatNewDataNode(int value, int DC,int lineNum,DataNode* head,int type)/*creat new node*/
{
    DataNode* newDataNode= calloc(1,sizeof (struct DataNode));
    if(newDataNode==NULL)
    {
        printf("%d:      ",lineNum);
        perror("ERROR: ");
        return ERROR;
    }
    newDataNode->data= (Data*)calloc(1,sizeof (Data));
    if(newDataNode->data==NULL)
    {
        printf("%d:      ",lineNum);
        perror("ERROR: ");
        return ERROR;
    }
    newDataNode->data->DC=DC;
    newDataNode->data->value=value;
    newDataNode->data->space=type;
    return addDataNodeToTable(newDataNode,head);/*connect the new node to list*/
}
