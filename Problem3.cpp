#include <iostream>
#include <limits>
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

// Function to clear input buffer
void clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Function to display the menu
void displayMenu() {
    cout << "\n===== Sorted Linked List Menu =====\n";
    cout << "1. Insert a value\n";
    cout << "2. Remove a value at index\n";
    cout << "3. Display the list\n";
    cout << "4. Get value at index\n";
    cout << "5. Run test cases\n";
    cout << "6. Exit\n";
    cout << "Enter your choice: ";
}

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

// Function to handle the menu
void handleMenu(SortedLinkedList<int>& list) {
    int choice;
    int value, index;
    
    do {
        displayMenu();
        cin >> choice;
        clearInputBuffer();
        
        switch (choice) {
            case 1: // Insert a value
                cout << "Enter a value to insert: ";
                cin >> value;
                list.insert(value);
                cout << "Value inserted successfully!\n";
                break;
                
            case 2: // Remove a value at index
                cout << "Enter the index to remove: ";
                cin >> index;
                list.remove(index);
                break;
                
            case 3: // Display the list
                cout << "Current list: " << list << endl;
                break;
                
            case 4: // Get value at index
                cout << "Enter the index: ";
                cin >> index;
                try {
                    cout << "Value at index " << index << ": " << list[index] << endl;
                } catch (const std::out_of_range& e) {
                    cout << "Error: " << e.what() << endl;
                }
                break;
                
            case 5: // Run test cases
                cout << "\nRunning test cases...\n";
                test_case_1();
                test_case_2();
                test_case_3();
                break;
                
            case 6: // Exit
                cout << "Exiting program. Goodbye!\n";
                break;
                
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 6);
}



int main() {
    SortedLinkedList<int> list;
    handleMenu(list);
    return 0;
}