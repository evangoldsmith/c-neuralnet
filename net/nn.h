#include "math_ops.h"

typedef struct {
	int size;	// # of weights
	double data; // output of neuron
	double* w_grads; // gradients of each weight dOUTPUT/dWEIGHTi
	double* weights; // array of inputs coming into neuron
	double bias; // trigger happiness of the neuron
	double b_grad; // gradient of bias
} Neuron;

typedef struct {
	int size; // # of neurons
	Neuron* neurons;
} Layer;

typedef struct {
	int size; // # of layers
	int inputs;
	Layer* layers;	
	double lrate; // learning rate
	stack* eqs; // stack of equations for back prop
} MLP; 

// Training 
void train();
double* forward(MLP* mlp, double* inputs, int output_size);
void backward(MLP* mlp);
double activation(double input[], Neuron n, stack* eqs);
double calc_loss(double* output, double* target, int size);
 
// Helper functions
double random_double();
double* dbl_from_N(Neuron* neurons, int size);
double inverse_tanh(double x);

// Create MLP
MLP* create_mlp(int inputs, int* arr, int size, double learning_rate);
Neuron* create_neurons(int size, int inputs);
double* create_weights(int inputs);
double* create_grads(int inputs);

// Memory management
void free_mlp(MLP* mlp);
void free_layer(Layer layer);

// Debug
void print_eqs(MLP* mlp);
void mlp_info(MLP* mlp);
void layer_info(Layer layer);