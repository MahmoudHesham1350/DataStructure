#include <iostream>
#include <chrono>
#include <random>
#include <algorithm>
using namespace std;
using namespace chrono; 

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

    void mergeSortWrapper();
    void quickSortWrapper();

    void displayData();  // Print the current state of the array    // Done 
    void measureSortTime(void (SortingSystem::*sortFunc)()); // Measure sorting time

    void showMenu(); // Display menu for user interaction   // nearly Done
};

template <typename T> 
SortingSystem<T>::SortingSystem(int n) {
    size = n; 
    data = new T[n];
}

template <typename T> 
SortingSystem<T>::~SortingSystem() {
    delete[] data;
}

template <typename T> 
void SortingSystem<T>::displayData() {
    cout << "sorted data: ";
    for(int i = 0; i < size; i++) {
        cout << data[i] << " "; 
    }

    cout << endl <<"===============================" << endl;
}

template <typename T>
void SortingSystem<T>::measureSortTime(void (SortingSystem::*sortFunc)())
{
    auto startTime = high_resolution_clock::now(); 
    (this->*sortFunc)(); 
    auto endTime = high_resolution_clock::now(); 
    duration<double> duration = endTime - startTime; 
    cout << "The sorting time was : " << duration.count() << " Seconds." << endl; 
}

template <typename T>
void SortingSystem<T>::showMenu() {
    cout << "now please enter tha data that you want to sort : ";
    for(int i = 0; i < size; i++) {
        cin >> data[i];
    }
    cout << "please enter the number of the sorting algorithm you want to use" << endl;
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
    cout << "please enter your choice : "; 
    cin >> choice;
    while (choice < 1 || choice > 9) {
        cout << "please enter a valid choice" << endl;
        cin >> choice;
    }
    switch (choice) {
        case 1: measureSortTime(&SortingSystem::insertionSort); break;
        case 2: measureSortTime(&SortingSystem::selectionSort); break;
        case 3: measureSortTime(&SortingSystem::bubbleSort); break;
        case 4: measureSortTime(&SortingSystem::shellSort); break;
        case 5: measureSortTime(&SortingSystem::mergeSortWrapper); break;
        case 6: measureSortTime(&SortingSystem::quickSortWrapper); break;
        case 7: measureSortTime(&SortingSystem::countSort); break;
        case 8: measureSortTime(&SortingSystem::radixSort); break;
        case 9: measureSortTime(&SortingSystem::bucketSort); break;
    }
    displayData(); 
}

template <typename T>
void SortingSystem<T>::insertionSort() {
    T temp; 
    int i, j;
    for(i = 1; i < size; i++) 
    {
        temp = data[i]; 
        for(j = i; j > 0 && data[j-1] > temp; j--) //data[j-1]*
        {
            data[j] = data[j-1]; 
        }
        data[j] = temp;
    }
}

