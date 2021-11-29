/*
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_SIZE 1024

struct Student {
	int id;
	int english, math, korean;
};

void print_student(struct Student s[], int num)
{
	int i;
	for (i = 0; i < num; i++)
		printf("학번 : %d\t영어 : %d\t수학 : %d\t국어 : %d\n", s[i].id, s[i].english, s[i].math, s[i].korean);
}

struct Student sorted[MAX_SIZE];

void merge(struct Student list[], int left, int mid, int right)
{  
	int i, j, k, l;
	i = left; j = mid + 1; k = left;

	while (i <= mid && j <= right) {
		if (list[i].korean <= list[j].korean) {
			sorted[k++] = list[i++];
		}
		else
			sorted[k++] = list[j++];
	}

	if (i > mid) {
		for (l = j; l <= right; l++)
			sorted[k++] = list[l];
	}
	else {
		for(l = i; l <= mid; l++)
			sorted[k++] = list[l];
	}

	for (l = left; l <= right; l++)
		list[l] = sorted[l];
}

void merge_sort(struct Student list[], int left, int right)
{
	int mid;
	if (left < right) {
		mid = (left + right) / 2;
		merge_sort(list, left, mid);
		merge_sort(list, mid + 1, right);
		merge(list, left, mid, right);
	}
}

	int main(void)
	{
		int code;
		struct Student* student;
		int num, i;

		srand(time(NULL));

		printf("학생 수를 입력하세요 : ");
		scanf("%d", &num);
		student = (struct Student*)malloc(sizeof(struct Student) * num);

		srand(time(NULL));
		for (int n = 0; n < num; n++) {
			student[n].id = n + 1;
			student[n].english = (rand() % 100) + 1;
			student[n].math = (rand() % 100) + 1;
			student[n].korean = (rand() % 100) + 1;
		}

		print_student(student, num);
		merge_sort(student, 0, num - 1);

		printf("\n\n국어 성적으로 내림차순 정렬된 학생 정보\n");
		print_student(student, num);

		free(student);
	}
	*/