
typedef struct {
	int size;
	double * weights; // array of inputs coming into neuron
	double bias; // trigger happiness of the neuron
} Neuron;

typedef struct {
	int size;
	Neuron * nuerons;
} Layer;

typedef struct {
	int input;
	Layer * layers;	
	double lrate;
} MLP; 

void initialize();
void train();

MLP * create_mlp(int inputs, int * arr, int size, double learning_rate);
Layer * create_layers(int size, int *arr);
Neuron create_neuron(int size, double b);