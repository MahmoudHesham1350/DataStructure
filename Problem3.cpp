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

    bool isEmpty(){  // Check if the list is empty
        return this->head == nullptr;
    };

    void insert(Type value){  // Insert a value while keeping the list sorted
        Node<Type>* new_node = new Node<Type>(value);

        // Case 1: Empty list
        if (this->isEmpty()){  
            this->head = new_node;
            return;
        }

        // Case 2: Insert at the beginning
        else if (this->head->data > value){  
            new_node->next = this->head;
            this->head = new_node;
            return;
        }

        else {  // Case 3: Insert in the middle or at the end
            Node<Type>* current = this->head;
            while(current->next != nullptr && current->next->data <= value){
                current = current->next;
            }
            // insert the new node after the current node
            new_node->next = current->next;  
            current->next = new_node; 
        }
    };  

    void remove(int index){  // Delete node at given index
        // Case 1: Empty list or negative index
        if (this->isEmpty() || index < 0){  
            return;
        }

        Node<Type>* current_node = this->head;
        // Case 2: Delete the first node
        if (index == 0){ 
            this->head = this->head->next;
            delete current_node;
            return;
        }

        // Case 3: Delete a node in the middle or at the end
        Node<Type>* prev_node = this->head;
        current_node = this->head->next;
        for(int idx=0; idx < index-1; idx++){  // Traverse to the node to be deleted
            if (current_node->next == nullptr){ // Index out of range
                return;
            }
            else{
                current_node = current_node->next;
                prev_node = prev_node->next;
            }
        }
        // Delete the node and update the pointers
        prev_node->next = current_node->next; 
        delete current_node;
        return;
    };

    // Overloaded operators
    friend ostream& operator<<(ostream& os, const SortedLinkedList& list){
        os << "[";
        Node<Type>* current = list.head;
        while (current != nullptr) {
            os << current->data;
            if (current->next != nullptr) {
                os << ", ";
            }
            current = current->next;
        }
        os << "]";
        return os;
    };

    Type operator[](int index){
        if (this->isEmpty() || index < 0){  // Empty list or negative index
            throw std::out_of_range("Index out of range");
        }

        Node<Type>* current_node = this->head;
        for (int idx=0; idx < index; idx++){
            if (current_node->next == nullptr){
                throw std::out_of_range("Index out of range");
            }
            else{
                current_node = current_node->next;
            }
        }
        return current_node->data;
    };

    ~SortedLinkedList(){ // Destructor to free memory
        Node<Type>* current_node;
        while(!this->isEmpty()){ // Traverse the list and delete each node
            current_node = this->head;
            this->head = this->head->next;
            delete current_node;
        }
    };
};



void test_case_1(){
    SortedLinkedList<int> list;
    list.insert(5); // L = [5]
    list.insert(8); // L = [5, 8]
    list.insert(7); // L = [5, 7, 8]
    list.insert(6); // L = [5, 6, 7, 8]
    list.insert(6); // L = [5, 6, 6, 7, 8]
    cout << list << endl; // Output: [5, 6, 6, 7, 8]
}

void test_case_2() {
    SortedLinkedList<int> list;
    list.insert(5);
    list.insert(8);
    list.insert(7);
    list.insert(6);
    list.insert(6);
    
    try {
        cout << list[2] << endl; // Output: 6
        cout << list[10] << endl; // Should throw exception
    }
    catch (const std::out_of_range& e) {
        cout << "Exception caught: " << e.what() << endl;
    }
}

void test_case_3() {
    SortedLinkedList<int> list;
    list.insert(5);
    list.insert(8);
    list.insert(7);
    list.insert(6);
    list.insert(6);
    
    cout << list << endl; // Output: [5, 6, 6, 7, 8]
    list.remove(0);
    cout << list << endl; // Output: [6, 6, 7, 8]
    list.remove(100);
    cout << list << endl; // Output: [6, 6, 7, 8]
    list.remove(2);
    cout << list << endl; // Output: [6, 6, 8]
    list.remove(2);
    cout << list << endl; // Output: [6, 6]
}


int main() {
    test_case_1();
    test_case_2();
    test_case_3();
    return 0;
}