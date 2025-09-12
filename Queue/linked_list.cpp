// Let's implement a queue with a linked-list with nodes holding integer values
// front -> 10 -> 20 -> 30 -> 40 -> nullptr <- rear

#include <iostream>
#include <stdexcept>


using namespace std;

struct queue_node {
    queue_node *next;
    int value;
};


struct queue_structure {
    queue_node *rear, *front;
};

typedef struct queue_structure my_queue;

void create(my_queue **queue){
    (*queue) = new my_queue();
    (*queue)->rear = nullptr;
    (*queue)->front = nullptr;
}

bool isEmpty(my_queue *queue){
    return queue->rear == nullptr || queue->front == nullptr;
}

int size(my_queue *queue){
    size_t length = 0;

    if(isEmpty(queue)) return 0;

    queue_node *temp = queue->front;
    while(temp != nullptr){
        length++;
        temp = temp->next;
    }

    return length;
}

void enqueue(my_queue **queue, int value){
    queue_node *new_node = new queue_node();
    new_node->value = value;
    new_node->next = nullptr;

    if(size(*queue) == 0){
        (*queue)->rear = (*queue)->front = new_node;
    }else{
        ((*queue)->rear)->next = new_node;
        (*queue)->rear = new_node;
    }
}

int dequeue(my_queue **queue){
    int front_value;

    try{
        if((*queue)->front == nullptr) throw runtime_error("Dequeuing failed. queue is empty.");

        queue_node *temp = ((*queue)->front)->next;

        front_value = ((*queue)->front)->value;

        delete (*queue)->front;
        (*queue)->front = temp;
    } catch (const runtime_error& err){
        cerr << "\nError: " << err.what();
    }

    return front_value;
}

void display(my_queue *queue){
    try{
        if(isEmpty(queue)) throw runtime_error("Can't display empty queue.");

        queue_node *temp = queue->front;

        cout << "\nQueue elements: ";
        while(temp != nullptr){
            cout << temp->value << " -> ";
            temp = temp->next;
        }
        cout << endl;
    } catch (const runtime_error& err){
        cerr << "\nError encoutered: " << err.what();
    }
}

int main(){
    my_queue *queue;
    create(&queue);

    display(queue);

    enqueue(&queue, 10);
    enqueue(&queue, 20);
    enqueue(&queue, 30);
    enqueue(&queue, 40);

    while(!isEmpty(queue)){
        cout << "\nQueue element: " << dequeue(&queue);
    }

    display(queue);
    return 0;
}