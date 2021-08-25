/*Created by Elhanan Ilganiv and Halel Gabber
 *Last update: 17/08/2021*/

#ifndef PROJECT_DATA_H
#define PROJECT_DATA_H

typedef struct Data Data;
typedef struct DataNode DataNode;

/*this function gets DataNode and return the value of the data that saved in the DataNode.
 * in case of ERROR with the datanode head returns ERROR*/
int getData(DataNode* head);

/*this function gets DataNode and return the IC that saved in the DataNode.
 * in case of ERROR with the datanode head returns ERROR*/
int getDataIC(DataNode* head);

/*this function gets DataNode and return the data stract that saved in the DataNode.
 * in case of ERROR with the datanode head returns ERROR*/
Data * getDataStruct(DataNode* head);

/*this function gets DataNode and return the next DataNode in the list.
 * in case of ERROR with the datanode head returns ERROR*/
DataNode* getNextDataNode (DataNode* head);

/*this function gets DataNode and return the data space the the value needed.
 * in case of ERROR with the datanode head returns ERROR*/
int getDataSpace(DataNode* head);

/*this function creat the DataNodelist and return a pointer to the head of the list.
 * in case of ERROR with the datanode head returns ERROR*/
DataNode* creatDataList();

/*this function gets the head of the list and new datanode to insert into the list.
 * in case of ERROR with the datanode head returns ERROR*/
int addDataNodeToTable( DataNode* newData,DataNode* head);

/*this function gets:
 * value- the value of the data
 * Dc- the DC of the command
 * lineNum- the number of the line in the file
 * head- the head of the data list
 * type- if the command is CODE or DATA
 * the function creat a new command node and sent it to the addCommandToList
 * the function return SUCCESS if everything worked and ERROR otherwise.*/
int creatNewDataNode(int value, int DC,int lineNum,DataNode* head,int type);


#endif
