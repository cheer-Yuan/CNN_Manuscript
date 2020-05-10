//
// Created by cheerfulliu on 04/02/2020.
//

#ifndef VERSION_CONVOLUTIONNAL_CNN_1_H
#define VERSION_CONVOLUTIONNAL_CNN_1_H

#include <stdbool.h>
#include "mat.h"
#include "data_Images.h"



typedef struct nn_layer
{
    int inputNum;   //number of input data
    int outputNum;  //number of output data

    float** wData; // weight, size  = inputNum*outputNum
    float* biasData;   //biais ，size = outputNum

    float* v; // input to activation function
    float* y; // output of activation function
    float* d; // sigma, local gradient

    bool isFullConnect; //whether is fully connected
} nnLayer;

typedef struct cnn_network_neurons_1
{
    int layerNum;
    nnLayer* H1;
    nnLayer* O1;
    float* e; // error of training
} CNN_1  ;

typedef struct train_opts
{
    int numepochs; // number of ieration
    float alpha; // learning rate
} CNNOpts;

void cnnsetup_1(CNN_1* cnn, int inputsize, int outputSize);

nnLayer* initnnLayer(int inputNum, int outputNum);

void cnntrain(CNN_1* cnn, ImgArr inputData, CNNOpts opts, int trainNum);

void cnnff(CNN_1* cnn, float* inputData);

void nnff(float* output, float* input, float** wdata, float* bas, nSize nnSize);

float activation_Sigma(float input, float bas);

float activation_Relu(float input, float bas);

float vecMulti(float* vec1, float* vec2, int vecL);

void cnnbp(CNN_1* cnn,float* outputData); // backward propagation

float sigma_derivation(float y);

float relu_derivation(float y);

void cnnapplygrads(CNN_1* cnn, CNNOpts opts, float* inputData); // renew weights in IN -> H1 and H1 -> O1

void savecnndata(CNN_1* cnn, const char* filename, float* inputdata); // save data in the network

void cnnclear(CNN_1* cnn);

void savecnn(CNN_1* cnn, const char* filename);

void importcnn(CNN_1* cnn, const char* filename);

float cnntest(CNN_1* cnn, ImgArr inputData, int testNum);




#endif //VERSION_CONVOLUTIONNAL_CNN_1_H
