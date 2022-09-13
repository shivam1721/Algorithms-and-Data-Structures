// Coding Assignment 5 - Shivam Patel - 10001707265

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
 
#define HASHTABLESIZE 35
 
typedef struct Fifa21
{
    char *name;
    int fifa_id;
    char *country;
    char *club;
    float height;
    int rating;
    char workrate;
    char *position;
    struct Fifa21 *next_ptr;
}
FIFA21;
 
int MyHashFunction(char *names)
{
    int i, sum = 0;
    int length = strlen(names);
    for(i = 0; i < length; i++)
    {
        sum = sum + names[i];
    }
    return (sum % HASHTABLESIZE);
}

void AddNode(FIFA21 *NewNode, FIFA21 *Fifa21[])
{
    int HashIndex = MyHashFunction(NewNode->name);
    if (Fifa21[HashIndex] == NULL) 
    {
        #if PRINTINSERT
	printf("\nInserting %s at index %d\n", NewNode->name, HashIndex);
	#endif
	Fifa21[HashIndex] = NewNode;
    }
    else    
    {
	FIFA21 *TempPtr = Fifa21[HashIndex];
	while (TempPtr->next_ptr != NULL) 
	{
	    TempPtr = TempPtr->next_ptr;
	}
	TempPtr->next_ptr = NewNode;
	#if PRINTINSERT
	printf("\nInserting %s at index %d\n", NewNode->name, HashIndex);
	#endif
    }
}

void FreeDynamicMemory(FIFA21 *Fifa21[])
{
    FIFA21 *TempPtr = NULL, *NextPtr = NULL;
	
    for (int i = 0; i < HASHTABLESIZE; i++)
    {
	TempPtr = Fifa21[i];
 
	if (TempPtr != NULL) 
	{
	    while (TempPtr != NULL) 
	    {
		free(TempPtr->name);
		free(TempPtr->country);
		free(TempPtr->club);
		NextPtr = TempPtr->next_ptr;
		free(TempPtr);
		TempPtr = NextPtr;
	    }	
	}
    }
}

int DeleteNode(FIFA21 *Fifa21[])
{
    char LookupName[100] = {};
    int result = 0;
	
    printf("Enter the name of the Player to delete from the Fifa21 ");
    fgets(LookupName,100, stdin);
    fgets(LookupName, sizeof(LookupName)-1, stdin);
    LookupName[strlen(LookupName)-1] = '\0';

    int HashIndex = MyHashFunction(LookupName);

    FIFA21 *TempPtr = Fifa21[HashIndex];
    FIFA21 *PrevPtr = NULL;
 
    if (TempPtr == NULL) 
    {
        printf("\n\nPlayer %s does not exist in the Fifa21\n\n", LookupName);
	result = 0;
    }
    else 
    {
	while (TempPtr != NULL) 
	{
	    if (strcmp(TempPtr->name, LookupName) == 0)
	    {
		if (TempPtr == Fifa21[HashIndex])
		{
		    Fifa21[HashIndex] = TempPtr->next_ptr;
		    printf("\nPlayer %s has been deleted from the Fifa21\n\n", TempPtr->name);
		    free(TempPtr);
		    TempPtr = NULL;
		}
		else
		{
		    PrevPtr->next_ptr = TempPtr->next_ptr;
		    printf("\nPlayer %s has been deleted from the Fifa21\n\n", TempPtr->name);
		    free(TempPtr);
		    TempPtr = NULL;
		}
		result = 1;
	    }
	    else
	    {
		PrevPtr = TempPtr;
		TempPtr = TempPtr->next_ptr;
	    }
	}
	if (result == 0)
	{
	    printf("\n\nPlayer %s does not exist in the Fifa21\n\n", LookupName);
	}
    }
    return result;
}

void DisplayHashTable(FIFA21 *Fifa21[])
{
    int i;
    FIFA21 *TempPtr = NULL;
	
    for (i = 0; i < HASHTABLESIZE; i++) 
    {
        TempPtr = Fifa21[i];

	printf("\nFifa21[%d]-", i);
		
	if (TempPtr != NULL) 
        {
	    while (TempPtr != NULL)
            {
	        printf("%s|", TempPtr->name);
	        TempPtr = TempPtr->next_ptr;
            }
	}
    }
}

