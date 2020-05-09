//
// Created by cheerfulliu on 14/01/2020.
//

#include "data_Images.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "mat.h"
#include <dirent.h>


ImgArr read_Img_1D(const char* filename, int switcher)
{
    int num_Label = 10;
    int images_per_label;
    if(switcher == 1) images_per_label = 1000;
    else images_per_label = 100;
    char label_list[256][8];
    int len = 0;
    DIR* d;
    struct dirent* file;

    if(!(d = opendir(filename)))
    {
        printf("error opendir %s!!!\n",filename);
        exit(-1);
    }

    while((file = readdir(d)) != NULL)
    {
        //remove current and precedent location
        if(strncmp(file->d_name, ".", 1) == 0)
            continue;
        strcpy(label_list[len++], file->d_name);
    }
    closedir(d);

    // initialize the container of the image
    int number_of_images = images_per_label * len;
    ImgArr imgarr=(ImgArr)malloc(sizeof(ImgArr));
    imgarr->ImgNum = number_of_images;
    //printf("%d\n", imgarr->ImgNum);
    imgarr->ImgPtr = (Img_1D*)malloc(number_of_images * sizeof(Img_1D));


    for (int index = 0; index < num_Label; ++index)
    {
        //make a list of all documents
        struct dirent** namelist;

        int n = scandir(combine_strings(combine_strings(filename, label_list[index]), "/"),
                &namelist, 0, alphasort);

        for(int image = 0; image < images_per_label; ++image)
        {
            FILE* fp;
            fp = fopen(combine_strings(combine_strings(combine_strings(filename, label_list[index]), "/"),
                                       namelist[image + 2]->d_name), "rb+");

            imgarr->ImgPtr[index * images_per_label + image].r = 128;
            imgarr->ImgPtr[index * images_per_label + image].ImgData = (float*) malloc(128 * 128 * sizeof(float));
            imgarr->ImgPtr[index * images_per_label + image].LabelData = (float*) calloc(num_Label, sizeof(float));
            imgarr->ImgPtr[index * images_per_label + image].LabelData[atoi(label_list[index]) % 10] = 1.0;

            unsigned char* buff = (unsigned char*)malloc(3 * 128 * 128 * sizeof(unsigned char));


            fseek(fp, 15, SEEK_CUR);
            fread((unsigned char*)buff, sizeof(unsigned char), 128 * 128 * 3, fp);
;
            for(int pixel = 0; pixel < 128 * 128; ++pixel)
            {   //normalisation
                if(buff[pixel * 3] == 255) imgarr->ImgPtr[index * images_per_label + image].ImgData[pixel] = 1e-9;
                else imgarr->ImgPtr[index * images_per_label + image].ImgData[pixel] = 1.0;
            }

            free(buff);
            fclose(fp);
        }
        free(namelist);
    }


   return imgarr;
}
//
////Image reader
//ImgArr read_Img(const char* filename)
//{
//
//    int n_rows = 0;
//    int n_cols = 0;
//
//    //make a list of all documents
//    struct dirent **namelist;
//
//    int n = scandir(filename, &namelist, 0, alphasort);
//    printf("%d\n", n);  //number of images
//
//
//    // initialize the container of the image
//    int number_of_images = n - 2;   //characteristic of function scandir
//    MinstImgArr imgarr=(ImgArr)malloc(sizeof(ImgArr));
//    imgarr->ImgNum = number_of_images;
//    imgarr->ImgPtr = (MinstImg*)malloc(number_of_images * sizeof(MinstImg));
//
//
//
//
//    for (int index_Images = 0; index_Images < number_of_images; ++index_Images)
//    {
//
//        //read the file
//        FILE *fp = NULL;
//        printf("%s\n", combine_strings(filename, namelist[index_Images + 2]->d_name));
//        fp = fopen(combine_strings(filename, namelist[index_Images + 2]->d_name), "rb+");
//
//        if (fp == NULL)
//            printf("Failed to open the file\n");
//        assert(fp);
//
//        char buff[16];      //image's type
//
//        //read image format
//        if (!fgets(buff, sizeof(buff), fp)) {
//            perror(filename);
//            exit(1);
//        }
//
//        //check the image format
//        if (buff[0] != 'P' || buff[1] != '6') {
//            fprintf(stderr, "Invalid image format (must be 'P6')\n");
//            exit(1);
//        }
//
//        //read image size information
//        if (fscanf(fp, "%d %d", &n_rows, &n_cols) != 2) {
//            fprintf(stderr, "Invalid image size (error loading '%s')\n", filename);
//            exit(1);
//        }
//
//        //jump useless lines
//        while (fgetc(fp) != '\n');
//        while (fgetc(fp) != '\n');
//
//        int compt = 0;
//
//        for (int i = 0; i < number_of_images; ++i)
//        {
//            imgarr->ImgPtr[i].r = n_rows;
//            imgarr->ImgPtr[i].c = n_cols;
//            imgarr->ImgPtr[i].ImgData = (float**) malloc(n_rows * sizeof(float*));
//            for (int r = 0; r < n_rows; ++r) {
//                imgarr->ImgPtr[i].ImgData[r] = (float *) malloc(n_cols * sizeof(float));
//                for (int c = 0; c < n_cols; ++c)
//                {
//                    // transfer to float
//                    unsigned char rr = 0, g = 0, b = 0;
//                    fread((unsigned char *) &rr, 1, 1, fp);
//                    fread((unsigned char *) &g, 1, 1, fp);
//                    fread((unsigned char *) &b, 1, 1, fp);
//
//                    //since here is no grayscale or colors, we just take 0 directly when we meet
//                    //a value different to 255
//                    //imgarr->ImgPtr[i].ImgData[r][c] = (float) (rgb2Grayscale(rr, g, b));
//                    if (rr == 255)
//                        imgarr->ImgPtr[i].ImgData[r][c] = 255.0;
//                    else
//                        imgarr->ImgPtr[i].ImgData[r][c] = 0.0;
//                    compt++;
//                }
//
//            }
//        }
//        fclose(fp);
//    }
//    free(namelist);
//    return imgarr;
//}
//
////label_Reader
//LabelArr read_Lable(const char* filename)
//{
//    FILE  *fp=NULL;
//    fp=fopen(filename,"rb+");
//    if(fp==NULL)
//        printf("open file failed\n");
//    assert(fp);
//
//    int number_of_labels = 20;  //same value as the number of images
//    int label_long = 10;
//
//
//    //if the file contains a number of labels, read it (here no)
//    //fread((unsigned char*)&number_of_labels,sizeof(number_of_labels),1,fp);
//    //printf("%d\n", number_of_labels);
//
//    // initialize
//    LabelArr labarr=(LabelArr)malloc(sizeof(LabelArr));
//    labarr->LabelNum=number_of_labels;
//    labarr->LabelPtr=(MinstLabel*)malloc(number_of_labels*sizeof(MinstLabel));
//
//    for(int i = 0; i < number_of_labels; ++i)
//    {
//        labarr->LabelPtr[i].l=label_long;
//        labarr->LabelPtr[i].LabelData=(float*)calloc(label_long,sizeof(float));
//        unsigned char temp = 0;
//        fread((int*) &temp, sizeof(temp),1,fp);
//        labarr->LabelPtr[i].LabelData[(int)temp]=1.0;
//    }
//    fclose(fp);
//    return labarr;
//}
//
//


