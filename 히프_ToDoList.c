
#define _CRT_SECURE_NO_WARNINGS
#define MAX_ELEMENT 100
#define MAX_STRING 50

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
	char plan[MAX_STRING];
	int minute;
} element;

typedef struct
{
	element heap[MAX_ELEMENT];
	int heap_size;
} HeapType;

HeapType *create()
{
	return (HeapType *)malloc(sizeof(HeapType));
}

void init(HeapType *h)
{
	h->heap_size = 0;
}

void insert_max_heap(HeapType *h, element item)
{
	int i;
	i = ++(h->heap_size);

	while ((i != 1) && (item.minute < h->heap[i / 2].minute))
	{
		h->heap[i] = h->heap[i / 2];
		i /= 2;
	}
	h->heap[i] = item;
}

element delete_max_heap(HeapType *h)
{
	int parent, child;
	element item, temp;

	item = h->heap[1];
	temp = h->heap[(h->heap_size)--];
	parent = 1;
	child = 2;

	while (child <= h->heap_size)
	{
		if ((child < h->heap_size) && (h->heap[child].minute) > h->heap[child + 1].minute)
			child++;
		if (temp.minute <= h->heap[child].minute)
			break;

		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;
	}
	h->heap[parent] = temp;
	return item;
}

int main()
{
	HeapType *heap;
	heap = create();
	init(heap);
	char selection;
	printf("삽입(i), 삭제(d), 종료(q) : ");
	scanf(" %c", &selection);
	printf("---------------------------------\n");
	while (selection != 'q')
	{
		if (selection == 'i')
		{
			char plan[MAX_STRING];
			int minute;
			printf("할 일 : ");
			scanf("%s", &plan);
			printf("시간(분) : ");
			scanf("%d", &minute);
			element e1;
			strcpy(e1.plan, plan);
			e1.minute = minute;
			insert_max_heap(heap, e1);
			printf("---------------------------------\n");
		}
		else if (selection == 'd')
		{
			if (heap->heap_size == 0)
			{
				printf("더 이상 할 일이 없습니다.\n");
				printf("---------------------------------\n");
				break;
			}
			element e2 = delete_max_heap(heap);
			printf("< %d, %s >\n", e2.minute, e2.plan);
			printf("---------------------------------\n");
		}
		else
		{
			printf("잘못 입력하셨습니다.\n");
			printf("---------------------------------\n");
		}
		printf("삽입(i), 삭제(d), 종료(q) : ");
		scanf(" %c", &selection);
		fflush(stdin);
		printf("---------------------------------\n");
	}
	free(heap);
	return 0;
}