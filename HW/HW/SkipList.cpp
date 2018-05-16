const int MaxLevel = 3;
const int MAX = 10000;
const int MIN = -1;

#include<cstdlib>
#include<ctime>
#include<iostream>
using namespace std;

struct Node{
	int key;
	int value;
	Node *next;
	Node *down;
};

struct SkipList{
	int level;
	Node **head;
	Node *tail;
};

//to implement insertion, deletion, and searching.

Node *createNode(int level, int key, int value)
{
	Node *node = new Node;
	node -> key = key;
	node -> value = value;
	return node;
}

SkipList *createSkl(void)
{
	SkipList *skl = new SkipList;
	skl -> level = 0;
	skl -> head = new Node*[MaxLevel];
	skl->tail = new Node;
	skl->tail->down = nullptr;
	skl->tail->next = nullptr;
	skl->tail->key = MAX;
	for(int i=0;i<MaxLevel;i++)
	{
		skl->head[i] = new Node;
		skl->head[i]->key = MIN;
		skl->head[i]->next = skl->tail;
		skl->head[i]->down = ((i==0)?nullptr:(skl->head[i-1]));
	}
	return skl;
}

//insertion
int randomLevel()
{
	srand(static_cast<unsigned int>(time(NULL)));

	int k = 0;
	while(rand()%2)
	{
		k++;
	}
	k = (k < MaxLevel) ? k : MaxLevel;
	return k;
}
int insertNode(SkipList *skl ,int key, int value)
{
	int k = randomLevel();

	Node **update = new Node*[k+1];
	Node *p = skl -> head[k];
	int n = k;
	while(p)
	{
		while(p->next->key < key)
		{ 
			p = p->next;
		}
		update[n] = p;
		p = p->down;
		n--;
	}
	for(int i=0;i<=k;i++)
	{
		Node *pnode = new Node;
		pnode->next = update[i]->next;
		update[i]->next = pnode;
		pnode->down = ((i==0)?nullptr:(update[i-1]->next));
		pnode->key = key;
		pnode->value=value;
	}
	return 0;
}

int searchNode(SkipList *skl ,int key)
{
	Node *p = skl -> head[MaxLevel-1];
	while (true)
	{
		while(p->next->key<key)
		{
			p=p->next;
		}
		if(p->down == nullptr)
		{
			if(p->next->key == key)
			{
				return p->next->value;
			}
			else
			{
				cout << "There is no such node!!!" << endl;
				return -1;
			}
		}
		p = p->down;
	}
}

bool deleteNode(SkipList *skl ,int key)
{
	Node *p = skl -> head[MaxLevel-1];
	Node *firstDelete = nullptr;
	bool flag = false;
	while(p)
	{
		while(p->next->key<key)
		{
			p = p->next;
		}
		if(p->next->key==key)	
		{
			firstDelete = p->next;
			p->next = p->next->next;
			delete firstDelete;
			firstDelete = nullptr;
			flag = true;
		}
		else
		{
			p = p->down;
		}
	}
	return flag;
}

int main(void)
{
	int n = 8, i;
	int value[7], key[7];
	srand(time(NULL));
	for (i = 0; i < n; i++)
		key[i] = i;

	for (i = n - 1; i > 0; i--){
		long r = rand() % i;
		long temp = key[i];
		key[i] = key[r];
		key[r] = temp;
		value[i] = rand() % n;
	}
	value[0] = rand() % n;
	SkipList *skl = createSkl();
	for (int i = 0; i < n; i++)
		insertNode(skl, key[i], value[i]);
	cout << searchNode(skl, 5) << endl;
	deleteNode(skl, 5);
	cout << searchNode(skl, 5) << endl;
	return 0;
}