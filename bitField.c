/*Created by Elhanan Ilganiv and Halel Gabber
 *Last update: 17/08/2021*/
#include "bitField.h"
#include <stdio.h>
#include <math.h>
#include "stdlib.h"


typedef struct Rcommand{/*represnt binary code for R commands*/
    unsigned int notInUse:6;
    unsigned int funct:5;
    unsigned int rd:5;
    unsigned int rt:5;
    unsigned int rs:5;
    unsigned int opcode:6;
}Rcommand;

typedef struct Icommand{/*represnt binary code for I commands*/
    unsigned int immed:16;
    unsigned int rt:5;
    unsigned int rs:5;
    unsigned int opcode:6;
}Icommand;

typedef struct Jcommand{/*represnt binary code for J commands*/
    unsigned int address:25;
    unsigned int reg:1;
    unsigned int opcode:6;
}Jcommand;

typedef struct outputNode{
    unsigned int  * data;/*represtnt the binary code*/
    int IC;/*represent the IC of this command*/
    outputNode* next;
}outputNode;

unsigned int* getOutputData(outputNode* head)
{
   if(head!=NULL)
    return head->data;
   else
       return ERROR;
}
int getIC(outputNode* head)
{
    if(head!=NULL)
        return head->IC;
    else
        return ERROR;
}
outputNode* getNextOutputNode (outputNode* head)
{
    if(head!=NULL)
         return head->next;
    else
        return ERROR;
}
outputNode* creatoutputList()/*creat link list*/
{
    outputNode* head;
    head=( outputNode*)calloc(1,sizeof (outputNode));
    if(head==NULL)
    {
        perror("ERROR- Cant creat output list-");
        return NULL;
    }
    head->data=(int *) calloc(1,sizeof (int));
    if(head->data==NULL)
    {
        perror("ERROR: ");
        return NULL;
    }
    return head;
}

int addCommandToOutputList( outputNode* newCommand,outputNode* head)/*add the new node to link list*/
{

    if(head==NULL)/*checking if calloc succsess*/
        return ERROR;

    while (head->next!=NULL)/*pass the link list until you reach end of list*/
    {
        head=head->next;
    }
     /*set the next to be new lable only if its not the first one because if its the firsy=t one its already in the list as head from line 87*/
     head->next=newCommand;/*add new node to list*/
    return SUCCESS;
}

int RcommandBinaryBuild(int opcode,int funct,int rs,int rd,int rt,int IC,int lineNum,outputNode* head)/*build binary code for R commands*/
{
    Rcommand* new;
    new=(Rcommand*) calloc(1,sizeof (Rcommand));
    if(new==NULL) {
        printf("%d:     ",lineNum);
        perror("ERROR: ");
        return ERROR;
    }
    new->opcode=opcode;
    new->rt=rt;
    new->funct=funct;
    new->rs=rs;
    new->rd=rd;
    new->notInUse=0;
    outputNode * newCommand;/*creat node to connect the list*/
    newCommand=(outputNode*) calloc(1,sizeof (outputNode));
    if(newCommand==NULL){
        printf("%d:     ",lineNum);
        perror("ERROR: ");
        return ERROR;
    }
    newCommand->IC=IC;/*UPDATE THE IC*/
    newCommand->data=(int*)new;
    return addCommandToOutputList(newCommand,head);
}
int IcommandBinaryBuild(int opcode,int rs,int rt, int immed,int IC,int lineNum,outputNode* head)/*build binary code for J commands*/
{

    Icommand *new;
    new = (Icommand *) calloc(1, sizeof(Icommand));
    if (new == NULL) {
        printf("%d:     ",lineNum);
        perror("ERROR: ");
        return ERROR;
    }
    new->opcode = opcode;
    new->rt = rt;
    new->rs = rs;
    new->immed = immed;
    outputNode *newCommand;/*creat node to connect the list*/
    newCommand = checkIfCommandInsert(IC, head);

    if (newCommand != NULL) {/*if newcommand is NULL so the command not inserted yet to output list
        * if it not NULL we wand change specific NODE */
        newCommand->data = (int*)new;
        return SUCCESS;
    }
    else {
        /*the command dont exist in the list so it new command lets add it*/
        newCommand = (outputNode *) calloc(1, sizeof(outputNode));
        if (newCommand == NULL) {
            printf("%d:     ",lineNum);
            perror("ERROR: ");
            return ERROR;
        }
        newCommand->IC = IC;/*UPDATE THE IC*/
        newCommand->data = (int *) new;

        return addCommandToOutputList(newCommand, head);
    }
}
int  JcommandBinaryBuild(int opcode, int address, int reg,int IC,int lineNum,outputNode* head)/*build binary code for J commands*/
{
    Jcommand* new;
    new=(Jcommand*) calloc(1,sizeof (Jcommand));
    if(new==NULL) {
        printf("%d:     ",lineNum);
        perror("ERROR: ");
        return  ERROR;
    }
    new->opcode=opcode;
    new->address=address;
    new->reg=reg;
    outputNode * newCommand;/*creat node to connect the list*/
    newCommand = checkIfCommandInsert(IC, head);
    if (newCommand != NULL) {/*if newcommand is NULL so the command not inserted yet
        * if it not NULL we want change specific NODE */
        newCommand->data = (int*)new;
        return SUCCESS;
    }
    else {
    newCommand=(outputNode*) calloc(1,sizeof (outputNode));
    if(newCommand==NULL){
        printf("%d:     ",lineNum);
        perror("ERROR: ");
        return ERROR;
    }
    newCommand->IC=IC;/*UPDATE THE IC*/
    newCommand->data=(int*)new;
    return addCommandToOutputList(newCommand,head);
    }
 }
outputNode* checkIfCommandInsert(int IC,outputNode* head)
/*this will check if in first scan we alredy insert this command
 * becuse, in first scan it possible to not know the binary code of this command.
 * it will return error if the command was inserted in first scan.
 * return success if the command is not inserted yet.*/
{
  while(head!=NULL)
  {
      if(IC==head->IC)
          return head;
      head=head->next;
  }
    return NULL;
}