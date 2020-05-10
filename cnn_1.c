    //
// Created by cheerfulliu on 04/02/2020.
//

#include "cnn_1.h"

//setup a nn 1 hidden layer 1 out layer, inputsize OF HIDDEN LAYER and outputsize of NUMBER OF CLASS
void cnnsetup_1(CNN_1* cnn, int inputSize, int outputSize)
{
    cnn->layerNum = 2;
    cnn->H1 = initnnLayer(1024, inputSize);    //128*128
    cnn->O1 = initnnLayer(inputSize, outputSize);
    cnn->e = (float*)calloc(cnn->H1->outputNum, sizeof(float));
}

//initialize a fully connected layer
nnLayer* initnnLayer(int inputNum, int outputNum)
{
    nnLayer* nnL = (nnLayer*)malloc(sizeof(nnLayer));

    nnL->inputNum = inputNum;
    nnL->outputNum = outputNum;

    nnL->biasData = (float*)calloc(outputNum, sizeof(float));

    nnL->d = (float*)calloc(outputNum, sizeof(float));
    nnL->v = (float*)calloc(outputNum, sizeof(float));
    nnL->y = (float*)calloc(outputNum, sizeof(float));

    // init weights
    nnL->wData = (float**)malloc(outputNum * sizeof(float*));
    srand((unsigned)time(NULL));
    for(int i = 0;i < outputNum; ++i){
        nnL->wData[i] = (float*)malloc(inputNum*sizeof(float));
        for(int j = 0; j < inputNum; ++j){
            float randnum = (((float)rand() / (float)RAND_MAX) - 0.5) * 2; //generate a fake random number
            //make the value approching zero : avoid the saturation of the neurons when training
            nnL->wData[i][j] = randnum * sqrt(fabsf((float)6.0 / (float)(inputNum + outputNum)));
        }
    }

    nnL->isFullConnect = true;

    return nnL;
}

//main function of the training
void cnntrain(CNN_1* cnn, ImgArr inputData, CNNOpts opts, int trainNum)
{
    for(int e = 0;e<opts.numepochs;e++){
        printf("Epoch num : %d\n", e + 1);
        for(int n = 0; n < trainNum; ++n)
        {
            //printf("Training num : %d\n", n + 1);

            int outSize = cnn->H1->inputNum;
            nSize H1inSize = {128, 128};
            /*
            float* H1inData = (float*)malloc((cnn->H1->inputNum) * sizeof(float));

            //develop in 1 dimension
            for(int r = 0; r < H1inSize.r; ++r)
                for(int c = 0; c < H1inSize.c; ++c)
                    H1inData[r * c  + c] = inputData->ImgPtr[n].ImgData[r][c];
*/

            cnnff(cnn, inputData->ImgPtr[n].ImgData);  // forward propagation : calculate the error


            cnnbp(cnn, inputData->ImgPtr[n].LabelData);   // backward propagation : calculate the gradients
            //char* filedir="E:\\Code\\Matlab\\PicTrans\\CNNData\\";
            //const char* filename=combine_strings(filedir,combine_strings(intTochar(n),".cnn"));
            //const char* filename = "../cnn.txt";
            //savecnndata(cnn, filename, inputData->ImgPtr[n].ImgData);

            cnnapplygrads(cnn, opts, inputData->ImgPtr[n].ImgData);
            /*
            for(int i = 0; i < 40; ++i)
            {
                for(int j = 0; j < 128 * 128; ++j)
                {
                    if (isnan(cnn->H1->wData[i][j])) printf("%d, %d\n", i, j);
                }
            }
            for(int i = 0; i <  cnn->H1->outputNum; ++i)
            {
                printf("%f\t", cnn->H1->y[i]);
            }
            printf("\n");
            for(int i = 0; i <  cnn->O1->outputNum; ++i)
            {
                printf("%f\t", cnn->O1->y[i]);
            }
            printf("\n");
            */
            //free(H1inData);
        }
    }

}

