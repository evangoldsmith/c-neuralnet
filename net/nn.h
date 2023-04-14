
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

void train();
void forward(MLP* mlp, double* inputs);
double activation(double input[], Neuron n);

double random_double();

MLP* create_mlp(int inputs, int* arr, int size, double learning_rate);
Neuron* create_neurons(int size, int inputs);
double* create_weights(int inputs);

void mlp_info(MLP* mlp);
void layer_info(Layer layer);