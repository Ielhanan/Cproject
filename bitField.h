/*Created by Elhanan Ilganiv and Halel Gabber
 *Last update: 17/08/2021*/

#ifndef PROJECT_BITFIELD_H
#define PROJECT_BITFIELD_H
#define ERROR -100000
#define SUCCESS -200000

typedef struct Icommand Icommand;
typedef struct Rcommand Rcommand;
typedef struct Jcommand Jcommand;
typedef struct outputNode outputNode;

/*this function gets outputNode and return the data that saved in the outputNode.
 * in case of ERROR with the output head returns ERROR*/
unsigned int* getOutputData(outputNode* head);

/*this function gets outputNode and return the IC value of it.
 * in case of ERROR with the output head returns ERROR*/
int getIC(outputNode* head);

/*this function gets outputNode and return the next outputNode of the list.
 * in case of ERROR with the output head returns ERROR*/
outputNode* getNextOutputNode (outputNode* head);

/*this function creat outPut list and return the head of the list.
 * in case of ERROR with the output head returns ERROR*/
outputNode* creatoutputList();

/*this function gets:
 * head- the head of the output list
 * newCommand- the new outputNode that need to get in the list.
 * the function add the new outputNode to the list. return SUCCESS if everything worked and ERROR otherwise.*/
int addCommandToOutputList( outputNode* newCommand,outputNode* head);

/*this function gets:
 * opcode- the opcode of the command
 * funct- the funct of the command
 * rs- the rs of the command
 * rd- the rd of the command
 * rt- the rt of the command
 * Ic- the IC of the command
 * lineNum- the number of the line in the file
 * head- the head of the output list
 * the function creat a new command node and sent it to the addCommandToList
 * the function return SUCCESS if everything worked and ERROR otherwise.*/
int RcommandBinaryBuild(int opcode,int funct,int rs,int rd,int rt,int IC,int lineNum,outputNode* head);

/*this function gets:
 * opcode- the opcode of the command
 * rs- the rs of the command
 * rt- the rt of the command
 * immed- the immed ot the command
 * Ic- the IC of the command
 * lineNum- the number of the line in the file
 * head- the head of the output list
 * the function creat a new command node and sent it to the addCommandToList
 * the function return SUCCESS if everything worked and ERROR otherwise.*/
int IcommandBinaryBuild(int opcode,int rs,int rt, int immed,int IC,int lineNum,outputNode* head);

/*this function gets:
 * opcode- the opcode of the command
 * address- the address of the command
 * reg- the reg ot the command
 * Ic- the IC of the command
 * lineNum- the number of the line in the file
 * head- the head of the output list
 * the function creat a new command node and sent it to the addCommandToList
 * the function return SUCCESS if everything worked and ERROR otherwise.*/
int  JcommandBinaryBuild(int opcode, int address, int reg,int IC,int lineNum,outputNode* head);

/*this will check if in first scan we alredy insert this command
 * becuse, in first scan it possible to not know the binary code of this command.
 * it will return error if the command was inserted in first scan.
 * return success if the command is not inserted yet.*/
outputNode* checkIfCommandInsert(int IC,outputNode* head);

    #endif
