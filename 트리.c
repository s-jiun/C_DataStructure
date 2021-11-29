#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#define TRUE 1
#define FALSE 0
#define MAX_TREE_SIZE 20

typedef struct TreeNode {
	int data;
	struct TreeNode* left, * right;
} TreeNode;

int get_nonleaf_count(TreeNode* root) {
	int count = 0;
	if (root != NULL) {
		if (root->left == NULL && root->right == NULL)
			return 0;
		else
			count = 1 + get_nonleaf_count(root->left) + get_nonleaf_count(root->right);

	}
	return count;
}

int get_oneleaf_count(TreeNode* root) {
	int count = 0;
	if (root != NULL) {
		if ((root->left != NULL) ^ (root->right != NULL))
			count = 1 + get_oneleaf_count(root->left) + get_oneleaf_count(root->right);
		else
			count = get_oneleaf_count(root->left) + get_oneleaf_count(root->right);
	}
	return count;
}

int get_twoleaf_count(TreeNode* root) {
	int count = 0;
	if (root != NULL) {
		if (root->left != NULL && root->right != NULL)
			count = 1 + get_twoleaf_count(root->left) + get_twoleaf_count(root->right);
		else
			count = get_twoleaf_count(root->left) + get_twoleaf_count(root->right);
	}
	return count;
}

int get_max(TreeNode* root) {
	int root_data, left, right, max = INT_MIN;
	if (root != NULL) {
		root_data = root->data;
		left = get_max(root->left);
		right = get_max(root->right);
		if (left > right)
			max = left;
		else
			max = right;
		if (root_data > max)
			max = root_data;
	}
	return max;
}

int get_min(TreeNode* root) {
	int root_data, left, right, min = INT_MAX;
	if (root != NULL) {
		root_data = root->data;
		left = get_min(root->left);
		right = get_min(root->right);
		if (left > right)
			min = right;
		else
			min = left;
		if (root_data < min)
			min = root_data;
	}
	return min;
}

void preorder(TreeNode* root) {
	if (root != NULL) {
		printf("%d ", root->data);
		preorder(root->left);
		preorder(root->right);
	}
}

void node_increase(TreeNode* root) {
	if (root != NULL) {
		root->data++;
		node_increase(root->left);
		node_increase(root->right);
	}
}

int equal(TreeNode* root1, TreeNode* root2) {
	if (root1 == NULL && root2 == NULL)
		return TRUE;

	if (root1 == NULL || root2 == NULL)
		return FALSE;

	if (root1->data != root2->data)
		return FALSE;
	return equal(root1->left, root2->left) && equal(root1->right, root2->right);
}

TreeNode* copy(TreeNode* root) {
	TreeNode* clone;
	if (root == NULL)
		return NULL;
	clone = (TreeNode*)malloc(sizeof(TreeNode));
	clone->left = copy(root->left);
	clone->right = copy(root->right);
	clone->data = root->data;
	return clone;
}

TreeNode n1 = { 15, NULL, NULL };
TreeNode n2 = { 4, &n1, NULL };
TreeNode n3 = { 16, NULL, NULL };
TreeNode n4 = { 25, NULL, NULL };
TreeNode n5 = { 15, &n3, &n4 };
TreeNode n6 = { 15, &n2, &n5 };
TreeNode* root = &n6;
TreeNode m1 = { 15, NULL, NULL };
TreeNode m2 = { 4, &n1, NULL };
TreeNode m3 = { 16, NULL, NULL };
TreeNode m7 = { 28, NULL, NULL }; // �߰� 
TreeNode m4 = { 25, NULL, &m7 }; // ���� 
TreeNode m5 = { 15, &m3, &m4 };
TreeNode m6 = { 15, &m2, &m5 };
TreeNode* root2 = &m6;

int main() {
	TreeNode* clone;

	printf("��)\n");
	printf("Ʈ�� root �� ��ܸ������ ������ %d.\n", get_nonleaf_count(root));
	printf("Ʈ�� root2 �� ��ܸ������ ������ %d.\n", get_nonleaf_count(root2));

	printf("Ʈ�� root �� �ڽ��� �ϳ��� �ִ� ����� ������ %d.\n", get_oneleaf_count(root));
	printf("Ʈ�� root2 �� �ڽ��� �ϳ��� �ִ� ����� ������ %d.\n", get_oneleaf_count(root2));
	
	printf("Ʈ�� root �� �ڽ��� ���� �ִ� ����� ������ %d.\n", get_twoleaf_count(root));
	printf("Ʈ�� root2 �� �ڽ��� ���� �ִ� ����� ������ %d.\n", get_twoleaf_count(root2));

	printf("Ʈ�� root ���� ���� ū ���� %d.\n", get_max(root));
	printf("Ʈ�� root2 ���� ���� ū ���� %d.\n", get_max(root2));
	printf("Ʈ�� root ���� ���� ���� ���� %d.\n", get_min(root));
	printf("Ʈ�� root2 ���� ���� ���� ���� %d.\n", get_min(root2));

	printf("\n��)\n");
	preorder(root);
	node_increase(root);
	printf("\n");
	preorder(root);
	printf("\n");
	printf("%s\n", equal(root, root) ? "����" : "�ٸ���");
	printf("%s\n", equal(root2, root2) ? "����" : "�ٸ���");
	printf("%s\n", equal(root, root2) ? "����" : "�ٸ���");

	printf("\n��)\n");
	clone = copy(root);
	preorder(root);
	printf("\n");
	preorder(clone);
	printf("\n");
}