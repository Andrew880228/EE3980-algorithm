// EE3980 HW11 0/1 Knapsack Problem
// 106061225, 楊宇羲
// 2021/6/2

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

typedef struct DATA {                           // store name, weight, profit and p/w
    char name[2];
    int weight;
    int profit;
    double value;
}DATA;

int N, M;                                       // N for total items, M for limit weight
int fp, fw;                                     // final profit, final weight
int *cx;                                        // current solution
int *x;                                         // final solution
DATA *data;                                     // store data

double GetTime(void);                           // get local time in seconds
double Bound(int k, int cp, int cw);            // avoid unnecessary traversal
void ReadData(void);                            // store data
void SortData(void);                            // sort data
void PrintResult(double t);                     // print outcome
void BKnap(int k, int cp, int cw);              // execute 0/1 kanpsack

int main(void)
{
    double t;
    
    ReadData();                                 // read data
    SortData();                                 // sort data
    
    t = GetTime();                              // start count time
    BKnap(0, 0, 0);                             // execute knapsack function
    t = GetTime() - t;                          // stop count time
    
    PrintResult(t);                             // print result
    
    return 0;
}

void ReadData(void)                             // read data
{
    int i;                                      // for loop
    
    fp = 0;                                     // initialization
    fw = 0;
    
    scanf("%d %d", &N, &M);
    data = (DATA*)malloc(N * sizeof(DATA));     // dynamic allocation
    cx = (int*)malloc(N * sizeof(int));
    x = (int*)malloc(N * sizeof(int));
    
    for (i = 0; i < N; i++) {                   // store data
        scanf("%s %d %d", data[i].name, &data[i].weight, &data[i].profit);
        data[i].value = (double)data[i].profit / (double)data[i].weight;
        cx[i] = 0;
        x[i] = 0;
    }
}

void SortData(void)                             // sort data in order of p/w
{
    int i, j;                                   // for loop
    DATA key;                                   // store key item
    
    for (i = 1; i < N; i++) {                   // perform insertion sort
        key = data[i];
        j = i - 1;
        while (key.value > data[j].value && j >= 0) {
            data[j + 1] = data[j];
            j--;
        }
        data[j + 1] = key;
    }
}

void BKnap(int k, int cp, int cw)               // execute 0/1 knapsack
{
    int i;                                      // for loop
    
    if (cw + data[k].weight < M) {              // not exceeding limit weight
        cx[k] = 1;                              // put kth item in
        /* move on next item */
        if (k < N - 1) BKnap(k + 1, cp + data[k].profit, cw + data[k].weight);
        /* the last item, check result */
        else if ((k == N - 1) && (cp + data[k].profit > fp)) {
            fp = cp + data[k].profit;           // store final profit & weight
            fw = cw + data[k].weight;
            for (i = 0; i < N; i++) x[i] = cx[i];   // update store solution
        }
    }

    if (Bound(k, cp, cw) >= (double)fp) {       // if there are still space
        cx[k] = 0;                              // take out kth item
        if (k < N - 1) BKnap(k + 1, cp, cw);    // move on next item
        else if ((cp > fp) && (k == N - 1)) {   // last item, check result
            fp = cp;                            // store final profit & weight
            fw = cw;
            for (i = 0; i < N; i++) x[i] = cx[i];   // update solution
        }
    }
}

double Bound(int k, int cp, int cw)             // estimate remaining items' profit
{
    int i;                                      // for loop
    int mp;                                     // max profit
    int mw;                                     // max weight
    
    mp = cp;                                    // initializations
    mw = cw;
    
    for (i = k + 1; i < N; i++) {               // start estimating
        mw = mw + data[i].weight;               // update weight
        if (mw < M) mp = mp + data[i].profit;   // check if exceeds max weight
        else return (double)(mp + (1 - ((mw - M) / data[i].weight)) * data[i].profit);
    }
    
    return (double) mp;
}

void PrintResult(double t)                      // print result
{
    int i;
    
    printf("Pick items:\n");
    for (i = 0; i < N; i++) {                   // x[i] = 1 means item is picked
        if (x[i] == 1) printf("  %s %d %d\n", data[i].name, data[i].weight, data[i].profit);
    }
    printf("N = %d, M = %d\n", N, M);
    printf("Weight = %d, Profits = %d\n", fw, fp);
    printf("CPU time: %f sec\n", t);            // CPU time
}

double GetTime()                                // get local time
{
    struct timeval tv;

    gettimeofday(&tv, NULL);
    return tv.tv_sec + 1e-6 * tv.tv_usec;       // sec + micro sec
}
