//
// Created by cheerfulliu on 14/01/2020.
//

#include "cnn.h"

//set unclude "cnn.h"p the network
void cnnsetup(CNN* cnn, nSize inputSize,int outputSize)
{
    cnn->layerNum = 3;

    nSize inSize;
    int mapSize = 5;
    inSize.c = inputSize.c;
    inSize.r = inputSize.r;
    cnn->C1 = initCovLayer(inSize.c, inSize.r, 5, 1, 1);
    inSize.c = inSize.c-mapSize + 1;
    inSize.r = inSize.r-mapSize + 1;

    cnn->S2 = initPoolLayer(inSize.c, inSize.r, 2, 1, 1, AvePool);
    inSize.c = inSize.c / 2;
    inSize.r = inSize.r / 2;

    cnn->O3 = initOutLayer(inSize.c * inSize.r,  outputSize);

    cnn->e=(float*)calloc(cnn->O3->outputNum,sizeof(float));
}

CovLayer* initCovLayer(int inputWidth,int inputHeight,int mapSize,int inChannels,int outChannels)
{
    CovLayer* covL=(CovLayer*)malloc(sizeof(CovLayer));

    covL->inputHeight=inputHeight;
    covL->inputWidth=inputWidth;
    covL->mapSize=mapSize;

    covL->inChannels=inChannels;
    covL->outChannels=outChannels;

    covL->isFullConnect=true;
    //initialize the weight，[r][c]
    int i,j,c,r;
    srand((unsigned)time(NULL));
    covL->mapData=(float****)malloc(inChannels*sizeof(float***));
    for(i=0;i<inChannels;++i){
        covL->mapData[i]=(float***)malloc(outChannels*sizeof(float**));
        for(j=0;j<outChannels;++j){
            covL->mapData[i][j]=(float**)malloc(mapSize*sizeof(float*));
            for(r=0;r<mapSize;++r){
                covL->mapData[i][j][r]=(float*)malloc(mapSize*sizeof(float));
                for(c=0;c<mapSize;++c){
                    float randnum = (((float)rand() / (float)RAND_MAX) - 0.5) * 2;
                    covL->mapData[i][j][r][c] = randnum * sqrtf((float)6.0 / (float)(mapSize * mapSize * (inChannels + outChannels)));
                    //printf("%f\n", covL->mapData[i][j][r][c]);  OK
                }
            }
        }
    }
    // gradients of weights
    covL->dmapData=(float****)malloc(inChannels*sizeof(float***));
    for(i=0;i<inChannels;++i){
        covL->dmapData[i]=(float***)malloc(outChannels*sizeof(float**));
        for(j=0;j<outChannels;++j){
            covL->dmapData[i][j]=(float**)malloc(mapSize*sizeof(float*));
            for(r=0;r<mapSize;++r){
                covL->dmapData[i][j][r]=(float*)calloc(mapSize,sizeof(float));  //calloc : initialize the value to 0
            }
        }
    }

    covL->basicData=(float*)calloc(outChannels,sizeof(float));

    int outW=inputWidth-mapSize+1;
    int outH=inputHeight-mapSize+1;


    covL->d=(float***)malloc(outChannels*sizeof(float**));
    covL->v=(float***)malloc(outChannels*sizeof(float**));
    covL->y=(float***)malloc(outChannels*sizeof(float**));
    for(j=0;j<outChannels;++j){
        covL->d[j]=(float**)malloc(outH*sizeof(float*));
        covL->v[j]=(float**)malloc(outH*sizeof(float*));
        covL->y[j]=(float**)malloc(outH*sizeof(float*));
        for(r=0;r<outH;++r){
            covL->d[j][r]=(float*)calloc(outW,sizeof(float));
            covL->v[j][r]=(float*)calloc(outW,sizeof(float));
            covL->y[j][r]=(float*)calloc(outW,sizeof(float));
        }
    }

    return covL;
}

PoolLayer* initPoolLayer(int inputWidth,int inputHeight,int mapSize,int inChannels,int outChannels,int poolType)
{
    PoolLayer* poolL=(PoolLayer*)malloc(sizeof(PoolLayer));

    poolL->inputHeight=inputHeight;
    poolL->inputWidth=inputWidth;
    poolL->mapSize=mapSize;
    poolL->inChannels=inChannels;
    poolL->outChannels=outChannels;
    poolL->poolType=poolType;

    poolL->basicData=(float*)calloc(outChannels,sizeof(float));

    int outW=inputWidth/mapSize;
    int outH=inputHeight/mapSize;

    int j,r;
    poolL->d=(float***)malloc(outChannels*sizeof(float**));
    poolL->y=(float***)malloc(outChannels*sizeof(float**));
    for(j=0;j<outChannels;++j){
        poolL->d[j]=(float**)malloc(outH*sizeof(float*));
        poolL->y[j]=(float**)malloc(outH*sizeof(float*));
        for(r=0;r<outH;++r){
            poolL->d[j][r]=(float*)calloc(outW,sizeof(float));
            poolL->y[j][r]=(float*)calloc(outW,sizeof(float));
        }
    }

    return poolL;
}

