//
// Created by cheerfulliu on 11/01/2020.
//
//Activation function 

#ifndef PHASE_1_FUNCTION_TRIGGER_H
#define PHASE_1_FUNCTION_TRIGGER_H

#include <math.h>

//Sigmoid function (squashes any value of x into a value between 0 and 1)
static inline double sigmoid(double x)
{
    return 1.0 / (1.0 + exp(-x));
}

//Sigmoid derivative
static inline double d_sigmoid(double x)
{
    return x * (1 - x);
}

#endif //PHASE_1_FUNCTION_TRIGGER_H
