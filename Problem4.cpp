#include <iostream>
using namespace std;

template <typename T>
class SortingSystem {
private:
    T* data;  // Dynamic array for storing input data
    int size; // Size of the array

public:
    SortingSystem(int n);  // Constructor   // Done
    ~SortingSystem();      // Destructor    // Done

    void insertionSort();  // (1) Insertion Sort
    void selectionSort();  // (2) Selection Sort
    void bubbleSort();     // (3) Bubble Sort
    void shellSort();      // (4) Shell Sort
    void mergeSort(int left, int right); // (5) Merge Sort
    void quickSort(int left, int right); // (6) Quick Sort
    void countSort();      // (7) Count Sort (Only for int)
    void radixSort();      // (8) Radix Sort (Only for int)
    void bucketSort();     // (9) Bucket Sort

    void merge(int left, int mid, int right); // Merge Sort Helper
    int partition(int low, int high); // Quick Sort Helper

    void displayData();  // Print the current state of the array    // Done 
    void measureSortTime(void (SortingSystem::*sortFunc)()); // Measure sorting time

    void showMenu(); // Display menu for user interaction   // nearly Done
};


template <typename T> 
SortingSystem<T>::SortingSystem(int n) {
    this.size = n; 
    this.data = new T[n];
}

template <typename T> 
SortingSystem<T>::~SortingSystem() {
    delete[] data;
}


template <typename T> 
void SortingSystem<T>::displayData() {
    for(int i = 0; i < size; i++) {
        cout << data[i] << " "; 
    }
    cout << "===============================" << endl;
}

template <typename T>
void SortingSystem<T>::showMenu() {
    cout << "please enter tha data that you want to sort" << endl;
    for(int i = 0; i < size; i++) {
        cin >> data[i];
    }
    cout << "now please enter the number of the sorting algorithm you want to use" << endl;
    cout << "1) Insertion Sort" << endl;
    cout << "2) Selection Sort" << endl;
    cout << "3) Bubble Sort" << endl;
    cout << "4) Shell Sort" << endl;
    cout << "5) Merge Sort" << endl;
    cout << "6) Quick Sort" << endl;
    cout << "7) Count Sort" << endl;
    cout << "8) Radix Sort" << endl;
    cout << "9) Bucket Sort" << endl;
    int choice;
    cin >> choice;
    while (choice < 1 || choice > 9) {
        cout << "please enter a valid choice" << endl;
        cin >> choice;
    }
    switch (choice) {
        case 1:
            insertionSort();
            measureSortTime(&SortingSystem::insertionSort);
            break;
        case 2:
            selectionSort();
            measureSortTime(&SortingSystem::selectionSort);
            break;
        case 3:
            bubbleSort();
            measureSortTime(&SortingSystem::bubbleSort);
            break;
        case 4:
            shellSort();
            measureSortTime(&SortingSystem::shellSort);
            break;
        case 5:
            mergeSort(0, size - 1);
            measureSortTime(&SortingSystem::mergeSort);
            break;
        case 6:
            quickSort(0, size - 1);
            measureSortTime(&SortingSystem::quickSort);
            break;
        case 7:
            countSort();
            measureSortTime(&SortingSystem::countSort);
            break;
        case 8:
            radixSort();
            measureSortTime(&SortingSystem::radixSort);
            break;
        case 9:
            bucketSort();
            measureSortTime(&SortingSystem::bucketSort);
            break;
    }
}


template <typename T>
void SortingSystem<T>::insertionSort() {
    T temp; 
    int i, j;
    for(i = 0; i < size; i++) 
    {
        temp = data[i]; 
        for(j = i; j > 0 && data[i] < data[j]; j--) //data[j-1]*
        {
            data[j] = data[j-1]; 
        }
        data[j] = temp
    }
}


template <typename T>
void SortingSystem<T>::selectionSort() {
    T minValue; 
    int i, j, minIndex; 
    for(i = 0; i < n-1; i++)
    {
        minValue = data[i]; 
        minIndex = i; 
        for(j = i+1; j < n; j++)
        {
            if(data[j] < minValue)
            {
                minValue = data[j]; 
                minIndex = j; 
            }
        }
        if(minIndex != i)
            swap(data[i],data[minIndex]);
    }
}


template <typename T>
void SortingSystem<T>::bubbleSort() {
    for(int i = n-1; i >= 0; i--)
    {
        for(int j = 0; j < i; j++)
        {
            if(data[j] > data[j+1])
                swap(data[j],data[j+1]); 
        }
    }
}

