/*Created by Elhanan Ilganiv and Halel Gabber
 *Last update: 17/08/2021*/

#include <string.h>
#include "stdio.h"
#include <ctype.h>
#include <stdlib.h>
#include "ICommand.h"
#include "Labels.h"
#include "extern.h"
#include "generalFunc.h"

int JCommandCheck (char* input,int IC,int lineNum,outputNode* outputHead,Node* labelHead, int scan,externNode* externHead ) {/*need to add lable table as paramter and extern table and ....*/
    int opcode=0;
    int reg;
    int address;
    char *p;/*temp pointer*/
    char *name = NULL; /*for the strtok*/
    char *token = NULL; /*for the strtok*/

    p = strchr(input, '$');
        if (p == NULL) /*there is no $ sign so it lable not register*/
              reg=0;
        else
            reg=1;
    name = strtok(input, " ");
    if (name == NULL) {
        printf("%d:     ERROR: Wrong command name \n",lineNum);
        return ERROR;
    }
    if (strcmp(name, "jmp") == 0) {/*jmp cmd*/
        opcode = 30;
        if (reg == 1) {
            address = checkReg(p, lineNum);
        }
        else
        {
            name = strtok(NULL, " ");/*we get the lable name*/
            address = checkLableInTable(name, labelHead);/*check lable in lable table*/
        }
    }/*end of jmp case*/
    else if (strcmp(name, "la")==0) {
        if (reg == 1){
            printf("%d:     ERROR: Illegal command \n",lineNum);
        return ERROR;
    }
        opcode = 31;
        name = strtok(NULL, " ");/*we get the lable name*/
        address = checkLableInTable(name,labelHead);/*check lable in lable table*/
    }
    else if (strcmp(name, "call")==0) {
        if (reg == 1){
            printf("%d:     ERROR: Illegal command \n",lineNum);
            return ERROR;
        }
        opcode = 32;
        name = strtok(NULL, " ");/*we get the lable name*/
        address = checkLableInTable(name,labelHead);/*check lable in lable table*/

    }
    else if ((strcmp(name, "stop")==0)){
        if (reg == 1){
            printf("%d:     ERROR: Illegal command \n",lineNum);
            return ERROR;
        }
        opcode = 63;
        address = 0;
    }
    if(opcode==0)/*all if are not ture so the command is not familiar to us , need to display ilegal command */
    {
        printf("%d:     ERROR: Not legal command \n",lineNum);
        return ERROR;
    }
    if(address==ERROR)/* THE LABLE DOSNT EXIST if it first scan so ignore it ,
             * if it 2nd scan we enter next if , and display error*/
        if(scan==2) {/*we in 2nd scan*/
            printf("%d:     ERROR: The lable dont exist \n",lineNum);
            return ERROR;
        }
    if((address==0)&&((opcode!=63))&&(scan==2))/* the lable is external becuse the address is 0 and the command is not stop*/
        /*we add the this extern lable to list only in 2nd scan,
         * now we need to add the current IC and the lable name to external link list*/
        if((creatNewExternNode(IC,lineNum,name,externHead)==ERROR))/*her we add to the extern link list the extern lable */
        {
            printf("%d:     ERROR: Cant insert to extern table \n",lineNum);
            return ERROR;
        }
   if( JcommandBinaryBuild(opcode,address,reg,IC,lineNum,outputHead)==ERROR)
    return ERROR;
    return SUCCESS;
}



/*finish dis*/