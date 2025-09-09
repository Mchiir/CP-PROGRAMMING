// Let's implement a stack of integer number elements
// [10, 20, 30, 0, 0, 0, 0, 0, 0, 0]
//          ^
//          top

#include <iostream>
#include <stdio.h>

using namespace std;

#define MAX_SIZE 10

struct stack_base_structure
{
    int stack_array[MAX_SIZE];
    int stack_array_top_index;
};

typedef struct stack_base_structure stack;

void create(stack *s)
{
    s->stack_array_top_index = -1;
}

int isEmpty(stack *s)
{
    if (s->stack_array_top_index == -1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int isFull(stack *s)
{
    if (s->stack_array_top_index == (MAX_SIZE - 1))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void push(stack *s, int element)
{
    if (isFull(s))
    {
        cout << "\nStack overflow";
        return;
    }
    else
    {
        // s->stack_array_top_index++; // increment to top index
        s->stack_array[++s->stack_array_top_index] = element; // push element at top index in the array
    }
}

int pop(stack *s)
{
    if (isEmpty(s))
    {
        cout << "\nStack underflow";
        return -1;
    }
    else
    {
        return s->stack_array[s->stack_array_top_index--]; // return top element at the top index, then post-decrement
    }
}

void display(stack *s)
{
    if (isEmpty(s))
    {
        cout << "\nStack is empty";
        return;
    }
    else
    {
        cout << "\nStack elements :" << endl;
        stack temp = *s;
        while (temp.stack_array_top_index > -1)
        {
            cout << temp.stack_array[temp.stack_array_top_index--] << " ";
        }
    }
}

int main()
{
    stack s1;
    create(&s1);

    push(&s1, 10);
    push(&s1, 20);
    push(&s1, 30);
    push(&s1, 40);
    push(&s1, 50);
    push(&s1, 60);
    push(&s1, 70);
    push(&s1, 80);
    push(&s1, 90);
    push(&s1, 100);
    push(&s1, 200);
    push(&s1, 300);

    cout << "\nStack1 top element: " << pop(&s1);
    display(&s1);

    return 0;
}