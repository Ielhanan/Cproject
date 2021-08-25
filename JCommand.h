/*Created by Elhanan Ilganiv and Halel Gabber
 *Last update: 17/08/2021*/

#ifndef PROJECT_JCOMMAND_H
#define PROJECT_JCOMMAND_H
#include "Labels.h"
#include "extern.h"

#define ERROR -100000
#define SUCCESS -200000

/*this function gets:
 * input- the line of the command
 * IC- the IC of the current line
 * lineNum- the line number in the file
 * outputhead- its head of output list
 * lableHead- is head of lable list
 * scan represnt if we in first scan or 2nd scan
 * externhead- the head of the extern list
 * this function analyze the I command and send the right values to the JCommandBinaryBild to insert the command to the outputlist
 * the function return ERROR if something went wrong and SUCCESS otherwise.*/
int JCommandCheck (char* input,int IC,int lineNum,outputNode* outputHead,Node* labelHead,int scan,externNode*);


#endif
