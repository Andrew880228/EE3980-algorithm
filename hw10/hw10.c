// EE3980 HW10 Coin Set Design, II
// 106061225, 楊宇羲
// 2021/5/17
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

int DP_Recursive(int n);                    // recursive
int DP_TopDown(int n);                      // top down
void DP_BottomUp(int n);                    // bottom up
void initialize(int n);                     // initialize CoinNum
double GetAvg(int n);                       // return average of Coins
double GetTime(void);                       // get local time

int NCoin;                                  // total value
int p[4] = {1, 5, 10, 50};                  // initialize Coin values
int *CoinNum;                               // store minimum coin number

int main(void)
{
    int i, j, k, C3, C4;                    // initialize
    double minCoin = 99.0, sum, t;
    
    NCoin = 99;
    CoinNum = (int *)malloc(NCoin * sizeof(int));    // open spaces
    
    // for original set
    printf("Original coin set:\n");
    t = GetTime();
    for (i = 0; i < NCoin; i++) CoinNum[i] = DP_Recursive(i + 1);
    printf("  DP recursive: {1, 5, 10, 50} average is %g, ", GetAvg(NCoin));
    printf("CPU time: %g sec\n", GetTime() - t);
    t = GetTime();
    for (i = 0; i < NCoin; i++) {
        initialize(NCoin);
        DP_TopDown(i);        // get coins for 1 ~ 99
    }
    printf("  DP top-down:  {1, 5, 10, 50} average is %g, ", GetAvg(NCoin));
    printf("CPU time: %g sec\n", GetTime() - t);
    t = GetTime();
    DP_BottomUp(NCoin);
    printf("  DP bottom-up: {1, 5, 10, 50} average is %g, ", GetAvg(NCoin));
    printf("CPU time: %g sec\n", GetTime() - t);
    
    // changing $50
    printf("Replacing $50:\n");
    t = GetTime();
    for(i = p[2] + 1; i < 99; i++) {                    // test from 1 ~ 100
        p[3] = i;                            // give value to 3rd coin
        for (j = 0; j < NCoin; j++) CoinNum[j] = DP_Recursive(j + 1);                            // get all coin
        sum = GetAvg(NCoin);
        if (sum < minCoin) {                // get the minimum average
            minCoin = sum;
            C3 = i;
        }
    }
    p[3] = C3;
    printf("  DP recursive: {1, 5, 10, %d} average is %g, ", C3, minCoin);
    printf("CPU time: %g sec\n", GetTime() - t);
    t = GetTime();
    for(i = p[2] + 1; i < 99; i++) {        // test from 1 ~ 100
        p[3] = i;                           // give value to 3rd coin
        for (j = 0; j < NCoin; j++) {
            initialize(NCoin);
            DP_TopDown(j);                  // get all coin
        }
        sum = GetAvg(NCoin);
        if (sum < minCoin) {                // get the minimum average
            minCoin = sum;
            C3 = i;
        }
    }
    p[3] = C3;
    printf("  DP top-down:  {1, 5, 10, %d} average is %g, ", C3, minCoin);
    printf("CPU time: %g sec\n", GetTime() - t);
    t = GetTime();
    for(i = p[2] + 1; i < 99; i++) {        // test from 1 ~ 100
        p[3] = i;                           // give value to 3rd coin
        DP_BottomUp(NCoin);                 // get all coin
        sum = GetAvg(NCoin);
        if (sum < minCoin) {                // get the minimum average
            minCoin = sum;
            C3 = i;
        }
    }
    p[3] = C3;
    printf("  DP bottom-up: {1, 5, 10, %d} average is %g, ", C3, minCoin);
    printf("CPU time: %g sec\n", GetTime() - t);
    
    // changing $10
    printf("Replacing $10:\n");
    minCoin = 99;
    p[3] = 50;
    t = GetTime();
    initialize(NCoin);
    for(i = p[1] + 1; i < p[3]; i++) {      // test from 1 ~ 100
        p[2] = i;                           // give value to 3rd coin
        for (j = 0; j < NCoin; j++) CoinNum[j] = DP_Recursive(j + 1);
        sum = GetAvg(NCoin);
        if (sum < minCoin) {                // get the minimum average
            minCoin = sum;
            C3 = i;
        }
    }
    printf("  DP recursive: {1, 5, %d, 50} average is %g, ", C3, minCoin);
    printf("CPU time: %g sec\n", GetTime() - t);
    t = GetTime();
    for(i = p[1] + 1; i < p[3]; i++) {      // test from 1 ~ 100
        p[2] = i;                           // give value to 3rd coin
        for (j = 0; j < NCoin; j++) {
            initialize(NCoin);
            DP_TopDown(j);                  // get all coin
        }
        sum = GetAvg(NCoin);
        if (sum < minCoin) {                // get the minimum average
            minCoin = sum;
            C3 = i;
        }
    }
    printf("  DP top-down:  {1, 5, %d, 50} average is %g, ", C3, minCoin);
    printf("CPU time: %g sec\n", GetTime() - t);
    t = GetTime();
    for(i = p[1] + 1; i < p[3]; i++) {      // test from 1 ~ 100
        p[2] = i;                           // give value to 3rd coin
        DP_BottomUp(NCoin);                 // get all coin
        sum = GetAvg(NCoin);
        if (sum < minCoin) {                // get the minimum average
            minCoin = sum;
            C3 = i;
        }
    }
    printf("  DP bottom-up: {1, 5, %d, 50} average is %g, ", C3, minCoin);
    printf("CPU time: %g sec\n", GetTime() - t);
    
    // changing $10 and $50
    printf("Replacing $10 and $50:\n");
    C4 = 99;
    minCoin = 99;
    t = GetTime();
    initialize(NCoin);
    for(i = p[1] + 1; i < 99; i++) {        // test from 1 ~ 100
        p[2] = i;                           // give value to 2nd coin
        for(j = i + 1; j <= 99; j++) {      // test from 1 ~ 100
            p[3] = j;                       // give value to 3rd coin
            for (k = 0; k < NCoin; k++) {
                CoinNum[k] = DP_Recursive(k + 1);               // get all coins
            }
            sum = GetAvg(NCoin);
            if (sum < minCoin) {            // get the minimum average
                minCoin = sum;
                C3 = i;
                C4 = j;
            }
        }
    }
    p[2] = C3;
    p[3] = C4;
    printf("  DP recursive: {1, 5, %d, %d} average is %g, ", C3, C4, minCoin);
    printf("CPU time: %g sec\n", GetTime() - t);
    t = GetTime();
    for(i = p[1] + 1; i < 99; i++) {         // test from 1 ~ 100
        p[2] = i;                            // give value to 2nd coin
        for(j = i + 1; j <= 99; j++) {       // test from 1 ~ 100
            p[3] = j;                        // give value to 3rd coin
            for (k = 0; k < NCoin; k++) {
                initialize(NCoin);
                DP_TopDown(k);
            }                          // get all coins
            sum = GetAvg(NCoin);
            if (sum < minCoin) {           // get the minimum average
                minCoin = sum;
                C3 = i;
                C4 = j;
            }
        }
    }
    p[2] = C3;                            // print result
    p[3] = C4;
    printf("  DP top-down:  {1, 5, %d, %d} average is %g, ", C3, C4, minCoin);
    printf("CPU time: %g sec\n", GetTime() - t);
    t = GetTime();
    for(i = p[1] + 1; i < 99; i++) {                // test from 1 ~ 100
        p[2] = i;                            // give value to 2nd coin
        for(j = i + 1; j <= 99; j++) {            // test from 1 ~ 100
            p[3] = j;                        // give value to 3rd coin
            DP_BottomUp(NCoin);                  // get all coins
            sum = GetAvg(NCoin);
            if (sum < minCoin) {            // get the minimum average
                minCoin = sum;
                C3 = i;
                C4 = j;
            }
        }
    }
    p[2] = C3;                            // print result
    p[3] = C4;
    printf("  DP bottom-up: {1, 5, %d, %d} average is %g, ", C3, C4, minCoin);
    printf("CPU time: %g sec\n", GetTime() - t);

    return 0;
}

