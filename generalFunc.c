/*Created by Elhanan Ilganiv and Halel Gabber
 *Last update: 17/08/2021*/

#include "generalFunc.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>


int checkCommas(char* line)
{
    int length;
    int i;
    int comma=0;
    int sawdigit=0;
    int digit=0;

    length= strlen(line);
    for(i=0; i<length;i++)
    {
        if((line[i]=='.')||(isalpha(line[i])))
            continue;
        else
        if(isdigit(line[i]))
        {
            sawdigit=1;
            digit=1;
            comma=0;
        }
        else /*its not a digit or . or letter*/
        {
            if(line[i]==',')
                if((sawdigit==0)||(comma==1))
                    return ERROR;
                else
                {
                    comma=1;
                    digit=0;
                }
        }
    }/*end of for*/
    if(comma==1)
        return ERROR;
    else
        return SUCCESS;
}/*end of checkCommas*/

int checkReg(char * token,int lineNum)
{
    char * p;
    char * p2;
    int i;
    long num;
    int len;
    int sawdigit=0;

    p=strchr(token, '$');
    if(p==NULL)
    {
        printf("%d:  ERROR: no $ sign \n",lineNum);
        return ERROR;
    }
    len= strlen(p);
    for (i=1; i<len; i++)
    {
        if (isdigit(p[i]))
        {
           sawdigit=1;
            continue;
        }
        else if(isspace(p[i]))
            if(sawdigit==0)
            {

                printf("%d      ERROR:cant have space between $ and the num \n",lineNum);
                return ERROR;
            }
            else /*we alredy saw a digit.*/
                continue;

        else {
            printf("%d:  ERROR: illegal register \n",lineNum);
            return ERROR;
        }
    }
    p++;
    num=atoi(p);
    if((num>31)||(num<0))
    {
        printf("%d:   ERROR: register not in range \n",lineNum);
        return ERROR;
    }
    return num;
}/*end of checkReg*/

