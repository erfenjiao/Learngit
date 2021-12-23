#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef char* HuffmanCode[6];

typedef struct
{
	int weight;
	int parent , Lchild , Rchild;
}HTNode , HuffmanTree[15];


void select(HuffmanTree ht , int m , int * s1 , int *s2)
{
	int c[30] = {0};
	int cnt = 0;
	for(int i = 1 ; i <= m ; i++)
	{
		if(ht[i].parent == 0)
		{
			c[cnt++] = ht[i].weight;
		}
	}
	
	for(int i = 0 ; i < cnt ; i++)
	{
		for(int j = 0 ; j < cnt-i-1 ; j++)
		{
			if(c[j] > c[j+1])
            {
				int temp = c[j];
				c[j] = c[j+1];
				c[j+1] = temp;
			}
		}
	}
	for(int i = 1 ; i <= m ; i++)
	{
		if(c[0] == ht[i].weight)
		{
			*s1 = i;
		}
		if(c[1] == ht[i].weight)
		{
			*s2 = i;
		}
	}
}



void Create(HuffmanTree ht , int w[])
{
	int s1,s2;
	for(int i = 0 ; i <= 6 ; i++)
	{
		ht[i].weight = w[i];
		ht[i].Lchild = 0;
		ht[i].Rchild = 0;
		ht[i].parent = 0;
	}
	for(int i = 7 ; i <= 11 ;i++)
	{
		ht[i].weight = 0;
		ht[i].Lchild = 0;
		ht[i].Rchild = 0;
		ht[i].parent = 0;
	}
	for(int i = 7 ; i <= 11 ; i++)
	{
		select(ht , i-1 , &s1 , &s2);
		ht[i].weight = ht[s1].weight + ht[s2].weight;
		ht[i].Lchild = s1;
		ht[i].Rchild = s2;
		ht[s1].parent = i;
		ht[s2].parent = i;
	}
}

void HuffmanCode1(HuffmanTree ht , HuffmanCode hc)
{
	char *cd;
	int start , c , p;
	cd = (char *)malloc(6*sizeof(char));
	cd[5] = '\0';
	for(int i = 1 ; i <= 6 ; i++)
	{
		start = 5;
		c = i;
		p = ht[i].parent;
		while(p != 0)
		{
			--start;
			if(ht[p].Lchild == c)
			{
				cd[start] = '0';
			}
			else
			{
				cd[start] = '1';
			}
			c = p;
			p = ht[p].parent;
		}
		hc[i] = (char*)malloc((6-start)*sizeof(char));
		strcpy(hc[i] , &cd[start]);
		
	}
	free(cd);
}

void Print(HuffmanCode hc)
{
	for(int i = 1 ; i <=6 ; i++)
	{
		switch(i)
		{
			case 1:
				printf("A:%s" , hc[1]);	
				break;
			case 2:
				printf("B:%s" , hc[2]);
				break;
			case 3:
				printf("C:%s" , hc[3]);
				break;
			case 4:
				printf("D:%s" , hc[4]);
				break;
			case 5:
				printf("E:%s" , hc[5]);
				break;
			case 6:
				printf("F:%s" , hc[6]);
				break;
		}
		printf("\n");
	}
}

void PrintLn(HuffmanTree ht , int p)
{
	switch(p)
	{
		case 1:
			printf("A");
			break;
		case 2:
			printf("B");
			break;
		case 3:
			printf("C");
			break;
		case 4:
			printf("D");
			break;
		case 5:
			printf("E");
			break;
		case 6:
			printf("F");
			break;
	}
}

void TranHuffmanCode(HuffmanTree ht , char* c)
{
	int p=11;
    int i;
	for(i = 0 ; c[i] != '\0' ; i++)
	{
		if(c[i] == '0')
		{
			p = ht[p].Lchild;
			if(ht[p].Lchild == 0 && ht[p].Rchild == 0)
			{
				PrintLn(ht , p);
				p = 11;
			}
		}
		if(c[i] == '1')
		{
			p = ht[p].Rchild;
			if(ht[p].Lchild == 0 && ht[p].Rchild == 0)
			{
				PrintLn(ht , p);
				p = 11;
			}
		}
	}
}

int main()
{
	HuffmanTree ht;
	int w[7];
	for(int i = 1 ; i <= 6 ;i++)
	{
		scanf("%d",&w[i]);
	}
	Create(ht , w);
	HuffmanCode hc;         //typedef char *  HuffmanCode
	HuffmanCode1(ht , hc);
	char s[6] , c[100]; 
	scanf("%s",s);
	scanf("\n%s",c);
	Print(hc);
	for(int i = 0 ; i < strlen(s) ; i++)
	{
		switch(s[i])
		{
			case 'A': printf("%s",hc[1]); break;
			case 'B': printf("%s",hc[2]); break;
			case 'C': printf("%s",hc[3]); break;
			case 'D': printf("%s",hc[4]); break;
			case 'E': printf("%s",hc[5]); break;
			case 'F': printf("%s",hc[6]); break;
				
		}
	}
	printf("\n");
    
	TranHuffmanCode(ht , c);
	printf("\n");
	return 0;
}
