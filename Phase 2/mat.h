//
// Created by cheerfulliu on 14/01/2020.
//

#ifndef VERSION_CONVOLUTIONNAL_MAT_H
#define VERSION_CONVOLUTIONNAL_MAT_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

#include <time.h>

#define full 0
#define same 1
#define valid 2

typedef struct Mat2DSize{
    int c;
    int r;
}nSize;

float** rotate180(float** mat, nSize matSize);

void addmat(float** res, float** mat1, nSize matSize1, float** mat2, nSize matSize2);

float** correlation(float** map,nSize mapSize,float** inputData,nSize inSize,int type);

float** cov(float** map,nSize mapSize,float** inputData,nSize inSize,int type);

float** UpSample(float** mat,nSize matSize,int upc,int upr);

float** matEdgeExpand(float** mat,nSize matSize,int addc,int addr);

float** matEdgeShrink(float** mat,nSize matSize,int shrinkc,int shrinkr);

void savemat(float** mat,nSize matSize,const char* filename);

void multifactor(float** res, float** mat, nSize matSize, float factor);
float summat(float** mat,nSize matSize);

char * combine_strings(const char *a, const char *b);


#endif //VERSION_CONVOLUTIONNAL_MAT_H
