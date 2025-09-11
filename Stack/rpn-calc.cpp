// Let's implement RPN with linked-list stack and stack from c++ STL(Standard Template library)
// supported operators (+, -, *, /, (, ) )

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <set>
#include <stdexcept>
#include <cctype>
#include <stack>

using namespace std;

// supported operators
const set<string> SUPPORTED_OPERATORS = {"+", "-", "*", "/", "(", ")"};

struct node {
    struct node *next;
    int value;
};

typedef struct node my_stack;

// Function declarations

// Custom stack
void create(my_stack **top);
int isEmpty(my_stack **top);
void push(my_stack **top, int element);
int pop(my_stack **top);
void display(my_stack **top);

// Helper functions
bool isNumber(const string& s);
int precedence(const string& op);

// RPN
vector<string> infix_to_postfix(const string& infix_expression);
int postfix_to_value(const vector<string>& postfix);
string format_infix(const string& infix);
int calculate(const string& infix_input);
bool validate_infix(const string& infix);

void show_menu(){
    cout << "\n========= CLI Calculator Menu =========\n";
    cout << "1. Check if string is a number\n";
    cout << "2. Validate infix expression\n";
    cout << "3. Convert infix to postfix\n";
    cout << "4. Evaluate postfix expression\n";
    cout << "5. General calculator (evaluate infix)\n";
    cout << "6. Exit\n";
    cout << "=======================================\n";
    cout << "Enter your choice: ";
}


int main(){
    // string random_expression1 = "6 * 3 - ( 4 - 5 ) + 2";
    // string random_expression2 = "( 4 + 7 ) + 12 / 3";
    // string random_expression3 = "12 * 4 / 3 + ( 32 + 5 ^ 1 )";
    // int result1 = calculate(random_expression1);
    // cout << "\n" << random_expression1 << " = " << result1 << endl;

    // int result2 = calculate(random_expression2);
    // cout << "\n" << random_expression2 << " = " << result2 << endl;

    // int result3 = calculate(random_expression3);
    // cout << "\n" << random_expression3 << " = " << result3 << endl;

    cout << "\nWelcome!, Let's evaluate mathematical expressions";
    cout << "\nSupported operators: ";
    for(const auto& op: SUPPORTED_OPERATORS){
        cout << op << " ";
    }
    cout << endl;

    while(true){
        show_menu();
        int choice;
        cin >> choice;
        cin.ignore();

        if (choice == 6) {
            std::cout << "Goodbye!\n";
            break;
        }

        std::string input;
        switch (choice) {
            case 1: {
                std::cout << "Enter a string to check if it's a number: ";
                std::getline(std::cin, input);
                bool result = isNumber(input);
                std::cout << "'" << input << "' is " << (result ? "" : "not ") << "a number.\n";
                break;
            }
            case 2: {
                std::cout << "Enter infix expression for validation: ";
                std::getline(std::cin, input);
                bool result = validate_infix(input);
                std::cout << "Expression is " << (result ? "VALID" : "INVALID") << ".\n";
                break;
            }
            case 3: {
                std::cout << "Enter infix expression to convert to postfix: ";
                std::getline(std::cin, input);
                if (!validate_infix(input)) {
                    std::cout << "Invalid infix expression!\n";
                    break;
                }
                std::vector<std::string> postfix = infix_to_postfix(input);
                std::cout << "Postfix: ";
                for (const auto& token : postfix)
                    std::cout << token << " ";
                std::cout << std::endl;
                break;
            }
            case 4: {
                std::cout << "Enter postfix expression (space separated): ";
                std::getline(std::cin, input);
                std::vector<std::string> tokens;
                std::string token;
                std::istringstream iss(input);
                while (iss >> token) {
                    tokens.push_back(token);
                }
                int value = postfix_to_value(tokens);
                std::cout << "Value of postfix expression: " << value << std::endl;
                break;
            }
            case 5: {
                std::cout << "Enter infix expression to evaluate: ";
                std::getline(std::cin, input);
                int result = calculate(input);

                std::cout << "Result: " << result << std::endl;
                break;
            }
            default: {
                std::cout << "Invalid choice! Please try again.\n";
                break;
            }
        }
    }

    
    return 0;
}


// Function defintions

// my_stack *top;
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

vector<string> infix_to_postfix(const string& infix_expression){
    stringstream ss(infix_expression);
    vector<string> postfix;
    string token;
    stack<string> operations_stack;

    while(ss >> token){ // whitespace splitting
        // cout << "\n current token: " << token;

        
        if(isNumber(token)){
            postfix.push_back(token);

        }else if(SUPPORTED_OPERATORS.count(token)){
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
            }else{
                // operator handling

                if(!operations_stack.empty() && precedence(operations_stack.top()) >= precedence(token) && operations_stack.top() != "(" && operations_stack.top() != ")"){
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

int postfix_to_value(const vector<string>& postfix){
    my_stack *top;
    create(&top);
    
    for(const string& token : postfix){
        if(isNumber(token)){
            push(&top, stoi(token));
        }else if(SUPPORTED_OPERATORS.count(token)){
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
                if(val2 == 0) throw runtime_error("Can't divide by zero");
                    push(&top, (val1/val2));
            }else
                continue;

        }else{
            continue;
        }
    }
    
    return pop(&top);
}


string format_infix(const string& infix){
    if(infix.empty()) throw invalid_argument("Invalid infix: "+ infix);
    if(SUPPORTED_OPERATORS.count(string(1, infix[0])) && string(1, infix[0]) != "(" && string(1, infix[0]) != ")") throw invalid_argument("Invalid infix: "+ infix);

    string corrected_infix = "";
    size_t i = 0;
    while(i < infix.size()){
        
        if(isspace(infix[i])){
            ++i;
            continue;
        }else if(isdigit(infix[i])){
            string number = "";

            while(i < infix.size() && isdigit(infix[i])){
                number += infix[i];
                ++i;
            }
        
            corrected_infix += number + " ";
        }else{
            string op(1, infix[i]);
            if(SUPPORTED_OPERATORS.count(op)){
                corrected_infix += op + " ";
                ++i;
            } else {
                throw invalid_argument("Invalid token in infinix: "+ op);
            }
        }
    }
    
    return corrected_infix;
}

bool validate_infix(const string& infix){
    if(infix.empty()) return false;
    if(SUPPORTED_OPERATORS.count(string(1, infix[0])) && infix[0] != '(')
        return false;

    for(char c : infix){
        if(!isdigit(c) && !isspace(c) && !SUPPORTED_OPERATORS.count(string(1,c)))
            return false;
    }
    return true;
}


int calculate(const string& infix_input){
    

    cout << "\nReceived infix_input: " << infix_input;

    string formated_infix = format_infix(infix_input);

    cout << "\nValidated infix: " << formated_infix;


    vector<string> postfix = infix_to_postfix(formated_infix);

    cout << "\nThe postfix vector: ";
    for(const auto& token : postfix ){
        cout << token << " ";
    }
    cout << endl;

    int result = postfix_to_value(postfix);

    return result;
}