typedef struct eq{
    double data1;
    double data2;
    char op;
}eq;

typedef struct node{
    eq *data;
    struct node *next;
}node;

typedef struct stack{
    node *head;
}stack;

// Stack Opertaions
void push(stack *stack, eq* data);
eq* pop(stack *stack);
eq* show(stack *stack);

// Memory Management
void free_stack(stack* stack);
void free_node(node* node);

// Equation Operations
eq* newEq(double data1, double data2, char op);

// Debug Functions
void printStack(stack* stack);