OutLayer* initOutLayer(int inputNum, int outputNum)
{
    OutLayer* outL = (OutLayer*)malloc(sizeof(OutLayer));

    outL->inputNum = inputNum;
    outL->outputNum = outputNum;


    outL->basicData = (float*)calloc(outputNum, sizeof(float));

    outL->d = (float*)calloc(outputNum, sizeof(float));
    outL->v = (float*)calloc(outputNum, sizeof(float));
    outL->y = (float*)calloc(outputNum, sizeof(float));

    // init weights
    outL->wData = (float**)malloc(outputNum * sizeof(float*));
    srand((unsigned)time(NULL));
    for(int i = 0;i < outputNum; ++i){
        outL->wData[i] = (float*)malloc(inputNum*sizeof(float));
        for(int j = 0;j < inputNum; ++j){
            float randnum = (((float)rand() / (float)RAND_MAX) - 0.5) * 2; //generate a fake random number
            //make the value approching zero : avoid the saturation of the neurons during the proces odf training
            outL->wData[i][j] = randnum * sqrt((float)6.0 / (float)(inputNum + outputNum));
        }
    }

    outL->isFullConnect = true;

    return outL;
}

int vecmaxIndex(float* vec, int veclength )//retern the max index
{
    int i;
    float maxnum=-1.0;
    int maxIndex=0;
    for(i=0;i<veclength;++i){
        if(maxnum<vec[i]){
            maxnum=vec[i];
            maxIndex=i;
        }
    }
    return maxIndex;
}

// test the network after predict
float cnntest(CNN* cnn, ImgArr inputData,LabelArr outputData,int testNum)
{
    int incorrectnum = 0;  // false prediction
    for(int n = 0; n < testNum; ++n)
    {;
        cnnff(cnn, inputData->ImgPtr[n].ImgData);
        for(int i = 0; i <  cnn->O3->outputNum; ++i)
        {
            printf("%f\t", cnn->O3->y[i]);
        }
        printf("\n");
        if(vecmaxIndex(cnn->O3->y, cnn->O3->outputNum) !=
        vecmaxIndex(outputData->LabelPtr[n].LabelData, cnn->O3->outputNum))
            incorrectnum++;
        cnnclear(cnn);
    }
    return (float)incorrectnum/(float)testNum;
}

// save cnn
void savecnn(CNN* cnn, const char* filename)
{
    FILE  *fp=NULL;
    fp=fopen(filename,"wb");
    if(fp==NULL)
        printf("write file failed\n");

    int i,j,r;
    // C1 layer
    for(i=0;i<cnn->C1->inChannels;++i)
        for(j=0;j<cnn->C1->outChannels;++j)
            for(r=0;r<cnn->C1->mapSize;++r)
            {
                fwrite(cnn->C1->mapData[i][j][r],sizeof(float),cnn->C1->mapSize,fp);
            }


    fwrite(cnn->C1->basicData,sizeof(float),cnn->C1->outChannels,fp);

    // O3 layer
    for(i=0;i<cnn->O3->outputNum;++i)
        fwrite(cnn->O3->wData[i],sizeof(float),cnn->O3->inputNum,fp);
    fwrite(cnn->O3->basicData,sizeof(float),cnn->O3->outputNum,fp);

    fclose(fp);
}


// inport cnn data
void importcnn(CNN* cnn, const char* filename)
{
    FILE  *fp=NULL;
    fp=fopen(filename,"rb");
    if(fp==NULL)
        printf("write file failed\n");

    int i,j,c,r;
    // C1 layer
    for(i=0;i<cnn->C1->inChannels;++i)
        for(j=0;j<cnn->C1->outChannels;++j)
            for(r=0;r<cnn->C1->mapSize;++r)
                for(c=0;c<cnn->C1->mapSize;++c){
                    float* in=(float*)malloc(sizeof(float));
                    fread(in,sizeof(float),1,fp);
                    cnn->C1->mapData[i][j][r][c]=*in;
                }

    for(i=0;i<cnn->C1->outChannels;++i)
        fread(&cnn->C1->basicData[i],sizeof(float),1,fp);

    // O3 layer
    for(i=0;i<cnn->O3->outputNum;++i)
        for(j=0;j<cnn->O3->inputNum;++j)
            fread(&cnn->O3->wData[i][j],sizeof(float),1,fp);

    for(i=0;i<cnn->O3->outputNum;++i)
        fread(&cnn->O3->basicData[i],sizeof(float),1,fp);

    fclose(fp);
}

