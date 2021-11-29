#define _CRT_SECURE_NO_WARNINGS
#define MAX_STRING 100

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	int id;
	char name[MAX_STRING];
	char tel[MAX_STRING];
	char dept[MAX_STRING];
} element;

typedef struct TreeNode {
	element data;
	struct TreeNode* left, * right;
} TreeNode;

element get_data() {
	element data;
	int id;
	char name[MAX_STRING];
	char tel[MAX_STRING];
	char dept[MAX_STRING];

	printf("학번 입력:");
	scanf("%d", &id);
	fflush(stdin);
	data.id = id;

	printf("이름 입력:");
	scanf("%s", &name);
	fflush(stdin);
	strcpy(data.name, name);

	printf("전화번호 입력:");
	scanf("%s", &tel);
	fflush(stdin);
	strcpy(data.tel, tel);

	printf("학과 입력:");
	scanf("%s", &dept);
	fflush(stdin);
	strcpy(data.dept, dept);

	return data;
}

TreeNode* new_node(element data) {
	TreeNode* temp = (TreeNode*)malloc(sizeof(TreeNode));
	temp->data = data;
	temp->left = temp->right = NULL;
	return temp;
}

TreeNode* insert_node(TreeNode* node, element data) {
	if (node == NULL) return new_node(data);

	if (data.id < node->data.id)
		node->left = insert_node(node->left, data);
	else if (data.id > node->data.id)
		node->right = insert_node(node->right, data);

	return node;
}

TreeNode* search(TreeNode* node, int id) {
	if (node == NULL) return NULL;

	if (id == node->data.id) return node;
	else if (id < node->data.id)
		return search(node->left, id);
	else
		return search(node->right, id);
}

TreeNode* min_value_node(TreeNode* node) {
	TreeNode* current = node;

	while (current->left != NULL)
		current = current->left;

	return current;
}

TreeNode* delete_node(TreeNode* root, int id) {
	if (root == NULL) return root;

	if (id < root->data.id)
		root->left = delete_node(root->left, id);
	else if(id > root->data.id)
		root->right = delete_node(root->right, id);
	else {
		if (root->left == NULL) {
			TreeNode* temp = root->right;
			free(root);
			return temp;
		}
		else if (root->right == NULL) {
			TreeNode* temp = root->left;
			free(root);
			return temp;
		}
		TreeNode* temp = min_value_node(root->right);
		root->data = temp->data;
		root->right = delete_node(root->right, id);
	}
	return root;
}

void print_inorder(TreeNode* root) {
	if (root) {
		print_inorder(root->left);
		printf("-----------------------------------\n");
		printf("학번: %d\n", root->data.id);
		printf("이름: %s\n", root->data.name);
		printf("전화번호: %s\n", root->data.tel);
		printf("학과: %s\n", root->data.dept);
		print_inorder(root->right);
	}
}

void print_data(TreeNode* node) {
	printf("-----------------------------------\n");
	printf("학번: %d\n", node->data.id);
	printf("이름: %s\n", node->data.name);
	printf("전화번호: %s\n", node->data.tel);
	printf("학과: %s\n", node->data.dept);
}

int get_count(TreeNode* root) {
	int count = 0;
	if (root)
		count = 1 + get_count(root->left) + get_count(root->right);

	return count;
}

int main() {
	TreeNode* root = NULL;
	char selection;
	printf("Enter i(nsert), d(elete), s(earch), p(rint), c(ount), q(uit):");
	scanf(" %c", &selection);
	while (selection != 'q') {
		if (selection == 'i') {
			element data = get_data();
			root = insert_node(root, data);
		}
		else if (selection == 'd') {
			int id;
			printf("삭제할 학번 입력:");
			scanf("%d", &id);
			root = delete_node(root, id);
		}
		else if (selection == 's') {
			int id;
			printf("탐색할 학번 입력:");
			scanf("%d", &id);
			TreeNode* temp = search(root, id);
			if (temp == NULL)
				printf("id가 %d인 학생은 없습니다.\n", id);
			else
				print_data(temp);
		}
		else if (selection == 'p') {
			printf("학생 정보 학번 순 출력\n");
			print_inorder(root);
		}
		else if (selection == 'c') {
			printf("현재 저장된 학생의 총 수는 %d\n", get_count(root));
		}
		else {
			printf("잘못 입력하셨습니다.\n");
		}
		printf("Enter i(nsert), d(elete), s(earch), p(rint), c(ount), q(uit):");
		scanf(" %c", &selection);
		fflush(stdin);
	}
	return 0;
}