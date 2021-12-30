
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ===== 원형큐 코드 시작 ======
#define MAX_QUEUE_SIZE 3
#define MAX_STRING_SIZE 10

typedef struct
{
	char name[MAX_STRING_SIZE];
} element;

typedef struct
{ // 큐 타입
	element data[MAX_QUEUE_SIZE];
	int front, rear;
} QueueType;

// 오류 함수
void error(char *message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}

// 공백 상태 검출 함수
void init_queue(QueueType *q)
{
	q->front = q->rear = 0;
}

// 공백 상태 검출 함수
int is_empty(QueueType *q)
{
	return (q->front == q->rear);
}

// 포화 상태 검출 함수
int is_full(QueueType *q)
{
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}

// 원형큐 출력 함수
void queue_print(QueueType *q)
{
	printf("QUEUE(front=%d rear=%d) = ", q->front, q->rear);
	if (!is_empty(q))
	{
		int i = q->front;
		do
		{
			i = (i + 1) % (MAX_QUEUE_SIZE);
			printf("%d | ", q->data[i]);
			if (i == q->rear)
				break;
		} while (i != q->front);
	}
	printf("\n");
}

// 삽입 함수
void enqueue(QueueType *q, element item)
{
	if (is_full(q))
		error("ť�� ��ȭ�����Դϴ�");
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->data[q->rear] = item;
}

// 삭제 함수
element dequeue(QueueType *q)
{
	if (is_empty(q))
		error("ť�� ��������Դϴ�");
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->data[q->front];
}

// 꺼내보는 함수
element peek(QueueType *q)
{
	if (is_empty(q))
		error("ť�� ��������Դϴ�");
	return q->data[(q->front + 1) % MAX_QUEUE_SIZE];
}
// ===== 원형큐 코드 끝 ======

int get_count(QueueType *q)
{
	if (q->rear < q->front)
		return (q->rear + MAX_QUEUE_SIZE - q->front);
	else
		return (q->rear - q->front);
}

void print_queue(QueueType *q)
{
	int temp = (q->front + 1) % MAX_QUEUE_SIZE;
	while (temp != (q->rear + 1) % MAX_QUEUE_SIZE)
	{
		printf("%s ", q->data[temp].name);
		temp = (temp + 1) % MAX_QUEUE_SIZE;
	}
	printf("\n");
}

void match(char *name, QueueType *myQ, QueueType *partnerQ)
{
	element newPerson, partner;
	if (is_empty(partnerQ))
	{
		if (is_full(myQ))
		{
			printf("아직 대상자가 없습니다. 대기자가 꽉찼으니 담기회를 이용...\n");
		}
		else
		{
			strcpy(newPerson.name, name);
			enqueue(myQ, newPerson);
			printf("아직 대상자가 없습니다. 기다려 주십시오.\n");
		}
	}
	else
	{
		partner = dequeue(partnerQ);
		printf("커플이 탄생했습니다! %s과 %s\n", name, partner.name);
	}
}

int main(void)
{
	QueueType male;
	init_queue(&male);
	QueueType female;
	init_queue(&female);

	char name[MAX_STRING_SIZE];
	char gender;
	char input;

	printf("미팅 주선 프로그램입니다.\n");

	do
	{
		printf("i<nsert, 고객입력>, c<heck, 대기자 체크>, q<uit>: ");
		scanf(" %c", &input);
		switch (input)
		{
		case 'i':
			printf("이름을 입력: ");
			scanf("%s", name);
			printf("성별을 입력(m or f): ");
			scanf(" %c", &gender);
			if (gender == 'm')
				match(name, &male, &female);
			else if (gender == 'f')
				match(name, &female, &male);
			else
			{
				printf("잘못 입력하셨습니다.\n");
			}
			break;
		case 'c':
			printf("남성 대기자 %d명: ", get_count(&male));
			print_queue(&male);
			printf("여성 대기자 %d명: ", get_count(&female));
			print_queue(&female);
			break;
		case 'q':
			break;
		default:
			printf("잘못 입력하셨습니다.\n");
		}
	} while (input != 'q');
}