int DP_Recursive(int n)                     // recursive method
{
    int j, min, check;                      // initialize
    
    if (n == 1) return 1;                   // terminal condition
    else {
        min = n;
        for (j = 3; j >= 1; j--) {          // test through coin value 1 ~ 4
            if ((n - p[j]) >= 0) {          // if can use
                check = DP_Recursive(n - p[j]);
                if ((1 + check) < min) {
                    min = 1 + check;        // store result
                }
            }
        }
    }
    
    return min;
}

void DP_BottomUp(int n)                // bottom up method
{
    int i, j, min;                           // initialize
    CoinNum[0] = 1;                          // one coin for 1 dollar
    for (i = 1; i < n; i++) {                // 1 ~ n coin combinations
        min = n;
        for (j = 3; j >= 0; j--) {            // test through coin value 1 ~ 4
            if ((i + 1 - p[j]) >= 0) {                // if can use
                if ((1 + CoinNum[i - p[j]]) < min) {    // if lesser coin #
                    min = 1 + CoinNum[i - p[j]];        // store result
                }
            }
        }
        CoinNum[i] = min;                    // store result
    }
}

int DP_TopDown(int n)                // top-down
{
    
    int j, min;                            // initialize
    if (CoinNum[n] != NCoin) return CoinNum[n];
    CoinNum[0] = 1;                            // one coin for 1 dollar
    if (n >= 1) {
        min = NCoin;
        for (j = 3; j >= 0; j--) {            // test through coin value 1 ~ 4
            if ((n + 1 - p[j]) >= 0) {                // if can use
                if (( 1 + DP_TopDown(n - p[j])) < min) {    // if lesser coin #
                    min =  1 + DP_TopDown(n - p[j]);        // store result
                }
            }
        }
        CoinNum[n] = min;                    // store result
    }
    return CoinNum[n];
}

double GetAvg(int n) {                // count average
    int i;
    double sum = 0.0;
    for (i = 0; i < n; i++) {
        sum = sum + (double)CoinNum[i];
    }
    sum = sum / n;
    return sum;
}

void initialize (int n)                 // initialize array
{
    int i;
    
    for (i = 0; i < n; i++) {
        if (i == 0) CoinNum[i] = 1;
        else CoinNum[i] = NCoin;
    }
}

double GetTime(void)                    // get local time
{
    struct timeval tv;

    gettimeofday(&tv, NULL);
    return tv.tv_sec + 1e-6 * tv.tv_usec;       // sec + micro sec
}
