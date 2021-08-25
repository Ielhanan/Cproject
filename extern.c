/*Created by Elhanan Ilganiv and Halel Gabber
 *Last update: 17/08/2021*/

#include "extern.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"


typedef struct ext{
     int IC;
     char* lable;
}ext;

typedef struct externNode {
    ext* data;
   externNode* next;
}externNode;

char * getExternLableName(externNode* head)
{
    if(head!=NULL)
        return head->data->lable;
    else
        return ERROR;
}
int getExternLableIC(externNode* head)
{
    if(head!=NULL)
        return head->data->IC;
    else
        return ERROR;
}
externNode* getNextEternNode (externNode* head)
{
    return head->next;
}
ext* getExtStruct(externNode* head)
{
    return head->data;
}
externNode* creatExternLinkList()
{
    externNode* head;
    head=(externNode* ) calloc(1,sizeof (externNode));
    if(head==NULL)
    {
        perror("ERROR: Cant creat extern list ");
        return NULL;
    }
    head->data=(ext*) calloc(1,sizeof (ext));
    if(head->data==NULL)
    {
        perror("ERROR: Cant creat extern list");
        return NULL;
    }
    return head;
}
int insertExtern(ext* new,int lineNum,externNode* head)/* change the argument to ext struct and calloc in this methode */
{
    if(head==NULL)
        return ERROR;
    externNode* newExternNode;
    newExternNode =(externNode*) calloc(1,sizeof (newExternNode));
    if(newExternNode==NULL)/*check if calloc success*/
    {
        printf("%d:     ",lineNum);
        perror("ERROR: ");
        return ERROR;
    }
    newExternNode->data=(ext*) calloc(1,sizeof (new));
    if(newExternNode->data==NULL)
    {
        printf("%d:     ",lineNum);
        perror("ERROR: ");
        return ERROR;
    }
    newExternNode->data=new;
    while((head->next)!=NULL)/* continue the list until reach empty space*/
        head=head->next;
    head->next=newExternNode;
    head=head->next;
    head->next=NULL;
    return SUCCESS;
}
int creatNewExternNode(int IC,int lineNum,char* lable,externNode* head)
{
     ext* newExtern;
    newExtern=(ext*)calloc(1,sizeof (ext));
    if(newExtern==NULL){
        printf("%d:     ",lineNum);
        perror("ERROR: ");
    return ERROR;}
     newExtern->lable=lable;
    newExtern->IC=IC;
   return insertExtern(newExtern,lineNum,head);
}