//main function of the training
void cnntrain(CNN* cnn,	ImgArr inputData,LabelArr outputData,CNNOpts opts,int trainNum)
{

    for(int e = 0;e<opts.numepochs;e++){
        printf("Epoch num : %d\n", e + 1);
        for(int n = 0;n<trainNum;++n){
            printf("Training num : %d\n", n + 1);
            cnnff(cnn,inputData->ImgPtr[n].ImgData);  // forward propaganda : calculate the error



            cnnbp(cnn,outputData->LabelPtr[n].LabelData);   // backward propaganda : calculate the gradients



            //char* filedir="E:\\Code\\Matlab\\PicTrans\\CNNData\\";
            //const char* filename=combine_strings(filedir,combine_strings(intTochar(n),".cnn"));
            const char* filename = "../cnn.txt";
            savecnndata(cnn,filename,inputData->ImgPtr[n].ImgData);


            cnnapplygrads(cnn,opts,inputData->ImgPtr[n].ImgData);           //passed too much time on it : Problem



            cnnclear(cnn);
        }
    }
}

// forward prapaganda
void    cnnff(CNN* cnn,float** inputData)
{
    int outSizeW=cnn->S2->inputWidth;
    int outSizeH=cnn->S2->inputHeight;

    int i,j,r,c;
    // C1 layer
    nSize mapSize={cnn->C1->mapSize,cnn->C1->mapSize};
    nSize inSize={cnn->C1->inputWidth,cnn->C1->inputHeight};
    nSize outSize={cnn->S2->inputWidth,cnn->S2->inputHeight};
    for(i=0;i<(cnn->C1->outChannels);++i){
        for(j=0;j<(cnn->C1->inChannels);++j){
            float** mapout=cov(cnn->C1->mapData[j][i],mapSize,inputData,inSize,valid);
            addmat(cnn->C1->v[i],cnn->C1->v[i],outSize,mapout,outSize);
            for(r=0;r<outSize.r;++r)
                free(mapout[r]);
            free(mapout);
        }
        for(r=0;r<outSize.r;++r)
            for(c=0;c<outSize.c;++c)
                cnn->C1->y[i][r][c]=activation_Sigma(cnn->C1->v[i][r][c],cnn->C1->basicData[i]);
    }

    // S2 layer
    inSize.c=cnn->S2->inputWidth;
    inSize.r=cnn->S2->inputHeight;
    outSize.c=inSize.c/cnn->S2->mapSize;
    outSize.r=inSize.r/cnn->S2->mapSize;
    for(i=0;i<(cnn->S2->outChannels);++i){
        if(cnn->S2->poolType==AvePool)
            avgPooling(cnn->S2->y[i],outSize,cnn->C1->y[i],inSize,cnn->S2->mapSize);
    }

    // O3 layer
    float* O3inData = (float*)malloc((cnn->O3->inputNum) * sizeof(float));
    for(i = 0; i < (cnn->S2->outChannels); ++i)     //develop in 1 dimension
        for(r = 0;r < outSize.r; ++r)
            for(c = 0; c < outSize.c; ++c)
                O3inData[i * outSize.r * outSize.c + r * outSize.c + c] = cnn->S2->y[i][r][c];

    nSize nnSize = {cnn->O3->inputNum, cnn->O3->outputNum};
    nnff(cnn->O3->v, O3inData, cnn->O3->wData, cnn->O3->basicData, nnSize);
    for(i = 0; i < cnn->O3->outputNum; ++i)
        cnn->O3->y[i] = activation_Sigma(cnn->O3->v[i], cnn->O3->basicData[i]);
    free(O3inData);
}

// activation function sigmod
float activation_Sigma(float input,float bas)
{
    float temp=input+bas;
    return (float)1.0/((float)(1.0+exp(-temp)));
}

void avgPooling(float** output,nSize outputSize,float** input,nSize inputSize,int mapSize)
{
    int outputW=inputSize.c/mapSize;
    int outputH=inputSize.r/mapSize;
    if(outputSize.c!=outputW||outputSize.r!=outputH)
        printf("ERROR: output size is wrong!!");

    int i,j,m,n;
    for(i=0;i<outputH;++i)
        for(j=0;j<outputW;++j)
        {
            float sum=0.0;
            for(m=i*mapSize;m<i*mapSize+mapSize;m++)
                for(n=j*mapSize;n<j*mapSize+mapSize;++n)
                    sum=sum+input[m][n];

            output[i][j]=sum/(float)(mapSize*mapSize);
        }
}

