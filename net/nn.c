#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "nn.h"

double random_double() { return (double)rand() / RAND_MAX * 2 - 1; }

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
            l.neurons[j].data = activation(x, l.neurons[j], mlp->eqs);
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

void backward(MLP* mlp) {
    stack *eqs = mlp->eqs;
    int layer = mlp->size - 1;
    int i = 0;
    while (eqs->head != NULL) {
        eq* e = pop(eqs);
        printf("eq %d: %f %c %f\n", i, e->data1, e->op, e->data2);
        switch (e->op)
        { 
            case '+':
                if (i == 0) {
                    mlp->layers[layer].neurons[i].b_grad = 1.0;
                } else {
                    mlp->layers[layer].neurons[i].b_grad = mlp->layers[layer].neurons[i-1].b_grad;
                }
                break;
            case '*':
                if (i == 0) {
                    mlp->layers[layer].neurons[i].b_grad = e->data2;
                } else {
                    mlp->layers[layer].neurons[i].b_grad = mlp->layers[layer].neurons[i-1].b_grad * e->data2;
                }
                break;
            case 't':
                if (i == 0) {
                    mlp->layers[layer].neurons[i].b_grad = 1;
                } else {
                    mlp->layers[layer].neurons[i].b_grad = mlp->layers[layer].neurons[i-1].b_grad * inverse_tanh(e->data1);
                }
            
                break;
            default:
                printf("ERROR: invalid operation\n");
                break;
        }
        i++;
        layer--;
    }
}

// Function to calculate the output of a neuron
// for each wi and xi in neuron -> tanh(sum(wi*xi)+b)
double activation(double* input, Neuron n, stack *eqs) {
    double out = 0.0;
    for (int i = 0; i < n.size; i++) {
        //printf("ACTIVATION -- input: %f, weight: %f, bias: %f\n", input[i], n.weights[i]);
        out += input[i] * n.weights[i];
        push(eqs, newEq(input[i], n.weights[i], '*'));
    }
    push(eqs, newEq(out, n.bias, '+'));
    push(eqs, newEq(out + n.bias, 0.0, 't'));
    return tanh(out + n.bias);
}

double inverse_tanh(double x) {
    return 1 - pow(x, 2);
}

void add_eq(MLP* mlp, eq* data) {
    push(mlp->eqs, &data);
}

void print_eqs(MLP* mlp) {
    printStack(mlp->eqs);
}

// Instantiates and returns a new MLP
MLP * create_mlp(int input, int * arr, int size, double learning_rate) {
    MLP* mlp = (MLP*) malloc(sizeof(MLP));
    mlp->inputs = input;
    mlp->size = size;
    mlp->lrate = learning_rate;
    int p_neurons = input;

    mlp->eqs = (stack*) malloc(sizeof(stack));
    mlp->eqs->head = NULL;

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
        neurons[i].b_grad = 0.0;
        neurons[i].size = inputs;
        neurons[i].weights = create_weights(inputs);
        neurons[i].w_grads = create_grads(inputs);
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

// Creates and instantiates dynamic array of gradients for each weight in a neuron, initialized to 0.00
double* create_grads(int inputs) {
    double * grads = (double*) malloc(sizeof(double) * inputs);
    for (int i = 0; i < inputs; i++) {
        grads[i] = 0.00;
    }

    return grads;
}

// Converts dynamic array of Neurons to doubles
double* dbl_from_N(Neuron* neurons, int size) {
    double* output = (double*) malloc(sizeof(double) * size);
    for (int i = 0; i < size; i++) {
        output[i] = neurons[i].data;
    }
    return output;
}

// Memory management
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
        free(layer.neurons[i].w_grads);
    }
    free(layer.neurons);
}

// Debug functions
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
        printf("\tbias: %f,\t b_grad: %f\n\n", layer.neurons[i].bias, layer.neurons[i].b_grad);
        for (int j = 0; j < layer.neurons[i].size; j++) {
            printf("\t\tweight %d : %f,\t grad : %f\n", j, layer.neurons[i].weights[j], layer.neurons[i].w_grads[j]);
        }
    }
}