#include "data_Images.h"
#include <time.h>
#include <sys/time.h>
#include "mat.h"

#include "cnn_1.h"

#define Nodes_1 30

void test_Network_1_on_all()
{
    ImgArr testImg = read_Img_1D("../../../Dataset/test/", 0);


    int outSize = 10;

    CNN_1 * cnn_Test = (CNN_1*)malloc(sizeof(CNN_1));
    cnnsetup_1(cnn_Test,Nodes_1,outSize);
    importcnn(cnn_Test, "../train_of_cnn_1_on_numbers.cnn");



    int testNum = testImg->ImgNum;
    float incorrectRatio = 0.0;

    incorrectRatio = cnntest(cnn_Test, testImg, testNum);
    printf("test finished!! \nincorrectrate rate = %f\n", incorrectRatio);

}

void train_cnn_1()
{
    //read images
    struct timeval start_read, end_read;
    gettimeofday(&start_read, NULL );
    ImgArr trainImg = read_Img_1D("../../../Dataset/train/", 1);
    gettimeofday(&end_read, NULL );
    long timeuse_read =1000000 * ( end_read.tv_sec - start_read.tv_sec ) + end_read.tv_usec - start_read.tv_usec;
    printf("time for reading : %f\n", timeuse_read /1000000.0);


    int outSize = 10;


    //initializing
    CNN_1* cnn = (CNN_1*)malloc(sizeof(CNN_1));
    cnnsetup_1(cnn, Nodes_1, outSize);

    CNNOpts opts;
    opts.numepochs = 5;
    opts.alpha = 0.0001;
    int trainNum = trainImg->ImgNum;

    struct timeval start, end;
    gettimeofday(&start, NULL );
    cnntrain(cnn, trainImg, opts, trainNum);
    gettimeofday(&end, NULL );
    long timeuse =1000000 * ( end.tv_sec - start.tv_sec ) + end.tv_usec - start.tv_usec;
    printf("train finished!!\n");
    printf("train epoch : %d\nnodes in hidden layer : %d\ntime for training : %f\n", opts.numepochs, Nodes_1,
           timeuse /1000000.0);
    savecnn(cnn,"../train_of_cnn_1_on_numbers.cnn");
}


























int main()
{
    train_cnn_1();
    test_Network_1_on_all();


    return 0;

}
