/******************************************************************************
myBST.c
Description: 
    creates a binary serach tree for a selection of students
    reads a file for the data and fills the tree
    prints the tree with inOrder processing
    searches the tree for 3 particular students and deletes them if found
        prints the updated tree if the studnt is deleted
    destroys the tree
    
Written by: Caleb Mueller
Start date:3/6/2023
End date:3/10/2023

WRITTEN IN OnlineGDB
*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


typedef struct studentStruct
{
    char lastName[25];
    char firstName[25];
    int scores[4];
}studentStruct;

typedef struct TREENODE
{
    studentStruct* ptStudentStruct;
    struct TREENODE* leftLink;
    struct TREENODE* rightLink;
}TREENODE;

typedef struct TREE
{
    int studentCount;
    TREENODE* root;
}TREE;


//FUNCTION DECLARATIONS
TREE* createTree();
//allocates memory for tree header, and initalizes the structure
void removeFirstLine(FILE* file);
//removes the first line of a file and discards it
int readStudentData(studentStruct* dataIn, FILE* file);
//reads in a single line from a formatted file and fills the dataIn structure
bool isTreeEmpty(TREE* tree);
//checks if the root of the tree exists
TREENODE* createTreeNode(studentStruct* data);
//allocates and initilizes a treenode
TREENODE* addToTree(TREENODE* subtreeRoot, TREENODE* node);
//adds the passed in tree node to the binary search tree
void fillStudentTree(TREE* tree, FILE* inFile);
//reads file line by line and creates and inserts tree nodes for every read in 
//line
void printStudentRecord(TREENODE* root);
//prints the entire tree
void printStudentData(studentStruct* student);
//prints out the data for the passed in data structure

/****************************FUNCTION IS REDUNDANT*****************************/
bool isLeaf(TREENODE* node);
//checks if the passed in tree node is a is a leaf
/****************************END OF REDUNDANT FUNCTION*************************/

TREENODE* searchAndDelete(TREE* tree, TREENODE* root, char goalFName[], 
                                                      char goalLName[]);
//searches the tree for the node contaiing the goal strings and deletes it and 
//adjusts the tree
TREENODE* destroySubTree(TREE* tree, TREENODE* node);
//destroys the passed in suptree and decremts the tree count accordingly
void destroyTree(TREE* tree);
//destroys the entire tree


int main()
{
    //Local Varibles
    FILE* inputFile;
    TREE* studentRecord;
    
    //opeing data file and removing header line
    inputFile = fopen("studentData.txt", "r");
    if(!inputFile)
    {
        printf("File not found\n");
        exit(404);
    }
    
    /*##########################################################################
    this is the statement that if un commented will make this program work
    and i truly have no clue why
    ##########################################################################*/
    //printf(".\n");
    removeFirstLine(inputFile);
    
    //Creating tree structure and filling it with students
    studentRecord = createTree();
    fillStudentTree(studentRecord, inputFile);
    
    //input file is no longer needed, so close it before i forget
    fclose(inputFile);
    
    //printing tree before deletion of students
    printf("The students in the tree are:\n\n");
    printStudentRecord(studentRecord->root);
    
    //looking for student that isnt in tree
    printf("Looking for Winston Curchill...\n");
    searchAndDelete(studentRecord, studentRecord->root, "Winston", "Churchill");
    
    //looking for student that is easily removed from tree, 
    //and printing updated tree
    printf("Looking for Thomas Pelham-Holles...\n");
    searchAndDelete(studentRecord, studentRecord->root, 
    "Thomas", "Pelham-Holles");
    printf("New tree looks like:\n\n");
    printStudentRecord(studentRecord->root);
    
    
    //looking for studnt that is an internal node with 2 children
    //and printing updated tree
    printf("Looking for Spencer Compton...\n");
    searchAndDelete(studentRecord, studentRecord->root, "Spencer", "Compton");
    printf("New tree looks like:\n\n");
    printStudentRecord(studentRecord->root);
    
    //emptying and destroying tree structure
    destroyTree(studentRecord);
    
    return 0;
}

/*
createTree
    allocates memory for tree
    intalizes values in tree header
Pre:
    none
Returns:
    pointer to head of created tree
*/
TREE* createTree()
{
    //Local Varibles
    TREE* tree;
    
    //Alloctaing memory for Tree
    tree = (TREE*)malloc(sizeof(TREE));
    
    //Exiting program if out of memory
    if(!tree)
    {
        printf("Tree failed to be created\n");
        exit(1);
    }
    
    //Intailizing tree 
    tree->studentCount = 0;
    tree->root = NULL;
    
    //alerting user
    printf("Tree successfully created.\n");
   
    return tree;
}

