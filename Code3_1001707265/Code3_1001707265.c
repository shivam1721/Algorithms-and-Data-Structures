//Name: Shivam Patel
//ID: 1001707265
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

void PrintArray(int ArrayToPrint[], int SizeAP)
{
    int i;
    for(i = 0; i < SizeAP; i++)
        printf("%d\n", ArrayToPrint[i]);   
}

void swap(int *SwapA, int *SwapB)
{
    int temp = *SwapA;
    *SwapA= *SwapB;
    *SwapB= temp;   
}

int partition (int A[], int low, int high)
{
    #if QSM
    int middle = (high+low)/2;
    swap(&A[middle], &A[high]);
    #elif QSRND
    int random = (rand() % (high-low+1)) + low;
    swap(&A[random], &A[high]);
    #endif
    int pivot = A[high];
    int i, j = 0;
    i = (low - 1);
    for (j = low; j < high; j++)
    {
        if (A[j] < pivot)
        {
            i++;
            swap(&A[i], &A[j]);        
        }        
    }
    swap(&A[i+ 1], &A[high]);
    return (i+ 1);    
}

void QuickSort(int A[], int low, int high)
{
    if (low < high)
    {
        int ndx = partition(A, low, high);
        QuickSort(A, low, ndx - 1);
        QuickSort(A, ndx + 1, high);        
    }    
}

int ReadFileIntoLL(int argc,  char *argv[], int **AP)
{
    int line = 0;
    char fname[100];
    int i = 0;
    FILE *pfile = NULL;
    if(argc == 3)
    {
        strcpy(fname, argv[1]);
        pfile = fopen(fname, "r");
    }
    else if(argc == 2)
    {
        strcpy(fname, argv[1]);
        pfile = fopen(fname, "r");
    }
    else
    {
        printf("File must be provided on command line...exiting \n");
        exit(0);
    }           
    while (fgets(fname, sizeof(fname), pfile))
    {
        line++;
    }   
    fseek(pfile,0,SEEK_SET);      
    *AP = malloc(line * sizeof(int));    
    while (fgets(fname, sizeof(fname), pfile))
    {
        (*AP) [i] = atoi(fname);
        i++;
    }
    fclose(pfile);       
    return line;
}
 
int main(int argc, char *argv[])
{
    int *AP = NULL;
    clock_t start, end;
    int i,s;
    long sum = 0;
    int elements;
    char read_ele[20] = {};    
    if(argc == 3)
    {
        strcpy(read_ele, argv[2]);
        s = atoi(argv[2]);
    }
    else
    {
        printf("Number of runs not specified on command line....defaulting to 10\n");
        s = 10;
    }
    for(i = 0; i < s; i++)
    {
        elements = ReadFileIntoLL(argc, argv, &AP);
        #ifdef PRINTARRAY
        PrintArray(AP,elements);
        printf("\n");
        #endif
        start = clock();
        QuickSort(AP,0,elements-1);
        end = clock();
        printf("Run %d complete : %ld ticks\n",i+1,end-start);
        sum += (end-start);
        #ifdef PRINTARRAY
        PrintArray(AP,elements);
        printf("\n");
        #endif
        free(AP);
    }   
    printf("The average runtime for %d ticks is %ld \n",i,sum/s);  
    printf("\n");
    printf("\n");
    printf("Processed %d records\n",elements);        
    return 0;
}
	
	
	

