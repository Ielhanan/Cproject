/*Created by Elhanan Ilganiv and Halel Gabber
 *Last update: 17/08/2021*/

#ifndef PROJECT_C_ENTRY_H
#define PROJECT_C_ENTRY_H
#define ERROR -100000
#define SUCCESS -200000
typedef struct ent ent;
typedef struct entryNode entryNode;

/*this function gets entryNode and return the lable name of this node.
 * in case of ERROR with the entryNode head returns ERROR*/
char * getEntryLableName(entryNode* head);

/*this function gets entryNode and return the IC of this node.
 * in case of ERROR with the entryNode head returns ERROR*/
int getLableIC(entryNode* head);

/*this function gets entryNode and return the next entryNode in the list.
 * in case of ERROR with the entryNode head returns ERROR*/
entryNode* getNextEntryNode (entryNode* head);

/*this function gets entryNode and return the ent stract of this node.
 * in case of ERROR with the entryNode head returns ERROR*/
ent* getEntStruct(entryNode* head);

/*this function craet the entry list and return a pointer to the head of the list.
 * in case of ERROR with the entryNode head returns ERROR*/
entryNode* creatEntryLinkList();

/*this function gets entryNode head and new ent node and insert the ent node to the list.
 * in case of ERROR with the entryNode head returns ERROR*/
int insertEntry(ent* ,entryNode* );

/*this function gets:
 * IC_ the IC of the command
 * lable-the lable name
 * head- the head of the entry list
 * the function creat a new node to the entry list.
 * in case of ERROR with the entryNode head returns ERROR*/
int creatNewEntry(int IC, char* lable,entryNode* head);


#endif
