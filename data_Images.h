#ifndef VERSION_CONVOLUTIONNAL_DATA_IMAGES_H
#define VERSION_CONVOLUTIONNAL_DATA_IMAGES_H

typedef struct MinstImg
{
    int c, r;  //large and width of the image
    float** ImgData;    //matrix containing data of the image
} MinstImg;

typedef struct Img_1D
{
    int r;
    float*  ImgData;    //matrix containing data of the image
    float* LabelData;
} Img_1D;



//contains all images
typedef struct MinstImgArr
{
    int ImgNum;     //number of images
    MinstImg* ImgPtr;   //pointer to the data of the image
} *MinstImgArr;

typedef struct ImgArr
{
    int ImgNum;     //number of images
    Img_1D* ImgPtr;   //pointer to the data of the image
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

ImgArr read_Img_1D(const char* filename, int switcher); // readimg

void avereduce2(ImgArr trainImg);

void avereduce4(ImgArr trainImg);

void maxreduce4(ImgArr trainImg);

void conv4kern(ImgArr trainImg);

void maxpooling2s2(ImgArr trainImg);



#endif //VERSION_CONVOLUTIONNAL_DATA_IMAGES_H
