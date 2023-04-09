#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "nn.h"

#define INIT_BIAS 1.0

double random_double() { return (double)rand() / RAND_MAX * 2 - 1; }

void train() {
    /*
    
    forward pass
    calculate loss

    backward pass

    update params

    print loss
    
    */
}

void forward() {

}

// Function to calculate the output of a neuron
double activation(double input[], Neuron n, int weights) {
    // for each wi adn xi in neuron -> tanh(sum(wi*xi + b))
    double out = 0.0;
    int input_size = sizeof(input) / sizeof(input[0]);
    int size = (weights > input_size) ? input_size : weights;


````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````                                                                                                                                                                
    for (int i = 0; i < size; i++) {
        printf("input: %f, weight: %f, bias: %f\n", input[i], n.weights[i]);
        out += input[i] * n.weights[i] + n.bias;
    }

    return tanh(out);
}

MLP * create_mlp(int input, int * arr, int size, double learning_rate) {
    MLP* mlp = (MLP*) malloc(sizeof(MLP));
    mlp->inputs = input;
    mlp->size = size;
    mlp->lrate = learning_rate;
    int p_neurons = input;

    mlp->layers = (Layer*) malloc(sizeof(Layer) * size);
    for (int i = 0; i < size; i++) {
        if (i > 0) {
            p_neurons = mlp->layers[i-1].size;
        }
        mlp->layers[i].size = arr[i];
        mlp->layers[i].neurons = create_neurons(arr[i], p_neurons);
    }
    return mlp;
}

// Creates dynamic array of neurons to be stored in layers of MLP
Neuron * create_neurons(int size, int inputs) {
    Neuron * neurons = (Neuron*) malloc(sizeof(Neuron) * size);
    for (int i = 0; i < size; i++) {
        neurons[i].bias = INIT_BIAS;
        neurons[i].size = inputs;
        neurons[i].weights = create_weights(inputs);
    }

    return neurons;
}

// Creates and instantiates dynamic array of weights (doubles {-1 -> +1}) to store in a neuron
double * create_weights(int inputs) {
    double * weights = (double*) malloc(sizeof(double) * inputs);
    for (int i = 0; i < inputs; i++) {
        weights[i] = random_double();
    }

    return weights;
}

void mlp_info(MLP* mlp) {
    printf("mlp info\n-------\n");
    printf("inputs: %d\nlrate: %f\nsize: %d\n", mlp->inputs, mlp->lrate, mlp->size);
}

void layer_info(Layer layer) {
    printf("layer info\n-------\n");
    printf("size: %d\n", layer.size);
    for (int i = 0; i < layer.size; i++) {
        printf("- neuron %d\n", i);
        printf("\tinputs: %d\n", layer.neurons[i].size);
        printf("\tbias: %f\n", layer.neurons[i].bias);
        for (int j = 0; j < layer.neurons[i].size; j++) {
            printf("\t\tweight %d : %f\n", j, layer.neurons[i].weights[j]);
        }
    }
}