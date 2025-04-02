#include <iostream>
#include <chrono>
#include <random>
#include <algorithm>
#include <fstream>
using namespace std;
using namespace chrono;

int inputChoice;
int take_choice(int const higher_bound, int const lower_bound = 0) {
    int choice;
    bool valid_input = false;

    while (!valid_input) {
        cout << "Enter choice (" << lower_bound << "-" << higher_bound << "): ";
        if (cin >> choice) {
            if (choice >= lower_bound && choice <= higher_bound) {
                valid_input = true;
            } else {
                cout << "Invalid choice. Value out of range." << endl;
            }
        } else {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid choice. Please enter a number." << endl;
        }
    }

    return choice;
}

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
    cout.flush();
    cout << " [";
    cout << this->data[0] ;
    for(int i = 1; i < size; i++) {
        cout << ", " << this->data[i] ;
    }
    cout << "]" << endl;
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
    switch (inputChoice) {
        case 1:{
            cout << "now please enter tha data that you want to sort : ";
            for(int i = 0; i < size; i++) {
                cin >> data[i];
            }
        break;
        }
        case 2:{
            ifstream testcases("problem4_testcases.txt");
            if (!testcases) {
                cerr << "Error opening file!" << endl;
            }
            testcases.ignore(1000, '\n');
            int index = 0;
            while (testcases >> data[index] && index < size) {
                index++;
            }
            break;
        }
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
    int const choice = take_choice(9);
    cout << "main data is : ";
    displayData();
    try {
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
            default:
                throw invalid_argument("Invalid choice.");
        }
        displayData();
    } catch (exception &e) {
        cout << e.what() << endl;
    }
}

template <typename T>
void SortingSystem<T>::insertionSort() {
    T temp;
    int i, j;
    int count = 0; 
    for(i = 1; i < size; i++) 
    {
        bool hasChanged = false; 
        temp = data[i]; 
        for(j = i; j > 0 && data[j-1] > temp; j--) 
        {
            data[j] = data[j-1]; 
            hasChanged = true; 
        }
        data[j] = temp;
        if(hasChanged)
        {
            count++; 
            cout << "iteration " << count << ':'; 
            displayData(); 
        }
    }
}

template <typename T>
void SortingSystem<T>::selectionSort() {
    cout << "Sorting using selection Sort..." << endl; 
    T minValue; 
    int i, j, minIndex;
    int count = 0;  
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
        {
            swap(data[i],data[minIndex]);
            count++; 
            cout << "interation " << count << ": "; 
            displayData(); 
        }
    }
}

template <typename T>
void SortingSystem<T>::bubbleSort() {
    cout << "Sorting using bubble Sort..." << endl; 
    int count = 0; 
    for(int i = size-1; i >= 0; i--)
    {
        bool hasChanged = false; 
        for(int j = 0; j < i; j++)
        {
            if(data[j] > data[j+1])
            {
                swap(data[j],data[j+1]); 
                hasChanged = true; 
            }
        }
        if(hasChanged)
        {
            count++; 
            cout << "interation " << count << ": "; 
            displayData(); 
        }
    }
}

