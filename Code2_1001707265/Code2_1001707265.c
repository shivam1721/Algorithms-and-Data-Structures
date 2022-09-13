//Name: Shivam Patel
//ID: 1001707265
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

void merge(int arr[], int left, int middle, int right)
{
    int i, j, k;
    int n1 = middle -left + 1;
    int n2 = right -middle;
    int L[n1], R[n2];
    for (i= 0; i< n1; i++)
    {
        L[i] = arr[left + i];
    }
        for (j = 0; j < n2; j++)
    {
        R[j] = arr[middle + 1 + j];
    }
    i= 0;
    j = 0; 
    k = left;    
    while (i< n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i]; 
            i++;
        }
        else
        {
            arr[k] = R[j]; 
            j++;            
        }
        k++;        
    }
    while (i< n1)
    {
        arr[k] = L[i];
        i++;
        k++;        
    }
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;        
    }
}

void mergeSort(int arr[], int L, int R)
{
    if (L < R)
    {
        int M = (L+R)/2;
        mergeSort(arr, L, M);
        mergeSort(arr, M+1, R);
        merge(arr, L, M, R);       
    }    
}

void insertionSort(int arr[], int n)
{
    int i, key, j;
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

void printArray(int A[], int size)
{
    int i;
    for (i = 0; i < size; i++)
    {
       printf("%d\n", A[i]);
    }            
}

int ReadFileIntoLL(int argc,  char *argv[], int **AP)
{
    int line = 0;
    char fname[100];
    int i = 0;
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
    return line;
    fclose(pfile);       
}
 
int main(int argc, char *argv[])
{
    int *AP = NULL;
    clock_t start, end;
    printf("Merge Sort \n");
    int elements = ReadFileIntoLL(argc, argv, &AP);
    #ifdef PRINTARRAY
    printArray(AP, elements);
    #endif
    start = clock();
    mergeSort(AP,0,elements-1);
    end = clock();
    printf("Merge Sort ticks  = %ld\n", end-start);
    #ifdef PRINTARRAY
    printArray(AP, elements);
    #endif
    free(AP);
    printf("\n");
    printf("Insertion Sort \n");  
    ReadFileIntoLL(argc, argv, &AP);
    #ifdef PRINTARRAY
    printArray(AP, elements);
    #endif
    start = clock();
    insertionSort(AP,elements);
    end = clock();
    printf("Insertion Sort ticks  = %ld\n", end-start);
    #ifdef PRINTARRAY
    printArray(AP, elements);
    #endif
    free(AP);
    return 0;
}
	
	
	

