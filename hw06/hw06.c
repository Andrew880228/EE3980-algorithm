// EE3980 HW06 Stock Short Selling Revisited
// 106061225, 楊宇羲
// 2021/4/13

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

typedef struct STKprice {               // Stock's price & date
    int year, month, day;
    double price, change;
}STKprice;

typedef struct RSLT {                   // Contains start, end date and maximum
    int sell, buy;
    double min;
}RSLT;

void ReadData(void);                    // read everyday's price
void PrintData(RSLT result);
double GetTime(void);                   // Get local time
RSLT MaxSubArrayBF(void);               // brute-force sub array solution
RSLT MaxSubArrayBFI(void);              // improved brute-force max sub array
RSLT MaxSubArray(int begin, int end);   // divide & conquer approach
RSLT MaxSubArrayXB(int begin, int mid, int end);    // cross boundary condition
RSLT MaxSubArrayDP(void);

STKprice *data;                         // array to store price
int N;                                  // size of array

int main(void)
{
    int i = 0;                          // for loop
    int R = 5000;                       // Repetition time
    double t;                           // time variable
    RSLT result;                        // contains start & end date and maximum
    
    ReadData();                         // read in data
    
    t = GetTime();                      // start counting CPU time
    result = MaxSubArrayBF();           // brute-force solution for 1 time
    t = GetTime() - t;                  // end count time
    printf("Brute-force approach: CPU time %g s\n", t); // print outcome
    PrintData(result);
    
    t = GetTime();                      // start counting CPU time
    result = MaxSubArrayBFI();          // improved brute-force solution
    t = GetTime() - t;                  // end count time
    printf("Improved Brute-force approach: CPU time %g s\n", t); // print
    PrintData(result);
    
    t = GetTime();                      // start counting time
    for(i = 0; i < R; i++) {            // repeat 5000 times
        result = MaxSubArray(0, N - 1); // divide and counquer approach
    }
    t = (GetTime() - t) / R;            // end counting time
    printf("Divide and Conquer: CPU time %g s\n", t);   // print outcome
    PrintData(result);
    
    t = GetTime();                      // start counting time
    for(i = 0; i < R; i++) {            // repeat 5000 times
        result = MaxSubArrayDP();       // dynamic programming approach
    }
    t = (GetTime() - t) / R;            // end counting time
    printf("Dynamic Programming: CPU time %g s\n", t);   // print outcome
    PrintData(result);
    return 0;
}
void ReadData(void)                     // read in data
{
    int i = 0;                          // for loop
    
    scanf("%d", &N);                    // read in size of array
    printf("N = %d\n", N);
    
    data = (STKprice*)malloc(N * sizeof(STKprice)); // dynamic array allocation
    
    for (i = 0; i < N; i++)             // scan in data
    {
        scanf("%d %d %d", &data[i].year, &data[i].month, &data[i].day);
        scanf("%lf", &data[i].price);
        
        // derive the change of today and yesterday except the first day
        if (i != 0) data[i].change = data[i].price - data[i - 1].price;
        else data[i].change = 0;
    }
}
void PrintData(RSLT result)                 // print outcome
{
    printf("  Sell: %d/%d/%d at %.4lf\n", data[result.sell - 1].year,
                                          data[result.sell - 1].month,
                                          data[result.sell - 1].day,
                                          data[result.sell - 1].price);
    printf("  Buy: %d/%d/%d at %.4lf\n", data[result.buy].year,
                                         data[result.buy].month,
                                         data[result.buy].day,
                                         data[result.buy].price);
    printf("  Earning: %.4lf per share.\n", -1 * result.min);
}
double GetTime(void)                        // get local time
{
    struct timeval tv;
    
    gettimeofday(&tv, NULL);
    return tv.tv_sec + 1e-6 * tv.tv_usec;   // sec + micro sec
}
RSLT MaxSubArrayBF(void)                    // brute-force solution
{
    int i, j, k;                            // for loops
    RSLT result;                            // for storing low, high, change
    result.min = 0.0;                       // initializations of result
    result.sell = 0;
    result.buy = N - 1;
    
    for (i = 0; i < N; i++) {               // determine start index
        for (j = i; j < N; j++) {           // determine end index
            double sum = 0;                 // start counting sum
            for (k = i; k <= j; k++) {      // from start to end
                sum += data[k].change;      // derive sum
            }
            if (sum < result.min) {
                result.min = sum;           // found max, update informations
                result.sell = i;
                result.buy = j;
            }
        }
    }
    return result;
}
RSLT MaxSubArrayBFI(void)                   // improved brute-force solution
{
    int i, j;                               // for loops
    RSLT result;                            // for storing low, high, change
    result.min = 0.0;                       // initializations of result
    result.sell = 0;
    result.buy = N - 1;
    
    for (i = 0; i < N; i++) {               // determine start index
        for (j = i; j < N; j++) {           // determine end index
            if (data[j].price - data[i].price < result.min) {   // find smaller
                result.min = data[j].price - data[i].price;
                result.sell = i + 1;        // store new sell date
                result.buy = j;             // store new buy date
            }
        }
    }
    
    return result;                          // return result
}
RSLT MaxSubArray(int begin, int end)        // divide and conquer approach
{
    RSLT result;                            // store information
    int mid;                                // initialization
    if (begin == end) {                     // terminal condition
        result.sell = begin;
        result.buy = end;
        result.min = 0;
        return result;
    }
    mid = (begin + end) / 2;                // determine middle index
    
    RSLT lsum = MaxSubArray(begin, mid);    // check left sum
    RSLT rsum = MaxSubArray(mid + 1, end);  // check right sum
    RSLT xsum = MaxSubArrayXB(begin, mid, end); // check cross boundary sum
    
    // comparisons of the above three sums
    if (lsum.min <= rsum.min && lsum.min <= xsum.min) {
        return lsum;                        // left sum is the smallest
    }
    else if (rsum.min <= lsum.min && rsum.min <= xsum.min) {
        return rsum;                        // right sum is the smallest
    }
    return xsum;                            // cross sum is the smallest
}
RSLT MaxSubArrayXB(int begin, int mid, int end) // cross boundary condition
{
    RSLT result;                            // store information
    int i;                                  // for loop
    double sum;                             // for checking sum
    double rsum;                            // right hand side's sum
    double lsum;                            // left hand side's sum
    result.sell = 0;                        // initialize sell's date
    result.buy = mid + 1;                   // initialize buy's date
    
    sum = 0.0;
    lsum = 0.0;
    for (i = mid; i > begin; i--) {
        sum += data[i].change;              // counting sum
        if (sum < lsum) {                   // determine left min
            lsum = sum;                     // update left sum
            result.sell = i;                // update sell's date
        }
    }
    
    sum = 0.0;
    rsum = 0.0;                      		// right hand side's sum
    for (i = mid + 1; i < end; i++)
    {
        sum += data[i].change;              // counting sum
        if (sum < rsum) {                   // determine right sum
            rsum = sum;                     // update right sum
            result.buy = i;                 // update buy date
        }
    }
    
    result.min = rsum + lsum;               // update total sum
    return result;
}
RSLT MaxSubArrayDP(void)                    // dynamic programming
{
    RSLT result;                            // initializations
    double localmin = 0.0;
    int i;                                  // for loop & buy date
    int sell;                               // for sell date

    sell = 1;                               // initial values
    result.sell = 1;
    result.buy = N - 1;
    result.min = 10000000;
    
    for (i = 0; i < N; i++) {
        /* find max(data[i], data[i] + local min) */
        if (data[i].change < localmin + data[i].change) {
            localmin = data[i].change;
            sell = i;                       // sell date recorded
        }else {
            localmin = data[i].change + localmin;
        }
        /* find max(local min, absolute min) */
        if (localmin < result.min) {
            result.min = localmin;          // minimum updated
            result.buy = i;                 // buy date updated
            result.sell = sell;             // sell date updated
        }
    }
    return  result;
}
