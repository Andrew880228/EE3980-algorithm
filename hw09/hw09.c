// EE3980 HW09 Coin Set Design
// 106061225, 楊宇羲
// 2021/5/10
#include <stdio.h>
#include <stdlib.h>

double NCoinGreedy(void);               // find each value's coin needed, return average

int NCoin;                              // range of possible value
int p[4] = {1, 5, 10, 50};              // initialize Coin values set

int main(void)
{
    int i, j, dd, dd2;                  // initialize variables
    double minAvg = 99.0, avg;          // find minimum average
    
    NCoin = 99;                         // value ranges from 1 to 99
    dd = NCoin;                         // change in coin set
    dd2 = NCoin;                        // change in coin set

    /* find minimum average of original coin set */
    printf("For coin set {1, 5, 10, 50} the average is %g\n", NCoinGreedy());

    for(p[3] = p[2] + 1; p[3] < NCoin; p[3]++) { // test from p[2] ~ 99
        avg = NCoinGreedy();            // get all coins
        if (avg < minAvg) {             // find the minimum average
            minAvg = avg;
            dd = p[3];
        }
    }

    /* find minimum average of changing p[3] */
    printf("Coin set {1, 5, 10, %d} has ", dd);
    printf("the minimum average of %g\n", minAvg);
    
    minAvg = 99.0;
    p[3] = 50;
    for(p[2] = p[1] + 1; p[2] < p[3]; p[2]++) {  // test from p[1] ~ p[3]
        avg = NCoinGreedy();            // get all coins
        if (avg < minAvg) {             // find the minimum average
            minAvg = avg;
            dd = p[2];
        }
    }

    /* find minimum average of changing p[2] */
    printf("Coin set {1, 5, %d, 50} has ", dd);
    printf("the minimum average of %g\n", minAvg);
    
    minAvg = 99.0;
    
    for(p[2] = p[1]; p[2] <= NCoin; p[2]++) {    // test from p[1] ~ 99
        for(p[3] = p[2] + 1; p[3] <= NCoin; p[3]++) {   // test from p[2] ~ 99
            avg = NCoinGreedy();        // get all coins
            if (avg < minAvg) {         // get the minimum average
                minAvg = avg;
                dd = p[2];
                dd2 = p[3];
            }
        }
    }

    /* find minimum average of changing p[2], p[3] */
    printf("Coin set {1, 5, %d, %d} has ", dd, dd2);
    printf("the minimum average of %g\n", minAvg);
  
    return 0;
}

double NCoinGreedy(void)                // get all Coin num and save solution
{
    int i, j, lmin, value;              // initialize variables
    double sum = 0.0;                   // calculate sum & average
    
    for (i = 0; i < NCoin; i++) {       // 1 ~ NCoin possible values
        lmin = i + 1;                   // if all consist of 1 dollar
        value = i + 1;                  // check if bigger than coin set value
        for (j = 3; j > 0; j--) {       // test all coin set values
            while (value >= p[j]) {     // if bigger than coin set value
                lmin = lmin - p[j] + 1; // update local min
                value = value - p[j];   // update virtual value
            }
        }
        sum = sum + (double)lmin; // calculate average
    }
    return sum / NCoin;                 // return average
}
