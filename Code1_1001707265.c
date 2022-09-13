#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

typedef struct node
{
    int number;
    struct node *next_ptr;
}
NODE;

void AddNodeToLL(int Number, NODE **LinkedListHead)
{  
   NODE *NewNode;
   NewNode = malloc(sizeof(NODE));
   NewNode->number = Number;
   NewNode->next_ptr = NULL;
  
   if(*LinkedListHead == NULL)
       *LinkedListHead = NewNode;       
   else
   {
       NODE *lastNode = *LinkedListHead;      
       while(lastNode->next_ptr != NULL)
       {
          lastNode = lastNode->next_ptr;
       }      
       lastNode->next_ptr = NewNode;
   }
}

void ReadFileIntoLL(int argc,  char *argv[], NODE **LLH)
{
    int line = 0;
    int sum = 0;
    int valu = 0;
    char fname[100];
    char stRead[1000];
   
    FILE *pfile = NULL;
    if(argc == 2)
    {
        strcpy(fname, argv[1]);
        pfile = fopen(fname, "r");
    }
    else
    {
        printf("File must be provided on command line...exiting \n");
        exit(0);
    }
          
    while (fgets(stRead, sizeof(stRead), pfile))
    {
        valu = atoi(stRead);
        AddNodeToLL(valu, LLH);
        sum += atoi(stRead);
        line++;
    }
    printf("\n%d records were read for a total sum of %d \n" ,line,sum);  
    fclose(pfile);
}

void PrintLL(NODE *LLH)
{
    int sumfree = 0;
    int linefree = 0;   
    while (LLH != NULL)
      {
         sumfree += LLH->number;
         linefree++;
         printf("\n%p %d %p\n", LLH, LLH->number, LLH->next_ptr);
         LLH = LLH -> next_ptr;
         
      }
      printf("\n%d records were read for a total sum of %d \n" ,linefree,sumfree);
}

void FreeLL(NODE **LLH)
{
    NODE* current = *LLH;
    NODE* next_ptr;
    int sumfreeing = 0;
    int linefreeing = 0;     

    while (current != NULL)
    {
        next_ptr = current->next_ptr;
        #ifdef PRINT
        printf("\nFreeing %p %d %p\n", current, current->number, current->next_ptr);
        #endif
        sumfreeing += current->number;
        linefreeing++;
        free(current);
        current = next_ptr;           
    }
    printf("\n%d records were deleted for a total sum of %d \n" ,linefreeing,sumfreeing);

    *LLH = NULL;
}
   
int main(int argc, char *argv[])
{
    NODE *LLH = NULL;
    clock_t start, end;
     
    /* capture the clock in a start time */
    start = clock();
    ReadFileIntoLL(argc, argv, &LLH);
    end = clock();
    /* capture the clock in an end time */
    printf("\n%ld ticks to write the file into the linked list\n", end-start);
   
    #ifdef PRINT
    /* capture the clock in a start time */
    start = clock();
    PrintLL(LLH);
    end = clock();
    /* capture the clock in an end time */
    printf("\n%ld ticks to print the linked list\n", end-start);
    #endif
      
    /* capture the clock in a start time */
    start = clock();
    FreeLL(&LLH);
    end = clock();
    /* capture the clock in an end time */
    printf("\n%ld ticks to free the linked list\n", end-start);
   
    return 0;
   
}
