/**
 * 1.建立哈夫曼树：读入文件(*.souce)，统计文件中字符出现的频度，并以这些字符的频度作为权值，建立哈夫曼树。
 * 2.编码：利用已建立好的哈夫曼树，获得各个字符的哈夫曼编码，并对正文进行编码，然后输出编码结果，并存入文件(*.code)中。
 * 3.译码：利用已建立好的哈夫曼树将文件(*.code)中的代码进行译码，并输出译码结果，并存入文件(*.decode)中。
 * 4.利用位操作，实现文件的压缩与解压。(选)
 * 
 */
#include<stdio.h>
#include<malloc.h>
#include<string.h>
#define INTERNAL 1
#define LEAF 0
#define MAX 16	//MAXimum length of codeword, more the MAX more overhead
char padding;
unsigned char N;

typedef struct symCode
{ char x;
  char code[MAX];
}symCode;

// char ext[]=".hzip";
// char dext[]=".txt";
char ext[]=".code";    //压缩
char dext[]=".encode"; //解码

typedef struct node
{
	char x;
	int freq;
	char *code;
	int type;
	struct node *next;
	struct node *left;
	struct node *right;
}node;

node *HEAD,*ROOT;

void printll();
void makeTree();
void genCode(node *p,char* code);
void insert(node *p,node *m);
void addSymbol(char c);
void writeHeader(FILE *f);
void writeBit(int b,FILE *f);
void writeCode(char ch,FILE *f);
char *getCode(char ch);

node* newNode(char c)
{
	node *q;
	q=(node *)malloc(sizeof(node));
	q->x=c;
	q->type=LEAF;	//leafnode
	q->freq=1;
	q->next=NULL;
	q->left=NULL;
	q->right=NULL;
	return q;
}

int main(int argc , char ** argv)
{
	FILE *fp , *fp2;
	char ch;
	int t;
	HEAD = NULL;
	ROOT = NULL;

	if(argc <= 2)
	{
		printf("----------\n");
		printf("Usage:\n %s <input-file-to-zip> <zipped-output-file>\n***Huffman File Encoder***\nAuthor: erfenjiao\n",argv[0]);
		if(argc==2)
		{
			argv[2]=(char *)malloc(sizeof(char)*(strlen(argv[1])+strlen(ext)+1));
			strcpy(argv[2],argv[1]);
			strcat(argv[2],ext);
			argc++;
		}
		else
			return 0;
	}
	fp=fopen(argv[1],"rb");
	if(fp==NULL)
	{
		printf("[!]Input file cannot be opened.\n");
		return -1;
	}
	printf("----------\n");
	printf("Reading file : %s\n",argv[1]);
	while(fread(&ch , sizeof(char) , 1 , fp) != 0)
	{
		addSymbol(ch);
	}

	printf("----------\n");
	printf("construct huaffmanTree\n");
	makeTree();

	// printf("----------\n");
	// printf("\nAssigning Codewords.\n");
	// genCode(ROOT,"\0");	//preorder traversal


	
}

//统计，一条链表
void addSymbol(char c)
{
	node *p , *q , *m;
	if(HEAD == NULL)      //link is null , newNode.
	{
		HEAD = newNode(c);
		return ;
	}
	p = HEAD;
	q = NULL;
	if(p->x == c)           //find
	{
		p->freq++;          
		if(p->next == NULL)  //p node is end code in this link
		{
			return ;
		}
		if(p->freq > p->next->freq)  
		{
			HEAD = p->next;
			p->next = NULL;
			insert(p , HEAD);
		}
		return ;
	}

	while(p->next != NULL && p->x != c)  //依次往后查找
	{
		q = p;
		p = p->next;
	}

	if(p->x == c)
	{
		p->freq++;
        if(p->next == NULL)
			return;	
		if(p->freq > p->next->freq)
		{
			m = p->next;
			q->next = p->next;
			p->next = NULL;
			insert(p , HEAD);
		}
	}
	else          //not find
	{
		q = newNode(c);
		q->next = HEAD;
		HEAD = q;
	}

}

//按频率在列表中插入p，从m开始向右
//我们不能放置小于m的节点，因为我们没有ptr到m左边的节点
void insert(node *p,node *m)
{
	if(m->next==NULL)
	{  
		m->next=p; 
		return;
	}
	while(m->next->freq < p->freq)
	{  
		m=m->next;
	    if(m->next==NULL)
	    { 
			m->next=p; 
			return; 
		}
	}
  	p->next=m->next;
  	m->next=p;
}

void makeTree()
{
	printf("----------\n");
	printf("makeTree() begin...\n");
	node  *p,*q;
	p = HEAD;
	while(p != NULL)
	{
		q = newNode('@');
		q->type = INTERNAL;	 //internal node
		q->left = p;		
		q->freq = p->freq;
		printf("q->left ")
		if(p->next != NULL)  
		{
			p = p->next;
			q->right = p;	
			q->freq += p->freq;
		}
		p = p->next;	
		if(p == NULL)	
			break;
		if(q->freq <= p->freq)
		{
			q->next = p;
			p = q;
		}
		else
			insert(q , p);	//find appropriate position
	}//while
	ROOT=q; //q created at last iteration is ROOT of h-tree
}

void genCode(node *p,char* code)
{
	char *lcode , *rcode;
	static node *s;
	static int flag;
	if(p != NULL)
	{
	//sort linked list as it was
		if(p->type == LEAF)   //leaf node
		{	if(flag == 0) //first leaf node
			{
				flag = 1 ; 
				HEAD = p;
			}
			else	//other leaf nodes
			{ 
				s->next = p;
			}		//sorting LL
			p->next = NULL;
			s = p;
		}

	//assign code
		p->code = code;	//assign code to current node
	//	printf("[%c|%d|%s|%d]",p->x,p->freq,p->code,p->type);
		lcode=(char *)malloc(strlen(code)+2);
		rcode=(char *)malloc(strlen(code)+2);
		sprintf(lcode , "%s0" , code);
		sprintf(rcode , "%s1" , code);
	//recursive DFS
		genCode(p->left  , lcode);		//left child has 0 appended to current node's code
		genCode(p->right , rcode);
	}
}
