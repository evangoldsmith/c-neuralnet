#include <stdio.h>
#include <stdlib.h>
#include "math_ops.h"

void push(stack *stack, eq* data) {
    node *new_node = malloc(sizeof(node));
    new_node->data = data;
    new_node->next = stack->head;
    stack->head = new_node;
}

eq* pop(stack *stack) {
    if (stack->head == NULL) {
        return NULL;
    }
    eq *data = stack->head->data;
    node *old_head = stack->head;
    stack->head = stack->head->next;
    free_node(old_head);
    return data;
}

eq* show(stack *stack) {
    return stack->head->data;
}

eq* newEq(double data1, double data2, char op) {
    eq *e = (eq*) malloc(sizeof(eq));
    e->data1 = data1;
    e->data2 = data2;
    e->op = op;
    return e;
}

void free_stack(stack* stack) {
    node* current = stack->head;
    while (current != NULL) {
        node* next = current->next;
        free_node(current);
        current = next;
    }
    free(stack);
}
void free_node(node* node) {
    if (node->data != NULL) {
        free(node->data);        
    }

    free(node);
}

void printStack(stack* stack) {
    node* current = stack->head;
    int n = 0;
    while (current != NULL) {
        printf("eq %d: %f %c %f\n", n, current->data->data1, current->data->op, current->data->data2);
        current = current->next;
        n++;
    }
}
