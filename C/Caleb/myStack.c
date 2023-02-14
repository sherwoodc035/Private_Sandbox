/*
myStack.c
Description:
    ahah
Written by:Caleb Mueller
Start date:1/31/2023
End date:
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//Global Varibles
bool outOfData = false;

//Structure definitions
typedef struct studentStruct
{
    char lastName[25];
    char firstName[25];
    int scores[4];
}studentStruct;

typedef struct stackNode
{
    studentStruct* ptStudentStruct;
    struct stackNode* link;
}stackNode;
  
  
typedef struct stackHead
{
    int studentCount;
    stackNode* top;
}stackHead;
  
//FUNCTION DECLARATIONS
stackHead* createStack();
    /*creates the stack head, and initalizes count to zero and top of stack to 
    NULL*/
bool pushStack(stackHead* stack, void* dataIn);
    /*creates a new node in the stack, inserts the data given, and pushes the 
    other nodes down*/
void seperateString(char* string, char* destination);
    /**/
studentStruct* readStudentData(FILE* file);
    /*Reads in student data from a file and returns pointer to filled student 
    structure*/
void createStudentRecord(FILE* file, stackHead* stack);
    /*fills student recod stack*/
int getCount(stackHead* stack);
    /*takes in stack head and returns count
    seems like a pointless function in this, but it was asked for*/
void popStack(stackHead* stack);

void printStudentRecord (stackHead* stack);

bool stackEmpty(stackHead* stack);

void destroyStack(stackHead* stack);

/* Jake's functions */
studentStruct* readfile(FILE* file) {
	studentStruct* dataIn;
	int n = 100;
	char buffer[n];
	bool headerline = true;

	while (fgets(buffer, n, file)) {
		/* skip headerline from being recorded into struct */
		if (headerline)
			headerline = false;
		else {
			/* create a new structure to hold student data */
			studentStruct* newSt = (studentStruct*)malloc(sizeof(studentStruct));
			/* read the data from buffer into struct using sscanf */
			sscanf(
				buffer,
				"%s,%s,%d,%d,%d,%d", 
				newSt->firstName,
				newSt->lastName, 
				newSt->scores[0],
				newSt->scores[1],
				newSt->scores[2],
				newSt->scores[3]
			);
			/* reads until fgets() returns a NULL pointer */
		}
	}

	return newSt;
} /* end readfile() */

int main()
{
    stackHead* studentHead;
    studentStruct* data;
      
    FILE* inputFile;
    char header[100];
      
    studentHead = createStack();
      
    inputFile = fopen("studentData.txt", "r");
      
    fgets(header, 100, inputFile);//trying to read in header line
      
    printf("%s\n",header);
      
    createStudentRecord(inputFile, studentHead);
    fclose(inputFile);
    popStack(studentHead);
    destroyStack(studentHead);
  
  

    return 0;
}


stackHead* createStack()
{
    stackHead* stack;
    
    stack = (stackHead*) malloc(sizeof(stackHead));
    
    if (stack)
    {
        stack->studentCount = 0;
        stack->top = NULL;
        printf("Stack Created\n");
    }
    else
    {
        printf("Stack was failed to be created\n");
        exit;
    }
    
    return stack;
}

bool pushStack(stackHead* stack, void* dataIn)
{
    bool success;
    stackNode* newNode;
    
    newNode = (stackNode*) malloc(sizeof(stackNode));
    
    if (newNode)
    {
        newNode->ptStudentStruct = dataIn;
        newNode->link = stack->top;
        stack->top = newNode;
        stack->studentCount ++;
        success = true;
    }
    else
    {
        success = false;
    }
    
    return success;
}

