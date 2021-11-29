#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SIZE 10
#define SWAP(x, y, t) ( (t)=(x), (x)=(y), (y)=(t) )

int partition(int list[], int left, int right)
{
	//여기 코드 완성하기
	//while문 사용 
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
	//여기 코드 완성 
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

	printf("\n<list1(같은수로 구성된 데이터)의 결과 출력>\n");
	quick_sort(list1, 0, n - 1); // 퀵정렬 호출 
	print_list(list1, n);

	srand(time(NULL));
	for (i = 0; i < n; i++)      	// 난수 생성 및 출력 
		list2[i] = rand() % 100;

	printf("\n\n<list2(난수로 생성된 데이터)의 결과 출력>\n");
	quick_sort(list2, 0, n - 1); // 퀵정렬 호출 
	print_list(list2, n);

	return 0;
}