// forward propagation
void cnnff(CNN_1* cnn, float* inputData)
{
    nSize nnSize_H1 = {cnn->H1->inputNum, cnn->H1->outputNum}; //forward feeding H1
    nnff(cnn->H1->v, inputData, cnn->H1->wData, cnn->H1->biasData, nnSize_H1);


    for(int i = 0; i < cnn->H1->outputNum; ++i) //activation H1
        cnn->H1->y[i] = activation_Sigma(cnn->H1->v[i], cnn->H1->biasData[i]);

    nSize nnSize_O1 = {cnn->O1->inputNum, cnn->O1->outputNum}; //forward feeding O1
    nnff(cnn->O1->v, cnn->H1->y, cnn->O1->wData, cnn->O1->biasData, nnSize_O1);
    //v : output of dotpro; y : input of dotpro  wData: [i][j] i = size of O1 j: size of H1

    for(int i = 0; i < cnn->O1->outputNum; ++i) //activation O1
        cnn->O1->y[i] = activation_Sigma(cnn->O1->v[i], cnn->O1->biasData[i]);



}

//input * wight + bias
void nnff(float* output, float* input, float** wdata, float* bias, nSize nnSize)
{
    int w = nnSize.c;
    int h = nnSize.r;
    for(int i = 0; i < h; ++i) output[i] = vecMulti(input, wdata[i], w) + bias[i];
}

// activation function sigmod
float activation_Sigma(float input,float biaas)
{
    float temp = input + biaas;
    return (float)1.0 / ((float)(1.0 + exp( - temp)));
}

//dot product of 2 vectors
float vecMulti(float* vec1, float* vec2, int vecL)
{
    float m = 0;
    for(int i = 0; i < vecL; ++i) {
        m = m + vec1[i] * vec2[i];
        //printf("%d, %f, %f, %f\n",i,  vec1[i], vec2[i], m);
    }
    return m;

}

void cnnbp(CNN_1* cnn,float* outputData) // backward propagation
{
    for(int i = 0; i < cnn->O1->outputNum; ++i) cnn->e[i] = outputData[i] - cnn->O1->y[i];  //error vector

    // O1 layer, calculate sigma deriv
    for(int i = 0; i < cnn->O1->outputNum; ++i) cnn->O1->d[i] = cnn->e[i] * sigma_derivation(cnn->O1->y[i]);


    // H1 layer, calculate sigma deriv
    for(int j = 0; j < cnn->H1->outputNum; ++j) //j < 30
    {   //i < 10
        for (int i = 0; i < cnn->O1->outputNum; ++i) cnn->H1->d[j] += cnn->O1->d[i] * cnn->O1->wData[i][j];
        cnn->H1->d[j] = cnn->H1->d[j] * sigma_derivation(cnn->H1->y[j]);
    }
}

//derive of stigma
float sigma_derivation(float y)
{
    return activation_Sigma(y, 0) * (1 - activation_Sigma(y, 0));
}

void cnnapplygrads(CNN_1* cnn, CNNOpts opts, float* inputData) // renew weights in IN -> H1 and H1 -> O1
{

    //weights IN -> H1
    for(int i = 0; i < cnn->H1->outputNum; ++i)
        for(int j = 0; j < cnn->H1->inputNum; ++j)
            cnn->H1->wData[i][j] = cnn->H1->wData[i][j] + opts.alpha * inputData[j] * cnn->H1->d[i];

    //weights H1 -> O1
    for(int i = 0; i < cnn->O1->outputNum; ++i)
        for(int j = 0; j < cnn->O1->inputNum; ++j)
            cnn->O1->wData[i][j] = cnn->O1->wData[i][j] + opts.alpha * cnn->H1->y[j] * cnn->O1->d[i];
}

// used to test
void savecnndata(CNN_1* cnn, const char* filename, float* inputdata) // save data in the network
{
    FILE  *fp = NULL;
    fp = fopen(filename,"wb");
    if(fp == NULL)
        printf("write file failed\n");

    // H1 layer
    for(int i = 0; i < cnn->H1->outputNum; ++i)
        fwrite(cnn->H1->wData[i], sizeof(float), cnn->H1->inputNum, fp);
    fwrite(cnn->H1->biasData,sizeof(float),cnn->H1->outputNum,fp);
    fwrite(cnn->H1->v, sizeof(float), cnn->H1->outputNum, fp);
    fwrite(cnn->H1->d, sizeof(float), cnn->H1->outputNum, fp);
    fwrite(cnn->H1->y, sizeof(float), cnn->H1->outputNum, fp);
    
    //O1 layer
    for(int i = 0; i < cnn->O1->outputNum; ++i)
        fwrite(cnn->O1->wData[i], sizeof(float), cnn->O1->inputNum, fp);
    fwrite(cnn->O1->biasData,sizeof(float),cnn->O1->outputNum,fp);
    fwrite(cnn->O1->v, sizeof(float), cnn->O1->outputNum, fp);
    fwrite(cnn->O1->d, sizeof(float), cnn->O1->outputNum, fp);
    fwrite(cnn->O1->y, sizeof(float), cnn->O1->outputNum, fp);
    
    fclose(fp);
}

