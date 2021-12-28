#define MAX 16	//MAXimum length of codeword, more the MAX more overhead
char padding;
unsigned char N;

typedef struct symCode
{ char x;
  char code[MAX];
}symCode;

char ext[]=".code";      //压缩
char dext[]=".decode";   //解压

char *bitsInChar(char n)
{
    int i,k,and,j;
    char *temp = (char *)malloc(9*sizeof(char));
    j=0;

    for(i=7;i>=0;i--)
    {
        and = 1 << i;
        k = n & and;
        if(k == 0) 
            temp[j++]='0'; 
        else 
            temp[j++]='1';
    }
    temp[j]='\0';
    return temp;
}