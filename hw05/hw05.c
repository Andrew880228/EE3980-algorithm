// EE3980 HW05 Better Sorts
// 106061225, 楊宇羲
// 2021/4/5

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>

char **list;                                    // target array to sort
char **temp;                                    // for heap sort to store temporarily
char **a;                                       // original array
int N;                                          // size of array
int R;                                          // repitition

double GetTime(void);                           // get local time in seconds
void ReadArray(void);                           // store data in array
void CopyArray(void);                           // copy array
void PrintArray(void);                          // display result
void HeapSort(char **list, int n);              // perform heap sort
void MergeSort(char **list, int low, int high); // perform merge sort
void QuickSort(char **list, int low, int high); // perform quick sort
void Heapify(int i, int n);                     // find max heap
void Merge(int low, int mid, int high);         // for merge sort
int Partition(int low, int high);               // swap value to appropriate position

int main(void)
{
    int i;                                      // for loop counting
    double t;                                   // for CPU time counting
    
    scanf("%d", &N);                            // size of array
    printf("N = %d\n", N);
    R = 500;                                    // repetition time

    ReadArray();
    
    // heap sort
    t = GetTime();                              // start counting time
    for (i = 0; i < R; i++) {                   // repeat R times
        CopyArray();                            // call copy function
        HeapSort(list, N);                      // start heap sort
    }
    t = (GetTime() - t) / R;                    // stop and calculate time
    printf("Heap Sort CPU time : %e s\n", t);
     
    // merge sort
    t = GetTime();                              // start counting time
    for (i = 0; i < R; i++) {                   // repeat R times
        CopyArray();                            // call copy function
        MergeSort(list, 0, N - 1);              // start merge sort
    }
    t = (GetTime() - t) / R;                    // stop and calculate time
    printf("Merge Sort CPU time: %e s\n", t);
    
    // quick sort
    t = GetTime();                              // start counting time
    for (i = 0; i < R; i++) {                   // repeat R times
        CopyArray();                            // call copy function
        QuickSort(list, 0, N - 1);              // start quick sort
    }
    t = (GetTime() - t) / R;                    // stop and calculate time
    printf("Quick Sort CPU time: %e s\n", t);
    
    PrintArray();                               // print array

    return 0;
}
void HeapSort(char **list, int n)               // heap sort
{
    int i;                                      // for loop counting
    char *temp;                                 // for swapping
    
    for (i = (n - 1) / 2; i >= 0; i--) {        // initialize whole array to max heap
        Heapify(i, n - 1);
    }
    for (i = n - 1; i >= 1; i--) {              // repeat n - 1 times
        temp = list[i];                         // swap list[i] with list[0]
        list[i] = list[0];
        list[0] = temp;
        Heapify(0, i - 1);                      // find the remaining max heap
    }
}
void Heapify(int i, int n)                      // find max heap
{
    int j;                                      // left child
    char *item;                                 // parent is target
    int done;                                   // check if it is done
    
    j = 2 * i + 1;                              // statements
    item = list[i];
    done = 0;
    
    while (j <= n && !done) {                   // stop when it is done
        if (j < n && strcmp(list[j], list[j + 1]) < 0) j++; // right child is bigger
        if (strcmp(item, list[j]) > 0) done = 1;            // in right position
        else {
            list[(j - 1) / 2] = list[j];        // let child become parent
            j = 2 * j + 1;
        }
    }
    list[(j - 1) / 2] = item;                   // store item to child's position
}
void MergeSort(char **list, int low, int high)  // merge sort
{
    int mid;
    if (low < high) {                           // terminal condition
        mid = (low + high) / 2;                 // determine mid index
        MergeSort(list, low, mid);              // left part
        MergeSort(list, mid + 1, high);         // right part
        Merge(low, mid, high);                  // perform merge
    }
}
void Merge(int low, int mid, int high)          // start merge o the right position
{
    int h;                                      // compare left half
    int i;                                      // storing temp array
    int j;                                      // compare right half
    int k;                                      // loop variable
    
    h = low;                                    // statements
    i = low;
    j = mid + 1;

    while (h <= mid && j <= high) {             // compare left & right then pick
        if (strcmp(list[h], list[j]) <= 0) {    // if left is smaller, pick left
            temp[i] = list[h];                  // store it to temp
            h++;                                // go to next one
        }else {                                 // otherwise, pick right
            temp[i] = list[j];                  // store it to temp
            j++;                                // go to next one
        }
        i++;                                    // store next temp
    }
    
    if (h > mid) {                              // if left side has done
        for (k = j; k <= high; k++) {           // store all the right side
            temp[i] = list[k];
            i++;
        }
    }else {                                     // if right side done first
        for (k = h; k <= mid; k++) {            // store all the left side
            temp[i] = list[k];
            i++;
        }
    }
    for (k = low; k <= high; k++) {             // update correct array to list
        list[k] = temp[k];
    }
}
void QuickSort(char**list, int low, int high)   // perform quick sort
{
    int mid;                                    // find mid index
    if (low < high) {                           // terminal condition
        mid = Partition(low, high + 1);         // determine mid
        QuickSort(list, low, mid - 1);          // do left part
        QuickSort(list, mid + 1, high);         // do right part
    }
}
int Partition(int low, int high)
{
    char *v;                                    // target
    char *temp;                                 // for swapping
    int i;                                      // left element
    int j;                                      // right element
    int flag;                                   // check initial condition
    
    v = list[low];                              // initial conditions
    i = low;
    j = high;
    flag = 0;
    
    while (i < j) {                             // terminal condition
        // find i such that list[i] >= v
        while (flag == 0 || (strcmp(list[i], v) < 0 && i < N)){
            i++;
            if (flag == 0) flag = 1;
        }
        flag = 0;
        // find j such that list[j] <= v
        while (flag == 0 || (strcmp(list[j], v) > 0 && j < N)){
            j--;
            if (flag == 0) flag = 1;
        }
        if (i < j) {                            // swap list[i] & list[j]
            temp = list[i];
            list[i] = list[j];
            list[j] = temp;
        }
    }
    list[low] = list[j];                        // swap list[low] & v
    list[j] = v;
    return j;                                   // return j's position
}
void ReadArray(void)                            // read in datas
{
    int i;                                              // for loop
    
    a = (char**)malloc((N + 1) * sizeof(char*));        // the original array
    list = (char**)malloc((N + 1) * sizeof(char*));     // the array being sorted
    temp = (char**)malloc((N + 1) * sizeof(char*));     // temporary array
        
    for (i = 0; i < N; i++) {
        a[i] = (char*)malloc(50 * sizeof(char));        // dynamic arrays
        list[i] = (char*)malloc(50 * sizeof(char));
        temp[i] = (char*)malloc(50 * sizeof(char));
        scanf("%s", a[i]);                              // store strings
    }
    a[N] = "zzzzzz";                                    // for quick sort
    list[N] = "zzzzzz";                                 // for quick sort
    temp[N] = "zzzzzz";                                 // for quick sort
}
void CopyArray(void)                            // copy data
{
    int i;                                      // loop counting
    for(i = 0; i < N; i++) {
        list[i] = a[i];                         //copy a to list every repetition
    }
}
void PrintArray(void)
{
    int i;                                      // loop counting
    for (i = 0; i < N; i++) {                   // Display sorted array
        printf("%d %s\n", i + 1, list[i]);
    }
}
double GetTime()
{
    struct timeval tv;

    gettimeofday(&tv, NULL);
    return tv.tv_sec + 1e-6 * tv.tv_usec;       // sec + micro sec
}
