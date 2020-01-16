//
// Created by cheerfulliu on 13/01/2020.
//

#ifndef VERSION_CONVOLUTIONNAL_DATA_IMAGES_H
#define VERSION_CONVOLUTIONNAL_DATA_IMAGES_H


typedef struct MinstImg
{
    int c, r;  //large and width of the image
    float** ImgData;    //matrix containing data of the image
} MinstImg;

//contains all images
typedef struct MinstImgArr
{
    int ImgNum;     //number of images
    MinstImg* ImgPtr;   //pointer to the data of the image
} *ImgArr;

//output?
typedef struct MinstLabel
{
    int l;  //length of the label
    float* LabelData;   //output marked data
} MinstLabel;

typedef struct MinstLabelArr
{
    int LabelNum;
    MinstLabel* LabelPtr;
} *LabelArr;

LabelArr read_Lable(const char* filename); // read label

ImgArr read_Img(const char* filename); // readimg


#endif //VERSION_CONVOLUTIONNAL_DATA_IMAGES_H
