// Let's implement RPN with linked-list stack
// supported operators (+, -, *, /, () , ^)

#include <iostream>
#include <stdio.h>
#include <string>
#include <sstream>
#include <vector>
#include <set>
#include <stdexcept>
#include <cctype>
#include <stack>

using namespace std;

struct node {
    struct node *next;
    int value;
};

typedef struct node my_stack;

my_stack *top;

void create(my_stack **top){
    (*top) = nullptr;
}

int isEmpty(my_stack **top){
    return (*top) == nullptr;
}

void push(my_stack **top, int element){
    // stack *new_node = new stack;
    my_stack *new_node = (my_stack *) malloc (sizeof(my_stack)); // casting and mem allocation
    new_node->value = element;
    new_node->next = *top;
    *top = new_node;
}

int pop(my_stack **top){
    if(isEmpty(top)){
        cout << "\nStack underflow";
        return -1;
    }else{
        int top_value;
        my_stack *temp;

        top_value = (*top)->value; // use brackets, as -> has high precedence
        temp = *top;
        *top = (*top)->next;
        free (temp);
        return top_value;
    }
}



void display(my_stack **top){
    if(isEmpty(top)){
        cout << "\nStack is empty";
        return;
    }else{
        cout << "\nStack elements :" << endl;
        my_stack *temp = (*top);

        while(temp != nullptr){
            cout << temp->value << " ";
            temp = temp->next;
        }
    }
}

bool isNumber(const string& s){
    if (s.empty()) return false;
    for (char c : s) {
        if (!isdigit(static_cast<unsigned char>(c))) return false;
    }

    return true;
}

// operator precedence
int precedence(const string& op){
    if(op == "*" || op == "/") return 2;
    if(op == "+" || op == "-") return 1;
    return 0;
}

vector<string> infix_to_postfix(const string& infix_expression, const set<string>& supported_operators){
    stringstream ss(infix_expression);
    vector<string> postfix;
    string token;
    stack<string> operations_stack;

    while(ss >> token){ // whitespace splitting
        if(isNumber(token)){
            postfix.push_back(token);

        }else if(supported_operators.count(token)){
            if(token == "("){
                operations_stack.push(token);
            }else if(token == ")"){
                // popping until closing bracket

                while(!operations_stack.empty() && operations_stack.top() != "("){
                    postfix.push_back(operations_stack.top());
                    operations_stack.pop();
                }

                if(operations_stack.empty())
                    throw invalid_argument("Mismatched parentheses");

                operations_stack.pop();// removing closing bracket
            }
            
            if(!operations_stack.empty()){
                postfix.push_back(token);
            }else{
                // operator handling

                while(!operations_stack.empty() && precedence(operations_stack.top()) >= precedence(token) && operations_stack.top() != "("){
                    postfix.push_back(operations_stack.top());
                    operations_stack.pop();
                }

                // if token > stack_top_operator in precedence
                operations_stack.push(token);
            }
        }else{
            throw invalid_argument("Invalid token: " + token);
        }
    }

    while(!operations_stack.empty()){
        if(operations_stack.top() == "(" || operations_stack.top() == ")")
            throw invalid_argument("Mismatched parentheses");
        
        postfix.push_back(operations_stack.top());
        operations_stack.pop();
    }

    return postfix;
}

int postfix_to_value(const vector<string>& postfix, const set<string>& supported_operators){
    my_stack *top;
    create(&top);
    cout << "\nThe postfix vector: ";
    for(const auto& token : postfix ){
        cout << token << " ";
    }
    cout << endl;
    
    for(const string& token : postfix){
        if(isNumber(token)){
            push(&top, stoi(token));
        }else if(supported_operators.count(token)){
            int val2 = pop(&top);
            if(isEmpty(&top)) throw runtime_error("Not enough operands");
            int val1 = pop(&top);

            if(token == "+")
                push(&top, (val1+val2));
            else if(token == "-")
                push(&top, (val1-val2));
            else if(token == "*")
                push(&top, (val1*val2));
            else if(token == "/"){
                if(val2 == 0) throw invalid_argument("Can't divide by zero");
                    push(&top, (val1/val2));
            }else
                continue;

        }else{
            continue;
        }
    }
    
    return pop(&top);
}

int calculate(const string& infix_input){
    const set<string> SUPPORTED_OPERATORS = {"+", "-", "*", "/", "(", ")"};

    vector<string> postfix = infix_to_postfix(infix_input, SUPPORTED_OPERATORS);
    int result = postfix_to_value(postfix, SUPPORTED_OPERATORS);

    return result;
}

int main(){
    string random_expression = "6 * 3 - ( 4 - 5 ) + 2";

    int result = calculate(random_expression);
    cout << "\n" << random_expression << " = " << result << endl;
    return 0;
}