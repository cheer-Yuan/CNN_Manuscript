//
// Created by cheerfulliu on 14/01/2020.
//

#include "mat.h"

float** rotate180(float** mat, nSize matSize)//  transpose
{
    int i,c,r;
    int outSizeW=matSize.c;
    int outSizeH=matSize.r;
    float** outputData=(float**)malloc(outSizeH*sizeof(float*));
    for(i=0;i<outSizeH;++i)
        outputData[i]=(float*)malloc(outSizeW*sizeof(float));

    for(r=0;r<outSizeH;++r)
        for(c=0;c<outSizeW;++c)
            outputData[r][c]=mat[outSizeH-r-1][outSizeW-c-1];

    return outputData;
}

// mode "full" : size = inSize + mapSize - 1
// mode "same" : size unchanged
// mode "valid" : size = inSize - mapSize + 1

float** correlation(float** map,nSize mapSize,float** inputData,nSize inSize,int type)
{
    int i,j,c,r;
    int halfmapsizew;
    int halfmapsizeh;
    if(mapSize.r%2 == 0&&mapSize.c%2 == 0){ //half size of the convolution kernel
        halfmapsizew = (mapSize.c)/2;
        halfmapsizeh = (mapSize.r)/2;
    }else{
        halfmapsizew = (mapSize.c-1)/2;
        halfmapsizeh = (mapSize.r-1)/2;
    }

    // default mode of output, size  =  inSize+(mapSize-1)
    int outSizeW = inSize.c+(mapSize.c-1); //enlarge of the size
    int outSizeH = inSize.r+(mapSize.r-1);
    float** outputData = (float**)malloc(outSizeH*sizeof(float*));
    for(i = 0;i<outSizeH;++i)
        outputData[i] = (float*)calloc(outSizeW,sizeof(float));

    //enlarge the result container
    float** exInputData = matEdgeExpand(inputData,inSize,mapSize.c-1,mapSize.r-1);

    for(j = 0;j<outSizeH;++j)
        for(i = 0;i<outSizeW;++i)
            for(r = 0;r<mapSize.r;++r)
                for(c = 0;c<mapSize.c;++c){
                    outputData[j][i] = outputData[j][i]+map[r][c]*exInputData[j+r][i+c];
                }

    for(i = 0;i<inSize.r+2*(mapSize.r-1);++i)
        free(exInputData[i]);
    free(exInputData);

    nSize outSize = {outSizeW,outSizeH};

    //different modes of return
    switch(type){
        case full:
            return outputData;
        case same:{
            float** sameres = matEdgeShrink(outputData,outSize,halfmapsizew,halfmapsizeh);
            for(i = 0;i<outSize.r;++i)
                free(outputData[i]);
            free(outputData);
            return sameres;
        }
        case valid:{
            float** validres;
            if(mapSize.r%2 == 0&&mapSize.c%2 == 0)
                validres = matEdgeShrink(outputData,outSize,halfmapsizew*2-1,halfmapsizeh*2-1);
            else
                validres = matEdgeShrink(outputData,outSize,halfmapsizew*2,halfmapsizeh*2);
            for(i = 0;i<outSize.r;++i)
                free(outputData[i]);
            free(outputData);
            return validres;
        }
        default:
            return outputData;
    }
}

//convolution
float** cov(float** map,nSize mapSize,float** inputData,nSize inSize,int type)
{
    // rotation of the charc kernel
    float** flipmap = rotate180(map,mapSize);
    float** res = correlation(flipmap,mapSize,inputData,inSize,type);
    int i;
    for(i = 0;i<mapSize.r;++i)
        free(flipmap[i]);
    free(flipmap);
    return res;
}

// upper sampling
float** UpSample(float** mat,nSize matSize,int upc,int upr)
{
    int i,j,m,n;
    int c = matSize.c;
    int r = matSize.r;
    float** res = (float**)malloc((r*upr)*sizeof(float*)); // init result
    for(i = 0;i<(r*upr);++i)
        res[i] = (float*)malloc((c*upc)*sizeof(float));

    for(j = 0;j<r*upr;j = j+upr){
        for(i = 0;i<c*upc;i = i+upc)    //++width
            for(m = 0;m<upc;m++)
                res[j][i+m] = mat[j/upr][i/upc];

        for(n = 1;n<upr;++n)      //++hight
            for(i = 0;i<c*upc;++i)
                res[j+n][i] = res[j][i];
    }
    return res;
}

//grandir un 2d mat by 0s
float** matEdgeExpand(float** mat,nSize matSize,int addc,int addr)
{
    int i,j;
    int c = matSize.c;
    int r = matSize.r;
    float** res = (float**)malloc((r+2*addr)*sizeof(float*)); //init result
    for(i = 0;i<(r+2*addr);++i)
        res[i] = (float*)malloc((c+2*addc)*sizeof(float));

    for(j = 0;j<r+2*addr;++j){
        for(i = 0;i<c+2*addc;++i){
            if(j<addr||i<addc||j >= (r+addr)||i >= (c+addc))
                res[j][i] = (float)0.0;
            else
                res[j][i] = mat[j-addr][i-addc];
        }
    }
    return res;
}

// shrink a 2 dim matrice
float** matEdgeShrink(float** mat,nSize matSize,int shrinkc,int shrinkr)
{
    int i,j;
    int c = matSize.c;
    int r = matSize.r;
    float** res = (float**)malloc((r-2*shrinkr)*sizeof(float*)); //init result
    for(i = 0;i<(r-2*shrinkr);++i)
        res[i] = (float*)malloc((c-2*shrinkc)*sizeof(float));


    for(j = 0;j<r;++j){
        for(i = 0;i<c;++i){
            if(j >= shrinkr&&i >= shrinkc&&j<(r-shrinkr)&&i<(c-shrinkc))
                res[j-shrinkr][i-shrinkc] = mat[j][i]; //copy
        }
    }
    return res;
}

//add mat
void addmat(float** res, float** mat1, nSize matSize1, float** mat2, nSize matSize2)
{
    int i,j;
    if(matSize1.c != matSize2.c || matSize1.r != matSize2.r)
        printf("ERROR: Size is not same!");

    for(i = 0;i<matSize1.r;++i)
        for(j = 0;j<matSize1.c;++j)
            res[i][j] = mat1[i][j]+mat2[i][j];
}

//miltiplication matrices
void multifactor(float** res, float** mat, nSize matSize, float factor)
{
    int i,j;
    for(i = 0;i<matSize.r;++i)
        for(j = 0;j<matSize.c;++j)
            res[i][j] = mat[i][j]*factor;
}

//sum matrices
float summat(float** mat,nSize matSize)
{
    float sum = 0.0;
    int i,j;
    for(i = 0;i<matSize.r;++i)
        for(j = 0;j<matSize.c;++j)
            sum = sum+mat[i][j];
    return sum;
}

//combine 2 strings
char* combine_strings(const char* a, const char* b)
{
    char *ptr;
    int lena = strlen(a),lenb = strlen(b);
    int i,l = 0;
    ptr  =  (char *)malloc((lena+lenb+1) * sizeof(char));
    for(i = 0;i<lena;++i)
        ptr[l++] = a[i];
    for(i = 0;i<lenb;++i)
        ptr[l++] = b[i];
    ptr[l] = '\0';
    return(ptr);
}