//
// Created by cheerfulliu on 11/01/2020.
//

#ifndef PHASE_1_INPUT_H
#define PHASE_1_INPUT_H


double scaling(int input)
{
    double scaled = input / 255.0 * 0.999 + 0.001;
    return scaled;
}

#endif //PHASE_1_INPUT_H
