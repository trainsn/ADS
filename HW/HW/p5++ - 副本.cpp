#include <iostream>
#include <queue>
#include <algorithm> 
using namespace std;

const int SIZE = 67;

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

int substr(string str1, string str2)	// judge the prefix 
{
	for (int i = 0; str1[i] != '\0' && str2[i]!='\0'; i++)
		if (str1[i] != str2[i])
			return 0;
	return 1;
}

int main()
{
	freopen("p5in.txt", "r", stdin);
	freopen("p5out.txt", "w", stdout);
	int n;
	int count = 1;	//number of case
	//while(true)
	{
		cin >> n; 
		if(n == 0)
		{
			return 0;	
		}	
		//cout << "case " << count++ << ":" << endl; 
		cost = 0;
		char ch;
		int f[SIZE];
		priority_queue<pNode ,vector<pNode>, cmp> que;	//the heap is used for store the node of Huffman tree  

		for (int i = 0; i < n; i++){
			Node* temp = new Node;
			cin >> temp->ch >>  temp->fre;
			f[i] = temp->fre;
			temp->left = temp->right = NULL;
			que.push(temp);
		}
	
		Node *z, *l, *r;
		//Construct the Huffman tree 
		for (int i = 0; i < n-1; i++){	 
			z = new Node;
			/*We repeated extract tow nodes l and r of lowest frequency from the queue 
			and replace them in the queue with a new node z representing their merger*/
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
		dfs(que.top(),0);
		
		int test, len[SIZE] = { 0 };
		char exp[SIZE][SIZE];
		string code[SIZE];
		
		//input the test case 
		cin >> test;
		cin.get();	// get line break
		
		for (int i = 0; i < test; i++){
			int tempCost = 0;
			//for each testCase, compute its cost 
			for (int j = 0; j < n; j++){
				len[j] = 0;
				cin.getline(exp[j],SIZE);
				code[j] = &exp[j][2];
				//cout << exp[j] << endl;			
				tempCost += f[j] * code[j].length();
			}
			//cout << "cost is : " << tempCost << endl;
			//for each test case, we should first judge whether there it has the prefix property 
			sort(code, code + n);
			bool prefix = true;
			for (int j = 0; j < n - 1; j++)
				if (substr(code[j], code[j + 1]))
				{
				cout << "No" << endl;
				prefix = false;
				break;
				}
			if (!prefix)
				continue;
			//if the test case has the prefix property and its cost equals the Huffman tree cost, it is valid 
			if (tempCost == cost)
				cout << "Yes" << endl;
			else
				cout << "No" << endl;
		}
	}
	system("pause");
	
}
