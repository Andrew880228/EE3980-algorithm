// EE3980 HW02 Random Data Searches
// 106061225, 楊宇羲
// 2021/3/15

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>

double GetTime(void);                           // get local time
int Search(char *word, char **list,int n);      // Linear Search
int Search2(char *word, char **list,int n);     // Search 2 Algorithm
int OEsearch(char *word, char **list,int n);    // Odd-even search
int ROEsearch(char *word, char **list,int n);   // Randomized odd-even search

int ran=0;

int main(void)
{

    int R = 500;                                // time of repetitions
    int n;                                      // size of the array
    int i, j;                                   // for loop counting
    int result;                                 // check search result
    double t, t0, t1;                           // for CPU time counting
    
    scanf("%d", &n);                            // size of array
    
    char **a = (char**)malloc(n * sizeof(char*));   // the original array
    char buffer[100];                               // buffer for storing
    
    for (i = 0; i < n; i++)
    {                                           // storing array to **a
        scanf("%s", buffer);
        a[i] = malloc(strlen(buffer));
        strcpy(a[i], buffer);
    }
    
    // linear search
    
    t0 = GetTime();                             // start counting time
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < R; j++)
        {
            result = Search(a[i], a, n);
        }
    }
    t1 = GetTime();                             // stop counting time
    t = (t1 - t0) / n / R;                      // calculate CPU time
    printf("Linear search average CPU time: %g\n", t);

    // search 2

    t0 = GetTime();                             // start counting time
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < R; j++)
        {
            result = Search2(a[i], a, n);
        }
    }
    t1 = GetTime();                             // stop counting time
    t = (t1 - t0) / n / R;                      // calculate CPU time
    printf("Search 2 algorithm average CPU time: %g\n", t);
    
    // odd even search

    t0 = GetTime();                             // start counting time
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < R; j++)
        {
            result = OEsearch(a[i], a, n);
        }
    }
    t1 = GetTime();                             // stop counting time
    t = (t1 - t0) / n / R;                      // calculate CPU time
    printf("Odd-even search average CPU time: %g\n", t);

    // odd even sort
    
    t0 = GetTime();                             // start counting time
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < R; j++)
        {
            result = ROEsearch(a[i], a, n);
        }
    }
    t1 = GetTime();                             // stop counting time
    t = (t1 - t0) / n / R;                      // calculate CPU time
    printf("Random odd-even search average CPU time: %g\n", t);
    
    t0 = GetTime();                             // start counting time
    for (j = 0; j < 10 * R; j++)
    {
        result = Search(a[n - 1], a, n);
    }
    t1 = GetTime();                             // stop counting time
    t = (t1 - t0) / 10 / R;                     // calculate CPU time
    printf("Linear search worst-case CPU time: %g\n", t);
    
    t0 = GetTime();                             // start counting time
    for (j = 0; j < 10 * R; j++)
    {
        result = Search2(a[n - 1], a, n);
    }
    
    t1 = GetTime();                             // stop counting time
    t = (t1 - t0) / 10 / R;                     // calculate CPU time
    printf("Search 2 algorithm worst-case CPU time: %g\n", t);
    
    t0 = GetTime();                             // start counting time
    for (j = 0; j < 10 * R; j++)
    {
        if (n%2==0) result = OEsearch(a[n - 1], a, n);
        else result = OEsearch(a[n - 2], a, n);
    }
    t1 = GetTime();                             // stop counting time
    t = (t1 - t0) / 10 / R;                     // calculate CPU time
    printf("Odd-even search worst-case CPU time: %g\n", t);
    
    t0 = GetTime();                             // start counting time
    for (j = 0; j < 10 * R; j++)
    {
        if (ran==0) result = OEsearch(a[n - 1], a, n);
        else result = OEsearch(a[n - 2], a, n);
    }
    
    t1 = GetTime();                            // stop counting time
    t = (t1 - t0) / 10 / R;                    // calculate CPU time
    printf("Random odd-even search worst-case CPU time: %g\n", t);
    return 0;
}

int Search(char *word, char **list,int n)
{
    
    int i;                                // for loop counting

    for (i = 0; i < n; i++)
    {
        if (strcmp(list[i], word) == 0) return i;
    }
    return -1;
}
 
int Search2(char *word, char **list,int n)
{
    
    int i;                                // for loop counting
    
    for (i = 0; i < n; i+=2)
    {
        if (strcmp(word, list[i]) == 0) return i;
        if (strcmp(word, list[i+1]) == 0) return i+1;
    }
    return -1;
}

int OEsearch(char* word, char **list,int n)
{
    
    int i;
    
    for (i = 0; i < n; i+=2)
    {
        if (strcmp(word, list[i]) == 0) return i;
    }
    for (i = 1; i < n; i+=2)
    {
        if (strcmp(word, list[i]) == 0) return i;
    }
    return -1;
}

int ROEsearch(char* word, char** list,int n)
{
    
    int i;
    int ran = rand() % 2;

    if (ran == 0)
    {
        for (i = 0; i < n; i+=2)
        {
            if (strcmp(word, list[i]) == 0) return i;
        }
        for (i = 1; i < n; i+=2)
        {
            if (strcmp(word, list[i]) == 0) return i;
        }
    }
    else
    {
        for (i = 1; i < n; i+=2)
        {
            if (strcmp(word, list[i]) == 0) return i;
        }
        for (i = 0; i < n; i+=2)
        {
            if (strcmp(word, list[i]) == 0) return i;
        }
    }
    return -1;
}

double GetTime(void)
{

    struct timeval tv;

    gettimeofday(&tv, NULL);
    return tv.tv_sec + 1e-6 * tv.tv_usec;    // sec + micro sec
}
