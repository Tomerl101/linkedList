#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define TRUE 1
#define FALSE 0

typedef enum {General=1, Surgical, Pharmacy, Counselling} Unit;

typedef struct
{
    char* name;
    char* id;
    char* condition;
    Unit* unit;
    int priority;
    struct Patient* next;
}Patient;

typedef struct
{
    char* name;
    char* doctor;
    int count;
    Patient* patient_list;
}Department;

void printList(Patient* head)
{
    Patient *current = head;  //Declare temp and Assign Starting Address to current
    while(current!=NULL)
    {
    printf("%s\n",current->name);
    printf("%s\n",current->id);
    printf("%s\n",current->condition);
    printf("%d\n",current->unit);
    printf("%s\n",current->priority);
    current=current->next;
    }
    return;
}

void getUnit (Patient* _patient, char* temp)
{
    switch (temp[0])
    {
        case 'G':
        _patient->unit = General;
        break;
        case 'S':
        _patient->unit = Surgical;
        break;
        case 'P':
        _patient->unit = Pharmacy;
        break;
        case 'C':
        _patient->unit = Counselling;
        break;
    }
    return;
}

Patient* inputData(Patient* _patient, char buff[])
{
    char* temp;

    temp=strtok(buff,",");
    _patient->name=strdup(temp);
    temp=strtok(NULL,",");
    _patient->id=strdup(temp);
    temp=strtok(NULL,",");
    _patient->condition=strdup(temp);
    temp=strtok(NULL,",");
    getUnit(_patient, temp);       //think of a function to make ->unit a enum (maybe with switch case)
    temp=strtok(NULL,",");
    _patient->priority=strdup(temp);

    return;
}

Patient* createPatientList(FILE* readFile, Patient* head)
{
    char buff[1024];
    Patient* current = head;    //save the head of the list
    while(TRUE)
    {
        if(fgets(buff,1024,readFile)!=NULL)  //read line of data from txt file
        {
            if(buff[0]=='#' || buff[0]=='\n')       //skip a line if it start with ' ' or #
                continue;
            inputData(current, buff);
            if(feof(readFile))
                break;
            current->next = (Patient*) malloc(sizeof(Patient));
            current = current->next;
        }
    }
    current->next = NULL;
    return head;
}
/*--------------------------------------------
        /------------/
        /  M A I N   /
        /------------/
----------------------------------------------*/
int main(int argc, char *argv[])
{
    /*check if the input file is valid*/
    FILE* readFile = fopen(argv[1],"r");
    if(readFile==NULL)
    {
        printf("File not found ...\n");
        return NULL;
    }
    /*create the head of the patient linked list*/
   Patient* head = (Patient*) malloc(sizeof(Patient));
   Patient* start = head;
   head->next = NULL;
    if(head==NULL)
    {
        printf("Error in allocating node, returning NULL\n");
        return NULL;
    }
    head = createPatientList(readFile, head); //initialize the patient linked lis
    printList(start);
    return;
}
