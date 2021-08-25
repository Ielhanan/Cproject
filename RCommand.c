/*Created by Elhanan Ilganiv and Halel Gabber
 *Last update: 17/08/2021*/

#include <string.h>
#include "stdio.h"
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include "RCommand.h"
#include "generalFunc.h"
#include "bitField.h"

int rs; /*for keeping the int number*/
int rt;
int rd;
int extra;
int opcode;
int funct;
int check;
char * name=NULL; /*for the strtok*/
char * token=NULL; /*for the strtok*/

int RcommandCheck (char *line,int IC,int lineNum,outputNode* outputHead,int scan) {
    /*the extra is always 0 in R commands*/
    if(scan==2)
        return SUCCESS;


    extra = 0;
    check=checkCommas(line);
    if(check==ERROR)
    {
        printf("%d:     ERROR: Illegal command \n",lineNum);
        return ERROR;
    }
    /*RUNNING THE FUNC FOR DELETING SPACES*/

    name = strtok(line, " ");
    if (name == NULL) {
        printf("%d:     ERROR: Wrong command name \n",lineNum);
        return ERROR;
    }


    if ((strcmp(name, "add") == 0) || (strcmp(name, "sub") == 0) || (strcmp(name, "and") == 0) ||(strcmp(name, "or") == 0) || (strcmp(name, "nor") == 0)) {

        /*the opcode os 0 in all of this type of R commands*/
        opcode = 0;

        /*getting the rs*/
        token = strtok(NULL, ",");
        if (token == NULL)
        {
            printf("%d:     ERROR: Incorrect command no registers \n ",lineNum);
            return ERROR;
        }
        rs = checkReg(token,lineNum); /*NEED TO CREAT checkReg*/
        if (rs ==ERROR) /*if the function checkReg faild and something is wrong its print the error and the file is done.*/
            return ERROR;


        /*getting the rt*/
        token = strtok(NULL, ",");
        if (token == NULL)
        {
            printf("%d:     ERROR: command incorrect no registers \n",lineNum);
            return ERROR;
        }
        rt = checkReg(token,lineNum);
        if (rt == ERROR) /*if the function checkReg faild and something is wrong its print the error and the file is done.*/
            return ERROR;


        /*getting the rd*/
        token = strtok(NULL, ",");
        if (token == NULL)
        {
            printf("%d:     ERROR: Incorrect command no registers \n",lineNum);
            return ERROR;
        }
        rd = checkReg(token,lineNum);
        if (rd ==ERROR) /*if the function checkReg faild and something is wrong its print the error and the file is done.*/
            return ERROR;


        /*defining funct by the chart*/
        if ((strcmp(name, "add") == 0))
            funct = 1;
        else if ((strcmp(name, "sub") == 0))
            funct = 2;
        else if ((strcmp(name, "and") == 0))
           funct = 3;
        else if ((strcmp(name, "or") == 0))
            funct = 4;
        else if ((strcmp(name, "nor") == 0))
            funct = 5;

    }
    else { /*its not add,sub,and,or,nor*/
        if ((strcmp(name, "move") == 0) || (strcmp(name, "mvhi") == 0) || (strcmp(name, "mvlo") == 0)) {

            /*getting the rs*/
            token = strtok(NULL, ",");
            if (token == NULL)
            {
                printf("%d      ERROR: Incorrect command no registers \n",lineNum);
                return ERROR;
            }
            rs = checkReg(token,lineNum);

            if (rs == ERROR) /*if the function checkReg faild and something is wrong its print the error and the file is done.*/
                return ERROR;


            /*getting the rd*/
            token = strtok(NULL, ",");
            if (token == NULL) {
                printf("%d      ERROR: incorrect command no registers",lineNum);
                return ERROR;
            }
            rd = checkReg(token,lineNum);

            if (rd ==ERROR) /*if the function checkReg faild and something is wrong its print the error and the file is done.*/
                return ERROR;


            /*its zero because there is no rt in this commands*/
           rt = 0;
            /*opcode is 1 in all of this commands*/
           opcode = 1;

            /*defining funct by the chart*/
            if ((strcmp(name, "move") == 0))
                funct = 1;
            if ((strcmp(name, "mvhi") == 0))
                funct = 2;
            if ((strcmp(name, "mvlo") == 0))
             funct = 3;

        }/*end of if*/
        else /*its non of the r commands*/
        {
            printf("%d      ERROR: Unknown command name \n",lineNum);
            return ERROR;
        }
    }/*end of else*/

    if((RcommandBinaryBuild(opcode,funct,rs,rd,rt,IC,lineNum,outputHead)==ERROR))/*build the binary code  and check if it success or not */
        return ERROR;

    return SUCCESS; /*if we got here everything was successful*/

}/*end of Rcommand*/