int whatCommandIsIt (char * line, int IC, int* DC,int lineNum, outputNode* outputhead, Node * lablehead, DataNode * datahead,int scan,entryNode * entryhead,externNode * externhead) {
    char *p;
    char *token;
    char * copyline ;
    char * lableName;
    char * tempLine;
    int input;
    int lable=0;
    int type;
    int check;
    int tempDC;
    tempLine= (char*)malloc(sizeof sizeof(char)*strlen(line)+1);
    if(tempLine==NULL)
    {
        perror((" %d ERROR : ",lineNum));
        return ERROR;
    }
    strcpy(tempLine,line);
    copyline = (char*)malloc(sizeof(char)*strlen(tempLine)+1);
    if(copyline==NULL) {
        printf("%d:     ",lineNum);
        perror("ERROR:");
        return ERROR;
    }
    strcpy(copyline,tempLine);
    p = strchr(copyline, ':'); /*checking if there is lable in the line*/
    if (p != NULL)
    {/* there is lable in this lin*/
        lable=1; /*terning on the flag of line with lable*/
        copyline=(++p); /*line need to point on the next char of p just after the :*/
        lableName=strtok(tempLine,":");
        check=checkLableName(lableName,lineNum);
        if(check==ERROR)
            return ERROR;
        token= strtok(NULL," "); /*getting the command name from the line*/
        tempDC=*DC;
    }
    else
        token= strtok(tempLine," "); /*getting the command name from the line*/

    /*check if its R-Command*/
    if ((strcmp(token, "add") == 0) || (strcmp(token, "sub") == 0) || (strcmp(token, "and") == 0) ||
        (strcmp(token, "or") == 0) || (strcmp(token, "nor") == 0)||(strcmp(token, "move") == 0) ||
        (strcmp(token, "mvhi") == 0) || (strcmp(token, "mvlo") == 0))
    {
        input=RcommandCheck(copyline,IC,lineNum,outputhead,scan);
        type=CODE;
    }

        /*check if its I-Command*/
    else /*its not a Rcommand*/
    if((strcmp(token, "addi") == 0) || (strcmp(token, "subi") == 0) || (strcmp(token, "andi") == 0) || (strcmp(token, "ori") == 0) ||
       (strcmp(token, "nori") == 0)||(strcmp(token, "beq") == 0) || (strcmp(token, "bne") == 0) || (strcmp(token, "blt") == 0)||
       (strcmp(token, "bgt") == 0) || (strcmp(token, "lb") == 0) || (strcmp(token, "sb") == 0) ||
       (strcmp(token, "lw") == 0) || (strcmp(token, "sw") == 0) || (strcmp(token, "lh") == 0) || (strcmp(token, "sh") == 0))
    {
        input=ICommandCheck(copyline,IC,lineNum,outputhead,lablehead,scan);
        type=CODE;
    }

        /*check if its J-Command*/
    else /*not a R-command or a I-command*/
    if((strcmp(token, "jmp") == 0) || (strcmp(token, "la") == 0) || (strcmp(token, "call") == 0) || (strcmp(token, "stop") == 0))
    {
        input=JCommandCheck(copyline,IC,lineNum,outputhead,lablehead,scan,externhead); /*need to add 1*/
        type=CODE;
    }
    else /*not R-command or a I-command or a J-command*/
    if((strcmp(token, ".db") == 0) ||(strcmp(token, ".dh") == 0) ||(strcmp(token, ".dw") == 0) ||(strcmp(token, ".asciz") == 0)
       || (strcmp(token, ".entry") == 0) ||(strcmp(token, ".extern") == 0) )
    {        input=guidanceCheck(copyline,DC,lineNum,lablehead ,datahead,scan,entryhead);
        type=DATA;
    }

    else/*not recognized command name*/
    {
        printf("%d:  ERROR: illegal command name \n",lineNum);
        return ERROR;
    }

    if(lable==1)
    {
        if(type==CODE)
        {
            check= lineWithLabale(tempLine,type,IC,scan,lineNum,lablehead,externhead,entryhead);
        }

        else
        if(type==DATA)
            lineWithLabale(tempLine,type,tempDC,scan,lineNum,lablehead,externhead,entryhead);
    }
    if(input==ERROR)
        if(type==CODE)
            return CODEERROR;
        else
            return ERROR;
    else
        return type;
}

