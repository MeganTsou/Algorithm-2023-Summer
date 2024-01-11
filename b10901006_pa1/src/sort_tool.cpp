// **************************************************************************
//  File       [sort_tool.cpp]
//  Author     [Yu-Hao Ho]
//  Synopsis   [The implementation of the SortTool Class]
//  Modify     [2020/9/15 Mu-Ting Wu]
//  Modify     [2023/9/12 Ming-Bang Fan]
// **************************************************************************

#include "sort_tool.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#define ll long long
// Constructor
SortTool::SortTool() {}

// Insertsion sort method
void SortTool::InsertionSort(vector<int> &data)
{
    // Function : Insertion sort
    // TODO : Please complete insertion sort code here
    int size = data.size();
    int key=0;
    int j=0;
    for (int i = 1; i < size; i++){
        key = data[i];
        j = i - 1;
        while (j >= 0 && data[j] > key){
            data[j + 1] = data[j];
            j--;
        }
        data[j + 1] = key;
    }
}

// Quick sort method
void SortTool::QuickSort(vector<int> &data, int f)
{
    QuickSortSubVector(data, 0, data.size() - 1, f);
}
// Sort subvector (Quick sort)
void SortTool::QuickSortSubVector(vector<int> &data, int low, int high, const int flag)
{
    // Function : Quick sort subvector
    // TODO : Please complete QuickSortSubVector code here
    // Hint : recursively call itself
    //        Partition function is needed
    // flag == 0 -> normal QS
    if ((low < high) && flag == 0){
        int q = Partition(data, low, high);
        QuickSortSubVector(data, low, q, 0);
        QuickSortSubVector(data, q + 1, high, 0);
    }
    // flag == 1 -> randomized QS
    else if ((low < high) && flag == 1){
        int q = RandomizedPartition(data, low, high);
        QuickSortSubVector(data, low, q, 1);
        QuickSortSubVector(data, q + 1, high, 1);
    }
}
int SortTool::RandomizedPartition(vector<int> &data, int low, int high)
{
    // Function : RQS's Partition the vector
    // TODO : Please complete the function
    srand(time(NULL));
    int p = (rand() % (high-low + 1)) + low;
    int key = data[p];
    data[p] = data[low];
    data[low] = key;
    return Partition(data, low, high);

}

int SortTool::Partition(vector<int> &data, int low, int high)
{
    // Function : Partition the vector
    // TODO : Please complete the function
    int key = data[low];
    int i = low-1;
    int j = high+1;
    while (true){
        do{
            j = j - 1;
        }
        while (data[j] > key);
        do{
            i = i + 1;
        }
        while(data[i] < key);

        if (i<j){
            int temp = data[i];
            data[i] = data[j];
            data[j] = temp;
        }
        else {
            return j;
        }
    }
    return 0;

}

// Merge sort method
void SortTool::MergeSort(vector<int> &data)
{
    MergeSortSubVector(data, 0, data.size() - 1);
}

// Sort subvector (Merge sort)
void SortTool::MergeSortSubVector(vector<int> &data, int low, int high)
{
    // Function : Merge sort subvector
    // TODO : Please complete MergeSortSubVector code here
    // Hint : recursively call itself
    //        Merge function is needed
    if (low<high){
        int p = (low+high)/2;
        MergeSortSubVector(data, low, p);
        MergeSortSubVector(data, p+1, high);
        Merge(data, low, p, p+1, high);
    }
    
}

// Merge
void SortTool::Merge(vector<int> &data, int low, int middle1, int middle2, int high)
{
    // Function : Merge two sorted subvector
    // TODO : Please complete the function
    vector<int> sub1;
    vector<int> sub2;
    for (int i=low; i<=middle1; i++){
        sub1.push_back(data[i]);
    }
    for (int i=middle2; i<=high; i++){
        sub2.push_back(data[i]);
    }

    int a = 0;
    int b = 0;
    for (int i=low; i<=high; i++){
        if ( (a<sub1.size()) && (b<sub2.size()) && (sub1[a] <= sub2[b]) ){
            data[i] = sub1[a];
            a++;
        }
        else if ((a<sub1.size()) && (b<sub2.size()) && (sub1[a] > sub2[b])){
            data[i] = sub2[b];
            b++;
        }
        else if ( (a >= sub1.size()) && (b<sub2.size()) ){
                data[i] = sub2[b];
                b++;
            }
        else if ( (a<sub1.size()) && (b >= sub2.size()) ){
            data[i] = sub1[a];
            a++;
        }
    }
}

// Heap sort method
void SortTool::HeapSort(vector<int> &data)
{
    // Build Max-Heap
    BuildMaxHeap(data);
    // 1. Swap data[0] which is max value and data[i] so that the max value will be in correct location
    // 2. Do max-heapify for data[0]
    for (int i = data.size() - 1; i >= 1; i--)
    {
        swap(data[0], data[i]);
        heapSize--;
        MaxHeapify(data, 0);
    }
}

// Max heapify
void SortTool::MaxHeapify(vector<int> &data, int root)
{
    // Function : Make tree with given root be a max-heap if both right and left sub-tree are max-heap
    // TODO : Please complete max-heapify code here
    
    int left_child = 2*root+1;
    int right_child = 2*root+2;
    int largest = 0;
    if (left_child < heapSize && data[left_child] > data[root]) largest = left_child;
    else largest = root;
    if (right_child < heapSize && data[right_child] > data[largest]) largest = right_child;
    if (largest != root){
        int temp = data[root];
        data[root] = data[largest];
        data[largest] = temp;
        MaxHeapify(data, largest);
    }


}

// Build max heap
void SortTool::BuildMaxHeap(vector<int> &data)
{
    heapSize = data.size(); // initialize heap size
    // Function : Make input data become a max-heap
    // TODO : Please complete BuildMaxHeap code here
    for (int i=(heapSize/2)-1; i>=0; i--){
        MaxHeapify(data,i);
    }
}
