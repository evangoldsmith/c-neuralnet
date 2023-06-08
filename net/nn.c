#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "nn.h"

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

// TODO: gonna have to take a 2d array of inputs 
// Forward pass throughout the MLP, calculating the output of each neuron through activation function
double* forward(MLP* mlp, double* inputs, int output_size) {

    double* output = (double*) malloc(sizeof(int) * output_size);

    for (int i = 0; i < mlp->size; i++) {
        Layer l = mlp->layers[i];
        
        double* x;
        // For first layer, use inputs
        if (i == 0) {
            x = inputs;
        } 
        // For all other layers, use previous layer's outputs
        else {
            x = dbl_from_N(mlp->layers[i-1].neurons, mlp->layers[i-1].size);
        }

        for (int j = 0; j < l.size; j++) {
            l.neurons[j].data = activation(x, l.neurons[j]);
        }   
    }

    // Return the output of the last layer
    for (int i = 0; i < output_size; i++) {
        output[i] = mlp->layers[mlp->size-1].neurons[i].data;
    }

    return output;
}

// TODO: gonna need to take a 2d array of targets
double calc_loss(double* output, double* target, int size) {
    double sum = 0.0;
    for (int i = 0; i < size; i++) {
        sum += pow(output[i] - target[i], 2);
    }
    return sum;
}

// Function to calculate the output of a neuron
// for each wi and xi in neuron -> tanh(sum(wi*xi + b))
double activation(double* input, Neuron n) {
    double out = 0.0;

    for (int i = 0; i < n.size; i++) {
        //printf("ACTIVATION -- input: %f, weight: %f, bias: %f\n", input[i], n.weights[i]);
        out += input[i] * n.weights[i] + n.bias;
    }

    return tanh(out);
}

// Instantiates and returns a new MLP
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
        neurons[i].bias = random_double();
        neurons[i].size = inputs;
        neurons[i].weights = create_weights(inputs);
        neurons[i].data = 0.0;
    }

    return neurons;
}

// Creates and instantiates dynamic array of weights (doubles {-1 -> +1}) to store in a neuron
double* create_weights(int inputs) {
    double * weights = (double*) malloc(sizeof(double) * inputs);
    for (int i = 0; i < inputs; i++) {
        weights[i] = random_double();
    }

    return weights;
}

// Converts dynamic array of Neurons to doubles
double* dbl_from_N(Neuron* neurons, int size) {
    double* output = (double*) malloc(sizeof(double) * size);
    for (int i = 0; i < size; i++) {
        output[i] = neurons[i].data;
    }
    return output;
}

void free_mlp(MLP* mlp) {
    for (int i = 0; i < mlp->size; i++) {
        free_layer(mlp->layers[i]);
    }
    free(mlp->layers);
    free(mlp);
}

void free_layer(Layer layer) {
    for (int i = 0; i < layer.size; i++) {
        free(layer.neurons[i].weights);
    }
    free(layer.neurons);
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
        printf("\tdata: %f\n", layer.neurons[i].data);
        printf("\tinputs: %d\n", layer.neurons[i].size);
        printf("\tbias: %f\n", layer.neurons[i].bias);
        for (int j = 0; j < layer.neurons[i].size; j++) {
            printf("\t\tweight %d : %f\n", j, layer.neurons[i].weights[j]);
        }
    }
}