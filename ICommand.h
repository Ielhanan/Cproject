/*Created by Elhanan Ilganiv and Halel Gabber
 *Last update: 17/08/2021*/

#ifndef PROJECT_ICOMMAND_H
#define PROJECT_ICOMMAND_H
#define ERROR -100000
#define SUCCESS -200000
#include "bitField.h"
#include "Labels.h"


/*this function gets:
 * input- the line of the command
 * IC- the IC of the current line
 * lineNum- the line number in the file
 * outputhead- its head of output list
 * lableHead- is head of lable list
 * scan represent if we in first scan or 2nd scan
 * this function analyze the I command and send the right values to the ICommandBinaryBild to insert the command to the outputlist
 * the function return ERROR if something went wrong and SUCCESS otherwise.*/
int ICommandCheck(char * ,int  ,int ,outputNode * ,Node * ,int );


/*this function gets:
 * commandNAme- the command name
 * lineNum- the number of the line in the file
 * the function check what is the currect opcode and return it if the command name is wrong return ERROR*/
int opcodeDetect(char* commandName,int lineNum);

#endif //UNTITLED9_ICOMMAND_H
