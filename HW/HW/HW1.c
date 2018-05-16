#include <stdio.h>
#include <stdlib.h>
#define  max(a,b) ((a)>(b)?(a):(b))

struct AvlNode;
typedef struct AvlNode *Position;
typedef struct AvlNode *AvlTree;

struct AvlNode
{
	int element;
	AvlTree left;
	AvlTree right;
	int height;	
};

int Height(AvlTree T)
{
	if (T == NULL)
		return -1;
	else
		return T->height;
}

Position LLRotation(Position k2)
{
	Position k1 = k2->left;
	k2->left = k1->right;
	k1->right = k2;
	k2->height = max(Height(k2->left), Height(k2->right)) + 1;
	k1->height = max(Height(k1->left), Height(k1->right)) + 1;
	return k1;
}

Position RRRotation(Position k1)
{
	Position k2 = k1->right;
	k1->right = k2->left;
	k2->left = k1;
	k2->height = max(Height(k2->left), Height(k2->right)) + 1;
	k1->height = max(Height(k1->left), Height(k1->right)) + 1;
	return k2;
}

Position LRRotation(Position k3)
{
	k3->left = RRRotation(k3->left);
	return LLRotation(k3);
}

Position RLRotation(Position k3)
{
	k3->right = LLRotation(k3->right);
	return RRRotation(k3);
}
AvlTree Insert(int x, AvlTree T)
{
	if (T == NULL)
	{
		T = (AvlTree)malloc(sizeof(struct AvlNode));
		T->element = x;
		T->left = T->right = NULL;
		T->height = 0;
	}
	else
	{
		if (x < T->element)
		{
			T->left = Insert(x, T->left);
			if (Height(T->left) - Height(T->right) == 2)
			{
				if (x < T->left->element)	//LL Rotation
					T = LLRotation(T);
				else
					T = LRRotation(T);
			}
		}
		else
		{
			T->right = Insert(x, T->right);
			if (Height(T->right) - Height(T->left) == 2)
			{
				if (x > T->right->element)
					T = RRRotation(T);
				else
					T = RLRotation(T);
			}
		}
	}
	T->height = max(Height(T->left), Height(T->right)) + 1;
	return T;
}
int main()
{
	int n,i,x;
	AvlTree T = NULL;
	scanf("%d", &n);
	for (i = 0; i < n; i++)
	{
		scanf("%d", &x);
		T = Insert(x, T);
	}
	printf("%d", T->element);
	system("pause");
}