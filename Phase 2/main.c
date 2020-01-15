#include <stdio.h>
#include <assert.h>
#include "data_Images.h"
#include "cnn.h"
#include "mat.h"
#include <assert.h>
void test_cnn()
{

    LabelArr testLabel=read_Lable("../label.txt");




    ImgArr testImg = read_Img("../hsf_0_00000.ppm");

    nSize inputSize={testImg->ImgPtr[0].c,testImg->ImgPtr[0].r};
    int outSize=10;     //testLabel->LabelPtr[0].l;


    CNN* cnn=(CNN*)malloc(sizeof(CNN));
    cnnsetup(cnn,inputSize,outSize);


    CNNOpts opts;
    opts.numepochs=1;
    opts.alpha = 1;
    int trainNum = 1;

    cnntrain(cnn,testImg,testLabel,opts,trainNum);



    FILE  *fp=NULL;
    fp=fopen("../cnn.txt","wb");
    if(fp==NULL)
        printf("write file failed\n");
    fwrite(cnn->L,sizeof(float),trainNum,fp);
    fclose(fp);

    savecnn(cnn,"structcnn.txt");
}

int main()
{
    test_cnn();

}
