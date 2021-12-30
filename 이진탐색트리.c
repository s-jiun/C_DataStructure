
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct TreeNode
{
	element key;
	struct TreeNode *left, *right;
} TreeNode;

TreeNode *search(TreeNode *node, int key)
{
	if (node == NULL)
		return NULL;
	if (key == node->key)
		return node;
	else if (key < node->key)
		return search(node->left, key);
	else
		return search(node->right, key);
}

TreeNode *new_node(int item)
{
	TreeNode *temp = (TreeNode *)malloc(sizeof(TreeNode));
	temp->key = item;
	temp->left = temp->right = NULL;
	return temp;
}

TreeNode *insert_node(TreeNode *node, int key)
{
	if (node == NULL)
		return new_node(key);

	if (key < node->key)
		node->left = insert_node(node->left, key);
	else if (key > node->key)
		node->right = insert_node(node->right, key);

	return node;
}

int get_minimum(TreeNode *node)
{
	TreeNode *current = node;

	while (current->left != NULL)
		current = current->left;

	return current->key;
}

int get_maximum(TreeNode *node)
{
	TreeNode *current = node;

	while (current->right != NULL)
		current = current->right;

	return current->key;
}

TreeNode *delete_node(TreeNode *root, int key)
{
	if (root == NULL)
		return root;

	if (key < root->key)
		root->left = delete_node(root->left, key);
	else if (key > root->key)
		root->right = delete_node(root->right, key);
	else
	{
		if (root->left == NULL)
		{
			TreeNode *temp = root->right;
			free(root);
			return temp;
		}
		else if (root->right == NULL)
		{
			TreeNode *temp = root->left;
			free(root);
			return temp;
		}
		root->key = get_minimum(root->right);
		root->right = delete_node(root->right, get_minimum(root->right));
	}
	return root;
}

void preorder(TreeNode *root)
{
	if (root)
	{
		printf("%d ", root->key);
		preorder(root->left);
		preorder(root->right);
	}
}

int get_height(TreeNode *node)
{
	int height = 0;

	if (node != NULL)
		height = 1 + max(get_height(node->left), get_height(node->right));

	return height;
}

int get_count(TreeNode *root)
{
	int count = 0;
	if (root)
		count = 1 + get_count(root->left) + get_count(root->right);

	return count;
}

int main()
{
	TreeNode *root = NULL;
	char selection;
	int key;
	printf("Enter i<nsert>, d<elete>, s<earch>, p<rint>, h<eight>, c<ount>, m<ax>, n<min>, q<uit>: ");
	scanf(" %c", &selection);
	while (selection != 'q')
	{
		switch (selection)
		{
		case 'i':
			printf("삽입할 key값 입력:");
			scanf("%d", &key);
			root = insert_node(root, key);
			break;
		case 'd':
			printf("삭제할 key값 입력:");
			scanf("%d", &key);
			delete_node(root, key);
			break;
		case 's':
			printf("탐색할 key값 입력:");
			scanf("%d", &key);
			if (search(root, key))
				printf("있음\n");
			else
				printf("없음\n");
			break;
		case 'p':
			preorder(root);
			printf("\n");
			break;
		case 'h':
			printf("트리의 높이는 %d\n", get_height(root));
			break;
		case 'c':
			printf("노드의 개수는 %d\n", get_count(root));
			break;
		case 'm':
			printf("가장 큰 값은 %d\n", get_maximum(root));
			break;
		case 'n':
			printf("가장 작은 값은 %d\n", get_minimum(root));
			break;
		default:
			printf("잘못 입력하셨습니다.\n");
		}
		printf("Enter i<nsert>, d<elete>, s<earch>, p<rint>, h<eight>, c<ount>, m<ax>, n<min>, q<uit>: ");
		scanf(" %c", &selection);
	}
	return 0;
}