/*
removeFirstLine
    removes the first 500 characters or full line (whichever was reached first) 
    of a text file
Pre:
    pointer of file to have line removed
Returns: 
    none   
*/
void removeFirstLine(FILE* file)
{
    //Local Varibles
	// char* line;
	char* line = NULL;
	// char l[500];
    // char* line = &l[0];
	
    
    //Reading in the first 500 characters or until newline is reached
    
    /*##########################################################################
    this is the line that actually causes the segfault so long as "line" is
    a char pointer and not a char array
    ##########################################################################*/
    
	printf("[i] Message before fgets() \n");
	fgets(line, 500, file);
	printf("[i] Message after fgets() \n");
    
    
    
    //returning nothing so the read in line string is discarded
    return;
}

/*
readStudentData
attempts to read in data from file to passed in structure
Pre: file pointer to data file that contains data in format of:
name,name,number,number,number,number
Returns: data in structure by reference
         0 if there is data left, 1 if there is none
*/
int readStudentData(studentStruct* dataIn, FILE* file)
{
    //Local Varibles
    int countDataIn = 0;
    int countCharIn = 0;
    char workingString[25];
    char workingChar;
    int result;
    
    //keeping count of what data piece being read in
    for(countDataIn = 0; countDataIn<6; countDataIn++ )
    {
        countCharIn = 0;
        workingChar = fgetc(file);
        
        //attempting to read in data char by char until one of these is met
        while(workingChar != ',' && workingChar != '\n' && workingChar != EOF)
        {
           workingString[countCharIn] = workingChar;
           countCharIn++;
           workingChar = fgetc(file);
        }
        //adding string terminator to end of string
        workingString[countCharIn] = '\0';
        
        //first thing read in is last name, so copy it to last name
        if (countDataIn == 0)
        {
            if (workingString[0] != '\0')
            {
                strcpy(dataIn->lastName, workingString);
            }
            else
            {
                strcpy(dataIn->lastName, "none");
            }
        }
        //second thing is first name, so put it in first name
        else if (countDataIn == 1)
        {
            if (workingString[0] != '\0')
            {
                strcpy(dataIn->firstName, workingString);
            }
            else
            {
                strcpy(dataIn->firstName, "none");
            }
        }
        //last 4 things should be scores, so add them to array
        else 
        {
            if (workingString[0] != '\0')
            {
                //count is minus to to macth score index with data in count
                dataIn->scores[countDataIn - 2] = atoi(workingString);
            }
            else
            {
                dataIn->scores[countDataIn - 2] = -1;
            }
        }
    }
    
    //return is an int to later attempt to return a value if data collecetion failed
    if (workingChar == EOF)
    {
        result = 1;//retuns sentinal value for the end of the file
    }
    else
    {
       result = 0; 
    }
    
    return result;
}

/*
isTreeEmpty
    Checks if passed in tree header contains any nodes
Pre:
    pointer to tree hader to be checked
Returns:
   true if tree is empty
   false if tree contains data
*/
bool isTreeEmpty(TREE* tree)
{
    //Local Variables
    bool result;
    
    //checking if root is an actual data structure
    if (!tree->root)
    {
        result = true;
    }
    else
    {
        result = false;
    }

    return result;

}

/*
createTreeNode
    allocates memory for tree node
    inserts passed in data pointer to that node
    initalizes links to null, as all nodes are inserted as leaves
Pre:
    pointer to data structure to be inserted into node
Returns:
    pointer to made tree node
*/
TREENODE* createTreeNode(studentStruct* data)
{
    //Local Varibles
    TREENODE* node;
    
    //allocating memory for node
    node = (TREENODE*)malloc(sizeof(TREENODE));
    
    //exiting program if node could not be created
    if(!node)
    {
        printf("Node failed to be created.\n");
        exit(1);
    }
    
    //initilizing node 
    node->ptStudentStruct = data;
    node->leftLink = NULL;
    node->rightLink = NULL;
    
    return node;
}

/*
addToTree
    adds the node to the tree using recursive logic to traverse the tree
Pre:
    pointer to root of subtree to add root to
    node to be added
Returns:
    pointer to updated subtree
*/
TREENODE* addToTree(TREENODE* subtreeRoot, TREENODE* node)
{
    //if the root is empty, just return the root as the new subtree
    //this is actually adding the node
    if(!subtreeRoot)
    {
        return node;
    }
    //checking if the node should go down the left subtree branch
    else if (strcmp(subtreeRoot->ptStudentStruct->lastName, 
                    node->ptStudentStruct->lastName) 
                    > 0)
    {
        //updating the subtree by passing down the node to the left side
        //and returning the updated subtree
        subtreeRoot->leftLink = addToTree(subtreeRoot->leftLink, node);
        return subtreeRoot;
    }
    //if not being inserted or left branch it must be right
    else
    {
        //updating the subtree by passing the node to the right side
        //and returning the updated subtree
        subtreeRoot->rightLink = addToTree(subtreeRoot->rightLink, node);
        return subtreeRoot;
    }
    
}

