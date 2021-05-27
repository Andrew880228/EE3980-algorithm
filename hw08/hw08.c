// EE3980 HW08 Grouping Friends
// 106061225, 楊宇羲
// 2021/5/3

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

typedef struct node {
    int index;
    double weight;
    struct node *next;
} node;

typedef struct RSLT {
    int i1;
    int i2;
    double weight;
} RSLT;

int V;                                          // number of vertex
int E;                                          // number of edge
double mincost;
RSLT *T;
node **adlist;

double GetTime(void);                           // get local time in seconds
void prim(void);
void ReadData(void);                            // store data
void PrintData(double t);

int main(void)
{
    double t;
    
    ReadData();
    t = GetTime();                            // Get CPU time
    prim();
    t = GetTime() - t;                        // Calculate CPU runtime
    PrintData(t);
     
    return 0;
}

void prim(void)
{
    int i, j, lminp = V;
    int i1, i2;
    double lmin;
    node near[V];
    node *curr;
    
    for (i = 0; i < V; i++) {
        near[i].index = -1;
        near[i].weight = 0.0;
        near[i].next = NULL;
    }
    
    for (curr = adlist[T[0].i1]->next; curr != NULL; curr = curr->next) {
        near[curr->index].index = T[0].i1;
        near[curr->index].weight = curr->weight;
    }
    for (curr = adlist[T[0].i2]->next; curr != NULL; curr = curr->next) {
        if (near[curr->index].weight != 0.0 && curr->weight < near[curr->index].weight) {
            near[curr->index].index = T[0].i2;
            near[curr->index].weight = curr->weight;
        }
        else if (near[curr->index].weight == 0) {
            near[curr->index].index = T[0].i2;
            near[curr->index].weight = curr->weight;
        }
    }
  
    near[T[0].i1].index = -2;
    near[T[0].i2].index = -2;
    
    for (i = 1; i < V - 1; i++) {
        lmin = 0.0;
        for (j = 0; j < V; j++) {
            if (near[j].index >= 0) {
                if (near[j].weight < lmin || lmin == 0) {
                    lminp = j;
                    lmin = near[j].weight;
                }
            }
        }
        if (lminp > near[lminp].index) {
            i1 = near[lminp].index;
            i2 = lminp;
        } else {
            i1 = lminp;
            i2 = near[lminp].index;
        }
        
        T[i].i1 = i1;
        T[i].i2 = i2;
        T[i].weight = lmin;
        mincost = mincost + lmin;
        int f, s;
        if (lminp > near[lminp].index) {
            f = near[lminp].index;
            s = lminp;
        } else {
            f = lminp;
            s = near[lminp].index;
        }
        
        near[lminp].index = -2;
        
        for (curr = adlist[lminp]; curr != NULL; curr = curr->next) {
            if (near[curr->index].index != -2) {
                if (near[curr->index].weight != 0.0 && curr->weight < near[curr->index].weight) {
                    near[curr->index].index = lminp;
                    near[curr->index].weight = curr->weight;
                }
                else if (near[curr->index].weight == 0) {
                    near[curr->index].index = lminp;
                    near[curr->index].weight = curr->weight;
                }
            }
        }
    }
}

void ReadData(void)
{
    int i, v1, v2;
    double weight;
    
    scanf("%d %d", &V, &E);
    
    adlist = (node**)malloc(V * sizeof(node*));
    T = (RSLT*)malloc((V - 1) * sizeof(RSLT));
    mincost = 0.0;
    
    for (i = 0; i < V; i++) {
        adlist[i] = (node*)malloc(sizeof(node));
        adlist[i]->index = i;
        adlist[i]->weight = 0.0;
        adlist[i]->next = NULL;
    }
    
    for (i = 0; i < E; i++) {
        
        node *build1;
        node *build2;
        node *curr;
        
        scanf("%d %d %lf",&v1, &v2, &weight);
        
        if (mincost == 0 || mincost > weight) {
            mincost = weight;
            T[0].i1 = v1 - 1;
            T[0].i2 = v2 - 1;
            T[0].weight = weight;
        } 

        build1 = (node*)malloc(sizeof(node));
        build1->index = v2 - 1;
        build1->weight = weight;
        build1->next = NULL;
        
        curr = adlist[v1 - 1];
        build1->next = curr->next;
        curr->next = build1;
        
        build2 = (node*)malloc(sizeof(node));
        build2->index = v1 - 1;
        build2->weight = weight;
        build2->next = NULL;
        
        curr = adlist[v2 - 1];
        build2->next = curr->next;
        curr->next = build2;
        
    }
}

void PrintData(double t)
{
    int i;
    
    printf("Minimum-cost spanning tree:\n");
    for (i = 0; i < V - 1; i++) {
        printf("  %d: <%d %d> %g\n", i + 1, T[i].i1 + 1, T[i].i2 + 1, T[i].weight);
    }
    printf("|V| = %d |E| = %d\n", V, E);
    printf("Minimum cost: %g\n", mincost);
    printf("CPU time: %g seconds\n", t);
}

double GetTime(void)
{
    struct timeval tv;

    gettimeofday(&tv, NULL);
    return tv.tv_sec + 1e-6 * tv.tv_usec;       // sec + micro sec
}

