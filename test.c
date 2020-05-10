//#include <stdio.h>
//#include <string.h>
//#include "mat.h"
//#include <dirent.h>
//#include <sys/stat.h>
//#include <stdlib.h>
//

//char filename[256][8];
//int len = 0;
//int trave_dir(char* path, int depth)
//{
//    DIR *d; //声明一个句柄
//    struct dirent *file; //readdir函数的返回值就存放在这个结构体中
//    struct stat sb;
//
//    if(!(d = opendir(path)))
//    {
//        printf("error opendir %s!!!\n",path);
//        return -1;
//    }
//    while((file = readdir(d)) != NULL)
//    {
//        //把当前目录.，上一级目录..及隐藏文件都去掉，避免死循环遍历目录
//        if(strncmp(file->d_name, ".", 1) == 0)
//            continue;
//        strcpy(filename[len++], file->d_name);
//    }
//    closedir(d);
//    return 0;
//}
//int main()
//{
//    int depth = 1;
//    int i;
//    trave_dir("../../Dataset_Numbers/", depth);
//    for(i = 0; i < len; i++)
//    {
//        printf("%d\t", atoi(filename[i]) % 10);
//    }
//    printf("\n");
//    return 0;
//}



/*
int readFileList(char *basePath)
{
    DIR *dir;
    struct dirent *ptr;
    char base[1000];

    if ((dir=opendir(basePath)) == NULL)
    {
        perror("Open dir error...");
        exit(1);
    }

    while ((ptr=readdir(dir)) != NULL)
    {
        if(strcmp(ptr->d_name,".")==0 || strcmp(ptr->d_name,"..")==0)    ///current dir OR parrent dir
            continue;
        else if(ptr->d_type == 8)    ///file
            printf("d_name:%s/%s\n",basePath,ptr->d_name);
        else if(ptr->d_type == 10)    ///link file
            printf("d_name:%s/%s\n",basePath,ptr->d_name);
        else if(ptr->d_type == 4)    ///dir
        {
            memset(base,'\0',sizeof(base));
            strcpy(base,basePath);
            strcat(base,"/");
            strcat(base,ptr->d_name);
            readFileList(base);
        }
    }
    closedir(dir);
    return 1;
}

int main(void)
{
    DIR *dir;
    char basePath[1000];

    ///get the current absoulte path
    memset(basePath,'\0',sizeof(basePath));
    getcwd(basePath, 999);
    printf("the current dir is : %s\n",basePath);

    ///get the file list
    memset(basePath,'\0',sizeof(basePath));
    strcpy(basePath,"./XL");
    readFileList(basePath);
    return 0;
}
*/

#include <stdlib.h>
#include <stdio.h>

int main()
{
    int* a = (int*)malloc(3 * sizeof(int));
    int* b = (int*)malloc(2 * sizeof(int));
    for(int i = 0; i < 3; ++i)
    {
        a[i] = i;
        if(i < 2 ) b[i] = i + 1;
    }

    realloc(a, 2 * sizeof(int));
    a = b;
    printf("%d\n", a[2]);
    return 0;
}