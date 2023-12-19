/*8. Napisati program koji omogućava rad s binarnim stablom pretraživanja. Treba
omogućiti unošenje novog elementa u stablo, ispis elemenata (inorder, preorder, postorder i
level order), brisanje i pronalaženje nekog elementa.*/

//1. dio

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _node* position;
typedef struct _node {
	int value;
	position left;
	position right;
}node;

position createNode(int);
position insert(position, int);
int preorder(positon);
int postorder(positon);
int inorder(positon);
position search(position);

int main() {
	position root = NULL;
	char c;
	int rootValue = 0;
	printf("Enter root value: ");
	scanf("%d", &rootValue);

	root = createNode(rootValue);
	printf("\n1-insert\n2-inorder\n3-preorder\n4-postorder\n5-search\nx-exit");

	while (1) {
		int Value=0;
		position result = NULL;
		printf("\nEnter your choice: ");
		scanf(" %c", &c);
		switch (c) {

		case'1':
			printf("\nEnter value: ");
			scanf("%d", &Value);
			insert(root, Value);
			continue;

		case'2':
			printf("\ninorder:\n");
			inorder(root);
			printf("\n");
			continue;

		case'3':
			printf("\npreorder:\n");
			preorder(root);
			printf("\n");
			continue;

		case'4':
			printf("\npostorder:\n");
			postorder(root);
			printf("\n");
			continue;
		case '5':
			printf("Enter a value you are looking for: ");
			scanf("%d", &Value);
			result=search(root,Value);
			if (result==NULL)
				printf("Value %d is not found!", Value);
			else
				printf("Value %d is found!", Value);
			continue;
			

		case'x':
			break;

		default:
			printf("Wrong input!");
		}
		break;
	}
	return 0;
}
position createNode(int Value) {
	position newNode = NULL;
	newNode = (position)malloc(sizeof(node));
	if (newNode == NULL) {
		printf("Allocation failed!");
		exit(-1);
	}
	newNode->value = Value;
	newNode->right = NULL;
	newNode->left = NULL;
}
position insert(position root, int Value) {
	if (root == NULL)
		return createNode(Value);
	if (Value < root->value) {
		root->left = insert(root->left, Value);
	}
	else if (Value >= root->value) {
		root->right = insert(root->right, Value);
	}
	return root;
}

int inorder(position root) {
	if (root) {
		inorder(root->left);
		printf("%d", root->value);
		inorder(root->right);
	}
	return 0;
}
int preorder(position root) {
	if (root) {
		printf("%d", root->value);
		preorder(root->left);
		preorder(root->right);
	}
	return 0;
}
int postorder(position root) {
	if (root) {
		postorder(root->left);
		postorder(root->right);
		printf("%d", root->value);

	}
	return 0;
}
position search(position root, int value) {
	
	if (root==NULL || root->value == value) {
		return root;
	}
	else if (value < root->value)
		return search(root->left, value);
	else
		return search(root->right, value);
}
