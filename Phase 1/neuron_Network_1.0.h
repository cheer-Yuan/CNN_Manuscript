//
// Created by cheerfulliu on 11/01/2020.
//

#ifndef PHASE_1_NEURON_NETWORK_1_0_H
#define PHASE_1_NEURON_NETWORK_1_0_H

#include <stdlib.h>
#include "function_Trigger.h"

#define Data 1000   //size of training group
#define In 784      //input of the network : 28 * 28 pixels
#define Out 10      //output of the network : 10 numbers
#define Neurons 100  //number of neurons in hidden layer
#define TrainLmt 10000    //times of the training
#define LR 0.01     //learning rate

/*
 * data_In[Data][In] : store inputs of the samples
 * data_Out[Data][Out] : store the outputs of the samples
 * weight_In[Neuron][In] : weights of input
 * delta_In[Neuron][In] : correction
 * weight_Out[Neuron][Out] : weights of output
 * delta_Out[Out][Neuron] : correction
 * activated[Neuron] : outputs of activation function
 * network_Out[Out] : outputs of the network
 */

typedef struct neurons
{
    double weight[100];
} neuron;

void init_Nework()
{
//    double data_In[Data][In], data_Out[Data][Out]
//    , weight_In[Neuron][In], d_In[Neuron][In]
//    , weight_Out[Neuron][Out], d_Out[Out][Neuron];

    for (int i = 0; i < Neurons; ++i)
        for (int j = 0; j < In; ++j)
        {
            weight_In[i][j] = (rand() % 999 + 1) / 1000.0;
            d_In[i][j] = 0.0;
        }
    for (int i = 0; i < Neurons; ++i)
        for (int j = 0; j < Out; ++j)
        {
            weight_Out[j][i] = (rand() % 999 + 1) / 1000.0;
            d_Out[j][i] = 0.0;
        }
}

//Compute and result the result on an sample
void compute_Out(int var)
{

    double y;


    //Input layer -> hidden layer
    for (int i = 0; i < Neurons; ++i){
        double sum = 0;
        for (int j = 0; j < In; ++j)
            sum += weight_In[i][j] * data_In[var][j];
        activated[i] = sigmoid(sum);
    }

    //Hidden layer -> output layer
    for (int i = 0; i < Out; ++i){
        double sum = 0;
        for (int j = 0; j < Neurons; ++j)
            sum += weight_Out[i][j] * activated[j];
        network_Out[i] = sum;
    }
}

void back_Update(int var)
{
    double t;
    for (int i = 0; i < Neurons; ++i)
    {
        t = 0;
        for (int j = 0; j < Out; ++j){
            t += (network_Out[j] - data_Out[var][j]) * weight_Out[j][i];

            delta_Out[j][i] = LR * (delta_Out[j][i] + (network_Out[j] - data_Out[var][j]) * activated[i]);
            weight_Out[j][i] -= delta_Out[j][i];
        }

        for (int j = 0; j < In; ++j){
            delta_In[i][j] = LR * (delta_In[i][j] + t * d_sigmoid(activated[i]) * data_In[var][j]);
            weight_In[i][j] -= delta_In[i][j];
        }
    }
}

void  train_Network()
{
    int c = 0;
    do
    {
        double e = 0.;      //error
        for (int i = 0; i < Data; ++i)
        {
            compute_Out(i);     //compute the ith sample
            e += fabs((network_Out[0] - data_Out[i][0]) / data_Out[i][0]);
            back_Update(i);      //update the network
        }
        //printf("%d  %lf\n",c,e/Data);
        c++;
    } while (c < TrainLmt && e / Data > 0.01);
}


#endif //PHASE_1_NEURON_NETWORK_1_0_H