template <typename T>
void SortingSystem<T>::shellSort() {
    cout << "Sorting using shell Sort..." << endl; 
    int i, j, gab; 
    T temp; 
    int count = 0; 
    for(gab = size / 2; gab >= 1; gab /= 2)
    {
        cout << "gab = " << gab << endl; 
        for(i = gab; i < size; i++)
        {
            bool hasChanged = false; 
            temp = data[i]; 
            for(j = i; j >= gab && data[j-gab] > temp; j -= gab)
            {
                data[j] = data[j-gab];
                hasChanged = true;  
            }
            data[j] = temp; 
            if(hasChanged)
            {
                count++; 
                cout << "iteration " << count << ": "; 
                displayData(); 
            }
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
    cout << "Sorting using merge Sort..." << endl; 
    mergeSort(0, size - 1);
}

template <typename T>
void SortingSystem<T>::merge(int left, int middle, int right) {
    T* sorted = new T[right-left+1]; 
    int index = 0; 
    int i = left, j = middle+1; 
    static int count = 0; 
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
    count++; 
    cout << "iteration " << count << ": ";
    displayData(); 
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
    cout << "Sorting using quick Sort..." << endl; 
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
    cout << "the pivot is : " << data[i] << endl; 
    cout << "the data :"; 
    displayData(); 
    return i; 
}

template <typename T>
void SortingSystem<T>::countSort() {
    if constexpr (!is_same_v<T, int>) {
        throw invalid_argument("Count Sort is only applicable for integer data");
    }
    else {
        int biggest_element = this->data[0];
        for (int i = 1; i < this->size; i++) {
            if (this->data[i] > biggest_element) {
                biggest_element = this->data[i];
            }
        }

        int *count_array = new int[biggest_element + 1]();
        int *output_array = new int[this->size];

        for (int i = 0; i < this->size; i++) {
            ++count_array[this->data[i]];
        }
        
        cout << "count array : [";
        for (int i = 0; i <= biggest_element; i++) {
            cout << count_array[i];
            if (i < biggest_element) cout << ", ";
        }
        cout << "]" << endl;

        for (int i = 1; i <= biggest_element; i++) {
            count_array[i] += count_array[i - 1];
        }

        cout << "cumulative count array : [";
        for (int i = 0; i <= biggest_element; i++) {
            cout << count_array[i];
            if (i < biggest_element) cout << ", ";
        }
        cout << "]" << endl;

        for (int i = this->size - 1; i >= 0; --i) {
            const int pos = --count_array[this->data[i]];
            output_array[pos] = this->data[i];
        }

        delete[] count_array;
        delete[] this->data;
        this->data = output_array;
    }
}

template <typename T>
void SortingSystem<T>::radixSort(){
    if constexpr (!is_same_v<T, int>) {
        throw invalid_argument("Radix Sort is only applicable for integer data");
    }
    else {
    //get the largest num
    int maxNum = data[0];
    for (int i = 1; i < size; i++)
    {
        if (data[i] > maxNum)
            maxNum = data[i];
    }

    //We'll find the correct placement of every number in our data by continuously sorting them according to a some decimal place, we'll do this starting from the very first one (unit's), and do it up to the highest decimal place the maximum number has
    for (int exp = 1; maxNum / exp > 0; exp *= 10)
    {
        //count array: the array that should record the # of occurrences of each digit (that's an index in it) in a given decimal place (exp) and we'll use the counting sort
        int* countArray = new int[10];
        for(int i=0;i<10;i++)
        {
            countArray[i] = 0;
        }

        for (int i = 0; i < size; i++)
        {
            countArray[(data[i] / exp) % 10]++;
        }

        //We'll convert it to a "cumulative" count array that records the position of a number's first occurrence in the sorted digits array according to its current decimal place
        for (int i = 1; i < 10; i++)
        {
            countArray[i] += countArray[i - 1];
        }
        int* sortedArray = new int[size];
        //We'll sort the numbers in this sorted order in the sorted array according to the correct placement of their current decimal place
        for (int i = size - 1; i >= 0; i--)
        {
            sortedArray[countArray[(data[i] / exp) % 10] - 1] = data[i];
            countArray[(data[i] / exp) % 10]--;
        }

        for (int i = 0; i < size; i++)
        {
            data[i] = sortedArray[i];
        }
        delete [] countArray;
        delete [] sortedArray;
    }
    }
}
template <typename T>
void SortingSystem<T>::bucketSort() {
    if (this->size <= 0) return;

    T** buckets = new T*[10];
    for (int i = 0; i < 10; i++) {
        buckets[i] = new T[this->size];
    }

    int CountBucket[10] = {0};

    T maxValue = this->data[0];
        for (int i = 1; i < this->size; i++) {
            if (this->data[i] > maxValue) {
                maxValue = this->data[i];
            }
        }

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
            cout << "Bucket[" << i << "]: ";
            this->insertionSort();
            this->displayData();
            cout << endl;
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




int main(){
    cout << "==============================================" << endl;
    cout << "        Welcome to the Sorting System!      " << endl;
    cout << "==============================================" << endl << endl;
    cout << "This program allows you to sort data using various sorting algorithms." << endl;
    while(true){
        cout << "What do you want to do ?" << endl;
        cout << "1) Sort some elments" << endl;
        cout << "2) Exit program" << endl;
        int exitChoice = take_choice(2, 1);
        if(exitChoice == 2){
            cout << "thx for using the program :)";
            break;
        }

        cout << "do you want to input the data or use the testcases file that already exists ? \n"; 
    cout << "1) Enter the data manually " << endl;
    cout << "2) Use the testcases file" << endl;
    inputChoice = take_choice(2, 1);
    ifstream testcases("problem4_testcases.txt");
    if (!testcases) {
        cerr << "Error opening file!" << endl;
    }


        cout << "Select the type of data you want to sort:" << endl;
        cout << "  1) Integer" << endl;
        cout << "  2) Float" << endl;
        cout << "  3) Char" << endl;
        cout << "  4) String" << endl << endl;
        cout << "Enter your choice: ";
        int dataType;
        if(inputChoice == 2)
        {
            streambuf* originalCinBuffer = cin.rdbuf(); // Save original buffer
            cin.rdbuf(testcases.rdbuf());
            cin >> dataType; 
            cout << dataType; 
            cin.rdbuf(originalCinBuffer); 
        }
        else 
        {
            dataType = take_choice(4);
        }
        cout << "\nSpecify the number of elements to sort: ";
        int dataSize;
        if(inputChoice == 2)
        {
            streambuf* originalCinBuffer = cin.rdbuf(); // Save original buffer
            cin.rdbuf(testcases.rdbuf());
            cin >> dataSize; 
            cout << dataSize << endl; 
            cin.rdbuf(originalCinBuffer); 
        }
        else 
        {
            dataSize = take_choice(999999999);
        }

        switch(dataType) {
            case 1: {
                SortingSystem<int> intSorting(dataSize);
                intSorting.showMenu();
                break;
                }
            case 2: {
                SortingSystem<float> floatSorting(dataSize);
                floatSorting.showMenu();
                break;
                }
            case 3: {
                SortingSystem<char> charSorting(dataSize);
                charSorting.showMenu();
                break;
                }
            case 4: {
                SortingSystem<string> stringSorting(dataSize);
                stringSorting.showMenu();
                break;
                }
            default:
                cout << "Invalid data type selected." << endl;
            }
        }
        return 0;
}
