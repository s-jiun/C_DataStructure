#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SIZE 10
#define SWAP(x, y, t) ( (t)=(x), (x)=(y), (y)=(t) )

int partition(int list[], int left, int right)
{
	//���� �ڵ� �ϼ��ϱ�
	//while�� ��� 
	int pivot, temp;
	int low, high;

	low = left + 1;
	high = right;
	pivot = list[left];

	while (low <= high) {
		while (list[low] < pivot)
			low++;
		
		while (list[high] > pivot)
			high--;

		if (low <= high) {
			SWAP(list[low], list[high], temp);
			low++;
			high--;
		}
	}

	SWAP(list[left], list[high], temp);
	return high;
}
void quick_sort(int list[], int left, int right)
{
	//���� �ڵ� �ϼ� 
	if (left < right) {
		int q = partition(list, left, right);
		quick_sort(list, left, q - 1);
		quick_sort(list, q + 1, right);
	}
}

void print_list(int list[], int size)
{
	int i;
	for (i = 0; i < size; i++)
		printf("%d ", list[i]);
	printf("\n");
}

int main(void)
{
	int i, n = MAX_SIZE;
	int list1[] = { 3, 3, 3, 3, 3, 3, 3, 3, 3, 3 };
	int list2[MAX_SIZE];

	printf("\n<list1(�������� ������ ������)�� ��� ���>\n");
	quick_sort(list1, 0, n - 1); // ������ ȣ�� 
	print_list(list1, n);

	srand(time(NULL));
	for (i = 0; i < n; i++)      	// ���� ���� �� ��� 
		list2[i] = rand() % 100;

	printf("\n\n<list2(������ ������ ������)�� ��� ���>\n");
	quick_sort(list2, 0, n - 1); // ������ ȣ�� 
	print_list(list2, n);

	return 0;
}
