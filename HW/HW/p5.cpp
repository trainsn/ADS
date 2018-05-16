#include <stdio.h>
#include <stdlib.h> 
#include <queue>
#include <iostream>
#define SIZE 67
using namespace std;

typedef struct Node		//Node in the Huffman tree 
{
	char ch;
	int fre;
	Node* left;
	Node* right;
}*pNode;

struct cmp{	// define the compare rule for Huff,an tree node, used in the STl priority queue
	bool operator()(pNode node1, pNode node2){
		return node1->fre > node2->fre;
	}
};
int cost = 0;	//store the cost for the Huffman tree 

void dfs(pNode root,int depth)	//traverse the Huffman tree to compute the cost
{
	if (!root->left && !root->right)
		cost += root->fre* depth;
	if (root->left)
		dfs(root->left, depth + 1);
	if (root->right)
		dfs(root->right, depth + 1);
}

int substr(char* str1, char* str2)	// judge the prefix 
{
	for (int i = 2; str1[i] != '\0'; i++)
		if (str1[i] != str2[i])
			return 0;
	return 1;
}

int main()
{
	int n,i;
	char ch;
	int f[SIZE];
	priority_queue<pNode ,vector<pNode>, cmp> que;	//the heap is used for store the node of Huffman tree  
	while (1){
		cost = 0;
		scanf("%d", &n);
		if (!n)
			return 0;
		while (!que.empty())
			que.pop();

		for (i = 0; i < n; i++){
			Node* temp = new Node;
			scanf("%c", &ch);
			scanf("%c %d", &temp->ch, &temp->fre);
			f[i] = temp->fre;
			temp->left = temp->right = NULL;
			que.push(temp);
		}

		Node *z, *l, *r;
		//Construct the Huffman tree 
		for (i = 0; i < n - 1; i++){
			z = (Node*)malloc(sizeof(struct Node));
			//We repeated extract tow nodes l and r of lowest frequency from the queue and replace them in the queue with a new node z representing their merger
			l = que.top();
			que.pop();
			z->left = l;
			r = que.top();
			z->right = r;
			que.pop();

			//the node z has l as its left child and r as its right child and the frequency of z is computed as the sum of l and r 
			z->fre = l->fre + r->fre;
			que.push(z);
		}

		//traverse the Huffman tree for the cost 
		dfs(que.top(), 0);

		int test, len[SIZE] = { 0 }, j;
		char exp[SIZE][SIZE], encode[SIZE][SIZE];

		//input the test case 
		scanf("%d", &test);
		scanf("%c", &ch);
		for (i = 0; i < test; i++){
			int tempCost = 0;
			//for each testCase, compute its cost 
			for (j = 0; j < n; j++){
				len[j] = 0;
				cin.getline(exp[j], SIZE);
				for (int k = 2; exp[j][k] != '\0'; k++)
				{
					len[j]++;
				}
				tempCost += f[j] * len[j];
			}

			//for each test case, we should first judge whether there it has the prefix property 
			int flag = 1;
			for (j = 0; j < n; j++)
			{
				for (int k = 0; k < n; k++)
					if (j != k && len[j] <= len[k] && substr(&exp[j][0], &exp[k][0]))
					{
					printf("No\n");
					flag = 0;
					break;
					}
				if (!flag)
					break;
			}
			if (!flag)
				continue;

			//if the test case has the prefix property and its cost equals the Huffman tree cost, it is valid 
			if (tempCost == cost)
				printf("Yes\n");
			else
				printf("No\n");
		}
	}
	
	system("pause");
}