int lineWithLabale(char * lableName, int type, int counter,int scan,int lineNum, Node* lablehead,externNode * externhead, entryNode * entryhead )
{
    int check;
    if(scan==1)
    {
        check=checkLableInTable(lableName,lablehead); /*check if the lable is already in the table*/
        if(check!=ERROR)/*the lable is exsist in the lable table*/
            return ERROR;
        else/*the lable name is not exist*/
        {
            if(type==DATA)
            {
                check=creatNewNode( lableName,counter,lineNum,0,0,1,lablehead);
                if(check==ERROR)
                    return ERROR;
            }
            else /*type is not data*/
            {
                check=creatNewNode( lableName,counter,lineNum,0,0,0,lablehead);
                if(check==ERROR)
                    return ERROR;
            }
        }
        return SUCCESS;
    }
    else/*scan==2*/
    {
        check=checkLableInTable(lableName,lablehead);/*check if the lable is in the lable table check gets thr value of the IC or ERROR*/
        if(check!=ERROR)/*the lable is exsist in the lable table*/
        {
            /*checking if the lable is EXtern if it is entring it to the right list.*/
            check=checkIfLableIsExtern(lableName,lablehead);
            if(check==1) /*the lable is extern*/
                check=creatNewExternNode(counter,lineNum,lableName, externhead);
        }
        else/*the lable isnt exist!!!*/
            return ERROR;
    }
    return SUCCESS;
}
int creatobfile(char * filename,outputNode * outputhead,DataNode * datahead,int ICF,int DCF) {
    /*making the file names ready*/
    FILE *ob;
    unsigned int data;
    int IC;
    int i;
    char * e=".ob";

    strtok(filename,".");
    strcat(filename,e);
    /*creating .ob file*/
    ob = fopen(filename, "w+");
    if (ob != NULL)/*the file has been created*/
    {
        outputhead = getNextOutputNode(outputhead);/*ignore first node becuse he garbage node */
        fprintf(ob, "         %d %d      \n", ICF - 100, DCF); /*printing the data*/
        while (outputhead != NULL) {
            data = *(getOutputData(outputhead)); /*getting the data*/
            IC = getIC(outputhead); /*getting the IC*/
            if ((data == ERROR) || (IC == ERROR))
                return ERROR;

            fprintf(ob, "%d%d    %02x %02x %02x %02x \n",0, IC, data & 0xff, (data >> 8) & 0xff, (data >> 16) & 0xff,
                    (data >> 24) & 0xff); /*printing the data*/
            outputhead = getNextOutputNode(outputhead); /*getting the next line*/
        }/*end of outputlist*/

        /*now we add the data to output list */
        char *dataArrey;

        dataArrey = (char*)malloc(sizeof(char) * DCF + 1);/*need to get meemory for this */

        int i = 0;/*index for loop*/
        if (dataArrey == NULL) {
            perror("ERROR: ");
            return ERROR;
        }
        datahead = getNextDataNode(datahead);
        /*now we add all the data in arrey of chars , each spot in arrey contain a 8 bit value
         * the data that contain more then 8 bit like dw and dh are insert to 2\4 spots in arrey depends what type of data is it */
        while (datahead != NULL) {
            data = getData(datahead);
            i = getDataIC(datahead);
            if (getDataSpace(datahead) == 1)/*the data type is db we need one 8 bit in arrey */
                dataArrey[i] = data & 0xff;/*take 8 lsb bits*/
            else if (getDataSpace(datahead) ==
                     2) {/*the data type is dH we need store 2 8 bit in 2 places in dataArrey */
                dataArrey[i] = (data) & 0xff;/*take the 8 lsb bits*/
                dataArrey[i + 1] = (data >> 8) & 0xff;/*take the 8-15 bits */
            } else if (getDataSpace(datahead) ==4) {/*the data type is dw we need store 4 8 bits in 4 places in dataArrey*/
                dataArrey[i] = (data) & 0xff;/*take the 8 lsb bits*/
                dataArrey[i + 1] = (data >> 8) & 0xff;/*take the 8-16 bits */
                dataArrey[i + 2] = (data >> 16) & 0xff;/*take the 16-24 bits*/
                dataArrey[i + 3] = (data >> 24) & 0xff;/*take the 24-32 bits*/
            } else {
                dataArrey[i] = data;/*if we reach her so the data is asciz , evry asciz is 8 bit so no need to change it */

            }
            datahead = getNextDataNode(datahead);
        }
        i=0;
        while (i < DCF) {
            int j=0;/*j is counter how much byte alredy printed in current line */
            fprintf(ob,"%d%d    ",0,ICF);
            while((j<4)&&(i<DCF)){
            fprintf(ob, "%02x ", dataArrey[i] & 0xff);
            j++;
            i = i +1;
            }
            fprintf(ob," \n");
            ICF = ICF + 4;
        }

            fclose(ob);
            return SUCCESS;
        }/*end of working on the ob file*/
         /*there was a problen creating the file*/
        return ERROR;

    }/*end of creatobfile*/




int createntryfile (char * fileName,entryNode * entryhead)
{
    FILE * ent;
    char * lableName;
    int IC;
    int i;
    char * e=".ent";
    strtok(fileName,".");
    strcat(fileName,e);

    ent=fopen(fileName, "w+");
    if(ent!=NULL)/*the file has been created*/
    {
        while(entryhead!=NULL)
        {
            lableName= getEntryLableName(entryhead); /*getting the lable name*/
            IC=getLableIC(entryhead); /*getting the IC*/
            if((lableName==ERROR)||(IC==ERROR))
                return ERROR;
            if(IC==0)
            {
                entryhead= getNextEntryNode(entryhead); /*getting the next node*/
                continue; /*the first node is empty with IC 0 so skip it*/
            }
            fprintf(ent,"%s  %d%d \n",lableName,0,IC); /*printing the info*/
            entryhead= getNextEntryNode(entryhead); /*getting the next node*/
        }/*end of entry list*/
        return SUCCESS;
    }/*end of working on ent file*/
    else
        return ERROR;

}/*end of createntryfile function*/