template <typename T>
void SortingSystem<T>::selectionSort() {
    T minValue; 
    int i, j, minIndex; 
    for(i = 0; i < size-1; i++)
    {
        minValue = data[i]; 
        minIndex = i; 
        for(j = i+1; j < size; j++)
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
    for(int i = size-1; i >= 0; i--)
    {
        for(int j = 0; j < i; j++)
        {
            if(data[j] > data[j+1])
                swap(data[j],data[j+1]); 
        }
    }
}

template <typename T>
void SortingSystem<T>::shellSort() {
    int i, j, gab; 
    T temp; 
    for(gab = size / 2; gab >= 1; gab /= 2)
    {
        for(i = gab; i < size; i++)
        {
            temp = data[i]; 
            for(j = i; j >= gab && data[j-gab] > temp; j -= gab)
            {
                data[j] = data[j-gab]; 
            }
            data[j] = temp; 
        }
    }
}

template <typename T>
void SortingSystem<T>::mergeSort(int left, int right) {
    if(left >= right)
        return; 
    int middle = (left + right) / 2; 
    mergeSort(left, middle); 
    mergeSort(middle+1, right); 
    merge(left, middle, right); 
}

template <typename T>
void SortingSystem<T>::mergeSortWrapper() {
    mergeSort(0, size - 1);
}

template <typename T>
void SortingSystem<T>::merge(int left, int middle, int right) {
    T* sorted = new T[right-left+1]; 
    int index = 0; 
    int i = left, j = middle+1; 
    while(i <= middle && j <= right)
    {
        if(data[i] > data[j])
        {
            sorted[index] = data[j]; 
            j++; 
        }
        else 
        {
            sorted[index] = data[i]; 
            i++; 
        }
        index++; 
    }
    if(i <= middle)
    {
        for(;i <= middle; i++, index++)
            sorted[index] = data[i]; 
    }
    if(j <= right)
    {
        for(;j <= right; j++, index++)
            sorted[index] = data[j]; 
    }
    index = left; 
    for(int k = 0; k < right-left+1; k++, index++)
        data[index] = sorted[k]; 

    delete[] sorted; 
}

template <typename T>
void SortingSystem<T>::quickSort(int left, int right) {
    if(left >= right)
        return; 
    int middle = partition(left, right); 
    quickSort(left, middle-1); 
    quickSort(middle+1, right); 
}

template <typename T>
void SortingSystem<T>::quickSortWrapper() {
    quickSort(0, size - 1);
}

template <typename T>
int SortingSystem<T>::partition(int low, int high) {
    // generating a random pivot as a best practice 
    random_device rd;  
    mt19937 gen(rd()); 
    uniform_int_distribution<int> dist(low, high); 
    int pivotIndex = dist(gen);
    swap(data[low], data[pivotIndex]); 
    //main code 
    int i = low, j; 
    T pivot = data[low];
    for(j = i+1; j <= high; j++)
    {
        if(data[j] < pivot)
        {
            i++; 
            swap(data[i],data[j]); 
        }
    } 
    swap(data[i], data[low]); 
    return i; 
}

template <typename T>
void SortingSystem<T>::countSort() {
    
}

template <typename T>
void SortingSystem<T>::radixSort() {

}

template <typename T>
void SortingSystem<T>::bucketSort() {
    if (this->size <= 0) return;

    T** buckets = new T*[10];
    for (int i = 0; i < 10; i++) {
        buckets[i] = new T[this->size];
    }

    int CountBucket[10] = {0};

    T maxValue = *max_element(data, data + this->size);

    for (int i = 0; i < this->size; i++) {
    int bucketIndex = 0;
        if constexpr (is_same<T, int>::value || is_same<T, float>::value || is_same<T, double>::value) {
            bucketIndex = static_cast<int>((data[i] * 10) / (maxValue + 1));
        } else if constexpr (is_same<T, char>::value) {
            bucketIndex = static_cast<int>(data[i]) % 10;
        } else if constexpr (is_same<T, string>::value) {
            bucketIndex = data[i].empty() ? 0 : (data[i][0] % 10);
        }
        buckets[bucketIndex][CountBucket[bucketIndex]++] = data[i];
    }

    delete[] this->data;

    int total_size = this->size;
    for (int i = 0; i < 10; i++) {
        if (CountBucket[i] > 0) {
            this->size = CountBucket[i];
            this->data = buckets[i];
            insertionSort();
        }
    }

    int index = 0;

    this->data = new T[total_size];
    this->size = total_size;

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < CountBucket[i]; j++) {
            data[index++] = buckets[i][j];
        }
    }

    for (int i = 0; i < 10; i++) {
        delete[] buckets[i];
    }

}




int main()
{
    cout << "welcome ya user, how are you doing ?" << endl;
    cout << "i hope you're doing well. at first, allow me to welcome you in this Sorting System" << endl; 
    while(true)
    {
        cout << "what do you want to do ?" << endl; 
        cout << "1-sort some elments" << endl; 
        cout << "2-Exit program" << endl; 
        cout << "enter your choice : "; 
        int exitChoice; 
        cin >> exitChoice; 
        while(exitChoice < 1 || exitChoice > 2 || cin.fail())
        {
            cin.ignore(); 
            cout << "please Enter a Valid input!!!\n what's your choice ? :"; 
            cin >> exitChoice;
        }
        bool exit = (exitChoice == 2); 
        if(exit)
        {
            cout << "thx for using the program :)"; 
            break;
        }
        cout << "what is the type of the data you want to sort ?" << endl; 
        cout << "1-int" << endl; 
        cout << "2-float" << endl; 
        cout << "3-character" << endl; 
        cout << "4-string" << endl; 
        cout << "please enter you choice : "; 
        int dataType; 
        cin >> dataType; 
        while (!(dataType > 0 && dataType < 5) || cin.fail()) 
        {
            cin.ignore(); 
            cout << "Invalid input!!!" << endl; 
            cout << "please enter a valid number from the choices : "; 
            cin >> dataType; 
        } 

        cout << "now let me know, what is the size of the data you want to sort ? how many elemnts ? : "; 
        int dataSize; 
        cin >> dataSize; 
        while (dataSize <= 0 || cin.fail()) 
        {
            cin.ignore(); 
            cout << "Invalid input!!!" << endl; 
            cout << "please enter a valid postive size"; 
            cin >> dataSize; 
        } 
        if(dataType == 1)
        {
            SortingSystem<int> intSorting(dataSize); 
            intSorting.showMenu(); 
        }
        if(dataType == 2)
        {
            SortingSystem<float> floatSorting(dataSize); 
            floatSorting.showMenu(); 
        }
        if(dataType == 3)
        {
            SortingSystem<char> charSorting(dataSize); 
            charSorting.showMenu(); 
        }
        if(dataType == 4)
        {
            SortingSystem<string> stringSorting(dataSize); 
            stringSorting.showMenu(); 
        }
    }
    return 0; 
}