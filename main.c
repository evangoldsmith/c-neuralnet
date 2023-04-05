#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "net/nn.h"

#define INPUTS 2 // amount of inputs
#define SIZE 3 // amount of layers after inputs (including output)
#define LEARN_RATE 0.1 // rate at which params adjust after back prop

int main() {
    int num_inputs = 2;
    int layers[SIZE] = {2, 2, 1};

    MLP* mlp = create_mlp(INPUTS, layers, SIZE, LEARN_RATE);
    printf("mlp info\n-------\ninputs: %d\nlrate: %f\nsize: %d\n", mlp->input, mlp->lrate, SIZE);

    return 0;
}