
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
/***********************************/
/*********Data structure************/
/*1.Chain table of frequency       */
/*2.Our Huffman tree               */
/***********************************/
struct node{
		int element;
		struct node* next;
		struct node* left;
		struct node* right;
	};
typedef struct node* Gre;
/***********************************/
/************Function***************/
/*1.Name: Judge                    */
/*Judge codes is right or wrong    */
/*2.Name: W_pre                    */
/*Find its prefix whether is itself*/ 
/*3.Name: Wpl                      */
/*To determine the code's Wpl      */
/*whether is the smallest          */
/*4.Name: Wpl1                     */
/*To calculate Huffman             */
/*coding least WPL value           */
/***********************************/
void judge(char* Node_c,int* Node_f,char** code,int number,int length);//1.Judge function
int W_pre(char** code,int length);                                     //2.Compare function
int Wpl(char** code,int length,int* Fnode);                            //3.calculate function1
int Wpl1(Gre head,int height);                                         //4.calculate function2
/***********************************/
/*********Main Function*************/
/*Introduction:                    */
/* Get datas                        */
/*Function:                        */
/*1.Standard input and output      */
/*2.Proper use functions           */
/*  to get the right result        */
/***********************************/
int main()
{
	int Node_number;
	char* Node_c;
	int* Node_f;
	int count=1;                                                        //To storage the frequency of case
	scanf("%d",&Node_number);
	while(Node_number!=0)
	{
	Node_c=(char*)malloc(Node_number*(sizeof(char)));
	Node_f=(int*)malloc(Node_number*(sizeof(int)));
	int i;
	for(i=0;i<Node_number;i++)
		scanf("%s%d",&Node_c[i],&Node_f[i]);
    int s_number;
	scanf("%d",&s_number);
	char** code=(char**)malloc(s_number*Node_number*(sizeof(char*)));
	for(i=0;i<s_number*Node_number;i++)
		code[i]=(char*)malloc(63*sizeof(char));
	char* Node_c1;
	Node_c1=(char*)malloc(s_number*Node_number*(sizeof(char)));
	for(i=0;i<s_number*Node_number;i++)
		scanf("%s%s",&Node_c1[i],code[i]);
	printf("Case %d\n",count++);                                        //Flag for each input 
	for(i=0;i<s_number;i++)
		judge(Node_c,Node_f,code,i,Node_number);
	scanf("%d",&Node_number);
	}
}
/***********************************/
/*********Judge Function************/
/*Introduction:                    */
/* Enter the array to judge        */
/* and output standard results     */
/*Function:                        */
/*1.Proper the functions           */
/*  to determine the code          */
/*  whether meets the requirements */
/***********************************/
void judge(char* Node_c,int* Node_f,char** code,int number,int length)
{
	char** p=&code[number*length];                                   //The address used to store the value of each student in each Case
	int x1=W_pre(p,length);
	int x2=Wpl(p,length,Node_f);
	if(x1==0&&x2==1)                                                 //If each encoding does not have a prefix that is another encoding 
		printf("Yes\n");                                             //and the WPL value is the smallest, it is the correct encoding
	else printf("No\n");
}
/***********************************/
/*****Prefix Judgment Function******/
/**********(character)**************/
/*Introduction:                    */
/* Enter two characters to judge   */
/* their prefix                    */
/*Function:                        */
/*1.Find a shorter length in two   */
/*2.Take the same number from      */
/*  longer then determine whether  */
/*  the two characters  are equal  */
/*3.Return 0 for equal             */
/***********************************/
int W_pre1(char* a,char* b)                                        
{
	int a1=strlen(a);
	int b1=strlen(b);                                               //Take a,b code length
	char* x;
	if(a1<=b1)                                                      //Get the same number from long code and give X
	{
		x=(char*)malloc((a1+1)*sizeof(char));                       
	int i;
	for(i=0;i<a1;i++)
		x[i]=b[i];
	x[i]='\0';
	return strcmp(a,x);                                             //Return result as simplr of whether equal
	}
	else
	{
		x=(char*)malloc((b1+1)*sizeof(char));
	int i;
	for(i=0;i<b1;i++)
		x[i]=a[i];
	x[i]='\0';
	return strcmp(b,x);
	}
}
/***********************************/
/*****Prefix Judgment Function******/
/*************(array)***************/
/*Introduction:                    */
/* Enter array to judge all of     */
/* its codes' prefix               */
/*Function:                        */
/*1.Get the array need to judge    */
/*2.Call character judgment        */
/*  function to determine          */
/*  whether the code has prefix    */
/*3.Return 1 for equal             */
/***********************************/
int W_pre(char** code,int length)
{
	int i;
	int j;
	int l=1;                                                       //Initialization is not prefix 
	for(i=0;i<length-1;i++)                                        //The comparison of whether has prefix or not of the arrary
		for(j=i+1;j<length;j++)
		{
			l=W_pre1(code[i],code[j]);
			if(l==0)
				return 1;
		}

		return 0;
}
/***********************************/
/*******WPL Judgment Function*******/
/*Introduction:                    */
/* Enter code to build             */
/* its  Huffman coding tree.       */
/* Then determine whether is       */
/* the minimum coding value of the */
/* coding from question            */
/*Function:                        */
/*1.Calculate the WPL of question  */
/*2.Build Huffman coding tree      */
/*  of the question                */
/*3.Judge whether the code'WPL     */
/*  is minimum                     */
/***********************************/
int Wpl(char** code,int length,int* Fnode)
{
	int* fnode=(int*)malloc(length*sizeof(int));                  //Create a new frequency array in order to prevent the original frequency array from being changed
	int i;
	for(i=0;i<length;i++)
		fnode[i]=Fnode[i];
	
	int wpl2=0;
	for(i=0;i<length;i++)
	wpl2=wpl2+strlen(code[i])*fnode[i];                           //Calculate WPL of question 
	
	int j;
	int temp;
	for(i=0;i<length;i++)                                         //Sort the frequency array in ascending order 
		for(j=0;j<length-i-1;j++)
			if(fnode[j]>fnode[j+1])
			{
				temp=fnode[j+1];
				fnode[j+1]=fnode[j];
				fnode[j]=temp;
			}                                                    

	Gre head,tail,p;
	head=NULL;
	tail=head;
	for(i=0;i<length;i++)                                        
	{
		if(head==NULL)
		{
			head=(Gre)malloc(sizeof(struct node));
			head->element=fnode[i];
			head->left=NULL;
			head->right=NULL;
			head->next=NULL;
			tail=head;
		}
		else
		{
			p=(Gre)malloc(sizeof(struct node));
			p->element=fnode[i];
			p->left=NULL;
			p->right=NULL;
			p->next=NULL;
			tail->next=p;
			tail=p;
		}
	}                                                            //Convert the frequency array to a linked list 
	Gre ptr=head;
	while(ptr->next->next!=NULL)                                 //Build the Huffman tree by greedy algorithm.
	{                                                            //Due to the ascending sort, you can find the smallest two items by comparing the first three items
		if(ptr->element<=ptr->next->next->element)               //If the first two items of the weighted minimum, then create a new node, 
		{                                                        //the weight of the sum of the weights of the two items, which are the left and right sides of the number of two                                
			Gre q1;
			q1=(Gre)malloc(sizeof(struct node));
			q1->element=ptr->element+ptr->next->element;
			q1->left=ptr;
			q1->right=ptr->next;
			q1->next=ptr->next->next;
			ptr=q1;                                              //The new node as the head of the list, continue to cycle 
		}
		else                                                     //If the latter two weighted minimum, do as above
		{
			Gre q2;
			q2=(Gre)malloc(sizeof(struct node));
			q2->element=ptr->next->element+ptr->next->next->element;
			q2->left=ptr->next;
			q2->right=ptr->next->next;
			q2->next=ptr->next->next->next;                      //The new node connects the header node and the fourth item to continue the loop
			ptr->next=q2;

		}
	}

	Gre q3;
    q3=(Gre)malloc(sizeof(struct node));                        //Creates a new node, and the last two are merged into its left and right children
	q3->left=ptr;
	q3->right=ptr->next;
	q3->next=NULL;
	q3->element=0;
	int wpl1=0;
	wpl1=Wpl1(q3,0);                                            //Calculate the WPL of this Huffman code
	if(wpl2==wpl1)
		return 1;                                               //Judge the two WPL values
	else return 0;

}
/***********************************/
/******WPL calculate Function*******/
/*Introduction:                    */
/* Enter Huffman tree              */
/* calculate its WPL               */
/*Function:                        */
/*1.Get depth of the leaf nodes    */
/*2.Depth multiplied by frequency  */
/*  and added all together         */
/***********************************/
int Wpl1(Gre head,int height)                                   //Get the WPL by recursion
{
	if(head!=NULL)
		if(head->left==NULL)
			return height*head->element;                        //If it is a leaf node, its frequency value is multiplied by the depth 
		else                                                    //Depth plus 1
			return Wpl1(head->left,height+1)+Wpl1(head->right,height+1);
}