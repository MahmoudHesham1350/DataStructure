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

    void srt();
    T findMedian();
    T findMin();
    T findMax();
    double findMean();
    T findSum();

    void displayArray();
    void inputData();
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
void statisticaCalc<T>::srt(){
    for(int i = 1, j; i < size; i++)
    {
        T tmp = data[i];
        for(j = i; j >0 && tmp<data[j-1];j--)
            data[j] = data[j-1];
        data[j] = tmp;
    }
}

template <typename T>
T statisticaCalc<T>::findMedian(){
    srt();
    if(size % 2 == 0){
        return (data[size/2 - 1] + data[size/2]) / 2;
    }
    return data[size/2];
}

template <typename T>
T statisticaCalc<T>::findMin(){
    srt();
    return data[0];
}

template <typename T>
T statisticaCalc<T>::findMax(){
    srt();
    return data[size - 1];
}

template <typename T>
double statisticaCalc<T>::findMean(){
    srt();
    double sum = 0;
    for(int i = 0; i < size; i++){
        sum += data[i];
    }
    return sum / size;
}

template <typename T>
T statisticaCalc<T>::findSum(){
    srt();
    T sum = 0;
    for(int i = 0; i < size; i++){
        sum += data[i];
    }
    return sum;
}

template <typename T>
void statisticaCalc<T>::displayArray(){
    srt();
    for(int i = 0; i < size; i++){
        cout << data[i] << " ";
    }
    cout << endl;
}


template <typename T>
void statisticaCalc<T>::inputData(){
    for(int i = 0; i < size; i++){
        cout << "Enter data " << i + 1 << ": ";
        cin >> data[i];
    }
}

template <typename T>
void statisticaCalc<T>::statisticsMenu(){

    int choice;
    do{
        cout << "\n1. Find Median" << endl;
        cout << "2. Find Min" << endl;
        cout << "3. Find Max" << endl;
        cout << "4. Find Mean" << endl;
        cout << "5. Find Sum" << endl;
        cout << "6. Display Array" << endl;
        cout << "7. Exit" << endl;
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
    int size;
    cout << "Enter size of data: ";
    cin >> size;
    statisticaCalc<int> sc(size);
    sc.inputData();
    sc.statisticsMenu();
    return 0;
}
