#include<stdio.h>
#define Nfrb 10 //max number of forbidden strings
#define Lfrb 10 //max length of forbidden strings
#define Nalp 26 //number of characters in the alphabet

typedef struct node{
	int progr[Nfrb];
	struct node* next[Nalp];
	struct node* prev[Nalp];
} node;

char[Nfrb][Lfrb+1] strings;
node* root;
int N, L;

int main(void){
	scanf("%d %d", &N, &L);
	for(int i = 0; i < N; i++)
		scanf("%s", strings[i]);

	root = (node*) malloc(sizeof(node));
	for(int i = 0; i < Nfrb; i++)
		root->progr[i] = 0;
}
