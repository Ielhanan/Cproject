/*Created by Elhanan Ilganiv and Halel Gabber
 *Last update: 17/08/2021*/

#include <string.h>
#include "Labels.h"
#include "stdio.h"
#include <ctype.h>
#include <stdlib.h>
#include "ICommand.h"
#include "generalFunc.h"

int ICommandCheck(char* input,int IC,int lineNum,outputNode* outputHead,Node* labelHead, int scan) {

    int rs; /*for keeping the int number*/
    int rt;
    int opcode;
    char *name = NULL; /*for the strtok*/
    char *token = NULL; /*for the strtok*/
    int immed;
    /*RUNNING THE FUNC FOR DELETING SPACES*/

    name = strtok(input, " ");
    if (name == NULL) {
        printf("%d:     ERROR: Wrong command name \n",lineNum);
        return ERROR;
    }
    opcode = opcodeDetect(name,lineNum);

    /*getting the rs*/
    token = strtok(NULL, ",");
    if (token == NULL) {
        printf("%d:     ERROR: Command incorrect no registers \n ",lineNum);
        return ERROR;
    }
    rs = checkReg(token,lineNum);
    if (rs == ERROR) /*if the function checkReg faild and something is wrong its print the error and the file is done.*/
        return ERROR;
    /*end check rs */
    if((opcode>=15)&&(opcode<=18))/*this is bgt\blt\bne\bnq command rt is seccond in string so need now get rt*/
    {
        token = strtok(NULL, ",");
        if (token == NULL) {
            printf("%d:     ERROR: Command incorrect no registers \n",lineNum);
            return ERROR;
        }
        rt = checkReg(token,lineNum);
        /*if the function checkReg faild and something is wrong its print the error and the file is done.*/
        if (rt == ERROR)
            return ERROR;
        /*end get rt*/
    }
    /*get immed*/
    token = strtok(NULL, ",");
    if (token == NULL) {
        printf("%d:     ERROR: Lable/number not correct \n",lineNum);
        return ERROR;
    }
    while(isspace(token[0]))
    {
        token++;
    }

    if ((isdigit(token[0])!= 0)||(token[0]=='-')) /*if it true, the immed is number ,becuse lable cant start
     * with digit we need to convert it to int*/
        immed = atoi(token);
    else {
        immed = ((IC - checkLableInTable(token, labelHead))*-1);/*check if the lable exist,return ERROR if not exist
         * it return the IC of this lable ,
         * we store at immed the delta between the lable IC and command IC.*/
        if (immed == IC) {/*it means the lable is external becuse immed is equal to IC so it have 0 lines to move*/
            printf("%d:     ERROR: This lable is extern \n",lineNum);
            return ERROR;
        }
        if (immed == (IC - ERROR))/* if this if is true , it means the lable dont exist */
            if (scan == 2) {/*if it first scan so we need to ignore this ,
            *if we in 2nd scan and the immed is ERROR , the lable dont exist we need to exit the program*/
                printf("%d:     ERROR: Lable/number not correct \n",lineNum);
                return ERROR;
            }
    }
        /*end get immed */
    if((opcode<15)||(opcode>18)) {/*this is not command bgt\blt \beq\ bne, so rt is last in the string
        /*getting the rt*/
        token = strtok(NULL, ",");
        if (token == NULL) {
            printf("%d:     ERROR: Command incorrect no registers \n",lineNum);
            return ERROR;
        }
        rt = checkReg(token,lineNum);
        /*if the function checkReg faild and something is wrong its print the error and the file is done.*/
        if (rt == ERROR)
            return ERROR;
        /*end get rt*/
    }

        if ((IcommandBinaryBuild(opcode, rs, rt, immed, IC,lineNum, outputHead) == ERROR))
            /*build the binary code and check if it success or not */
            return ERROR;
        return SUCCESS;/*it means that the command are good */


}
int opcodeDetect(char* commandName,int lineNum)/*check if the command is legal, return the opcode*/
{
    if(strcmp(commandName,"addi")==0) return 10;
    else if(strcmp(commandName,"subi")==0) return 11;
    else if(strcmp(commandName,"andi")==0) return 12;
    else if(strcmp(commandName,"ori")==0) return 13;
    else if(strcmp(commandName,"nori")==0) return 14;
    else if(strcmp(commandName,"bne")==0) return 15;
    else if(strcmp(commandName,"beq")==0) return 16;
    else if(strcmp(commandName,"blt")==0) return 17;
    else if(strcmp(commandName,"bgt")==0) return 18;
    else if(strcmp(commandName,"lb")==0) return 19;
    else if(strcmp(commandName,"sb")==0) return 20;
    else if(strcmp(commandName,"lw")==0) return 21;
    else if(strcmp(commandName,"sw")==0) return 22;
    else if(strcmp(commandName,"lh")==0) return 23;
    else if(strcmp(commandName,"sh")==0) return 24;
    else
    {
        printf("%d:        ERROR: Illegal command", lineNum);
        return ERROR;
    }
}

