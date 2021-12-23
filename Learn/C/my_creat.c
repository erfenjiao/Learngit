//使用open系统调用在当前目录下创建一个名为example_62.c的文件，且新文件的权限为所有人均可读写
#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<errno.h>

int main()
{
    int fd;
    if((fd=open("example_62.c",O_CREAT|O_EXCL,S_IRUSR|S_IWUSR))==-1)
    //O_CREAT:若文件不存在则自动创立该文件，只有在此时才会用到第三个参数mode,以说明新文件的存取权限
    //O_EXCL:如果O_CREAT也被设置，此指令会去检查文件是否存在，不存在则创立该文件，若文件一存在将会导致打开方式出错
    {
        //if((fd=creat("example_62.c",S_IRWXU))==-1)
        //{
        perror("open");
        //printf("open:%s    with errno:%d\n",strerror(errno),errno);
        exit(1);
    }
    else
    {
        printf("creat file success\n");
    }
    close(fd);
    return 0;
        
}