// max pooling with the 1 dimension array, dim % 2 = 0, 4 pixels in 1
void maxpooling(ImgArr trainImg)
{
    int newSize = trainImg->ImgPtr[0].r / 2;
    for(int image = 0; image < trainImg->ImgNum; ++image)
    {
        float* newArray = (float*)malloc(newSize * newSize * sizeof(float));
        for(int row = 0; row < newSize; ++row)
        {
            for(int column = 0; column < newSize; ++column)
            {
                float buff = (trainImg->ImgPtr[image].ImgData[2 * row * trainImg->ImgPtr[image].r + 2 * column]
                        + trainImg->ImgPtr[image].ImgData[2 * row * trainImg->ImgPtr[image].r + 2 * column + 1]
                        + trainImg->ImgPtr[image].ImgData[(2 * row + 1) * trainImg->ImgPtr[image].r + 2 * column]
                        + trainImg->ImgPtr[image].ImgData[(2 * row + 1) * trainImg->ImgPtr[image].r + 2 * column + 1]) / 4;
                newArray[row * newSize + column] = buff;
            }
        }

        trainImg->ImgPtr[image].r = newSize;
        realloc(trainImg->ImgPtr[image].ImgData, newSize * newSize * sizeof(float));
        trainImg->ImgPtr[image].ImgData = newArray;
        newArray = NULL;
        free(newArray);
    }

}