
typedef struct {
	int size;	// # of weights
	double data;
	double* weights; // array of inputs coming into neuron
	double bias; // trigger happiness of the neuron
} Neuron;

typedef struct {
	int size;
	Neuron* neurons;
} Layer;

typedef struct {
	int size;
	int inputs;
	Layer* layers;	
	double lrate;
} MLP; 

// Training 
void train();
double* forward(MLP* mlp, double* inputs, int output_size);
double activation(double input[], Neuron n);
double calc_loss(double* output, double* target, int size);

// Helper functions
double random_double();
double* dbl_from_N(Neuron* neurons, int size);

// Create MLP
MLP* create_mlp(int inputs, int* arr, int size, double learning_rate);
Neuron* create_neurons(int size, int inputs);
double* create_weights(int inputs);

// Debug
void mlp_info(MLP* mlp);
void layer_info(Layer layer);