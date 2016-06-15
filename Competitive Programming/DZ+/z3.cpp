#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#define NEGINF -1000000000L

using namespace std;

int N, Q;

typedef struct node{
	long nrC; //number of children, if this node is a leaf this will equal 1!
	long sum; //sum of (nrFil - nrFer) of all children, if this node is a leaf this represents the size of the group
	long max; //worst happiness of some of this nodes child, if this node is a leaf this represents the happiness of the group
	long update; //update for max attributes which is needed for this nodes subtree (excluding itself)
	struct node* left;
	struct node* right;
} node;

node* init(int n, int sum){
	node* cur = (node*) malloc(sizeof(node));
	cur->nrC = n;
	cur->update = 0;

	if(n > 1){
		cur->left = init((int)(n/2. + 0.5), sum);
		cur->sum = cur->left->sum;
		cur->max = cur->left->max;

		cur->right = init(n/2, sum+cur->sum);
		cur->sum += cur->right->sum;
		cur->max = cur->right->max > cur->max ? cur->right->max : cur->max;
	}

	else{
		char in[10];
		scanf("%s %ld", in, &cur->sum);
		if(in[1] == 'i')
			cur->max = NEGINF;
		else{
			cur->max = sum;
			cur->sum = -cur->sum;
		}
		cur->left = cur->right = NULL;
	}

	return cur;
}

void updateNode(node* cur){
	if(cur->left == NULL || cur->right == NULL)
		return;
	if(cur->left->max > NEGINF)
		cur->left->max += cur->update;
	if(cur->right->max > NEGINF)
		cur->right->max += cur->update;
	cur->left->update = cur->right->update = cur->update;
	cur->update = 0;
}

node* insertFil(node* cur, int pos, int nr){
	if(cur->update != 0) //update if needed
		updateNode(cur);

	if(cur->nrC != 1){
		cur->nrC += 1;
		if(cur->left->nrC >= pos){
			long diffSum = cur->left->sum;
			cur->left = insertFil(cur->left, pos, nr);
			diffSum = cur->left->sum - diffSum;
			cur->right->update += diffSum;
			if(cur->right->max > NEGINF)
				cur->right->max += diffSum;
		}
		else
			cur->right = insertFil(cur->right, pos - cur->left->nrC, nr);

		cur->sum = cur->left->sum + cur->right->sum;
		cur->max = cur->left->max > cur->right->max ? cur->left->max : cur->right->max;
		return cur;
	}
	else{
		node* innerNode = (node*) malloc(sizeof(node));
		node* newGroup = (node*) malloc(sizeof(node));
		newGroup->sum = nr;
		newGroup->max = NEGINF;
		newGroup->left = newGroup->right = NULL;
		newGroup->update = innerNode->update = 0;
		newGroup->nrC = 1;
		innerNode->sum = nr + cur->sum;
		innerNode->max = cur->max;
		innerNode->nrC = 2;
		if(pos > 0){
			innerNode->left = cur;
			innerNode->right = newGroup;
		}
		else{
			innerNode->left = newGroup;
			innerNode->right = cur;
		}
		return innerNode;
	}
}

node* insertFer(node* cur, int pos, int nr, long sum){
	if(cur->update != 0) //update if needed
		updateNode(cur);

	if(cur->nrC != 1){
		cur->nrC += 1;
		if(cur->left->nrC >= pos){
			long diffSum = cur->left->sum;
			cur->left = insertFer(cur->left, pos, nr, sum);
			diffSum = cur->left->sum - diffSum;
			cur->right->update += diffSum;
			if(cur->right->max > NEGINF)
				cur->right->max += diffSum;
		}
		else
			cur->right = insertFer(cur->right, pos - cur->left->nrC, nr, sum + cur->left->sum);

		cur->sum = cur->left->sum + cur->right->sum;
		cur->max = cur->left->max > cur->right->max ? cur->left->max : cur->right->max;
		return cur;
	}
	else{
		node* innerNode = (node*) malloc(sizeof(node));
		node* newGroup = (node*) malloc(sizeof(node));
		newGroup->sum = nr;
		newGroup->max = sum;
		newGroup->left = newGroup->right = NULL;
		newGroup->update = innerNode->update = 0;
		newGroup->nrC = 1;
		innerNode->sum = nr + cur->sum;
		innerNode->max = cur->max > sum ? cur->max : sum;
		innerNode->nrC = 2;
		if(pos > 0){
			innerNode->left = cur;
			innerNode->right = newGroup;
		}
		else{
			innerNode->left = newGroup;
			innerNode->right = cur;
		}
		return innerNode;
	}
}

void destroyTree(node*  cur){
	if(cur->left != NULL && cur->right != NULL){
		destroyTree(cur->left);
		destroyTree(cur->right);
	} 
	free(cur);
}

node* removeFirst(node* cur, long nr, long diff){
	if(cur->update != 0)
		updateNode(cur);
	if(nr == 0)
		return cur;

	cur->nrC -= nr;
	if(cur->nrC == 0){
		destroyTree(cur);
		return NULL;
	}
	else{
		if(cur->left->nrC > nr){
			long diffSum = cur->left->sum;
			cur->left = removeFirst(cur->left, nr, diff);
			cur->sum = cur->left->sum + cur->right->sum;
			diffSum = diff + cur->left->sum - diffSum;
			cur->right->update += diffSum;
			if(cur->right->max > NEGINF)
				cur->right->max += diffSum;
			cur->max = cur->left->max > cur->right->max ? cur->left->max : cur->right->max;
			return cur;
		}
		
		else{
			nr -= cur->left->nrC;
			long diffSum = cur->left->sum;
			removeFirst(cur->left, cur->left->nrC, diff);
			diffSum = diff - diffSum;
			cur->right->update += diffSum;
			if(cur->right->max > NEGINF)
				cur->right->max += diffSum;
			cur->right = removeFirst(cur->right, nr, diffSum);
			node* retPointer = cur->right;
			free(cur);
			return retPointer;
		}
	}
}

void printTree(node* cur, int depth){
	printf("Depth: %d\tnrC: %ld\tsum: %ld\tmax: %ld\tupdate: %ld\n", depth, cur->nrC, cur->sum, cur->max, cur->update);
	if(cur->left != NULL)
		printTree(cur->left, depth+1);
	if(cur->right != NULL)
		printTree(cur->right, depth+1);
	return;
}

int main(void){
	cin >> N >> Q;
	node* tree = init(N, 0);
//	printTree(tree, 1);

	for(int i = 0; i < Q; i++){
		char in[10];
		scanf("%s", in);

		if(in[0] == 'g'){
			int pos, nr;
			scanf("%d %s %d", &pos, in, &nr);
			if(in[1] == 'i'){
				if(tree->nrC == 0){
					tree->nrC = 1;
					tree->sum = nr;
					tree->max = NEGINF;
				}
				else
					tree = insertFil(tree, pos, nr);
			}
			else{
				if(tree->nrC == 0){
					tree->nrC = 1;
					tree->sum = -nr;
				}
				else
					tree = insertFer(tree, pos, -nr, 0);
			}
		}

		else{
			int nr;
			scanf("%d", &nr);
			tree = removeFirst(tree, nr, 0);
			if(tree == NULL){
				tree = (node*) malloc(sizeof(node));
				tree->nrC = tree->sum = tree->max = tree->update = 0;
				tree->left = tree->right = NULL;
			}
		}
		printf("%ld\n", tree->max > 0 ? tree->max : 0);
//		printTree(tree, 1);
	}
}
