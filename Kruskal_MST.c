#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICE 100
#define INF 1000

int parent[MAX_VERTICE]; //부모노드

struct Edge
{
    int start, end, weight;
};

typedef struct GraphType
{
    int n;
    struct Edge edges[2 * MAX_VERTICE];
} GraphType;

void set_init(int n)
{
    for (int i = 0; i < n; i++)
        parent[i] = -1;
}

// curr이 속한 집합 반환
int set_find(int curr)
{
    if (parent[curr] == -1)
        return curr;
    while (parent[curr] != -1)
        curr = parent[curr];
    return curr;
}

// 두 개의 원소가 속한 집합을 합침
void set_union(int node1, int node2)
{
    int root1 = set_find(node1); //node1의 루트 조사
    int root2 = set_find(node2); //node2의 루트 조사
    if (root1 != root2)          //합침
        parent[root1] = root2;
}

void graph_init(GraphType *g)
{
    g->n = 0;
    for (int i = 0; i < 2 * MAX_VERTICE; i++)
    {
        g->edges[i].start = 0;
        g->edges[i].end = 0;
        g->edges[i].weight = INF;
    }
}

void insert_edge(GraphType *g, int start, int end, int weight)
{
    g->edges[g->n].start = start;
    g->edges[g->n].end = end;
    g->edges[g->n].weight = weight;
    g->n++;
}

// qsort()에 사용되는 함수
int compare(const void *a, const void *b)
{
    struct Edge *x = (struct Edge *)a;
    struct Edge *y = (struct Edge *)b;
    return (x->weight - y->weight);
}

void kruskal(GraphType *g, int num)
{
    int edge_accepted = 0; // 현재까지 선택된 간선의 수
    int uset, vset;        // 정점 u와 정점 v의 집합 번호
    struct Edge e;

    set_init(g->n);
    qsort(g->edges, g->n, sizeof(struct Edge), compare);
    printf("Kruskal 최소 신장 트리 알고리즘\n");
    int i = 0;
    while (edge_accepted < (num - 1))
    {
        e = g->edges[i];
        uset = set_find(e.start); // 정점 u의 집합 번호
        vset = set_find(e.end);   // 정점 v의 집합 번호

        if (uset != vset)
        {
            printf("간선 (%d, %d) %d 선택\n", e.start, e.end, e.weight);
            edge_accepted++;
            printf("%d\n", edge_accepted);
            set_union(uset, vset); // 두 집합을 합침
        }
        i++;
    }
}

int main()
{
    GraphType *g;
    g = (GraphType *)malloc(sizeof(GraphType));
    graph_init(g);

    insert_edge(g, 0, 1, 29);
    insert_edge(g, 1, 2, 16);
    insert_edge(g, 2, 3, 12);
    insert_edge(g, 3, 4, 22);
    insert_edge(g, 4, 5, 27);
    insert_edge(g, 5, 0, 10);
    insert_edge(g, 6, 1, 15);
    insert_edge(g, 6, 3, 18);
    insert_edge(g, 6, 4, 25);

    int *vertex = (int *)malloc(sizeof(int));
    vertex[0] = g->edges[0].start;

    int n = 1;

    for (int i = 0; i < g->n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (g->edges[i].start == vertex[j])
            {
                continue;
            }
            else
            {
                n++;
                realloc(vertex, sizeof(int) * n);
                vertex[n - 1] = g->edges[i].start;
            }
        }
    }

    kruskal(g, n);
    free(g);
    free(vertex);
    return 0;
}