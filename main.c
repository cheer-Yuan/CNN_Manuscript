#include "data_Images.h"
#include "cnn.h"
#include "mat.h"


void test_Network_on_O()
{
    ImgArr testImg = read_Img("../train_and_test_0/test_1/");
    LabelArr testLabel = read_Lable("../train_and_test_0/label_train_1.txt");

    nSize inputSize = {testImg->ImgPtr[0].c,testImg->ImgPtr[0].r};
    int outSize = testLabel->LabelPtr[0].l;

    CNN* cnn_Test = (CNN*)malloc(sizeof(CNN));
    cnnsetup(cnn_Test,inputSize,outSize);
    importcnn(cnn_Test, "../train_of_0_o_20.cnn");
    int testNum = 20;
    float incorrectRatio = 0.0;

    incorrectRatio = cnntest(cnn_Test, testImg, testLabel, testNum);
    printf("test finished!! \nincorrectrate rate = %f\n", incorrectRatio);
}
void test_Network_on_1()
{
    ImgArr testImg = read_Img("../train_and_test_0/test_1/");
    LabelArr testLabel = read_Lable("../train_and_test_0/label_test_1.txt");

    nSize inputSize = {testImg->ImgPtr[0].c,testImg->ImgPtr[0].r};
    int outSize = testLabel->LabelPtr[0].l;

    CNN* cnn_Test = (CNN*)malloc(sizeof(CNN));
    cnnsetup(cnn_Test,inputSize,outSize);
    importcnn(cnn_Test, "../train_of_0_1_20.cnn");
    int testNum = 20;
    float incorrectRatio = 0.0;

    incorrectRatio = cnntest(cnn_Test, testImg, testLabel, testNum);
    printf("test finished!! \nincorrectrate rate = %f\n", incorrectRatio);
}

void test_Network_on_0()
{
    ImgArr testImg=read_Img("../train_and_test_0/test_0/");
    LabelArr testLabel=read_Lable("../train_and_test_0/label_test_0.txt");

    nSize inputSize={testImg->ImgPtr[0].c,testImg->ImgPtr[0].r};
    int outSize=testLabel->LabelPtr[0].l;

    CNN* cnn_Test = (CNN*)malloc(sizeof(CNN));
    cnnsetup(cnn_Test,inputSize,outSize);
    importcnn(cnn_Test, "../train_of_0_1_20.cnn");

    int testNum = 20;
    float incorrectRatio = 0.0;

    incorrectRatio = cnntest(cnn_Test, testImg, testLabel, testNum);
    printf("OK\n");
    printf("test finished!! \nincorrectrate rate = %f\n", incorrectRatio);
}

void train_0_o_20()
{
    //read images
    ImgArr trainImg_0 = read_Img("../train_and_test_0/train_0/");
    LabelArr trainLabel_0 = read_Lable("../train_and_test_0/label_train_0.txt");
    ImgArr trainImg_1 = read_Img("../train_and_test_0/train_o/");
    LabelArr trainLabel_1 = read_Lable("../train_and_test_0/label_train_o.txt");

    nSize inputSize={trainImg_0->ImgPtr[0].c,trainImg_0->ImgPtr[0].r};  //define data size

    int outSize=trainLabel_0->LabelPtr[0].l;

    //initializing
    CNN* cnn=(CNN*)malloc(sizeof(CNN));
    cnnsetup(cnn,inputSize,outSize);


    // train on 0s and 1s
    CNNOpts opts;
    opts.numepochs = 1;
    opts.alpha = 1.0;
    int trainNum = 5;
    cnntrain(cnn,trainImg_0,trainLabel_0,opts,trainNum);
    cnntrain(cnn,trainImg_1,trainLabel_1,opts,trainNum);

    printf("train finished!!\n");
    savecnn(cnn,"../train_of_0_o_20.cnn");
}

void train_1_2_20_intersect()
{
    //read images
    ImgArr trainImg_0_1 = read_Img("../train_and_test_0/train_0_1_20_intersect/");
    LabelArr trainLabel_0_1 = read_Lable("../train_and_test_0/label_train_0_1_intersect.txt");


    nSize inputSize={trainImg_0_1->ImgPtr[0].c,trainImg_0_1->ImgPtr[0].r};  //define data size

    int outSize=trainLabel_0_1->LabelPtr[0].l;

    //initializing
    CNN* cnn=(CNN*)malloc(sizeof(CNN));
    cnnsetup(cnn,inputSize,outSize);


    // train on 0s and 1s
    CNNOpts opts;
    opts.numepochs = 1;
    opts.alpha = 1;
    int trainNum = 5;
    cnntrain(cnn,trainImg_0_1,trainLabel_0_1,opts,trainNum);

    printf("train finished!!\n");
    savecnn(cnn,"../train_of_0_1_with_20_intersect.cnn");
}

void train_1()
{
    //read images
    ImgArr trainImg_0_1 = read_Img("../train_and_test_0/train_1/");
    LabelArr trainLabel_0_1 = read_Lable("../train_and_test_0/label_train_1.txt");


    nSize inputSize={trainImg_0_1->ImgPtr[0].c,trainImg_0_1->ImgPtr[0].r};  //define data size

    int outSize = trainLabel_0_1->LabelPtr[0].l;

    //initializing
    CNN* cnn=(CNN*)malloc(sizeof(CNN));
    cnnsetup(cnn,inputSize,outSize);


    // train on 0s and 1s
    CNNOpts opts;
    opts.numepochs = 1;
    opts.alpha = 1;
    int trainNum = 5;
    cnntrain(cnn,trainImg_0_1,trainLabel_0_1,opts,trainNum);

    printf("train finished!!\n");
    savecnn(cnn,"../train_of_0_1_with_20_intersect.cnn");
}

void train_o()
{
    //read images
    ImgArr trainImg_0_1 = read_Img("../train_and_test_0/train_o/");
    LabelArr trainLabel_0_1 = read_Lable("../train_and_test_0/label_train_o.txt");


    nSize inputSize={trainImg_0_1->ImgPtr[0].c,trainImg_0_1->ImgPtr[0].r};  //define data size

    int outSize = trainLabel_0_1->LabelPtr[0].l;

    //initializing
    CNN* cnn=(CNN*)malloc(sizeof(CNN));
    cnnsetup(cnn,inputSize,outSize);


    // train on 0s and 1s
    CNNOpts opts;
    opts.numepochs = 1;
    opts.alpha = 1;
    int trainNum = 20;
    cnntrain(cnn,trainImg_0_1,trainLabel_0_1,opts,trainNum);

    printf("train finished!!\n");
    savecnn(cnn,"../train_of_o.cnn");
}

int main()
{
    /*
     * here we train the network on 20 zeros and 20 1
     */

    train_1();
    //train_1_2_20_intersect();
    //train_0_o_20();
    //train_o();
    //test_Network_on_1();
    //test_Network_on_0();
    //test_Network_on_O();
    return 0;

}
