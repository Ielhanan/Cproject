/*Created by Elhanan Ilganiv and Halel Gabber
 *Last update: 17/08/2021*/

#ifndef PROJECT_C_EXTERN_H
#define PROJECT_C_EXTERN_H
#define ERROR -100000
#define SUCCESS -200000


typedef struct ext ext;
typedef struct externNode  externNode;
typedef struct externNode externNode;

/*this function gets externNode and return the lable name of this node.
 * in case of ERROR with the externNode head returns ERROR*/
char * getExternLableName(externNode* head);

/*this function gets externNode and return the IC of this node.
 * in case of ERROR with the externNode head returns ERROR*/
int getExternLableIC(externNode* head);

/*this function gets externNode and return the next entryNode in the list.
 * in case of ERROR with the externNode head returns ERROR*/
externNode* getNextEternNode (externNode* head);

/*this function gets externNode and return the ext stract of this node.
 * in case of ERROR with the externNode head returns ERROR*/
ext* getExtStruct(externNode* head);

/*this function craet the extern list and return a pointer to the head of the list.
 * in case of ERROR with the externNode head returns ERROR*/
externNode* creatExternLinkList();

/*this function gets externNode head and new ext node and insert the ext node to the list.
 * in case of ERROR with the entryNode head returns ERROR*/
int insertExtern(ext* new,int lineNum,externNode* head);/* change the argument to ext struct and calloc in this methode */

/*this function gets:
 * IC_ the IC of the command
 * lable-the lable name
 * head- the head of the extern list
 * the function creat a new node to the extern list.
 * in case of ERROR with the entryNode head returns ERROR*/
int creatNewExternNode(int IC,int lineNum,char* lable,externNode* head);



#endif
