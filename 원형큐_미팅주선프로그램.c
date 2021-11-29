#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ===== ����ť �ڵ� ���� ======
#define MAX_QUEUE_SIZE 3
#define MAX_STRING_SIZE 10

typedef struct {
	char name[MAX_STRING_SIZE];
} element;

typedef struct { // ť Ÿ��
	element  data[MAX_QUEUE_SIZE];
	int  front, rear;
} QueueType;

// ���� �Լ�
void error(char* message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}

// ���� ���� ���� �Լ�
void init_queue(QueueType* q)
{
	q->front = q->rear = 0;
}

// ���� ���� ���� �Լ�
int is_empty(QueueType* q)
{
	return (q->front == q->rear);
}

// ��ȭ ���� ���� �Լ�
int is_full(QueueType* q)
{
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}

// ����ť ��� �Լ�
void queue_print(QueueType* q)
{
	printf("QUEUE(front=%d rear=%d) = ", q->front, q->rear);
	if (!is_empty(q)) {
		int i = q->front;
		do {
			i = (i + 1) % (MAX_QUEUE_SIZE);
			printf("%d | ", q->data[i]);
			if (i == q->rear)
				break;
		} while (i != q->front);
	}
	printf("\n");
}

// ���� �Լ�
void enqueue(QueueType* q, element item)
{
	if (is_full(q))
		error("ť�� ��ȭ�����Դϴ�");
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->data[q->rear] = item;
}

// ���� �Լ�
element dequeue(QueueType* q)
{
	if (is_empty(q))
		error("ť�� ��������Դϴ�");
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->data[q->front];
}

// ���� �Լ�
element peek(QueueType* q)
{
	if (is_empty(q))
		error("ť�� ��������Դϴ�");
	return q->data[(q->front + 1) % MAX_QUEUE_SIZE];
}
// ===== ����ť �ڵ� �� ======

int get_count(QueueType* q) {
	if (q->rear < q->front)
		return (q->rear + MAX_QUEUE_SIZE - q->front);
	else
		return (q->rear - q->front);
}

void print_queue(QueueType* q) {
	int temp = (q->front + 1) % MAX_QUEUE_SIZE;
	while (temp != (q->rear + 1) % MAX_QUEUE_SIZE) {
		printf("%s ", q->data[temp].name);
		temp = (temp + 1) % MAX_QUEUE_SIZE;
	}
	printf("\n");
}

void match(char* name, QueueType* myQ, QueueType* partnerQ) {
	element newPerson, partner;
	if (is_empty(partnerQ)) {
		if (is_full(myQ)) {
			printf("���� ����ڰ� �����ϴ�. ����ڰ� ��á���� ���ȸ�� �̿�...\n");
		}
		else {
			strcpy(newPerson.name, name);
			enqueue(myQ, newPerson);
			printf("���� ����ڰ� �����ϴ�. ��ٷ� �ֽʽÿ�.\n");
		}
	}
	else {
		partner = dequeue(partnerQ);
		printf("Ŀ���� ź���߽��ϴ�! %s�� %s\n", name, partner.name);
	}
}

int main(void) {
	QueueType male;
	init_queue(&male);
	QueueType female;
	init_queue(&female);

	char name[MAX_STRING_SIZE];
	char gender;
	char input;

	printf("���� �ּ� ���α׷��Դϴ�.\n");

	do {
		printf("i<nsert, ���Է�>, c<heck, ����� üũ>, q<uit>: ");
		scanf(" %c", &input);
		switch (input) {
		case 'i':
			printf("�̸��� �Է�: ");
			scanf("%s", name);
			printf("������ �Է�(m or f): ");
			scanf(" %c", &gender);
			if (gender == 'm')
				match(name, &male, &female);
			else if (gender == 'f')
				match(name, &female, &male);
			else {
				printf("�߸� �Է��ϼ̽��ϴ�.\n");
			}
			break;
		case 'c':
			printf("���� ����� %d��: ", get_count(&male));
			print_queue(&male);
			printf("���� ����� %d��: ", get_count(&female));
			print_queue(&female);
			break;
		case 'q':
			break;
		default:
			printf("�߸� �Է��ϼ̽��ϴ�.\n");
		}
	} while (input != 'q');
}

