//
// Created by cheerfulliu on 14/01/2020.
//

#ifndef VERSION_CONVOLUTIONNAL_CNN_H
#define VERSION_CONVOLUTIONNAL_CNN_H

#include <stdbool.h>
#include "mat.h"
#include "data_Images.h"

#define _USE_MATH_DEFINES
#define AvePool 0
#define MaxPool 1
#define MinPool 2

// convo layer
typedef struct convolutional_layer
{
    int inputWidth;
    int inputHeight;
    int mapSize;      //size of the characteristic model

    int inChannels;   //imput number
    int outChannels;  //output number

    // weight in the characteristic model, a 4-dimension-array because it is fully connected
    // its size = inChannels*outChannels*mapSize*mapSize
    // reference : DeapLearningToolboox
    float**** mapData;     //store this model
    float**** dmapData;    //store local gradient of the characteristic model

    float* basicData;   //biais(?), size = outChannels
    bool isFullConnect; //whether is fully connected
    bool* connectModel; //mode of connections (defalt = full connection)

    float*** v; // input to activation function
    float*** y; // outputs

    // local gradient of the output pixel
    float*** d; // sigma, the local gradient of the network
} CovLayer;

// pooling layer, used for layer S2 and S4
typedef struct pooling_layer
{
    int inputWidth;   //width of input image
    int inputHeight;  //height
    int mapSize;      //...

    int inChannels;   //...
    int outChannels;  //...

    int poolType;     //method of pooling
    float* basicData;   //biais(?)

    float*** y; // output of neuron after pooling, no activation function
    float*** d; // sigma
} PoolLayer;

// single layer of the network, fully connected
typedef struct nn_layer
{
    int inputNum;   //number of input data
    int outputNum;  //number of output data

    float** wData; // weight, size  = inputNum*outputNum
    float* basicData;   //biais ，size = outputNum

    float* v; // input to activation function
    float* y; // output of activation function
    float* d; // sigma

    bool isFullConnect; //whether is fully connected
} OutLayer;

typedef struct cnn_network
{
    int layerNum;
    CovLayer *C1;

    PoolLayer *S2;
    OutLayer* O3;
    float *e; // error of training

} CNN;

typedef struct train_opts
{
    int numepochs; // number of ieration
    float alpha; // learning rate
} CNNOpts;

void cnnsetup(CNN* cnn,nSize inputSize,int outputSize);

void cnntrain(CNN* cnn,	ImgArr inputData,LabelArr outputData,CNNOpts opts,int trainNum);

float cnntest(CNN* cnn, ImgArr inputData,LabelArr outputData,int testNum);

void savecnn(CNN* cnn, const char* filename);

void importcnn(CNN* cnn, const char* filename);


CovLayer* initCovLayer(int inputWidth,int inputHeight,int mapSize,int inChannels,int outChannels);
void CovLayerConnect(CovLayer* covL,bool* connectModel);

PoolLayer* initPoolLayer(int inputWidth,int inputHeigh,int mapSize,int inChannels,int outChannels,int poolType);
void PoolLayerConnect(PoolLayer* poolL,bool* connectModel);

OutLayer* initOutLayer(int inputNum,int outputNum);


float activation_Sigma(float input,float bas);

void cnnff(CNN* cnn,float** inputData);
void cnnbp(CNN* cnn,float* outputData);
void cnnapplygrads(CNN* cnn,CNNOpts opts,float** inputData);
void cnnclear(CNN* cnn);

void avgPooling(float** output,nSize outputSize,float** input,nSize inputSize,int mapSize);

void nnff(float* output,float* input,float** wdata,float* bas,nSize nnSize);

void savecnndata(CNN* cnn,const char* filename,float** inputdata);


#endif //VERSION_CONVOLUTIONNAL_CNN_H
