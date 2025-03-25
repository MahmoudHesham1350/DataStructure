#include <bits/stdc++.h>
using namespace std;

template <typename T>
class statisticaCalc{
private:
    T* data;
    int size;
public:
    statisticaCalc(int size);
    ~statisticaCalc();

    void sort();
    double findMedian();
    T findMin();
    T findMax();
    double findMean();
    T findSum();

    void displayArray();
    void inputData(ifstream &file);
    void statisticsMenu();
};

template <typename T>
statisticaCalc<T>::statisticaCalc(int size){
    this->size = size;
    data = new T[size];
}

template <typename T>
statisticaCalc<T>::~statisticaCalc(){
    delete[] data;
}

template <typename T>
void statisticaCalc<T>::sort(){
//    Insertion Sort
    for(int i = 1; i< size; i++)
    {
        T tmp = data[i];
        int j = i-1;
        while(j >= 0 && data[j] > tmp)
        {
            data[j+1] = data[j];
            j--;
        }
        data[j+1] = tmp;
    }
}

template <typename T>
double statisticaCalc<T>::findMedian(){
    if(size % 2 == 0){
        return (static_cast<double>(data[size/2 - 1]) + static_cast<double>(data[size/2])) / 2.0;
    }
    return static_cast<double>(data[size/2]);
}

template <typename T>
T statisticaCalc<T>::findMin(){
    return data[0];
}

template <typename T>
T statisticaCalc<T>::findMax(){
    return data[size - 1];
}

template <typename T>
double statisticaCalc<T>::findMean(){
    double sum = 0;
    for(int i = 0; i < size; i++){
        sum += data[i];
    }
    return sum / size;
}

template <typename T>
T statisticaCalc<T>::findSum(){
    T sum = 0;
    for(int i = 0; i < size; i++){
        sum += data[i];
    }
    return sum;
}

template <typename T>
void statisticaCalc<T>::displayArray(){
    for(int i = 0; i < size; i++){
        cout << data[i] << " ";
    }
    cout << endl;
}


template <typename T>
void statisticaCalc<T>::inputData(ifstream &file){
    for(int i = 0; i < size; i++){
        if (!(file >> data[i])) {
            cerr << "Error reading data from file!" << endl;
            exit(1);
        }
    }
    sort();
}

template <typename T>
void statisticaCalc<T>::statisticsMenu(){
    int choice;
    do{
        cout << "\n1-> Find Median" << endl;
        cout << "2-> Find Min" << endl;
        cout << "3-> Find Max" << endl;
        cout << "4-> Find Mean" << endl;
        cout << "5-> Find Sum" << endl;
        cout << "6-> Display Array" << endl;
        cout << "7-> Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;
        switch(choice){
            case 1:
                cout << "Median: " << findMedian() << endl;
                break;
            case 2:
                cout << "Min: " << findMin() << endl;
                break;
            case 3:
                cout << "Max: " << findMax() << endl;
                break;
            case 4:
                cout << "Mean: " << findMean() << endl;
                break;
            case 5:
                cout << "Sum: " << findSum() << endl;
                break;
            case 6:
                displayArray();
                break;
            case 7:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice" << endl;
        }
    }while(choice != 7);
}

int main()
{
    int size, typeChoice;
    string filename;

    cout << "Enter filename: ";
    cin >> filename;
    ifstream file(filename);
    if (!file) {
        cerr << "Error opening file!" << endl;
        return 1;
    }

    cout << "Enter size of data: ";
    cin >> size;

    cout << "Select data type:\n"
            "1. Integer\n"
            "2. Double\n"
            "Enter choice: ";
    cin >> typeChoice;

    if(typeChoice == 1){
        statisticaCalc<int> sc(size);
        sc.inputData(file);
        sc.statisticsMenu();
    }
    else if(typeChoice == 2){
        statisticaCalc<double> sc(size);
        sc.inputData(file);
        sc.statisticsMenu();
    }
    else {
        cout << "Invalid data type selection!" << endl;
    }

    file.close();
    return 0;
}
