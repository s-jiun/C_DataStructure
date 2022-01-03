#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICE 100
#define INF 100000

typedef struct GraphType
{
    int n;
    int weight[MAX_VERTICE][MAX_VERTICE];
} GraphType;

int Arr[MAX_VERTICE][MAX_VERTICE];

void printArr(GraphType *g)
{
    int i, j;
    printf("============================\n");
    for (i = 0; i < g->n; i++)
    {
        for (j = 0; j < g->n; j++)
        {
            if (Arr[i][j] == INF)
                printf("  *  ");
            else
                printf("%3d ", Arr[i][j]);
        }
        printf("\n");
    }
    printf("============================\n");
}

void floyd(GraphType *g)
{
    int i, j, k;
    for (i = 0; i < g->n; i++)
    {
        for (j = 0; j < g->n; j++)
        {
            Arr[i][j] = g->weight[i][j];
        }
    }
    printArr(g);

    for (k = 0; k = g->n; k++)
    {
        for (i = 0; i < g->n; i++)
        {
            for (j = 0; j < g->n; j++)
            {
                if (Arr[i][k] + Arr[k][j] < Arr[i][j])
                    Arr[i][j] = Arr[i][k] + Arr[k][j];
            }
        }
        printArr(g);
    }
}

int main()
{
    GraphType g = {7,
                   {{0, 7, INF, INF, 3, 10, INF},
                    {7, 0, 4, 10, 2, 6, INF},
                    {INF, 4, 0, 2, INF, INF, INF},
                    {INF, 10, 2, 0, 11, 9, 4},
                    {3, 2, INF, 11, 0, INF, 5},
                    {10, 6, INF, 9, INF, 0, INF},
                    {INF, INF, INF, 4, 5, INF, 0}}};

    floyd(&g);
    return 0;
}