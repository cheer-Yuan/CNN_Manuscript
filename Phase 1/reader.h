//
// Created by cheerfulliu on 27/12/2019.
//

#ifndef PHASE_1_READER_H
#define PHASE_1_READER_H

#include <bits/types/FILE.h>
#include <stdio.h>
#include <stdlib.h>
#define RGB_COMPONENT_COLOR 255

typedef struct      //store every pixel
{
    unsigned char red, green, blue;
} pixel;

typedef struct      //refer to the image
{
    int width, height;
    pixel *data;     //point to every pixel
} image;

image* readppm_File(const char *ppm_File)
{
    char buff[16];      //image's type
    FILE *fp;
    int rgb_Depth;

    //open PPM file for reading
    fp = fopen(ppm_File, "rb");
    if (!fp)        // error : fail to open the file
    {
        fprintf(stderr, "Unable to open file '%s'\n", ppm_File);
        exit(1);
    }

    //read image format
    if (!fgets(buff, sizeof(buff), fp))
    {
        perror(ppm_File);
        exit(1);
    }

    //check the image format
    if (buff[0] != 'P' || buff[1] != '6')
    {
        fprintf(stderr, "Invalid image format (must be 'P6')\n");
        exit(1);
    }
    printf(">>>>>>Format : %c%c\n",buff[0],buff[1]);

    //alloc memory form image
    image *image_Ptr = (image *)malloc(sizeof(image));
    if (!image_Ptr)
    {
        fprintf(stderr, "Unable to allocate memory\n");
        exit(1);
    }

    //read image size information
    if (fscanf(fp, "%d %d", &image_Ptr->width, &image_Ptr->height) != 2)
    {
        fprintf(stderr, "Invalid image size (error loading '%s')\n", ppm_File);
        exit(1);
    }
    printf(">>>>>width = %d, height = %d\n",image_Ptr->width,image_Ptr->height);

    //read rgb component
    if (fscanf(fp, "%d", &rgb_Depth) != 1)
    {
        fprintf(stderr, "Invalid rgb component (error loading '%s')\n", ppm_File);
        exit(1);
    }
    printf(">>>>>rgb_Depth = %d\n",rgb_Depth);

    //check rgb component depth
    if (rgb_Depth != RGB_COMPONENT_COLOR)
    {
        fprintf(stderr, "'%s' does not have 8-bits components\n", ppm_File);
        exit(1);
    }

    while (fgetc(fp) != '\n') ;
    //memory allocation for pixel data
    image_Ptr->data = (pixel*)malloc(image_Ptr->width * image_Ptr->height * sizeof(pixel));

    //read pixel data from file
    fread(image_Ptr->data, sizeof(pixel) ,image_Ptr->width*image_Ptr->height, fp);

    //verification
    printf("%d, %d, %d\n", image_Ptr->data[16383].red, image_Ptr->data[16383].green, image_Ptr->data[16383].blue);

    fclose(fp);
    return image_Ptr;
}

#endif //PHASE_1_READER_H