//dot product of 2 vectors
float vecMulti(float* vec1, float* vec2, int vecL)
{
    float m = 0;
    for(int i = 0; i < vecL; ++i) m = m + vec1[i] * vec2[i];
    return m;
}

//forward propagand of the output layer
void nnff(float* output, float* input, float** wdata, float* bas, nSize nnSize)
{
    int w = nnSize.c;
    int h = nnSize.r;
    for(int i = 0; i < h; ++i) output[i] = vecMulti(input, wdata[i], w) + bas[i];
}

//derive of figma
float sigma_derivation(float y)
{
    return y*(1-y);
}

void cnnbp(CNN* cnn,float* outputData) // backwards propagation
{

    int i,j,c,r;
    for(i = 0; i < cnn->O3->outputNum; ++i) cnn->e[i] = cnn->O3->y[i] - outputData[i];  //error vector

    // O3 layer, calculate sigma deriv
    for(i = 0; i < cnn->O3->outputNum; ++i) cnn->O3->d[i] = cnn->e[i] * sigma_derivation(cnn->O3->y[i]);


    // S2 layer, calculates the weights
    nSize outSize = {cnn->S2->inputWidth / cnn->S2-> mapSize, cnn->S2->inputHeight / cnn->S2->mapSize};
    for(i = 0; i < cnn->S2->outChannels; ++i)
        for(r = 0; r < outSize.r; ++r)
            for(c = 0; c < outSize.c; ++c)
                for(j = 0; j < cnn->O3->outputNum; ++j)
                {
                    int wInt = i * outSize.c * outSize.r + r * outSize.c + c;  //???
                    cnn->S2->d[i][r][c] = cnn->S2->d[i][r][c] + cnn->O3->d[j] * cnn->O3->wData[j][wInt];
                }


    // C1layer
    nSize S2dSize={cnn->S2->inputWidth / cnn->S2->mapSize,cnn->S2->inputHeight / cnn->S2->mapSize};

    // average pooling
    for(i = 0; i<cnn->C1->outChannels; ++i){
        float** C1e = UpSample(cnn->S2->d[i], S2dSize, cnn->S2->mapSize, cnn->S2->mapSize);
        for(r = 0; r<cnn->S2->inputHeight; ++r)
            for(c = 0; c<cnn->S2->inputWidth; ++c)      //according to the formula
                cnn->C1->d[i][r][c] = C1e[r][c]
                        * sigma_derivation(cnn->C1->y[i][r][c])
                        / (float)(cnn->S2->mapSize * cnn->S2->mapSize);
        for(r = 0; r < cnn->S2->inputHeight; ++r)
            free(C1e[r]);
        free(C1e);
    }

}

void cnnapplygrads(CNN* cnn,CNNOpts opts,float** inputData) // renew weights in S layer C1 layer and O3 layer
{

    int i,j,r,c;

    // C1 layer
    nSize dSize={cnn->S2->inputHeight,cnn->S2->inputWidth};     //124, 124
    nSize ySize={cnn->C1->inputHeight,cnn->C1->inputWidth};     //128, 128
    nSize mapSize={cnn->C1->mapSize,cnn->C1->mapSize};          //5, 5

    for(i=0;i<cnn->C1->outChannels;++i){    //<1
        for(j=0;j<cnn->C1->inChannels;++j){     //<1

            float** flipinputData=rotate180(inputData,ySize);
            float** C1dk=cov(cnn->C1->d[i],dSize,flipinputData,ySize,valid);
            multifactor(C1dk,C1dk,mapSize,-1*opts.alpha);
            addmat(cnn->C1->mapData[j][i],cnn->C1->mapData[j][i],mapSize,C1dk,mapSize);
            for(r=0;r<(dSize.r-(ySize.r-1));++r)
            {

                free(C1dk[r]);
            }
            free(C1dk);
            for(r=0;r<ySize.r;++r)
            {

                free(flipinputData[r]);
            }
            free(flipinputData);
        }
        cnn->C1->basicData[i]=cnn->C1->basicData[i]-opts.alpha*summat(cnn->C1->d[i],dSize);
    }

    // O3 layer
    float* O3inData=(float*)malloc((cnn->O3->inputNum)*sizeof(float));
    nSize outSize={cnn->S2->inputWidth/cnn->S2->mapSize,cnn->S2->inputHeight/cnn->S2->mapSize};
    for(i=0;i<(cnn->S2->outChannels);++i)
        for(r=0;r<outSize.r;++r)
            for(c=0;c<outSize.c;++c)
            {
                O3inData[i*outSize.r*outSize.c+r*outSize.c+c]=cnn->S2->y[i][r][c];

            }

    for(j=0;j<cnn->O3->outputNum;++j){
        for(i=0;i<cnn->O3->inputNum;++i)
        {

            cnn->O3->wData[j][i]=cnn->O3->wData[j][i]-opts.alpha*cnn->O3->d[j]*O3inData[i];
        }
        cnn->O3->basicData[j]=cnn->O3->basicData[j]-opts.alpha*cnn->O3->d[j];
    }
    free(O3inData);
}

