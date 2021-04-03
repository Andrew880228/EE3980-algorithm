// EE3980 HW03 Network Connectivity Problem
// 106061225, 楊宇羲
// 2021/3/22

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

double GetTime(void);
void ReadGraph(void);
void Connect1(void);
void Connect2(void);
void Connect3(void);
void SetUnion(int i, int j);
void WeightedUnion(int i, int j);
int SetFind(int i);
int CollapseFind(int i);

int **graph;
int *p;
int ns;
int v, e;

int main(void)
{
    
    int N = 100;
    int i;
    double  t0, t1, t2, t3, t;
    
    ReadGraph();
    
    t0 = GetTime();
    for (i = 0; i < N; i++)
    {
        Connect1();
    }
    t1 = GetTime();
    t = (t1 - t0) / N;
    printf("Connect1 CPU time: %g, Disjoint Sets: %d\n", t, ns);
    
    for (i = 0; i < N; i++)
    {
        Connect2();
    }
    t2 = GetTime();
    t = (t2 - t1) / N;
    printf("Connect2 CPU time: %g, Disjoint Sets: %d\n", t, ns);
    for (i = 0; i < N; i++)
    {
        Connect3();
    }
    t3 = GetTime();
    t = (t3 - t2) / N;
    printf("Connect3 CPU time: %g, Disjoint Sets: %d\n", t, ns);
    
    return 0;
}
void ReadGraph(void)
{
    int i;
    scanf("%d %d", &v, &e);
    printf("|V| = %d, |E| =  %d\n", v, e);
    
    graph = (int**) malloc(e * sizeof(int*));
    p = (int*) malloc((v + 1) * sizeof(int));
    
    for (i = 0; i < e; i++)
    {
        graph[i] = (int*) malloc(2 * sizeof(int));
        scanf("%d %d", &graph[i][0], &graph[i][1]);
    }
}
double GetTime(void)
{
    struct timeval tv;

    gettimeofday(&tv, NULL);
    return tv.tv_sec + 1e-6 * tv.tv_usec;    // sec + micro sec
}
void Connect1(void)
{
    int i;
    int r[v + 1];
    
    ns = v;
    
    for (i = 0; i <= v; i++) p[i] = -1;
    for (i = 0; i < e; i++)
    {
        int S0 = SetFind(graph[i][0]);
        int S1 = SetFind(graph[i][1]);
        if (S0 != S1)
        {
            ns--;
            SetUnion(S1, S0);
        }
    }
    for (i = 0; i <= v; i++) r[i] = SetFind(i);
}
void Connect2(void)
{
    int i;
    int r[v + 1];
    
    ns = v;
    for (i = 0; i <= v; i++) p[i] = -1;
    for (i = 0; i < e; i++)
    {
        int S0 = SetFind(graph[i][0]);
        int S1 = SetFind(graph[i][1]);
        if (S0 != S1)
        {
            ns--;
            WeightedUnion(S0, S1);
        }
    }
    for (i = 0; i <= v; i++) r[i] = SetFind(i);
}
void Connect3(void)
{
    int i;
    int r[v + 1];
    
    ns = v;
    
    for (i = 0; i <= v; i++) p[i] = -1;
    for (i = 0; i < e; i++)
    {
        int S0 = CollapseFind(graph[i][0]);
        int S1 = CollapseFind(graph[i][1]);
        if (S0 != S1)
        {
            ns--;
            WeightedUnion(S0, S1);
        }
    }
    for (i = 0; i <= v; i++) r[i] = SetFind(i);
}
int SetFind(int i)
{
    while (p[i] >= 0) i = p[i];
    
    return i;
}
int CollapseFind(int i)
{
    int r = i;
    int temp;
    while (p[r] > 0) r = p[r];
    while (i != r){
        temp = p[i];
        p[i] = r;
        i = temp;
    }
    return r;
}
void SetUnion(int i, int j)
{
    p[i] = j;
}
void WeightedUnion(int i, int j)
{
    int temp = p[i] + p[j];

    if (p[i] > p[j])
    {
        p[i] = j;
        p[j] = temp;
    }
    else
    {
        p[i] = temp;
        p[j] = i;
    }
}