void ShowByLetter(FIFA21 *Fifa21[])
{
    int i;
    FIFA21 *TempPtr = NULL;
    char LookupLetter = 'A';

    printf("\n\nEnter a letter of the alphabet ");
    scanf(" %c", &LookupLetter);
    LookupLetter = toupper(LookupLetter);

    for (i = 0; i < HASHTABLESIZE; i++) 
    {
        TempPtr = Fifa21[i];

	if (TempPtr != NULL) 
        {
	    while (TempPtr != NULL)
            {
		if (toupper(TempPtr->name[0]) == LookupLetter)
		{
		    printf("%s\n", TempPtr->name);
		}
		TempPtr = TempPtr->next_ptr;
	    }
	}
    }
}

void ShowByName(FIFA21 *Fifa21[])
{
    FIFA21 *TempPtr = NULL;
    char height[10] = {};
    char LookupName[100] = {};
    int FoundIt = 0;
	
    printf("\n\nEnter Players's name ");
    fgets(LookupName,100, stdin);
    fgets(LookupName, sizeof(LookupName)-1, stdin);
    LookupName[strlen(LookupName)-1] = '\0';	
		
    #if TIMING
    clock_t start, end;
    start = clock();
    #endif
    for (int i = 0; i < HASHTABLESIZE; i++) 
    {
	TempPtr = Fifa21[i];

	if (TempPtr != NULL) 
        {
	    while (TempPtr != NULL)
            {
		if (strcmp(TempPtr->name, LookupName) == 0)
		{
		    #if TIMING
		    end = clock();
		    printf("\n\nSearch took %ld tics\n\n", end-start);
		    #endif

		    FoundIt = 1;
		    printf("\n\n%s\n", TempPtr->name);
					
		    printf("Height\t\t");
		    sprintf(height, "%.2f", TempPtr->height);
		    for (int i = 0; i < strlen(height); i++)
		    {
		        if (height[i] == '.')
			{
			    printf(".");
			}
			else
			{
			    printf("%c", height[i]);
			}
		    }
		    printf("\n");
		    printf("Country\t\t%s\n", TempPtr->country);
		    printf("Club\t\t%s\n", TempPtr->club);					
		    if (TempPtr->workrate == 'H')
			printf("Workrate\tH\n");
		    else if (TempPtr->workrate == 'L')
			printf("Workrate\tL\n");
		    else
			printf("Workrate\t%c\n", TempPtr->workrate);					
		    printf("Position\t%s\n", (TempPtr->position));

		}
		TempPtr = TempPtr->next_ptr;
	    }
	}
    }
	
    if (FoundIt == 0)
    printf("\n\nPlayer %s not found in Fifa21\n\n", LookupName);
}

void AddNewPlayer(FIFA21 *Fifa21[])
{
    int HashIndex = 0;
    FIFA21 *NewNode;
    char TempBuffer[100] = {};

    NewNode = malloc(sizeof(FIFA21));
    NewNode->next_ptr = NULL;

    fgets(TempBuffer, sizeof(TempBuffer)-1, stdin);
	
    printf("\n\nEnter new Player's name ");
    fgets(TempBuffer, sizeof(TempBuffer)-1, stdin); 
    TempBuffer[strlen(TempBuffer)-1] = '\0';
    NewNode->name = malloc(strlen(TempBuffer)*sizeof(char)+1);
    strcpy(NewNode->name, TempBuffer);
	
    printf("\n\nEnter %s's fifa_id ", NewNode->name);
    scanf("%d", &(NewNode->fifa_id));
	
    fgets(TempBuffer, sizeof(TempBuffer)-1, stdin);
	
    printf("\n\nEnter %s's country ", NewNode->name);
    fgets(TempBuffer, sizeof(TempBuffer)-1, stdin); 
    TempBuffer[strlen(TempBuffer)-1] = '\0';
    NewNode->country = malloc(strlen(TempBuffer)*sizeof(char)+1);
    strcpy(NewNode->country, TempBuffer);

    printf("\n\nEnter %s's club ", NewNode->name);
    fgets(TempBuffer, sizeof(TempBuffer)-1, stdin);
    TempBuffer[strlen(TempBuffer)-1] = '\0';	
    NewNode->club = malloc(strlen(TempBuffer)*sizeof(char)+1);
    strcpy(NewNode->club, TempBuffer);

    printf("\n\nEnter %s's height as cm ", NewNode->name);
    scanf("%f", &(NewNode->height));
	
    printf("\n\nEnter %s's rating ", NewNode->name);
    scanf("%d", &(NewNode->rating));
		
    printf("\n\nEnter %s's workrate (H/M/L) ", NewNode->name);
    scanf(" %c", &(NewNode->workrate));
    NewNode->workrate = toupper(NewNode->workrate);
		
    fgets(TempBuffer, sizeof(TempBuffer)-1, stdin);
	
    printf("\n\nEnter %s's position ", NewNode->name);
    fgets(TempBuffer, sizeof(TempBuffer)-1, stdin);
    TempBuffer[strlen(TempBuffer)-1] = '\0';	
    NewNode->position = malloc(strlen(TempBuffer)*sizeof(char)+1);
    strcpy((NewNode->position), TempBuffer); 
	
    AddNode(NewNode, Fifa21);
}

