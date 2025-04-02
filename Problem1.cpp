#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
using namespace std;

class Guest {
    public:
    string name;
    string contact;
    string Iftar_date;
    Guest *next;
    //-------------------
    Guest(string name = "null", string contact = "null", string Iftar_date = "null"){
        this->name = name;
        this->contact = contact;
        this->Iftar_date = Iftar_date;
        next = NULL;
    }
    //-------------------
    void display_guest(){
        cout << "Guest: " << name;
        cout << ", Contact: " << contact;
        cout << ", Iftar date: " << Iftar_date << endl;
    }
    //-------------------
    void update_invitation(string newDate){
        Iftar_date = newDate;
    }
};

class IftarManager {
    private:
    Guest *head;
    int no_guests;
    public:
    IftarManager(){
        head = NULL;
        no_guests = 0;
    }
    //-------------------
    ~IftarManager() {
        while (head != NULL) {
            Guest* temp = head;
            head = head->next;
            delete temp;
        }
    }
    //-------------------
    int get_no_guests(){
        return this->no_guests;
    }
    //-------------------
    void add_guest(string name, string contact, string Iftar_date){
        Guest *newGuest = new Guest(name, contact, Iftar_date);
        if(head == NULL){
            head = newGuest;
            cout << "-> " << name << " Added successfully! <-" << endl;
            no_guests++;
        }
        else{
            newGuest->next = head;
            head = newGuest;
            cout << "-> " << name << " Added successfully! <-" << endl;
            no_guests++;
        }
    }
    //-------------------
    void Remove(string name) {
        if (head == NULL) {
            cout << "--> Guest list is empty! <--" << endl;
            return;
        }
        if (head->name == name) {
            Guest* node = head;
            head = head->next;
            cout << "--> " << node->name << " removed successfully <--" << endl;
            delete node;
            no_guests--;
            return;
        }
        Guest* temp = head;
        while (temp->next != NULL && temp->next->name != name) {
            temp = temp->next;
        }
        if (temp->next != NULL) {
            Guest* node = temp->next;
            temp->next = temp->next->next;
            cout << "--> " << node->name << " removed successfully <--" << endl;
            delete node;
            no_guests--;
        } else {
            cout << "-> " << name << " is not a guest <-\n";
        }
    }
    //-------------------
    void display_all_guests(){
        Guest* curr = head;
        while(curr != NULL){
            curr->display_guest();
            curr = curr->next;
        }
    } 
    //-------------------
    void update_guest_invitation(string name, string newDate){
        Guest *temp = head;
        bool found = false;
        while(temp != NULL){
            if(temp->name == name){
                found = true;
                break;
            }
            temp = temp->next;
        }
        if(found){
            temp->Iftar_date = newDate;
            cout << "-> Updated " << name << " iftar date successfully! <-\n";
        }
        else
        cout << "-> he is not a guest!! <-\n";
    }
    //-------------------
    void display_guest(string name){
        Guest *temp = head;
        bool found = false;
        while(temp != NULL){
            if(temp->name == name){
                found = true;
                break;
            }
            temp = temp->next;
        }
        if(found){
            cout << "Guest name : " << temp->name;
            cout << "\nGuest contact : " << temp->contact;
            cout << "\nGuest iftar date : " << temp->Iftar_date << "\n";
        }
        else
            cout << "-> he is not a guest!! <-\n";
    }
    //-------------------
    void send_reminder(string Date){
        cout << "Sending reminders...\n";
        Guest *temp = head;
        while(temp != NULL){
            if(temp->Iftar_date == Date){
                cout << "Sending reminder to " << temp->name << " at ";
                cout << temp->contact << " for Iftar on " << Date << endl;
            }
            temp = temp->next;
        }
    }
    //-------------------
    bool compare(string dateOne, string dateTwo){
        short countOne = 0;
        short countTwo = 0;
        string day = "";
        string dayUP = "";
        for(int i = dateOne.length() - 1; i > 0; i--){
            if(dateOne[i] == '-') break;
            else day += dateOne[i];
        }
        if(day.length() == 2){
            dayUP += day[1]; 
        }
        dayUP += day[0]; 
        countOne = stoi(dayUP);
        day = "";
        dayUP = "";
        for(int i = dateTwo.length() - 1; i > 0; i--){
            if(dateTwo[i] == '-') break;
            else day += dateTwo[i];
        }
        if(day.length() == 2){
            dayUP += day[1]; 
        }
        dayUP += day[0]; 
        countTwo = stoi(dayUP);
        return countTwo < countOne;
    }
    //-------------------
    void sort_guest_list() {
        if (!head || !head->next) {
            return;
        }
        Guest* sortedHead = NULL;
        Guest* curr = head;
    
        while (curr) {
            Guest* minNode = curr; 
            Guest* temp = curr->next;

            while (temp) {
                if (compare(minNode->Iftar_date, temp->Iftar_date)) {
                    minNode = temp;
                }
                temp = temp->next;
            }
            if (minNode == head) {
                head = head->next;
            }
            else {
                Guest* prev = head;
                while (prev->next != minNode) {
                    prev = prev->next;
                }
                prev->next = minNode->next;
            }
            if (!sortedHead) {
                sortedHead = minNode;
                sortedHead->next = NULL;
            } 
            else {
                Guest* last = sortedHead;
                while (last->next) {
                    last = last->next;
                }
                last->next = minNode;
                minNode->next = NULL;
            }
            curr = head;
        }
        head = sortedHead;
        cout << "--> Sorted succesfully! <--\n";
    }
}; 


