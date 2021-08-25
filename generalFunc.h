/*Created by Elhanan Ilganiv and Halel Gabber
 *Last update: 17/08/2021*/

#include "RCommand.h"
#include "JCommand.h"
#include "ICommand.h"
#include "extern.h"
#include "entry.h"
#include "guidanceCommand.h"
#include "bitField.h"
#include "data.h"
#define ERROR -100000
#define CODEERROR -150000
#define SUCCESS -200000
#define CODE -120000
#define DATA -130000

/*this function gets a line and check that there are no unneeded commas in the line
 * return SUCCESS if its all good and ERROR otherwise*/
int checkCommas(char* );

/*this function gets a string of the register and check that the register is correct.
 * return SUCCESS if its all good and ERROR otherwise*/
int checkReg(char * ,int lineNum);

/*this function gets:
 * line- the string of the line from the file
 * IC- the IC of the current line
 * DC- the DC of the current line
 * lineNum- the number of the line in the file
 * outputhead- the head of the out put list
 * lablehead- the head of the lable list
 * datahead- the head of the data list
 * int scan- the scan number 1/2
 * entryhead- the head of the entry list
 * externhead-the head of the extern list
 * this function gets the complete line from the main and analyse it:
 * checks if there is a lable in the line and send the relevant argument to the lineWithLAble function.
 * checks ehat is the command name and send the relevant argument to the right function to process the line.
 * the function calculate the next DC/IC and return ERROR/SUCCESS according to the result from all the other functions.*/
int whatCommandIsIt (char * , int , int* , int, outputNode* , Node * , DataNode * ,int ,entryNode *,externNode *);

/*this function gets:
 * lableName- the string of the lable name
 * type- what the type of the command CODE / DATA
 * counter- the DC/IC of the current line
 * lineNum-the number of the line in the file
 * lablehead- the head of the lable list
 * int scan- the scan number 1/2
 * entryhead- the head of the entry list
 * externhead-the head of the extern list
 * this function insert the lable name to the lable list and checks the lable is not been used before.
 * in the secound scan its add the lable to the extern list as well.
 * return ERROR/SUCCESS according to the checks the function does*/
int lineWithLabale(char * lableName, int type, int counter,int scan,int lineNum, Node* lablehead,externNode * externhead, entryNode * entryhead );

/*this function gets:
 * filename- the string of the current file name
 * outputhead- the head of the out put list
 * datahead- the head of the data list
 * ICF- the IC final of this file
 * DCF- the DC final of this file
 * this function creat the ob file and print all the relevant details into the file.*/
int creatobfile (char * ,outputNode *, DataNode *,int,int);

/*this function gets:
 * filename- the string of the current file name
 * entryhead- the head of the entry list
 * this function creat the ent file and print all the relevant details into the file.*/
int createntryfile (char * ,entryNode *);

/*this function gets:
 * filename- the string of the current file name
 * externhead- the head of the entry list
 * this function creat the ext file and print all the relevant details into the file.*/
int createxternfile (char * ,externNode *);

/*this function gets:
 * lablehead- the head of the lable list
 * entryhead- the head of the entry list
 * this function go on the lable list and check witch lable is entry and add the entry lables to the entry list.*/
int fillEntryList(Node* lablehead, entryNode* entryhead);

/*this function free the lable list*/
void freeLableList(Node* lableHead);

/*this function free the entry list*/
void freeEntryList(entryNode* entryHead);

/*this function free the extern list*/
void freeExternList(externNode* externHead);

/*this function free the data list*/
void freeDataList(DataNode* dataHead);

/*this function free the output list*/
void freeOutputList(outputNode* outputHead);

/*this function check that the number is legal return ERROR if not and SUCCESS if yes*/
int checknumber (char* num, int linenum);

/*checks if the lable name is legal return SUCCESS of ots is and ERROR otherwise*/
int checkLableName(char* name, int linenum);
