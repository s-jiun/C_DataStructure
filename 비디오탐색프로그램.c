#define _CRT_SECURE_NO_WARNINGS
#define MAX_VIDEO 100
#define MAX_CUST 20 // max customer
#define MAX_CHAR 50 // 문자열의 max 문자

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
	printf("Video제목 \t수량\n");
	printf("-----------------------\n");
	for (int i = 0; i < videoCount; i++) {
		printf("%-8s\t%d\n", videoList[i].title, videoList[i].qty);
	}
}

void purchaseVideo(VideoInfo videoList[], int* videoCountPtr) {
	char videoTitle[MAX_CHAR];
	int videoQty;
	printf("Enter Video 제목: ");
	scanf("%s", &videoTitle);
	printf("Enter Video 수량: ");
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
	printf("Enter Video 제목: ");
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
		printf("그런 비디오는 없습니다.\n");
		return;
	}
	else {
		if (video->qty == 0) {
			printf("모두 대여중입니다.\n");
			return;
		}
		else {
			(video->qty)--;
		}
	}
	printf("Enter 고객 id:(숫자3자리) ");
	scanf("%d", &customerID);
	strcpy(rentList[*rentCount].title, video->title);
	rentList[*rentCount].custId = customerID;
	(*rentCount)++;
}

void printAllRent(RentInfo rentList[], int rentCount) {
	printf("고객id \t Video제목\n");
	printf("-----------------------\n");
	for (int i = 0; i < rentCount; i++) {
		printf("%d \t %s\n", rentList[i].custId, rentList[i].title);
	}
}

void returnVideo(RentInfo rentList[], int* rentCount, VideoInfo videoList[], int videoCount) {
	char videoTitle[MAX_CHAR];
	int customerID;
	printf("Enter 고객id:(숫자3자리) ");
	scanf("%d", &customerID);
	int n = 0;
	while (customerID != rentList[n].custId) {
		if (n == *rentCount & customerID != rentList[n].custId) {
			printf("고객id를 잘못 입력하셨습니다.\n");
			return;
		}
		n++;
	}
	printf("Enter video 제목: ");
	scanf("%s", &videoTitle);
	int m = 0;
	while (strcmp(videoTitle, rentList[m].title) != 0) {
		if (m == *rentCount & (strcmp(videoTitle, rentList[m].title) != 0)) {
			printf("Video제목을 잘못 입력하셨습니다.\n");
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
	int rentCount = 0; // 현재 대출 건수는 0임
	RentInfo rentList[MAX_CUST];
	int choice;
	VideoInfo* videoPtr;

	printf("1(All Video 출력), 2(구입), 3(검색), 4(대여), 5(All 대여정보 출력), 6(반납), 7(종료): ");
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
				printf("그런 비디오는 없습니다.\n");
			else if (videoPtr->qty == 0)
				printf("모두 대여중입니다.\n");
			else
				printf("대여 가능합니다.\n");
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
		printf("1(All Video 출력), 2(구입), 3(검색), 4(대여), 5(All 대여정보 출력), 6(반납), 7(종료): ");
		scanf("%d", &choice);
		printf("\n");
	}
}