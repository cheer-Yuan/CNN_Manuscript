//
// Created by cheerfulliu on 27/12/2019.
//

#ifndef PHASE_1_RGB2GRAYSCALE_H
#define PHASE_1_RGB2GRAYSCALE_H

/*
 * 1). Grayscale = R*0.299 + G*0.587 + B*0.114
 *
 * 2). Gray = (R*30 + G*59 + B*11 + 50) / 100  Use integer in the calculation to gain performance
 *
 * 3). use >> but not / to gain moore performance : we transform the coef into 2^16(accurancy)
 * 0.299 * 65536 = 19595.264 ≈ 19595
 * 0.587 * 65536 + (0.264) = 38469.896 ≈ 38469
 * 0.114 * 65536 + (0.896) =   7471.104 + 0.896 = 7472
 */

int rgb2Grayscale(int red, int green, int blue)
{
    int grayscale = (red*19595 + green*38469 + blue*7472) >> 16;
    return grayscale;
}


#endif //PHASE_1_RGB2GRAYSCALE_H
