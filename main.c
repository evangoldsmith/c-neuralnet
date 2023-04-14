#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "net/nn.h"

#define NN_INPUTS 3 // amount of inputs
#define NN_SIZE 3 // amount of layers after inputs (including output)
#define LEARN_RATE 0.1 // rate at which params adjust after back prop

int main() {

    srand(0);
    int layers[NN_SIZE] = {4, 4, 1};

    MLP * mlp = create_mlp(NN_INPUTS, layers, NN_SIZE, LEARN_RATE);
    mlp_info(mlp);
    layer_info(mlp->layers[0]);

    // DATA SET
    double inputs[4][NN_INPUTS] = {
        {2.0, 3.0, -1.0}, 
        {3.0, -1.0, 0.5}, 
        {0.5, 1.0, 1.0},
        {1.0, 1.0, -1.0}, 
    };
    double outputs[4] = { 1.0, -1.0, -1.0, 1.0 };

    // TRAINING
    forward(mlp, &inputs);
    layer_info(mlp->layers[2]);

    return 0;
}