/*
fillStudentTree
    allcocates memory for student data
    fills student data
    creates student node and adds it to the tree
    increments number of students in the tree
    alerts user for the student that has been added and the number of students 
        in the tree
Pre:
   the head of the tree to be filled
   the file pointer of the file that contains the data for the students
Returns:
    none
*/
void fillStudentTree(TREE* tree, FILE* inFile)
{
    //Local Varibles
    studentStruct* data;
    int outOfData;
    TREENODE* currStudent;
    
    //looping until out of data flag breaks the loop
    while(1)
    {
        //allocating memory for student struct
        data = (studentStruct*)malloc(sizeof(studentStruct));
        
        //checking if emeory was allocated
        if(!data)
        {
            printf("Failed to create student structure.\n");
            exit(1);
        }
        
        //filling data strcuture, and giving it to a tree node
        outOfData = readStudentData(data, inFile);
        currStudent = createTreeNode(data);
        
        //checking if tree is empty
        if(isTreeEmpty(tree))
        {
            //if tree is empty the first node is the root
            tree->root = currStudent;
        }
        else
        {
            //otherwise just add node to tree
            addToTree(tree->root, currStudent);
        }
        
        //incrementing student count
        tree->studentCount++;
        
        //alerting user who was added to tree and how many students there are
        printf("Added %s %s ==> Student count is %d\n\n", 
        currStudent->ptStudentStruct->firstName, 
        currStudent->ptStudentStruct->lastName, 
        tree->studentCount);
        
        //breaking loop if entire file has been read
        if(outOfData == 1)
        {
            printf("File has been processed\n");
            break;
        }
        
    }
    
    return;
}

/*
printStudentRecord
    prints the entire student recored traversing inOrder
Pre:
   head of the tree to be printed 
Returns:
    nothing
*/
void printStudentRecord(TREENODE* root)
{
    //if theres stuff on the left, print it first
    if (root->leftLink != NULL)
    {
        printStudentRecord(root->leftLink);
    }
    
    //printing the data of the current node
    printStudentData(root->ptStudentStruct);
    
    //after you print the current node print all the right nodes
    if (root->rightLink != NULL)
    {
        printStudentRecord(root->rightLink);
    }
    
    return;
}

/*
printStudentData
    prints the data structure for one student
Pre:
    data strcuture to be printed
Returns:
    nothing
*/
void printStudentData(studentStruct* student)
{
    //printing the students first and last name
    printf("%s %s\n",   student->firstName, 
                        student->lastName);
        
    //printing scores
    printf("%11s%11s%11s%11s\n", "Mathematics", "Science", "Latin","Greek");
    
    for (int i=0 ; i<4; i++)
    {
        //checking if the score exists with the sentinal value
        if(student->scores[i] == -1)
        {
            //if the score doesnt exist print that it doesnt
            printf("%11s", "n/a");
        }
        else
        {
            //otherwise print the score
            printf("%11d", student->scores[i]);
        }
    }
    printf("\n\n");
}

/*
isLeaf
    checks if passed in tree node is a leaf
Pre:
    node to be checked
Returns:
    true if node is leaf, 
    false if node is not leaf
    
THIS FUNCTION IS NEVER USED, BUT I LIKE IT SO IM KEEPING IT
*/
bool isLeaf(TREENODE* node)
{
    //Local Varibles
    bool result = false;
    
    //if the two links are null, the node is a leaf
    if ((node->leftLink == NULL) &&(node->rightLink == NULL))
    {
        result = true;
    }
    return result;
}