void pass(string line, IftarManager& manager){
    string name, contact, iftarDate;
    int i = 0;
    for(i ; i < line.length(); i++){
        if(line[i] == ' ')
            break;
        else
            name += line[i];
    }
    i++;
    for(i ; i < line.length(); i++){
        if(line[i] == ' ')
        break;
        else
        contact += line[i];
    }
    i++;
    for(i ; i < line.length(); i++){
        if(line[i] == ' ')
            break;
        else
            iftarDate += line[i];
    }
    manager.add_guest(name, contact, iftarDate);
}

void menu(IftarManager& manager){
    cout << "What do you want to do?" << endl;
    short choice = 1;
    while(choice != 0){
        cout << "\n1) Add a new guest\n2) Update guest\n3) Display guest\n";
        cout << "4) Display all guests\n5) Sort guest list\n6) Send reminder";
        cout << "\n7) Number of guests\n8) Remove guest\n0) Exit\n--> ";
        cin >> choice;
        while(choice < 0 || choice > 8){
            cout << "Wrong operation number!" << endl;
            cout << "Please insert valid number.\n--> ";
            cin >> choice;
        }
        string info = "";
        string name, contact, iftarDate;
        switch (choice)
        {
        case 1:
            cout << "Put guest name : \n--> ";
            cin >> name;
            cout << "Put guest contact : \n--> ";
            cin >> contact;
            cout << "Put guest iftar date : \n--> ";
            cin >> iftarDate;
            manager.add_guest(name, contact, iftarDate);
            break;
        case 2:
            cout << "Put guest name : \n--> ";
            cin >> name;
            cout << "Put guest new date : \n--> ";
            cin >> iftarDate;
            manager.update_guest_invitation(name,iftarDate);
            break;
        case 3:
            cout << "Put guest name : \n--> ";
            cin >> name;
            manager.display_guest(name);
            break;
        case 4:
            manager.display_all_guests();
            break;
        case 5:
            manager.sort_guest_list();
            break;
        case 6:
            cout << "Put iftar date : \n--> ";
            cin >> iftarDate;
            manager.send_reminder(iftarDate);
            break;
        case 7:
            cout << "--> Number of guests: " << manager.get_no_guests() << " <--\n";
            break;
        case 8:
            cout << "Put guest name : \n--> ";
            cin >> name;
            manager.Remove(name);
            break;
        default:
            break;
        }
    }
}

void test_case(IftarManager& manager) {
    // Add guests
    manager.add_guest("Aisha", "aisha@gmail.com", "2025-03-15");
    manager.add_guest("Omar", "omar@gmail.com", "2025-03-18");
    manager.add_guest("Zainab", "zainab@gmail.com", "2025-03-20");
    manager.add_guest("Mohammed", "mohammed@gmail.com", "2025-03-16");
    manager.add_guest("Fatima", "fatima@gmail.com", "2025-03-15");
    manager.add_guest("Ahmad", "ahmad@gmail.com", "2025-03-17");
    manager.add_guest("Sara", "sara@gmail.com", "2025-03-19");
    manager.add_guest("Hassan", "hassan@gmail.com", "2025-03-15");
    manager.add_guest("Mariam", "mariam@gmail.com", "2025-03-16");
    manager.add_guest("Yusuf", "yusuf@gmail.com", "2025-03-18");

    cout << "\n=== Initial Guest List ===\n";
    manager.display_all_guests();

    // Update some invitation dates
    cout << "\n=== Updating Invitation Dates ===\n";
    manager.update_guest_invitation("Omar", "2025-03-15");
    manager.update_guest_invitation("Sara", "2025-03-16");
    manager.update_guest_invitation("Yusuf", "2025-03-15");

    cout << "\n=== Updated Guest List ===\n";
    manager.display_all_guests();

    // Test sorting
    cout << "\n=== Sorting Guest List by Date ===\n";
    manager.sort_guest_list();
    manager.display_all_guests();

    // Send reminders for specific dates
    cout << "\n=== Sending Reminders for March 15 ===\n";
    manager.send_reminder("2025-03-15");
    
    cout << "\n=== Sending Reminders for March 16 ===\n";
    manager.send_reminder("2025-03-16");

    // Remove some guests
    cout << "\n=== Removing Guests ===\n";
    manager.Remove("Ahmad");
    manager.Remove("Mariam");

    cout << "\n=== Final Guest List ===\n";
    manager.display_all_guests();
    
    cout << "\n=== Total Number of Guests ===\n";
    cout << "Number of guests: " << manager.get_no_guests() << endl;
}

int main() {
    IftarManager manager;
    
    /*
    string fileName = "";
    cout << "Insert file name with extension .txt : \n--> ";
    cin >> fileName;
    ifstream inFile(fileName);
    string line;
    if (inFile.is_open()) {
        while (getline(inFile, line)) { 
            pass(line, manager);
        }
        cout << "\nDone reading file :)\n";
        inFile.close();
    }
    else {
        cout << "Wrong file name : " << fileName << "\nTry again at another time :)\n";
        return 0;
    }
    */

    // Run test cases
    test_case(manager);

    // Start interactive menu
    menu(manager);
    
    return 0;
}
