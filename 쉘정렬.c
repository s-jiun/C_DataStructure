#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 10
#define SWAP(x, y, t) ((t) = (x), (x) = (y), (y) = (t))

int list[MAX_SIZE];
int n;

inc_insertion_sort(int list[], int first, int last, int gap)
{
    int i, j, key;
    for (i = first + gap; i <= last; i = i + gap)
    {
        key = list[i];
        for (j = i - gap; j >= first && key < list[j]; j = j - gap)
        {
            list[j + gap] = list[j];
        }
        list[j + gap] = key;
    }
}

void shell_sort(int list[], int size)
{
    int i, gap;
    for (gap = size / 2; gap > 0; gap = gap / 2)
    {
        if ((gap % 2) == 0)
            gap++;
        for (i = 0; i < gap; i++) // 부분리스트의 개수 = gap
            inc_insertion_sort(list, i, size - 1, gap);
    }
}

int main()
{
    int i;
    srand(time(NULL));
    for (i = 0; i < MAX_SIZE; i++)
        list[i] = rand() % 100;

    shell_sort(list, MAX_SIZE);
    for (i = 0; i < MAX_SIZE; i++)
        printf("%d ", list[i]);
    printf("\n");

    return 0;
}