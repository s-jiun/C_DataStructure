#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 10
#define SWAP(x, y, t) ((t) = (x), (x) = (y), (y) = (t))

int list[MAX_SIZE];
int n;

void bubble_sort(int list[], int n)
{
    int i, j, temp, isChanged;
    for (i = n - 1; i > 0; i--)
    {
        isChanged = 0;
        for (j = 0; j < i; j++)
        {
            if (list[j] > list[j + 1])
            {
                SWAP(list[j], list[j + 1], temp);
                isChanged = 1;
            }
        }
        if (!isChanged)
            break;
    }
}

int main()
{
    int i;
    srand(time(NULL));
    for (i = 0; i < MAX_SIZE; i++)
        list[i] = rand() % 100;

    bubble_sort(list, MAX_SIZE);
    for (i = 0; i < MAX_SIZE; i++)
        printf("%d ", list[i]);
    printf("\n");

    return 0;
}