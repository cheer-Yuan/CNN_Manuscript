//
// Created by cheerfulliu on 14/01/2020.
//

#include "data_Images.h"


#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "rgb2Grayscale.h"
#include "mat.h"


//Image reader
ImgArr read_Img(const char* filename)
{
    FILE *fp = NULL;
    fp = fopen(filename,"rb+");
    if(fp == NULL)
        printf("Failed to open the file\n");
    assert(fp);

    char buff[16];      //image's type

    int number_of_images = 1;
    int n_rows = 0;
    int n_cols = 0;

    //read image format
    if (!fgets(buff, sizeof(buff), fp))
    {
        perror(filename);
        exit(1);
    }

    //check the image format
    if (buff[0] != 'P' || buff[1] != '6')
    {
        fprintf(stderr, "Invalid image format (must be 'P6')\n");
        exit(1);
    }

    // initialize arrays of the image
    ImgArr imgarr=(ImgArr)malloc(sizeof(ImgArr));
    imgarr->ImgNum=number_of_images;
    imgarr->ImgPtr=(MinstImg*)malloc(number_of_images*sizeof(MinstImg));

    //read image size information
    if (fscanf(fp, "%d %d", &n_rows, &n_cols) != 2)
    {
        fprintf(stderr, "Invalid image size (error loading '%s')\n", filename);
        exit(1);
    }

    //jump useless lines
    while(fgetc(fp) !='\n');
    while(fgetc(fp) !='\n');

    int compt = 0;

    for(int i = 0; i < number_of_images; ++i)
    {
        imgarr->ImgPtr[i].r=n_rows;
        imgarr->ImgPtr[i].c=n_cols;
        imgarr->ImgPtr[i].ImgData=(float**)malloc(n_rows*sizeof(float*));
        for(int r = 0; r < n_rows; ++r)
        {
            imgarr->ImgPtr[i].ImgData[r]=(float*)malloc(n_cols*sizeof(float));
            for(int c = 0; c < n_cols; ++c)
            {
                // transfer to float
                unsigned char rr, g, b = 0;
                fread((unsigned char*) &rr, 1,1,fp);
                fread((unsigned char*) &g, 1,1,fp);
                fread((unsigned char*) &b, 1,1,fp);

                imgarr->ImgPtr[i].ImgData[r][c]=(float)(rgb2Grayscale(rr, g, b));
                compt++;
            }
            printf("\n");
        }
    }

    for (int i = 0; i < 128; ++i)
    {
        for(int j = 0; j < 128; ++j)
        {
            float a = imgarr->ImgPtr[0].ImgData[i][j];
            //if (a != 255.0) printf("%f\t", imgarr->ImgPtr[0].ImgData[i][j]);
        }
        printf("\n");
    }

    fclose(fp);
    return imgarr;
}

//label_Reader
LabelArr read_Lable(const char* filename)
{
    FILE  *fp=NULL;
    fp=fopen(filename,"rb+");
    if(fp==NULL)
        printf("open file failed\n");
    assert(fp);

    int number_of_labels = 1;
    int label_long = 10;


    //if the file contains a number of labels, read it (here no)
    //fread((unsigned char*)&number_of_labels,sizeof(number_of_labels),1,fp);
    //printf("%d\n", number_of_labels);

    // initialize
    LabelArr labarr=(LabelArr)malloc(sizeof(LabelArr));
    labarr->LabelNum=number_of_labels;
    labarr->LabelPtr=(MinstLabel*)malloc(number_of_labels*sizeof(MinstLabel));

    for(int i = 0; i < number_of_labels; ++i)
    {
        labarr->LabelPtr[i].l=10;
        labarr->LabelPtr[i].LabelData=(float*)calloc(label_long,sizeof(float));
        unsigned char temp = 0;
        fread((int*) &temp, sizeof(temp),1,fp);
        labarr->LabelPtr[i].LabelData[(int)temp]=1.0;
    }
    fclose(fp);
    return labarr;
}

//convert int to char
char* intTochar(int i)
{
    int itemp=i;
    int w=0;
    while(itemp>=10){
        itemp=itemp/10;
        w++;
    }
    char* ptr=(char*)malloc((w+2)*sizeof(char));
    ptr[w+1]='\0';
    int r;  //rest
    while(i>=10){
        r=i%10;
        i=i/10;
        ptr[w]=(char)(r+48);
        w--;
    }
    ptr[w]=(char)(i+48);
    return ptr;
}

//combine 2 str
char * combine_strings(char *a, char *b)
{
    char *ptr;
    int lena=strlen(a),lenb=strlen(b);
    int i,l=0;
    ptr = (char *)malloc((lena+lenb+1) * sizeof(char));
    for(i=0;i<lena;i++)
        ptr[l++]=a[i];
    for(i=0;i<lenb;i++)
        ptr[l++]=b[i];
    ptr[l]='\0';
    return(ptr);
}

//save the image data
void save_Img(ImgArr imgarr,char* filedir)
{
    int img_number = imgarr->ImgNum;

    int i, r;
    for (i = 0; i < img_number; i++) {
        const char *filename = combine_strings(filedir, combine_strings(intTochar(i), ".gray"));
        FILE *fp = NULL;
        fp = fopen(filename, "wb");
        if (fp == NULL)
            printf("write file failed\n");
        assert(fp);

        for (r = 0; r < imgarr->ImgPtr[i].r; r++)
            fwrite(imgarr->ImgPtr[i].ImgData[r], sizeof(float), imgarr->ImgPtr[i].c, fp);

        fclose(fp);
    }
}


