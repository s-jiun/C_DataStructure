
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 3

typedef int element;

typedef struct
{
	element data[MAX_QUEUE_SIZE];
	int front, rear;
} QueueType;

void error(char *message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}

void init_queue(QueueType *q)
{
	q->front = q->rear = 0;
}

int is_empty(QueueType *q)
{
	return (q->front == q->rear);
}

int is_full(QueueType *q)
{
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}

void enqueue(QueueType *q, element item)
{
	if (is_full(q))
	{
		error("큐가 포화상태입니다.");
	}
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->data[q->rear] = item;
}

element dequeue(QueueType *q)
{
	if (is_empty(q))
		error("큐가 공백상태입니다.");
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->data[q->front];
}

element peek(QueueType *q)
{
	if (is_empty(q))
		error("큐가 공백상태입니다.");
	return q->data[(q->front + 1) % MAX_QUEUE_SIZE];
}

int get_count(QueueType *q)
{
	return (q->rear - q->front);
}

int main()
{
	QueueType fibo;
	init_queue(&fibo);

	enqueue(&fibo, 0);
	enqueue(&fibo, 1);

	int n;
	printf("출력할 피보나치 수열의 개수 입력: ");
	scanf("%d", &n);

	printf("%d ", fibo.data[1]);

	for (int i = 2; i <= n; i++)
	{
		element f = fibo.data[1] + fibo.data[2];
		dequeue(&fibo);
		enqueue(&fibo, f);
		printf("%d ", f);
	}
	return 0;
}