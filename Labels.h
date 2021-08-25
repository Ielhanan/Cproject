/*Created by Elhanan Ilganiv and Halel Gabber
 *Last update: 17/08/2021*/

#ifndef PROJECT_LABELS_H
#define PROJECT_LABELS_H
#define MAX_COMMAND_LENGTH 82
#define ERROR -100000
#define SUCCESS -200000

typedef struct label label;
typedef struct Node Node;

/*this function gets
 * lable- the name of the lable
 * head- the head of the current list
 * the function check if the lable already exist.
 * return ERROR if the lable is not exist and the IC of the lable otherwise.*/
int checkLableInTable(char* lable, Node* head);

/*this function creart a new lable list and return the head of the list*/
Node* creatLablesList();

/*this function gets
 * symbol=name of the lable
 * IC- the ic of the line
 * isEntry- 0 if its not entry 1- if its entry
 * isExternal- 0 if its not entry 1- if its entry
 * the function return ERROR if the lable already exist and success otherwise*/
int creatNewNode(char* symbol, int IC,int lineNum,int isEntry,int isExternl,int isData,Node* head);

/*this function gets
* newLable- the lable that need to enter to the list
 * head- the head of the current lable
* the function return ERROR if the lable is already exist and success otherwise*/
 int  addLableToTable( int lineNum,Node* newLable,Node* head);

/*this function gets
* lable- the lable that need to be checked
 * head- the head of lable list
* the function return the value that save in the isExtern inside the node.*/
int checkIfLableIsExtern(char* lable, Node* head);

/*this function gets lable name and the head of lable list and change the value of isEntry of the lable to YES*/
int makeLableToExtern(char* lable, Node* head);

 /*this function gets lable name and the head of lable lust and return the value of the lable isEntry.*/
int checkIfLableIsEntry(char* lable, Node* head);

/*this function gets the name of the lable and the head of the lable list and change the value of isEntry to YES
 * the function return SUCCESS/ ERROR*/
int makeLableToEntry(char* lable, Node* head);

/*this function gets the lable head and currect the IC of all the DATA command (need to do DC+ICF)*/
int fixDataLables (Node* lableHead,int ICF);

/*this function gets a node of lable list and return a pointer to the next node
 * the function return ERROR if it fails*/
Node* getNextNode (Node* head);

/*this function gets a node of lable list and return the lable name
 * the function return ERROR if it fails*/
char* getLableName(Node * head);

/*this function gets a node of lable list and return the IC of the lable
 * the function return ERROR if it fails*/
int getICLable(Node* head);

/*this function gets a node of lable list and return the lable stract
 * the function return ERROR if it fails*/
label* getLableStruct (Node* head);



#endif

