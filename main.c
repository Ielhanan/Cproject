/*Created by Elhanan Ilganiv and Halel Gabber
 *Last update: 17/08/2021*/

#include <stdio.h>
#include <string.h>
#include "Labels.h"
#include <stdlib.h>
#include "RCommand.h"
#include "JCommand.h"
#include "extern.h"
#include "entry.h"
#include "guidanceCommand.h"
#include "data.h"
#include "generalFunc.h"


int main(int argc, char* argv[])
{
    int ICF;
    int lineNum=1;
    int IC=100;
    int* DC;
    int i;
    FILE *fd;
    int ch;
    char * token;
    char line[MAX_COMMAND_LENGTH];
    int index=0;
    int check;
    int checkF=SUCCESS; /*checkF is ERROR if one or more of the line had a problem*/
    int scan=1;
    char  fileName[20];
    Node* lablehead;
    outputNode * outputhead;
    DataNode * datahead;
    entryNode * entryhead;
    externNode * externhead;

    DC= malloc(sizeof (int));
    *DC=0;
    if(argc==1) /*check that the user provide file names*/
    {
        printf("ERROR: You must enter a file name \n try again \n");
        exit(0);
    }
    for (i=1; i<argc; i++) /*go through all the file name and open them*/
    {
        strcpy(fileName,argv[i]);

        if ((strstr(fileName, ".as") == NULL)) /*checking that the file type is as*/
        {
            printf("ERROR: Illegal file type! only .as is accepted \n");
            continue;
        }

        if (!(fd= fopen(argv[i],"r")))	/*trying to open the file to fd and check if it didnt work*/
        {
            printf("ERROR: Cannot open file number %d  \n ",i);
            continue;
        }

        lablehead=creatLablesList();
        outputhead=creatoutputList();
        datahead=creatDataList();
        entryhead=creatEntryLinkList();
        externhead=creatExternLinkList();
        checkF=SUCCESS;
        *DC=0;
        IC=100; /*stting up the starting IC in the beginning of the file*/
        lineNum=1; /*setting up the line counter in the beginning of the file*/
        index=0; /*reset index*/
        scan=1;
        while(!feof(fd))	/*as long as its not the end of the file*/
        {
            ch=fgetc(fd); /*get a char from the file*/
            if((ch!='\n')&&(ch!=-1)) /*as long as the char is not enter*/
                line[index++]=ch; /*add the char to the line command array*/
            else /*ch is enter or end of file*/
            {
                line[index]='\0'; /*for preventing extra not related chars*/
                /*************CHECKS IF ITS COMMENT OR EMPTY LINE ****************/
                if((line[0]==';') ||(strlen(line)==0))
                {
                    index=0;
                }
                else
                {
                     check=whatCommandIsIt(line,IC,DC,lineNum,outputhead,lablehead,datahead,scan,entryhead,externhead);
                     if((check==ERROR)||(check==CODEERROR)) /*there is an error in the file*/
                        checkF=ERROR; /***********  NEED TO CHECK THE REST OF THE FILE ANYWAY*********/
                     if((check==CODE)||(check==CODEERROR))
                        IC=IC+4;
                     index=0; /*starting from the beginning to creat a new line*/
                }/*end of else (case of a real line)*/
             lineNum++;
            }/*end of else (case of ch is an enter)*/


        }/*end of while (end of file)*/

        if(checkF!=ERROR)
        {

        check=fseek( fd, 0,  SEEK_SET ); /*returning to the bigining of the filevgor the secound scan*/
        if(check!=0)
        {
            printf("ERROR: Cant do the second scan. \n");
            checkF=ERROR;
        }
        else /*starting the secound scan*/
        {
            ICF=IC ;/*SAVE ICF*/
            fixDataLables(lablehead,ICF);/*need to fix lable list after end the program for output*/


            IC=100; /*stting up the starting IC in the beginning of the file*/
            lineNum=1; /*setting up the line counter in the beginning of the file*/

            scan=2;
            index=0;
            while(!feof(fd))	/*as long as its not the end of the file*/
            {
                ch=fgetc(fd); /*get a char from the file*/
                if((ch!='\n') &&(ch!=-1))/*as long as the char is not enter*/
                    line[index++]=ch; /*add the char to the line command array*/
                else /*ch is enter!*/
                {
                    line[index]='\0'; /*for preventing extra not related chars*/
                    /*************CHECKS IF ITS COMMENT OR EMPTY LINE ****************/
                    if((line[0]==';') ||(strlen(line)==0))
                    {
                        index=0;
                    }
                    else
                    {
                        check=whatCommandIsIt(line,IC,DC,lineNum,outputhead,lablehead,datahead,scan,entryhead,externhead);
                        if((check==ERROR)||(check==CODEERROR)) /*there is an error in the file*/
                            checkF=ERROR; /***********  NEED TO CHECK THE REST OF THE FILE ANYWAY*********/
                        if((check==CODE)||(check==CODEERROR))
                            IC=IC+4;
                        index=0; /*starting from the beginning to creat a new line*/
                    }/*end of else (case of a real line)*/
                lineNum++;
                }/*end of else (case of ch is an enter)*/

            }/*end of while (end of file)*/

        } /*end of second scan*/

            fclose(fd);	/*after we finish to print the file we close it.*/

        check=fillEntryList(lablehead,entryhead);
        if(check==ERROR)
            checkF=ERROR;
        }/*end of secound scan if first scan was successful*/
    if(checkF!=ERROR)
    {

        check=creatobfile(fileName,outputhead,datahead, ICF,*DC);  /*the function that creating the .ob outputfile*/
        if(check==ERROR)
            printf("ERROR: Cant creat .ob file \n");
        check= createntryfile(fileName,entryhead);
        if(check==ERROR)
            printf("ERROR: Cant creat .ent file \n");
        check= createxternfile(fileName,externhead);
        if(check==ERROR)
            printf("ERROR: Cant creat .ext file \n");
	strtok(fileName,".");
        printf("The files for %s has been created \n",fileName);
    }
        freeLableList(lablehead);
        freeEntryList(entryhead);
        freeDataList(datahead);
        freeOutputList(outputhead);
  	freeExternList(externhead);

    } /*end of for (loop for checking all the files*/


  

    return 0;
}


