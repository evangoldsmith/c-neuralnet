#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "net/nn.h"

#define NN_INPUTS 2 // amount of inputs
#define NN_SIZE 3 // amount of layers after inputs (including output)
#define LEARN_RATE 0.1 // rate at which params adjust after back prop

int main() {
    int layers[NN_SIZE] = {2, 2, 1};

    MLP * mlp = create_mlp(NN_INPUTS, layers, NN_SIZE, LEARN_RATE);
    mlp_info(mlp);
    layer_info(mlp->layers[2]);
    
    return 0;
}