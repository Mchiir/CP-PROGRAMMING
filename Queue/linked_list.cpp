// Let's implement a queue with a linked-list with nodes holding integer values

#include <iostream>
#include <stdexcept>


using namespace std;

struct queue_base_structure {
    struct queue_base_structure *next;
    int value;
};

typedef struct queue_base_structure my_queue;

void create(my_queue **rear){
    *rear = nullptr;
}

bool isEmpty(my_queue *rear){
    return rear == nullptr;
}

int size(my_queue *rear){
    size_t length = 0;

    if(isEmpty(rear)) return 0;

    my_queue *temp = rear;
    while(temp != nullptr){
        length++;
        temp = temp->next;
    }
    cout << endl;
   
    return length;
}

void enqueue(my_queue **rear, int value){
    my_queue *new_node = new my_queue();
    new_node->value = value;

    new_node->next = *rear;
    *rear = new_node;
}

int dequeue(my_queue **rear){
    int front_value;

    try{
        if(isEmpty(*rear)) throw runtime_error("Dequeuing failed. Queue is empty.");
        else if(size(*rear) == 1){
            front_value = (*rear)->value;
            delete *rear;

            *rear = nullptr;
        }else{

        my_queue *prev;
        my_queue *temp;
        
        temp = *rear;
        while(temp->next != nullptr){
            prev = temp;
            temp = temp->next;
        }

        front_value = temp->value;
        delete temp;
        prev->next = nullptr;
    }
    } catch (const runtime_error& err){
        cerr << "\nError: " << err.what();
    }

    return front_value;
}

void display(my_queue *rear){
    try{
        if(isEmpty(rear)) throw runtime_error("Can't display empty queue.");

        my_queue *temp = rear;
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
    my_queue *rear;
    create(&rear);

    display(rear);

    enqueue(&rear, 10);
    enqueue(&rear, 20);
    enqueue(&rear, 30);
    enqueue(&rear, 40);

    while(true){
        cout << "\nQueue element: " << dequeue(&rear);
    }

    display(rear);
    return 0;
}