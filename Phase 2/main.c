#include "data_Images.h"
#include "cnn.h"
#include "mat.h"


void test_Network()
{
    ImgArr testImg=read_Img("../train_and_test_0/test_1/");
    LabelArr testLabel=read_Lable("../train_and_test_0/label_test_1.txt");

    nSize inputSize={testImg->ImgPtr[0].c,testImg->ImgPtr[0].r};
    int outSize=testLabel->LabelPtr[0].l;

    CNN* cnn_Test = (CNN*)malloc(sizeof(CNN));
    cnnsetup(cnn_Test,inputSize,outSize);
    importcnn(cnn_Test, "../train_of_0_with_10.cnn");
    int testNum = 20;
    float incorrectRatio = 0.0;

    incorrectRatio = cnntest(cnn_Test, testImg, testLabel, testNum);
    printf("test finished!! \nincorrectrate rate = %f\n", incorrectRatio);
}

int main()
{
    /*
     * here we train the network on 100 zeros
     */

/*
    ImgArr trainImg=read_Img("../train_and_test_0/train_0/");
    LabelArr trainLabel=read_Lable("../train_and_test_0/label_train_0.txt");






    nSize inputSize={trainImg->ImgPtr[0].c,trainImg->ImgPtr[0].r};
    int outSize=trainLabel->LabelPtr[0].l;

    //initializing
    CNN* cnn=(CNN*)malloc(sizeof(CNN));
    cnnsetup(cnn,inputSize,outSize);

    // train
    CNNOpts opts;
    opts.numepochs=1;
    opts.alpha=1.0;
    int trainNum=5;
    cnntrain(cnn,trainImg,trainLabel,opts,trainNum);
    printf("train finished!!\n");
    savecnn(cnn,"../train_of_0_with_10.cnn");
*/
    test_Network();
    return 0;

}
