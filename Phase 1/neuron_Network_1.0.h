//
// Created by cheerfulliu on 11/01/2020.
//

#ifndef PHASE_1_NEURON_NETWORK_1_0_H
#define PHASE_1_NEURON_NETWORK_1_0_H

#include <stdlib.h>

#define Data 1000   //size of training group
#define In 784      //input of the network : 28 * 28 pixels
#define Out 10      //output of the network : 10 numbers
#define Neuron 100  //number of neurons in hidden layer
#define TrainC 10000    //times of the training

/*
 * data_In[Data][In] : store inputs of the samples
 * data_Out[Data][Out] : store the outputs of the samples
 * weight_In[Neuron][In] : weights of input
 * d_In[Neuron][In] : correction
 * weight_Out[Neuron][Out] : weights of output
 * d_Out[Out][Neuron] : correction
 * activate[Neuron] : outputs of activation function
 * network_Out[Out] : outputs of the network
 */

typedef struct neurons
{
    double weight[100];
} neuron;

void init_Nework()
{


    for (int i = 0; i < Neuron; ++i)
        for (int j = 0; j < In; ++j)
        {
            weight_In[i][j] = (rand() % 999 + 1) / 1000.0;
            d_In[i][j] = 0.0;
        }
    for (int i = 0; i < Neuron; ++i)
        for (int j = 0; j < Out; ++j)
        {
            weight_Out[j][i] = (rand() % 999 + 1) / 1000.0;
            d_Out[j][i] = 0.0;
        }
}

void  trainNetwork(){
    int i,c=0;
    do{
        e=0;
        for (i = 0; i < Data; ++i){
            computO(i);
            e+=fabs((OutputData[0]-d_out[i][0])/d_out[i][0]);
            backUpdate(i);
        }
        //printf("%d  %lf\n",c,e/Data);
        c++;
    }while(c<TrainC && e/Data>0.01);
}

#endif //PHASE_1_NEURON_NETWORK_1_0_H
