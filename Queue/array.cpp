// Let's implement a queue with array
// front -> 10 -> 20 -> nullptr <-rear

#include <iostream>
#include <stdexcept>

#define MAX_SIZE 5

using namespace std;

struct queue_node {
    int queue_array[MAX_SIZE];
    int front;
    int rear;
};

typedef struct queue_node queue;

void create(queue *q){
    q->front = q->rear = -1;
}

bool isEmpty(queue *q) {
    return q->front == -1;
}

bool isFull(queue *q) {
    return q->rear == MAX_SIZE - 1;
}

void enqueue(queue *q, int element){
    if (isFull(q)) {
        cerr << "Error: Queue is full. Cannot enqueue " << element << endl;
        return;
    }

    if(isEmpty(q)){
        q->front = 0;
    }

    q->queue_array[++q->rear] = element;
}

int dequeue(queue *q){
    int front_value = 0;
    if(isEmpty(q)) throw runtime_error("Queue is empty.");

    front_value = q->queue_array[q->front];

    if(q->front == q->rear){
        // Resetting after removing last element;
        q->front = q->rear = -1;
    }else{
        q->front++;
    }

    return front_value;
}

void display(queue *q){
    if(isEmpty(q)){
        cout << "\nQueue is empty, Can't display queue.";
        return;
    }

    cout << "\nQueue elements: ";
    int i = q->front;
    do{
      cout <<  q->queue_array[i] << " ";
      i++;
    } while (i <= q->rear);
    cout << endl;
}

int main(){
    queue my_queue;
    create(&my_queue);

    enqueue(&my_queue, 10);
    enqueue(&my_queue, 20);
    enqueue(&my_queue, 30);
    
    cout << "\nQueue element: "<< dequeue(&my_queue);
    cout << "\nQueue element: "<< dequeue(&my_queue);
    cout << "\nQueue element: "<< dequeue(&my_queue);
    display(&my_queue);

    enqueue(&my_queue, 40);
    enqueue(&my_queue, 50);
    enqueue(&my_queue, 60);
    enqueue(&my_queue, 70);

    display(&my_queue);

    return 0;
}