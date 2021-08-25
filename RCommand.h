/*Created by Elhanan Ilganiv and Halel Gabber
 *Last update: 17/08/2021*/

#ifndef PROJECT_C_Rcommand_H
#include "bitField.h"
#define ERROR -100000
#define SUCCESS -200000


/*this function gets:
 * line- the line of the command
 * IC- the IC of the current line
 * lineNum- the line number in the file
 * outputhead- its head of output list
 * scan represent if we in first scan or 2nd scan
 * this function analyze the R command and send the right values to the RCommandBinaryBild to insert the command to the outputlist
 * the function return ERROR if something went wrong and SUCCESS otherwise.*/
int RcommandCheck (char *line,int IC,int lineNum,outputNode* outputHead,int scan);

#endif