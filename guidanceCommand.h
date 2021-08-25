/*Created by Elhanan Ilganiv and Halel Gabber
 *Last update: 17/08/2021*/

#include "Labels.h"
#include "data.h"
#define ERROR -100000
#define CODEERROR -150000
#define SUCCESS -200000
#define CODE -120000
#define DATA -130000
#define MIN_B_RANGE -128
#define MIN_H_RANGE -32768
#define MIN_W_RANGE (-2147483647L - 1)
#define MAX_B_RANGE 127
#define MAX_H_RANGE 32767
#define MAX_W_RANGE 2147483647
#define MAX_COMMAND_LENGTH 82

/*this function gets:
 * line- the string with the command line
 * DC- a pointer to the DC counter
 * lineNum- the number of the current line in the file
 * labelHead- the head of the lable list
 * datahead- the head of the data list
 * scan- the number of the scab 1/2
 * entryhead- the head of the entry list
 * this function analyse the guidnace command and insert it to the data list.
 * return ERROR if something went wrong. and SUCCESS otherwise. */
int guidanceCheck (char *,int*,int, Node* ,DataNode * , int scan,entryNode*);

/*this function gets the sting of the data and check that the value is legal.
 * return ERROR if something went wrong. and SUCCESS otherwise. */
int checkDate(char * ,int );

/*this function gets the sting of the data and check that the value is legal.
 * return ERROR if something went wrong. and SUCCESS otherwise. */
int checkAscizData (char *, int * , int lineNum,DataNode * );
