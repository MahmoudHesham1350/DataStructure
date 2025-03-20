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
    public:
    IftarManager(){
        head = NULL;
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
    void add_guest(string name, string contact, string Iftar_date){
        Guest *newGuest = new Guest(name, contact, Iftar_date);
        if(head == NULL){
            head = newGuest;
            cout << "-> " << name << " Added successfully! <-" << endl;
        }
        else{
            newGuest->next = head;
            head = newGuest;
            cout << "-> " << name << " Added successfully! <-" << endl;
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

int main() {
    IftarManager manager;
    ifstream inFile("Problem1_testcases.txt");
    string line;

    if (inFile.is_open()) {
        while (getline(inFile, line)) { 
            pass(line, manager);
        }
        inFile.close();
    }
    manager.display_all_guests();
    cout << "------------------------------------------------------------------\n";
    manager.sort_guest_list();
    manager.display_all_guests();
}