int ReadFileIntoHashTable(int argc, char *argv[], FIFA21 *Fifa21[])
{
    FILE *FH = NULL;
    char FileLine[100] = {};
    char *token = NULL;
    int counter = 0;
    int HashIndex = 0;
    FIFA21 *NewNode;

    if (argc > 1)
    {
	FH = fopen(argv[1], "r");

	if (FH == NULL)
	{
	    perror("Exiting ");
	    exit(0);
	}		
	while (fgets(FileLine, sizeof(FileLine)-1, FH))
        {
	    token = strtok(FileLine, "|");

	    NewNode = malloc(sizeof(FIFA21));
	    NewNode->next_ptr = NULL;
			
	    NewNode->name = malloc(strlen(token)*sizeof(char)+1);
	    strcpy(NewNode->name, token);
			
	    token = strtok(NULL, "|");
	    NewNode->fifa_id = atoi(token);
			
	    token = strtok(NULL, "|");
	    NewNode->country = malloc(strlen(token)*sizeof(char)+1);
	    strcpy(NewNode->country, token);

	    token = strtok(NULL, "|");
	    NewNode->club = malloc(strlen(token)*sizeof(char)+1);
	    strcpy(NewNode->club, token);

	    token = strtok(NULL, "|");
	    NewNode->height = atof(token);
			
	    token = strtok(NULL, "|");
	    NewNode->rating = atoi(token);
			
	    token = strtok(NULL, "|");
	    NewNode->workrate = *token;
			
	    token = strtok(NULL, "|");
	    NewNode->position = malloc(strlen(token)*sizeof(char)+1);
	    strcpy(NewNode->position, token);

	    AddNode(NewNode, Fifa21);

	    counter++;
        }
    }
    else
    {
        printf("File must be provided on command line...exiting\n");
        exit(0);
    }	
    fclose(FH);	
    return counter;
}

int main(int argc, char *argv[]) 
{
    int MenuChoice = 0;
    int counter = 0;
    FIFA21 *Fifa21[HASHTABLESIZE] = {};

    enum Menu {SHOWBYLETTER=1, SHOWBYNAME, COUNT, DISPLAY, ADD, DELETE, EXIT};
 
    counter = ReadFileIntoHashTable(argc, argv, Fifa21);
 
    do
    {
        printf("\n\nFifa21 Menu\n\n"
	       "1. Show all Players in Fifa21 for a given letter\n"
	       "2. Look up FIfa Player by name\n"
	       "3. How many Players are in the Fifa21?\n"
	       "4. Display the Fifa21 Players\n"
	       "5. Add a new Player\n"
	       "6. Delete a Player from the Fifa21\n"
	       "7. Exit\n\n"
	       "Enter menu choice ");
	
	scanf("%d", &MenuChoice);
	printf("\n\n");

	switch (MenuChoice)
	{	
	    case SHOWBYLETTER:
		ShowByLetter(Fifa21);
	        break;
	    case SHOWBYNAME:
		ShowByName(Fifa21);
		break;
	    case COUNT:
		printf("Your Fifa21 contains %d Players\n", counter); 
		break;
 	    case DISPLAY:
		DisplayHashTable(Fifa21);
		break;
	    case ADD:
		AddNewPlayer(Fifa21);
		counter++;
		break;
	    case DELETE:
		if (DeleteNode(Fifa21))
		{
		    counter--;
		}
		break;
	    case EXIT:
		break;
	    default : 
		printf("Invalid menu choice\n\n"); 
	}
    }
    while (MenuChoice != EXIT);
	
    FreeDynamicMemory(Fifa21);

    return 0;
}			  
