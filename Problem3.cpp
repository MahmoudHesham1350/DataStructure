#include <iostream>
using namespace std;

// Node class for linked list
template <class Type>
class Node {
public:
    Type data;
    Node* next;
    Node(Type val){  // Constructor
        this->data = val;
        this->next = nullptr;
    }; 
};

// Sorted Linked List Class
template <class Type>
class SortedLinkedList {  // Pointer to the head of the list
private:
    Node<Type>* head; 

public:
    SortedLinkedList(){  // Constructor
        this->head = nullptr;
    };

    void insert(Type value){  // Insert a value while keeping the list sorted
        Node<Type>* new_node = new Node<Type>(value);
        if (this->head == nullptr){  // Case 1: Empty list
            this->head = new_node;
        }
        else if (this->head->data > value){  // Case 2: Insert at the beginning
            new_node->next = this->head;
            this->head = new_node;
        }
        else {  // Case 3: Insert in the middle or at the end
            Node<Type>* current = this->head;
            while(current->next != nullptr && current->next->data <= value){
                current = current->next;
            }
            new_node->next = current->next;  // new_node will point to the next node of the bigger value or nullptr
            current->next = new_node; // current will point to the new_node
        }
    };  

    void remove(Type index){  // Delete node at given index

    };

    // Overloaded operators
    friend ostream& operator<<(ostream& os, const SortedLinkedList& list){

    };
    int operator[](int index){

    };

    ~SortedLinkedList(){
        
    }; // Destructor to free memory
};


int main() {
    return 0;
}
