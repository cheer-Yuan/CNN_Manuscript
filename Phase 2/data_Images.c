//
// Created by cheerfulliu on 14/01/2020.
//

#include "data_Images.h"


#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "rgb2Grayscale.h"



//Image reader
ImgArr read_Img(const char* filename)
{
    FILE *fp = NULL;
    fp = fopen(filename,"rb");
    if(fp == NULL)
        printf("Failed to open the file\n");
    assert(fp);

    char buff[16];      //image's type
    int rgb_Depth;

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

    fscanf(fp,"%*[^\n]%*c");

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
                int rr, g, b = 0;
                fread((char*) &rr, 1,1,fp);
                fread((char*) &g, 1,1,fp);
                fread((char*) &b, 1,1,fp);

                imgarr->ImgPtr[i].ImgData[r][c]=(float)(rgb2Grayscale(rr, g, b));
            }
        }
    }

    printf("%d, %d\n", imgarr->ImgPtr[0].c,  imgarr->ImgPtr[0].r);
    for (int i = 0; i < 128; ++i)
    {
        for(int j = 0; j < 128; ++j)
        {
            float a = imgarr->ImgPtr[0].ImgData[i][j];
            if (a != 255.0) printf("%f\t", imgarr->ImgPtr[0].ImgData[i][j]);
        }
        printf("\n");
    }

    fclose(fp);
    return imgarr;
}





