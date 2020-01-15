#include "data_Images.h"
#include "cnn.h"
#include "mat.h"
#include <dirent.h>

void test_cnn()
{
    //read label and image
    LabelArr testLabel=read_Lable("../label.txt");
    ImgArr testImg = read_Img("../hsf_0_00000.ppm");

    //determine the size of input matrix
    nSize inputSize={testImg->ImgPtr[0].c,testImg->ImgPtr[0].r};
    int outSize=10;     //testLabel->LabelPtr[0].l;

    //initialize the network
    CNN* cnn=(CNN*)malloc(sizeof(CNN));
    cnnsetup(cnn,inputSize,outSize);

    //initialize the trainer
    CNNOpts opts;
    opts.numepochs=1;
    opts.alpha = 0.01;
    int trainNum = 1;

    cnntrain(cnn,testImg,testLabel,opts,trainNum);

    FILE  *fp=NULL;
    fp=fopen("../cnnL.ma","wb");
    if(fp==NULL)
        printf("write file failed\n");
    fwrite(cnn->L,sizeof(float),trainNum,fp);
    fclose(fp);
    printf("OK");

}

int main()
{
    /*
     * here we train the network on 100 zeros
     */


    ImgArr trainImg=read_Img("../train_and_test_0/train_0/");
    LabelArr trainLabel=read_Lable("../train_and_test_0/label_train_0.txt");


    ImgArr testImg=read_Img("E:\\Code\\VS2010 code\\CNN\\Minst\\test-images.idx3-ubyte");
    LabelArr testLabel=read_Lable("E:\\Code\\VS2010 code\\CNN\\Minst\\test-labels.idx1-ubyte");

    exit(0);

    nSize inputSize={testImg->ImgPtr[0].c,testImg->ImgPtr[0].r};
    int outSize=testLabel->LabelPtr[0].l;

    // CNN结构的初始化
    CNN* cnn=(CNN*)malloc(sizeof(CNN));
    cnnsetup(cnn,inputSize,outSize);

    // CNN训练
    /*
    CNNOpts opts;
    opts.numepochs=1;
    opts.alpha=1.0;
    int trainNum=55000;
    cnntrain(cnn,trainImg,trainLabel,opts,trainNum);
    printf("train finished!!\n");
    savecnn(cnn,"minst.cnn");
    // 保存训练误差
    FILE  *fp=NULL;
    fp=fopen("E:\\Code\\Matlab\\PicTrans\\cnnL.ma","wb");
    if(fp==NULL)
        printf("write file failed\n");
    fwrite(cnn->L,sizeof(float),trainNum,fp);
    fclose(fp);
    */



}