void cnnclear(CNN_1* cnn)
{

    // clear H1
    for(int i = 0; i < cnn->H1->outputNum; ++i)
    {
        cnn->H1->d[i] = (float)0.0;
        cnn->H1->v[i] = (float)0.0;
        cnn->H1->y[i] = (float)0.0;
    }
    for(int i = 0; i < cnn->O1->outputNum; ++i)
    {
        cnn->H1->d[i] = (float)0.0;
        cnn->H1->v[i] = (float)0.0;
        cnn->H1->y[i] = (float)0.0;
    }
}

// save cnn
void savecnn(CNN_1* cnn, const char* filename)
{
    FILE *fp = NULL;
    fp = fopen(filename,"wb");
    if(fp == NULL)
        printf("write file failed\n");

    // H1 layer
    for(int i = 0; i < cnn->H1->outputNum; ++i)
        fwrite(cnn->H1->wData[i], sizeof(float), cnn->H1->inputNum, fp);
    fwrite(cnn->H1->biasData, sizeof(float), cnn->H1->outputNum, fp);
    
    //O1 layer
    for(int i = 0; i < cnn->O1->outputNum; ++i)
        fwrite(cnn->O1->wData[i], sizeof(float), cnn->O1->inputNum, fp);
    fwrite(cnn->O1->biasData, sizeof(float), cnn->O1->outputNum, fp);

    fclose(fp);
}

// inport cnn data
void importcnn(CNN_1* cnn, const char* filename)
{
    FILE *fp = NULL;
    fp = fopen(filename,"rb");
    if(fp == NULL)
        printf("write file failed\n");
    
    // wait to be revised
    
    
    // H1 layer
    for(int i = 0; i<cnn->H1->outputNum; ++i)
        for(int j = 0; j<cnn->H1->inputNum; ++j)
            fread(&cnn->H1->wData[i][j], sizeof(float),1, fp);

    for(int i = 0; i<cnn->H1->outputNum; ++i)
        fread(&cnn->H1->biasData[i], sizeof(float),1, fp);

    // O1 layer
    for(int i = 0; i<cnn->O1->outputNum; ++i)
        for(int j = 0; j<cnn->O1->inputNum; ++j)
            fread(&cnn->O1->wData[i][j], sizeof(float),1, fp);

    for(int i = 0; i<cnn->O1->outputNum; ++i)
        fread(&cnn->O1->biasData[i], sizeof(float),1, fp);

    fclose(fp);
}

int vecmaxIndex(float* vec, int veclength )//retern the max index
{
    float maxnum = - 1.0;
    int maxIndex=0;
    for(int i = 0; i < veclength; ++i)
    {
        if(maxnum < vec[i])
        {
            maxnum = vec[i];
            maxIndex = i;
        }
    }
    return maxIndex;
}


// test the network after predict
float cnntest(CNN_1* cnn, ImgArr inputData, int testNum)
{
    int incorrectnum = 0;  // false prediction
    for(int n = 0; n < testNum; ++n)
    {/*
        nSize H1inSize = {128, 128};
        float* H1inData = (float*)malloc((cnn->H1->inputNum) * sizeof(float));


        //develop in 1 dimension
        for(int r = 0; r < H1inSize.r; ++r)
            for(int c = 0; c < H1inSize.c; ++c)
                H1inData[r * c  + c] = inputData->ImgPtr[n].ImgData[r][c];
        */


        cnnff(cnn, inputData->ImgPtr[n].ImgData);
        for(int j = 0; j < 10; ++j)
        {
            printf("%f\t", cnn->O1->y[j]);
        }
        printf("\n");

        if(vecmaxIndex(cnn->O1->y, cnn->O1->outputNum) !=
           vecmaxIndex(inputData->ImgPtr[n].LabelData, cnn->O1->outputNum))
            incorrectnum++;
        cnnclear(cnn);
    }
    return (float)incorrectnum/(float)testNum;
}