/*
searchAndDelete
    searches for enetered name and deleted node containg that name if found
Pre:
    tree header
    root of subtree to be searched
    first name to be searched
    last name to be searched
Returns:
    updated subtree
*/
TREENODE* searchAndDelete(TREE* tree, TREENODE* root, char goalFName[], 
                                                      char goalLName[])
{
    //Local Varibles
    TREENODE* dltNode;
    TREENODE* newRoot;
    TREENODE* swapNode;
    studentStruct* swapData;
    
    //base case of node not being found
    if (!root)
    {
        printf("%s %s not found.\n", goalFName, goalLName);
        return root;//returning root so no subtrees are updated in the recursion
    }
    
    //checking if goal node shoul be on the right of the current node
    else if(strcmp(goalLName, root->ptStudentStruct->lastName) > 0)
    {
        /*updating subtree with new subtree (so that no links are lost)
        this is needed because if the next node is the node to be removed, 
        the link needs to be set to null*/
        root->rightLink = searchAndDelete(tree, root->rightLink, 
                                          goalFName, goalLName);
    }
    
    //checking if goal node should be on the left of current node
    else if (strcmp(goalLName, root->ptStudentStruct->lastName) < 0)
    {
        /*updating subtree with new subtree (so that no links are lost)
        this is needed because if the next node is the node to be removed, 
        the link needs to be set to null*/
        root->leftLink = searchAndDelete(tree, root->leftLink, 
                                         goalFName, goalLName);
    }
    
    //if none of the above trigger, the last names of the current node and the 
    //search key matches
    else
    {
        //checking if the first names match so node can be deleted
        if (strcmp(goalFName, root->ptStudentStruct->firstName) == 0)
        {
            //holding the node to be deleted for free commands later
            dltNode = root;
            
            //checking if the node has no left child, for leaf and 
            //only right child cases
            if(!root->leftLink)
            {
                //say that you found the node
                printf("%s %s found.", goalFName, goalLName);
                printf("   ...removing %s %s\n", goalFName, goalLName);
                
                //setting the new root to the right child, to not lose subtrees
                newRoot = root->rightLink;
                
                //freeing the memory
                free (dltNode->ptStudentStruct);
                free(dltNode);
                tree->studentCount--;
                
                //alerting the user to new count
                printf("There are now %d students in the tree\n", 
                tree->studentCount);
                
                //returning updated subtree
                return newRoot;
                
            }
            
            //checking if theres no right child and (implicit) is a left child
            else if (!root->rightLink)
            {
                //say that you found the node
                printf("%s %s found.", goalFName, goalLName);
                printf("   ...removing %s %s\n", goalFName, goalLName);
                
                //setting the new root to the right child, to not lose subtrees
                newRoot = root->leftLink;
                
                //freeing the memory
                free (dltNode->ptStudentStruct);
                free(dltNode);
                tree->studentCount--;
                
                //alerting the user to new count
                printf("There are now %d students in the tree\n", 
                tree->studentCount);
                
                //returning updated subtree
                return newRoot;
            }
            
            //case where node has two children
            else
            {
                //largest node on left subtree will be swapped for the node to 
                //be deleted, so that the above deletion cases work
                swapNode = root->leftLink;
                
                //traversing the left subtree for the rightmost (largest) child
                while(swapNode->rightLink)
                {
                    swapNode = swapNode->rightLink;
                }
                
                //swap the data of the current node and the largest left node
                swapData = root->ptStudentStruct;
                root->ptStudentStruct = swapNode->ptStudentStruct;
                swapNode->ptStudentStruct = swapData;
                
                /*deleting the node after the swap, will eventually become
                one of the above cases 
                as the largest node on the left subtree must be a leaf*/
                root->leftLink = searchAndDelete(tree, root->leftLink, 
                                                 goalFName, goalLName);
                
            }
        }
        //if first names dont match, move to the right and keep checking
        else
        {
            root->rightLink = searchAndDelete(tree, root->rightLink, 
                                          goalFName, goalLName);
        }
    }
    
    return root;
}

/*
destroySubTree
    traverses the tree postorder and if the node is a leaf, deletes it
Pre:
    head of the tree so that count can be updaded
    root of subtree to be deleted
Returns:
    TREENODE that is null 
    
*/
TREENODE* destroySubTree(TREE* tree, TREENODE* node)
{
    //checking if left subtree exists and destroying it first
    if(node->leftLink != NULL)
    {
        node->leftLink = destroySubTree(tree, node->leftLink);
    }
    
    //checking if right subtree exists and destroying it first
    if(node->rightLink != NULL)
    {
       node->rightLink = destroySubTree(tree, node->rightLink);
    }
    
    //alerting the user that current node is about to be deleted
    printf("Now deleteing student %d: %s %s\n", tree->studentCount, 
    node->ptStudentStruct->firstName, node->ptStudentStruct->lastName);
    
    //freeing the memory
    free(node->ptStudentStruct);
    free(node);
    tree->studentCount--;
    
    return NULL;
}

/*
destroyTree
    destroys the tree containing all the students
Pre:
    head of tree to be destroyed
Returns:
    nothiing
*/
void destroyTree(TREE* tree)
{
    //alerting the user
    printf("Deleting students\n");
    
    //if the tree contains students in the first place, delete them
    if(!isTreeEmpty(tree))
    {
        //destroying the subtree that is the 
        tree->root = destroySubTree(tree, tree->root);
    }
    
    //making sure the tree now has no students before destorying the header
    printf("Checking if tree is empty\n");
    if (isTreeEmpty(tree))
    {
        printf("Tree is empty\n");
    }
    else
    {
        printf("Tree failed to be emptied... exiting program\n");
        exit(1);
    }
    
    //freeing the header
    printf("Destroying tree...\n");
    free(tree);
    printf("Tree destroyed\n");
    
    return;
}