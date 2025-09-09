// Let's implement a stack with linked-list
// top -> 10 -> 20 -> nullptr
// top is a pointer

#include <iostream>
#include <stdio.h>

using namespace std;

struct node {
    struct node *next;
    int value;
};

typedef struct node stack;

stack *top;

void create(stack **top){
    (*top) = nullptr;
}

int isEmpty(stack **top){
    return (*top) == nullptr;
}

void push(stack **top, int element){
    // stack *new_node = new stack;
    stack *new_node = (stack *) malloc (sizeof(stack)); // casting and mem allocation
    new_node->value = element;
    new_node->next = *top;
    *top = new_node;
}

int pop(stack **top){
    if(isEmpty(top)){
        cout << "\nStack underflow";
        return -1;
    }else{
        int top_value;
        stack *temp;

        top_value = (*top)->value; // use brackets, as -> has high precedence
        temp = *top;
        *top = (*top)->next;
        free (temp);
        return top_value;
    }
}

void display(stack **top){
    if(isEmpty(top)){
        cout << "\nStack is empty";
        return;
    }else{
        cout << "\nStack elements :" << endl;
        stack *temp = (*top);

        while(temp != nullptr){
            cout << temp->value << " ";
            temp = temp->next;
        }
    }
}

int main(){
    stack *top;
    create(&top);

    push(&top, 20);
    push(&top, 30);
    cout << (isEmpty(&top) ? "Stack is empty": "Stack has values");
    cout << "\nStack top element : " << pop(&top);
    display(&top);
    return 0;
}