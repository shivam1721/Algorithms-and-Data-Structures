// Name: Shivam Patel
// ID: 1001707265
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#define MAX 50

typedef struct
{
    char label[5];
    int distance;
    int previous;
    int visited;
}
Vertex;

void PrintArr(Vertex VertexArray[MAX], int VertexCount)
{
    #ifdef PRINTIT
    int i, j;
    printf("\n\nI\tL\tD\tP\tV\n");
    for (i = 0; i < VertexCount; i++)
    {
        printf("%d\t%s\t%d\t%d\t%d\n", i, VertexArray[i].label, VertexArray[i].distance, VertexArray[i].previous, VertexArray[i].visited);
    }
    printf("\n");
    #endif
}

void Dijkstra(Vertex VertexArray[], int AdjMatrix[MAX][MAX], int StartVertex, int VertexCount)
{
    int x, i;
    int CurrentVertex = StartVertex;  
    VertexArray[StartVertex].distance = 0;
    VertexArray[StartVertex].previous = -1;
    VertexArray[StartVertex].visited = 1;
    for (x = 0; x < VertexCount-1; x++)
    {
        for(i = 0; i < VertexCount; i++)
        {            
            if (AdjMatrix[CurrentVertex][i] != -1 && !VertexArray[i].visited)
            {
                if (VertexArray[CurrentVertex].distance + AdjMatrix[CurrentVertex][i] < VertexArray[i].distance)
                {
                    VertexArray[i].distance = VertexArray[CurrentVertex].distance + AdjMatrix[CurrentVertex][i];
                    VertexArray[i].previous = CurrentVertex;                    
                }
            }
        }
        int SmallestVertexIndex = -1;
        int SmallestVertex = INT_MAX;
        for(i = 0; i < VertexCount; i++)
        {
            if (!VertexArray[i].visited)
            {
                if (VertexArray[i].distance < SmallestVertex)
                {
                    SmallestVertex = VertexArray[i].distance;
                    SmallestVertexIndex = i;
                }
            }
        }
        CurrentVertex = SmallestVertexIndex;
        VertexArray[CurrentVertex].visited = 1;                                      
    }
}

int GetIndex(Vertex VertexArray[MAX], char vertexStartLabel[5], int VertexCount)
{
    int i; 
    for(i = 0; i < VertexCount; i++)
    {
        if(strcmp(VertexArray[i].label, vertexStartLabel) == 0)
            return i;           
    }
}

void addEdge(int VertexCount, int start, int end, int AdjMatrix[][MAX])
{
    AdjMatrix[VertexCount][start] = end;         
}

void addVertex(char label[], Vertex VertexArray[], int *VertexCount)
{
    VertexArray[*VertexCount].distance = INT_MAX;
    VertexArray[*VertexCount].previous = -1;
    VertexArray[*VertexCount].visited = 0;
    strcpy(VertexArray[*VertexCount].label, label);
    (*VertexCount)++;
}

void PrintVal(int AdjMatrix[MAX][MAX], int VertexCount)
{
    #ifdef PRINTIT
    int i, j;
    printf("\n");
    for (i = 0; i < VertexCount; i++)
    {
        for (j = 0; j < VertexCount; j++)
            printf("%5d\t", AdjMatrix[i][j]);
        printf("\n");
    }
    #endif
}

int ReadFileIntoLL(int argc,  char *argv[], Vertex VertexArray[MAX], int AdjMatrix[MAX][MAX])
{
    int VertexCount = 0, next, weight;
    char fname[100];
    FILE *pfile;
    char *token;
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
    while (fgets(fname, sizeof(fname)-1, pfile))
    {
        if(fname[strlen(fname)-1] == '\n')
            token = strtok(fname, ",");
        else
            token = strtok(fname, ",");
        addVertex(token, VertexArray, &VertexCount);
        token = strtok(NULL, ",");
        while (token != NULL)
        {
            next = atoi(token);
            token = strtok(NULL, ",");
            weight = atoi(token);
            addEdge(VertexCount-1, next, weight, AdjMatrix);
            token = strtok(NULL, ",");
        }
    }
    fclose(pfile);
    return VertexCount;
}

int main(int argc, char *argv[]) 
{    
    int i,j,k,VertexCount = 0, StartVertex = 0, destindex = -1, pathindex = -1, previndex = -1;
    int AdjMatrix[MAX][MAX];
    Vertex VertexArray[MAX];
    int arra[MAX];
    char vertexStartLabel[5], vertexEndLabel[5], path[5];
    for(i = 0; i < MAX; i++)
    {
        for(j = 0; j < MAX; j++)
        {
            AdjMatrix[i][j] = -1;
        }
    }
    VertexCount = ReadFileIntoLL(argc, argv, VertexArray, AdjMatrix);
    PrintVal(AdjMatrix, VertexCount);   
    printf("\nWhat is the starting vertex? ");
    scanf(" %s", vertexStartLabel);
    StartVertex = GetIndex(VertexArray, vertexStartLabel, VertexCount);
    Dijkstra(VertexArray, AdjMatrix, StartVertex, VertexCount);
    PrintArr(VertexArray, VertexCount);    
    printf("\nWhat is the destination vertex? ");
    scanf(" %s", vertexEndLabel);     
    return 0;
}