studentStruct* readStudentData(FILE* file)
{
    studentStruct* dataIn;
    
    char bufferLine[100];
    char workingString[25];
    
    
    char pLastName[25];
    char pFirstName[25];
    int pScores[4];
    
    //printf("working on read student\n");
    
    if (fgets(bufferLine, 100, file))
    {
        if(bufferLine[0] == ',')
        {
            strcpy(pLastName,"N/A");
            bufferLine[0] = ' ';
        }
        else
        {
            seperateString(bufferLine, workingString);
            strcpy(pLastName,workingString);
        }
        //printf("%s\n", pLastName);
        
        if(bufferLine[0]==',')
        {
            strcpy(pFirstName,"N/A");
            bufferLine[0] = ' ';
        }
        else
        {
            seperateString(bufferLine, workingString);
            strcpy(pFirstName,workingString); 
        }
        //printf("%s\n", pFirstName);
        
        if(bufferLine[0]==',')
        {
            pScores[0] = 0;
            bufferLine[0] = ' ';
        }
        else
        {
            seperateString(bufferLine, workingString);
            pScores[0]= atoi(workingString);
        }
        //printf("%d\n", pMathScore);
        
        if(bufferLine[0]==',')
        {
            pScores[1] = 0;
            bufferLine[0] = ' ';
            
        }
        else
        {
            seperateString(bufferLine, workingString);
            pScores[1] = atoi(workingString);
        }
        //printf("%d\n", pScienceScore);
        
        if(bufferLine[0]==',')
        {
            pScores[2] = 0;
            bufferLine[0] = ' ';
        }
        else
        {
            seperateString(bufferLine, workingString);
            pScores[2] = atoi(workingString);
        }
        //printf("%d\n", pLatinScore);

        if(bufferLine[0] == ',')
        {
            pScores[3] = 0;
        }
        else
        {
            pScores[3] = atoi( bufferLine);
        }
        //printf("%d\n", pGreekScore);
        
    }
    else
    {
        outOfData = true;
    }
    
    
    //printf("attempting to create student\n");
    if (!outOfData)
    {
        dataIn = (studentStruct*)malloc(sizeof(studentStruct));
                
        if (dataIn)
        {
            //printf("Student Created\n");
                
            strcpy(dataIn->lastName, pLastName);
            strcpy(dataIn->firstName, pFirstName);
            for (int i = 0; i<4; i++)
            {
                dataIn->scores[i] = pScores[i];
            }
            
            //printf("%s%s%d%d%d%d\n",dataIn->lastName, dataIn->firstName, dataIn->mathScore, dataIn->scienceScore, dataIn->latinScore, dataIn->greekScore);
        }
        else
        {
            printf("error creating student\n");
            exit;
        }
    
    }
    return dataIn;
}

void seperateString(char* string, char* destination)
{
    //printf("String is: %s\n", string);
    
    strcpy(destination, strtok(string, ","));
    strcpy(string, strtok(NULL, ""));
    
    //printf("String is: %s\n", string);
    
    return;
}

void createStudentRecord(FILE* file, stackHead* stack)
{
    studentStruct* data;
    
    printf("Student count is: %d\n", getCount(stack));
    printf("Adding students...\n\n");
    
    while (!outOfData)
    {
        data = readStudentData(file);
       
        if (!outOfData)
        {
            if(!pushStack(stack, data))
            {
               printf("failed to create stack\n");
               exit;
            }
            else
            {
               printf("Added: %s ",stack->top->ptStudentStruct->firstName);
               printf("%s to the stack\n",stack->top->ptStudentStruct->lastName);
               printf("Student count is: %d\n\n", getCount(stack));
            }
        }
        
    }
    return;
}

int getCount(stackHead* stack)
{
    return stack->studentCount;
}

void popStack(stackHead* stack)
{
    stackNode* temp;
    
    printf("Now popping stack contents.\n\n\n");
    while (!stackEmpty(stack))
    {
        
        printStudentRecord(stack);
        
        temp = stack->top;
        
        stack->top = stack->top->link;
        free(temp->ptStudentStruct);
        free(temp);
        stack->studentCount --;
        
    }
    
    return;
}

bool stackEmpty(stackHead* stack)
{
    bool result;
    
    if (stack->top == NULL)
    {
        result = true;
    }
    else
    {
        result = false;
    }
    
    return result;
}

void printStudentRecord (stackHead* stack)
{
    printf("Student %d\n", getCount(stack));
    printf("%s %s\n", stack->top->ptStudentStruct->firstName, stack->top->ptStudentStruct->lastName);
    printf("Mathematics Science Latin Greek\n");
    printf("%3d%12d%8d%6d\n\n", stack->top->ptStudentStruct->scores[0],
                                stack->top->ptStudentStruct->scores[1],
                                stack->top->ptStudentStruct->scores[2],
                                stack->top->ptStudentStruct->scores[3]);
}

void destroyStack(stackHead* stack)
{
    stackNode* temp;
    
    printf("Destorying stack...\n");
    
    while (!stackEmpty(stack))
    {
        
        temp = stack->top;
            
        stack->top = stack->top->link;
        free(temp->ptStudentStruct);
        free(temp);
        stack->studentCount --;
        
    }
    
    free(stack);
    printf("Stack destroyed\n");
    return;
}