int createxternfile (char * fileName,externNode * externhead)
{
    FILE * ext;
    char * lableName;
    int IC;
    char * p;
    int i;
    char * e=".ext";

    strtok(fileName,".");
    strcat(fileName,e);
    ext=fopen(fileName, "w+");
    externhead= getNextEternNode(externhead);/*skip the first node becuse he is garbage*/
    if(ext!=NULL)/*the file has been created*/
    {
        while(externhead!=NULL)
        {
            lableName= getExternLableName(externhead); /*getting the lable name*/
            IC=getExternLableIC(externhead); /*getting the IC*/
            if((lableName==ERROR)||(IC==ERROR))
                return ERROR;

            fprintf(ext,"%s  %d%d\n",lableName,0,IC); /*printing the info*/
            externhead= getNextEternNode(externhead); /*getting the next node*/
        }/*end of entry list*/
        return SUCCESS;
    }/*end of working on ent file*/
    else
        return ERROR;

}/*end of createxternfile function*/

int fillEntryList(Node* lablehead, entryNode* entryhead)
{
    char* lableName;
    Node * temp;
    int check;
    int IC;
    while(getNextNode(lablehead)!=NULL)
    {
        temp= getNextNode(lablehead);
        lableName=getLableName(lablehead);
        IC=getICLable(lablehead);
        check=checkIfLableIsEntry(lableName,lablehead);
        if(check==1) /*the lable is entry*/
            check= creatNewEntry(IC,lableName,entryhead);
        lablehead=temp;
    }


}/*end of fillEntryList*/

void freeLableList(Node* lableHead) {
    Node *temp;
    while (lableHead != NULL) {
        temp = lableHead;
        lableHead = getNextNode(temp);
        free(getLableStruct(temp));/*free struct data of lableNode*/
        free(temp);/*free the lableNode*/
    }
}/*end of freeLableList*/
void freeEntryList(entryNode* entryHead)
{
 entryNode* temp;
 while(entryHead!=NULL)
 {
     temp=entryHead;
     entryHead= getNextEntryNode(entryHead);
     free(getEntStruct(temp));
     free(temp);
 }
}
void freeExternList(externNode* externHead)
{
    externNode* pleaseWork;
    while(externHead!=NULL)
    {
        pleaseWork=externHead;
        externHead= getNextEternNode(externHead);
        free(getExtStruct(pleaseWork));
        free(pleaseWork);
    }
}
 void freeDataList(DataNode* dataHead){
    DataNode * temp;
    while(dataHead!=NULL)
    {
        temp=dataHead;
        dataHead= getNextDataNode(dataHead);
        free(getDataStruct(temp));
        free(temp);
    }
}
void freeOutputList(outputNode* outputHead)
{
    outputNode * temp;
    while(outputHead!=NULL)
    {
        temp=outputHead;
        outputHead= getNextOutputNode(outputHead);
        free(temp);
    }

}
int checknumber (char* num, int linenum)
{
    int len=strlen(num);
    int i;
    int sawdigit=0;
    for(i=0;i<len;i++)
    {
        if(isspace(num[i]))
            if(sawdigit==1)
            {
                printf("%d      ERROR: illegal num \n",linenum);
                return ERROR;
            }
            else
                continue;
        else if((isdigit(num[i]))||(num[i]=='-'))
        {
            sawdigit=1;
            continue;
        }
    }/*end of for*/
    return SUCCESS;
}/*end of check number*/

int checkLableName(char* name, int linenum)
{
    int len=strlen(name);
    int i;
    int sawchar=0;
    for(i=0;i<len;i++)
    {
        if(isspace(name[i]))
        {
           if(sawchar==1)  {
               printf("%d       ERROR: cant have space in lable name \n",linenum);
                return ERROR;
           }
           else
               continue;

        }
        else if(isalpha(name[i]))
            sawchar=1;
    }/*end of for*/
    return SUCCESS;
}/*end of chack lable name*/
