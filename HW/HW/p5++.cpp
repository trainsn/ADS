#include <iostream>
#include <queue>
#include <algorithm> 
#include <string>
using namespace std;

const int SIZE = 67;

typedef struct Node		//Node in the Huffman tree 
{
	char ch;
	int fre;
	Node* left;
	Node* right;
}*pNode;

struct cmp{	// define the compare rule for Huff,an tree node, used in the STL priority queue
	bool operator()(pNode node1, pNode node2){
		return node1->fre > node2->fre;
	}
};
int cost = 0;	//store the cost for the Huffman tree 

void dfs(pNode root,int depth,string code)	//traverse the Huffman tree to compute the cost
{	
	
	if (!root->left && !root->right)
	{
		cost += root->fre* depth;
		cout << root->ch << " " << code << endl;
	}
	if (root->left)
		dfs(root->left, depth + 1, code + '0');
	if (root->right)
		dfs(root->right, depth + 1, code + '1');
	
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

	cin >> n;
	if (n == 0)
	{
		return 0;
	}
	//cout << "case " << count++ << ":" << endl; 
	cost = 0;
	char ch;
	int f[SIZE];
	priority_queue<pNode, vector<pNode>, cmp> orique,que;	//the heap is used for store the node of Huffman tree  

	for (int i = 0; i < n; i++){
		Node* temp = new Node;
		cin >> temp->ch >> temp->fre;
		f[i] = temp->fre;
		temp->left = temp->right = NULL;
		orique.push(temp);
		count *= 2;
	}

	//while(true)
	for (int c = 0; c < count / 2; c++)
	{
		int tcount = c;
		Node *z, *l, *r;
		que = orique;
		//Construct the Huffman tree 
		for (int i = 0; i < n - 1; i++){
			z = new Node;
			/*We repeated extract tow nodes l and r of lowest frequency from the queue
			and replace them in the queue with a new node z representing their merger*/
			l = que.top();
			que.pop();
			r = que.top();
			que.pop();

			if (tcount%2 == 0)
			{
				z->left = l;
				z->right = r;
			}
			else {
				z->left = r;
				z->right = l;
			}
			tcount /= 2;
			//the node z has l as its left child and r as its right child and the frequency of z is computed as the sum of l and r 
			z->fre = l->fre + r->fre;
			que.push(z);
		}

		//traverse the Huffman tree for the cost 
		string str;
		dfs(que.top(), 0, str);
		cout << endl;
	}
	system("pause");
	
}
