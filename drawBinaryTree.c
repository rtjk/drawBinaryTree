#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct node {
	int data;
	struct node* left, *right;
};

void draw(struct node* tree);
void printSign(int n);

int* treeToArray(struct node* tree);
void recursiveTreeToArray(struct node* node, int x, int* absoluteData, int* dataSign);

int height(struct node* node);
int digits(int n);

void draw(struct node* tree) {

	if (tree == NULL)
		printf("\n\nEMPTY TREE\n\n");

	else {

		printf("\n\n");

		int* arrayFromTree = treeToArray(tree);

		int h = height(tree);

		int l = pow(2, h + 1) - 1; // arraysLength

		int* a = &arrayFromTree[0]; // absoluteData
		int* s = &arrayFromTree[l]; // dataSign

		int i;

		int max = a[0]; // maxAbsoluteData

		for (i = 1; i < l; i++)
			if (a[i] > max)
				max = a[i];

		int d = digits(max); // digitsOfMaxAbsoluteData

		int negative = 0; // negativeData

		for (i = 0; i < l & !negative; i++)
			if (s[i] == 1)
				negative = 1;

		int r, gi; //row, digits of Data
		int j = 0;

		for (r = h + 1; r >= 1; r--) {

			for (int i = 0; i < pow(2, r - 1) - 1; i++) {
				for (int k = 0; k <= d; k++)
					printf(" ");
				if (negative)
					printf(" ");
			}

			for (int i = 0; i < pow(2, h - r + 1); i++, j++) {

				if (a[j] != -1) {
					if (negative) {
						if (a[j] == 0)
							printSign(0);
						else
							printSign(-s[j]);
					}
					gi = digits(a[j]);
					for (int k = 0; k < (d - gi); k++)
						printf("0");
					printf("%d", a[j]);
				} else {
					if (negative)
						printf("_");
					for (int k = 0; k <= d; k++)
						printf("_");
				}

				for (int j = 0; j < pow(2, r) - 1; j++) {
					for (int k = 0; k <= d; k++)
						printf(" ");
					if (negative)
						printf(" ");
				}
			}

			printf("\n\n");
		}

	}

}

void printSign(int n) {
	if (n == 0) printf("0");
	if (n > 0) printf("+");
	if (n < 0) printf("-");
}

int* treeToArray(struct node* tree) {

	if (tree != NULL) {

		int maxNodes; // maximum possible number of nodes based on height
		maxNodes = pow(2, (height(tree)) + 1) - 1;

		// allocate
		int* arrayFromTree = malloc(2 * maxNodes * sizeof(int));

		// initialize
		int i;
		for (i = 0; i < 2 * maxNodes; i++)
			arrayFromTree[i] = -1;

		int* absoluteData = &arrayFromTree[0];		// absoluteData[i] = Data if node is not null
											 	 	// absoluteData[i] = -1 if node is null
		int* dataSign = &arrayFromTree[maxNodes];	// dataSign[i] = 1 if Data is negative
												 	// dataSign[i] = -1 otherwise

		absoluteData[0] = abs(tree->data);
		if (tree->data < 0)
			dataSign[0] = 1;

		recursiveTreeToArray(tree, 0, absoluteData, dataSign);
		return arrayFromTree;

	}

	else
		return NULL;

}

void recursiveTreeToArray(struct node* node, int x, int* absoluteData,
		int* dataSign) {

	if (node == NULL)
		return;

	if (node->left != NULL) {
		absoluteData[2 * x + 1] = abs(node->left->data);
		if (node->left->data < 0)
			dataSign[2 * x + 1] = 1;
	}

	if (node->right != NULL) {
		absoluteData[2 * x + 2] = abs(node->right->data);
		if (node->right->data < 0)
			dataSign[2 * x + 2] = 1;
	}

	recursiveTreeToArray(node->left, 2 * x + 1, absoluteData, dataSign);
	recursiveTreeToArray(node->right, 2 * x + 2, absoluteData, dataSign);

}

int height(struct node* node) {

	if (node == NULL)
		return -1;

	int leftHeight = height(node->left);
	int rightHeight = height(node->right);
	if (leftHeight > rightHeight)
		return leftHeight + 1;
	return rightHeight + 1;

}

int digits(int n) {
	int d = 0;
	while (n >= 10) {
		n = n / 10;
		d++;
	}
	return d;
}

////////////////////////////////////////////////////////////////////

struct node* newNode(int data) {
	struct node* node = (struct node*) malloc(sizeof(struct node));
	node->data = data;
	node->left = NULL;
	node->right = NULL;

	return (node);
}

int main() {

	struct node *root = newNode(832);
	root->left = newNode(-12);
	root->right = newNode(3);
	root->left->left = newNode(499);
	root->left->right = newNode(5);
	root->right->left = newNode(6);
	root->right->right = newNode(-7);
	root->left->right->left = newNode(938);

	draw(root);

	return 0;

}
