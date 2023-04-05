#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "nn.h"

void initialize() {
    
}

void train() {
    /*
    
    forward pass
    calculate loss

    backward pass

    update params

    print loss
    
    */
}

MLP * create_mlp(int inputs, int * arr, int size, double learning_rate) {
    MLP* mlp = (MLP*) malloc(sizeof(MLP));
    mlp->input = inputs;
    mlp->lrate = learning_rate;
    mlp->layers = create_layers(size, *arr);
    
    return mlp;
}

Layer * create_layers(int size, int *arr) {
    Layer * layers = (Layer*) malloc(sizeof(Layer) * size);
    
    for (int i = 0; i < size; i++) {
        layers[i] = create_column();
    }
    return layers;
}

Layer

Matrix* matrix_create(int row, int col) {
	Matrix *matrix = malloc(sizeof(Matrix));
	matrix->rows = row;
	matrix->cols = col;
	matrix->entries = malloc(row * sizeof(double*));
	for (int i = 0; i < row; i++) {
		matrix->entries[i] = malloc(col * sizeof(double));
	}
	return matrix;
}

Neuron create_neuron(int size, double b) {
    Neuron neuron;
    double* weights = (double*) malloc(sizeof(double) * size); 
    neuron.bias = b;
    return neuron;
}