#include <stdio.h>
#include <string.h>
#define HASHTABLESIZE 30

int MyHashFunction(char names[])
{
    int i, sum = 0;
    int length = strlen(names);
    for(i = 0; i < length; i++)
    {
        sum = sum + names[i];
    }
    return (sum % HASHTABLESIZE);
}

int main(void)
{
    char name[20];
    printf("Enter name ");
    scanf("%s", name);
    printf("The hash value for %s is %d\n", name, MyHashFunction(name));
    return 0;
}
