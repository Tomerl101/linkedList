#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define TRUE 1
#define FALSE 0

typedef enum {General=1, Surgical, Pharmacy, Counselling} Unit;

typedef struct Patient
{
    char* name;
    char* id;
    char* condition;
    int unit;
    int priority;
}Patient;
typedef struct Node
{
    struct Node* next;
    Patient* data;
}Node;
typedef struct List
{
      struct Node *head;
      struct Node *tail;
}List;
typedef struct Department
{
    char* name;
    char* doctor;
    int count;
    struct List list;
}Department;

void addNodeToEnd(List* theList)
{
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->next = NULL;
    newNode->data = NULL;

    if (theList->head==NULL && theList->tail== NULL)
         theList ->head = theList ->tail = newNode;
   else
    {
        theList->tail->next = newNode;
        theList->tail = newNode;
    }
	return;
}
void getUnit (Patient* patient, char* temp)
{
    switch (temp[0])
    {
        case 'G':
        patient->unit = 1;
        break;
        case 'S':
        patient->unit = 2;
        break;
        case 'P':
        patient->unit = 3;
        break;
        case 'C':
        patient->unit = 4;
        break;
    }
    return;
}
Patient* Add_data(List* theList, char buff[])
{
    theList->tail->data = (Patient*)malloc(sizeof(Patient));
    char* temp;
    temp=strtok(buff,",");
    theList->tail->data->id=strdup(temp);
    temp=strtok(NULL,",");
    theList->tail->data->name=strdup(temp);
    temp=strtok(NULL,",");
    theList->tail->data->condition=strdup(temp);
    temp=strtok(NULL,",");
    getUnit(theList->tail->data, temp);       //think of a function to make ->unit a enum (maybe with switch case)
    temp=strtok(NULL,",");
    theList->tail->data->priority=atoi(temp);
    return theList;
}
void maxPriority(List* theList)
{
    printf("\n->Patient with the highest priority:\n");
    Node* temp = theList->head;
    Patient maxPatient = *temp->data;
    while(temp != NULL)
    {
        if(maxPatient.priority < temp->data->priority)
            maxPatient = *temp->data;
        temp = temp->next;
    }
    printPatient(&maxPatient);
    return;
}
void freeData (Node* head)
{
    Node* temp=head;
    while(temp!=NULL)
    {
        head=head->next;
        free(temp);
        temp=head;
    }
}
void printDepartment(Department department)
{
    printf("\n======[ %s, %d ]=======\n", department.name, department.count);
    while(department.list.head !=NULL)
    {
    printf("\n%s\n",department.doctor);
    printPatient(department.list.head->data);
    department.list.head = department.list.head->next;
    }
    return 0;
}
void printPatient(Patient* patient)
{
    printf("\n%s\n",patient->id);
    printf("%s\n",patient->name);
    printf("%s\n",patient->condition);
    printf("%d\n",patient->unit);
    printf("%d\n",patient->priority);

    return 0;
}
void nameCredits()
{
    int a;
    for(a=1; a<=43; a++){
        printf("*");
    }
    printf("\n\n\t TOMER 203289673 & SHOHAM  \n\n");
    for(a=1; a<=43; a++){
        printf("*");
    }
    return;
}

 /*-----[ M A I N ]------*/

int main(int argc, char *argv[])
{

    nameCredits();
    /*check if the input file is valid*/
    FILE* readFile = fopen(argv[1],"r");
    if(readFile==NULL)
    {
        printf("File not found ...\n");
        return NULL;
    }
    char buff[1024];

    /*initializing the departments*/
    Department general = {"General", "Dr.Strange",0,{NULL, NULL}};
    Department surgical = {"Surgical", "Dr.who",0,{NULL, NULL}};
    Department pharmacy = {"Pharmacy", "Dr.Doom",0,{NULL, NULL}};
    Department counselling = {"Counselling", "Dr.Phil",0,{NULL, NULL}};

    /*initialize patient linked list*/
    List patientList = {NULL, NULL};
    //freeData(&patientList.head);

    /*load the data of patient from the user file*/
    while(fgets(buff,1024,readFile)!=NULL)
    {
        if(buff[0]=='#' || buff[0]=='\n')       //skip a line if it start with ' ' or #
            continue;
        addNodeToEnd(&patientList);
        Add_data(&patientList, buff);
    }

    /*temporary copy of the patient list*/
    List temp = patientList;

    /*send patient to the departments linked list*/
    while(temp.head != NULL)
    {
        switch(temp.head->data->unit)
        {
        case General:
            addNodeToEnd(&general.list);
            general.list.tail->data = temp.head->data;
            general.count++;
            break;
        case Surgical:
            addNodeToEnd(&surgical.list);
            surgical.list.tail->data = temp.head->data;
            surgical.count++;
            break;
        case Pharmacy:
            addNodeToEnd(&pharmacy.list);
            pharmacy.list.tail->data = temp.head->data;
            pharmacy.count++;
            break;
        case Counselling:
            addNodeToEnd(&counselling.list);
            counselling.list.tail->data = temp.head->data;
            counselling.count++;
            break;
        }
        temp.head = temp.head->next;
    }

    printDepartment(general);
    printDepartment(surgical);
    printDepartment(pharmacy);
    printDepartment(counselling);

    return 0;
}


/*==========================================================
    printf("patient in department: %d \n", general.count);
    printf("patient in department: %d \n", surgical.count);
    printf("patient in department: %d \n", pharmacy.count);
    printf("patient in department: %d \n", counselling.count);
    printDepartment(general);
    printDepartment(surgical);
    printDepartment(pharmacy);
    printDepartment(counselling);

    maxPriority(&general.list);
    maxPriority(&pharmacy.list);

    tomer shoam v4.1
=============================================================*/
