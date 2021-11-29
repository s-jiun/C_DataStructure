#define _CRT_SECURE_NO_WARNINGS
#define MAX_VIDEO 100
#define MAX_CUST 20 // max customer
#define MAX_CHAR 50 // ���ڿ��� max ����

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	char title[MAX_CHAR];
	int qty;
} VideoInfo;

typedef struct {
	int custId;
	char title[MAX_CHAR];
} RentInfo;

void printAllVideo(VideoInfo videoList[], int videoCount) {
	printf("Video���� \t����\n");
	printf("-----------------------\n");
	for (int i = 0; i < videoCount; i++) {
		printf("%-8s\t%d\n", videoList[i].title, videoList[i].qty);
	}
}

void purchaseVideo(VideoInfo videoList[], int* videoCountPtr) {
	char videoTitle[MAX_CHAR];
	int videoQty;
	printf("Enter Video ����: ");
	scanf("%s", &videoTitle);
	printf("Enter Video ����: ");
	scanf("%d", &videoQty);
	for (int i = 0; i < *videoCountPtr; i++) {
		if (strcmp(videoList[i].title, videoTitle) == 0) {
			(videoList[i].qty) += videoQty;
			return;
		}
	}
	strcpy(videoList[*videoCountPtr].title, videoTitle);
	videoList[*videoCountPtr].qty = videoQty;
	(*videoCountPtr)++;
}

VideoInfo* searchVideoByTitle(VideoInfo videoList[], int videoCount) {
	VideoInfo* video;
	char videoTitle[MAX_CHAR];
	printf("Enter Video ����: ");
	scanf("%s", &videoTitle);
	for (int i = 0; i < videoCount; i++) {
		if (strcmp(videoList[i].title, videoTitle) == 0) {
			video = &videoList[i];
			return video;
		}
	}
	return NULL;
}

void rentVideo(RentInfo rentList[], int* rentCount, VideoInfo videoList[], int videoCount) {
	int customerID;
	VideoInfo* video;
	video = searchVideoByTitle(videoList, videoCount);
	if (video == NULL) {
		printf("�׷� ������ �����ϴ�.\n");
		return;
	}
	else {
		if (video->qty == 0) {
			printf("��� �뿩���Դϴ�.\n");
			return;
		}
		else {
			(video->qty)--;
		}
	}
	printf("Enter �� id:(����3�ڸ�) ");
	scanf("%d", &customerID);
	strcpy(rentList[*rentCount].title, video->title);
	rentList[*rentCount].custId = customerID;
	(*rentCount)++;
}

void printAllRent(RentInfo rentList[], int rentCount) {
	printf("��id \t Video����\n");
	printf("-----------------------\n");
	for (int i = 0; i < rentCount; i++) {
		printf("%d \t %s\n", rentList[i].custId, rentList[i].title);
	}
}

void returnVideo(RentInfo rentList[], int* rentCount, VideoInfo videoList[], int videoCount) {
	char videoTitle[MAX_CHAR];
	int customerID;
	printf("Enter ��id:(����3�ڸ�) ");
	scanf("%d", &customerID);
	int n = 0;
	while (customerID != rentList[n].custId) {
		if (n == *rentCount & customerID != rentList[n].custId) {
			printf("��id�� �߸� �Է��ϼ̽��ϴ�.\n");
			return;
		}
		n++;
	}
	printf("Enter video ����: ");
	scanf("%s", &videoTitle);
	int m = 0;
	while (strcmp(videoTitle, rentList[m].title) != 0) {
		if (m == *rentCount & (strcmp(videoTitle, rentList[m].title) != 0)) {
			printf("Video������ �߸� �Է��ϼ̽��ϴ�.\n");
			return;
		}
		m++;
	}
	for (int i = 0; i < *rentCount; i++) {
		if (strcmp(rentList[i].title, videoTitle) == 0) {
			strcpy(rentList[i].title, rentList[i + 1].title);
			rentList[i].custId = rentList[i + 1].custId;
			(*rentCount)--;
		}
	}
	for (int j = 0; j < videoCount; j++) {
		if (strcmp(videoList[j].title, videoTitle) == 0) {
			videoList[j].qty++;
		}
	}
}

int main(void) {
	int videoCount = 5;
	VideoInfo videoList[MAX_VIDEO] = { {"Minari", 5}, {"Parasite", 3}, {"Avatar", 2}, {"Soul", 7}, {"HomeAlone", 3} };
	int rentCount = 0; // ���� ���� �Ǽ��� 0��
	RentInfo rentList[MAX_CUST];
	int choice;
	VideoInfo* videoPtr;

	printf("1(All Video ���), 2(����), 3(�˻�), 4(�뿩), 5(All �뿩���� ���), 6(�ݳ�), 7(����): ");
	scanf("%d", &choice);
	printf("\n");

	while (choice != 7) {
		switch (choice) {
		case 1:
			printAllVideo(videoList, videoCount);
			break;
		case 2:
			purchaseVideo(videoList, &videoCount);
			break;
		case 3:
			if ((videoPtr = searchVideoByTitle(videoList, videoCount)) == NULL)
				printf("�׷� ������ �����ϴ�.\n");
			else if (videoPtr->qty == 0)
				printf("��� �뿩���Դϴ�.\n");
			else
				printf("�뿩 �����մϴ�.\n");
			break;
		case 4:
			rentVideo(rentList, &rentCount, videoList, videoCount);
			break;
		case 5:
			printAllRent(rentList, rentCount);
			break;
		case 6:
			returnVideo(rentList, &rentCount, videoList, videoCount);
			break;
		}
		printf("-----------------------\n\n");
		printf("1(All Video ���), 2(����), 3(�˻�), 4(�뿩), 5(All �뿩���� ���), 6(�ݳ�), 7(����): ");
		scanf("%d", &choice);
		printf("\n");
	}
}