void cnnclear(CNN* cnn)
{

    int j,c,r;
    // clear C1
    for(j=0;j<cnn->C1->outChannels;++j){
        for(r=0;r<cnn->S2->inputHeight;++r){
            for(c=0;c<cnn->S2->inputWidth;++c){
                cnn->C1->d[j][r][c]=(float)0.0;
                cnn->C1->v[j][r][c]=(float)0.0;
                cnn->C1->y[j][r][c]=(float)0.0;
            }
        }
    }

    // clear S2
    for(j=0;j<cnn->S2->outChannels;++j){
        for(r=0;r<cnn->S2->inputHeight/cnn->S2->mapSize;++r){
            for(c=0;c<cnn->S2->inputWidth/cnn->S2->mapSize;++c){
                cnn->S2->d[j][r][c]=(float)0.0;
                cnn->S2->y[j][r][c]=(float)0.0;
            }
        }
    }
    // clear O3
    for(j=0;j<cnn->O3->outputNum;++j){
        cnn->O3->d[j]=(float)0.0;
        cnn->O3->v[j]=(float)0.0;
        cnn->O3->y[j]=(float)0.0;
    }
}

// used to test
void savecnndata(CNN* cnn,const char* filename,float** inputdata) // save data in the network
{
    FILE  *fp=NULL;
    fp=fopen(filename,"wb");
    if(fp==NULL)
        printf("write file failed\n");

    int i,j,r;
    // C1 layer
    for(i=0;i<cnn->C1->inputHeight;++i)
        fwrite(inputdata[i],sizeof(float),cnn->C1->inputWidth,fp);
    for(i=0;i<cnn->C1->inChannels;++i)
        for(j=0;j<cnn->C1->outChannels;++j)
            for(r=0;r<cnn->C1->mapSize;++r)
                fwrite(cnn->C1->mapData[i][j][r],sizeof(float),cnn->C1->mapSize,fp);

    fwrite(cnn->C1->basicData,sizeof(float),cnn->C1->outChannels,fp);

    for(j=0;j<cnn->C1->outChannels;++j){
        for(r=0;r<cnn->S2->inputHeight;++r){
            fwrite(cnn->C1->v[j][r],sizeof(float),cnn->S2->inputWidth,fp);
        }
        for(r=0;r<cnn->S2->inputHeight;++r){
            fwrite(cnn->C1->d[j][r],sizeof(float),cnn->S2->inputWidth,fp);
        }
        for(r=0;r<cnn->S2->inputHeight;++r){
            fwrite(cnn->C1->y[j][r],sizeof(float),cnn->S2->inputWidth,fp);
        }
    }

    // S2 layer
    for(j=0;j<cnn->S2->outChannels;++j){
        for(r=0;r<cnn->S2->inputHeight/cnn->S2->mapSize;++r){
            fwrite(cnn->S2->d[j][r],sizeof(float),cnn->S2->inputWidth/cnn->S2->mapSize,fp);
        }
        for(r=0;r<cnn->S2->inputHeight/cnn->S2->mapSize;++r){
            fwrite(cnn->S2->y[j][r],sizeof(float),cnn->S2->inputWidth/cnn->S2->mapSize,fp);
        }
    }

    // O3 layer
    for(i=0;i<cnn->O3->outputNum;++i)
        fwrite(cnn->O3->wData[i],sizeof(float),cnn->O3->inputNum,fp);
    fwrite(cnn->O3->basicData,sizeof(float),cnn->O3->outputNum,fp);
    fwrite(cnn->O3->v,sizeof(float),cnn->O3->outputNum,fp);
    fwrite(cnn->O3->d,sizeof(float),cnn->O3->outputNum,fp);
    fwrite(cnn->O3->y,sizeof(float),cnn->O3->outputNum,fp);

    fclose(fp);
}