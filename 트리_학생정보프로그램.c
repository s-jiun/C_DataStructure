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

	printf("�й� �Է�:");
	scanf("%d", &id);
	fflush(stdin);
	data.id = id;

	printf("�̸� �Է�:");
	scanf("%s", &name);
	fflush(stdin);
	strcpy(data.name, name);

	printf("��ȭ��ȣ �Է�:");
	scanf("%s", &tel);
	fflush(stdin);
	strcpy(data.tel, tel);

	printf("�а� �Է�:");
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
		printf("�й�: %d\n", root->data.id);
		printf("�̸�: %s\n", root->data.name);
		printf("��ȭ��ȣ: %s\n", root->data.tel);
		printf("�а�: %s\n", root->data.dept);
		print_inorder(root->right);
	}
}

void print_data(TreeNode* node) {
	printf("-----------------------------------\n");
	printf("�й�: %d\n", node->data.id);
	printf("�̸�: %s\n", node->data.name);
	printf("��ȭ��ȣ: %s\n", node->data.tel);
	printf("�а�: %s\n", node->data.dept);
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
			printf("������ �й� �Է�:");
			scanf("%d", &id);
			root = delete_node(root, id);
		}
		else if (selection == 's') {
			int id;
			printf("Ž���� �й� �Է�:");
			scanf("%d", &id);
			TreeNode* temp = search(root, id);
			if (temp == NULL)
				printf("id�� %d�� �л��� �����ϴ�.\n", id);
			else
				print_data(temp);
		}
		else if (selection == 'p') {
			printf("�л� ���� �й� �� ���\n");
			print_inorder(root);
		}
		else if (selection == 'c') {
			printf("���� ����� �л��� �� ���� %d\n", get_count(root));
		}
		else {
			printf("�߸� �Է��ϼ̽��ϴ�.\n");
		}
		printf("Enter i(nsert), d(elete), s(earch), p(rint), c(ount), q(uit):");
		scanf(" %c", &selection);
		fflush(stdin);
	}
	return 0;
}