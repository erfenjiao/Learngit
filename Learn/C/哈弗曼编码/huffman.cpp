/**
 * ①读取当前目录下的txt文件初始化哈夫曼编码和哈夫曼树
 * ②读取原始文件进行哈夫曼编码，并保存在你输入的文件里
 * ③读取哈夫曼编码文件进行解码，并保存在你输入的文件里
 * ④形象地输出哈夫曼树
 * ⑤显示哈夫曼编码程序的运行状态
 * ⑥退出程序 
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

char ext[]=".hzip";
char dext[]=".txt";

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



int main(int argc , char ** argv)
{
	FILE *fp , *fp2;
	char ch;
	int t;
	HEAD = NULL;
	ROOT = NULL;

	if(argc <= 2)
	{
		printf("Usage:\n %s <input-file-to-zip> <zipped-output-file>\n***Huffman File Encoder***\nAuthor: erfenjiao\n",argv[0]);
	}
	fp=fopen(argv[1],"rb");
	if(fp==NULL)
	{
		printf("[!]Input file cannot be opened.\n");
		return -1;
	}
	printf("")
	
}
