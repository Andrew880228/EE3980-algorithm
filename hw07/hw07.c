// EE3980 HW07 Grouping Friends
// 106061225, 楊宇羲
// 2021/4/28

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

typedef struct CONN CONN;
struct CONN{
    int index;
    struct CONN *next;
};

char **name;                                    // list of people
int N;                                          // number of people
int M;                                          // number of connection
int SUBSUM;
int order;
int *s, *f, *visited;
CONN **adlist;
CONN **adlistT;
CONN *roots;

double GetTime(void);                           // get local time in seconds
void ReadData(void);                            // store data
void PrintData(void);
void SCC(void);
void DFS_Call(CONN **graph);
void top_sort(int i, CONN **graph);                // Depth First search

int main(void)
{
    CONN *curr;
    double t;
    int i, k, j;
    ReadData();
    t = GetTime();                            // Get CPU time
    SCC();                                    // find SCC groups
    t = GetTime() - t;                        // Calculate CPU runtime
    
    curr = roots;                                // Initialize
    i = 0;
    k = 1;
    printf("N = %d M = %d Subgroup = %d CPU time = %g\n", N, M, SUBSUM, t);    // print result
    printf("Number of subgroups: %d\n", SUBSUM);
    
    while(curr->next != NULL){                    // go through f[i] according to travel order
        printf("  Subgroup %d: ", k);        // each n is a subgroup
        for(j = 0; j < (curr->index - curr->next->index - 1); j++){
            printf("%s " , name[f[i]]);
            i++;
        }
        printf("%s" , name[f[i]]);
        printf("\n");
    
        curr = curr->next;
        i++;
        k++;
    }
    
    
    return 0;
}

void ReadData(void)
{
    int i, j;
    int flag = 0;
    char *source, *destination = NULL;
    
    scanf("%d %d", &N, &M);
    
    source = (char*)malloc(10 * sizeof(char));
    destination = (char*)malloc(10 * sizeof(char));
    name = (char**)malloc(N * sizeof(char*));
    adlist = (CONN**)malloc(N * sizeof(CONN*));
    adlistT = (CONN**)malloc(N * sizeof(CONN*));
    
    s = (int*)malloc(N * sizeof(int));
    visited = (int*)malloc(N * sizeof(int));
    f = (int*)malloc(N * sizeof(int));
    

    for (i = 0; i < N; i++) {
        name[i] = (char*)malloc(10 * sizeof(char));
        adlist[i] = (CONN*)malloc(sizeof(CONN));
        adlist[i]->index = i;
        adlist[i]->next = NULL;
        adlistT[i] = (CONN*)malloc(sizeof(CONN));
        adlistT[i]->index = i;
        adlistT[i]->next = NULL;
        scanf("%s", name[i]);
    }
    
    for (i = 0; i < M; i++) {
        
        CONN *curr;
        CONN *build1;
        CONN *build2;
        
        build1 = (CONN*)malloc(sizeof(CONN));
        build1->next = NULL;
        build2 = (CONN*)malloc(sizeof(CONN));
        build2->next = NULL;
        
        scanf("%s -> %s",source, destination);
        
        for (j = 0; flag == 0; j++) {
            if (strcmp(destination, name[j]) == 0) {
                build1->index = j;
                curr = adlist[j];
                build2->next = curr->next;
                curr->next = build2;
                flag = 1;
            }
        }
        flag = 0;
        for (j = 0; flag == 0; j++) {
            if (strcmp(source, name[j]) == 0) {
                build2->index = j;
                curr = adlistT[j];
                build1->next = curr->next;
                curr->next = build1;
                flag = 1;
            }
        }
        flag = 0;
    }

}

void SCC(void)
{
    int i;
    for (i = 0; i < N; i++) {        // initialize graph's travel order
        s[i] = i;
    }
    DFS_Call(adlist);            // do DFS on Connect
    
    for (i = 0; i < N; i++) {        // initialize travel order
        s[i] = f[i];
    }
    DFS_Call(adlistT);            // do DFS on ConnectT
}

void DFS_Call(CONN **graph)
{
    int i;                            // Initialize loop index
    CONN *curr;                    // store travel orders
    
    SUBSUM = 0;                        // initialize subgroup num
    roots = NULL;                    // initialize roots
    curr = (CONN*)malloc(sizeof(CONN));
    curr->index = 0;
    curr->next = roots;
    roots = curr;
    
    for (i = 0; i < N; i++) {
        visited[i] = 0;
        f[i] = 0;
    }
    order = 0;
    for (i = 0; i < N; i++) {
        if (visited[s[i]] == 0) {            // if z[i] is not visited
            top_sort(s[i], graph);            // DFS z[i] in G
            CONN *curr;            // store travel times
            curr = (CONN*)malloc(sizeof(CONN));
            curr->index = order;
            curr->next = roots;
            roots = curr;
            SUBSUM++;                    // subgroup num + 1
        }
    }
}

void top_sort(int v, CONN **graph)                // Depth First search
{
    CONN *curr;                        // travel CONN
    
    visited[v] = 1;                        // v[i] is traveling
    for (curr = graph[v]->next; curr != NULL; curr = curr->next){
        if (visited[curr->index] == 0) {        // if vertice adjacents to i is not visited
            top_sort(curr->index, graph);        // DFS that vertice
        }
    }

    visited[v] = 2;                        // i visited
    f[N - order - 1] = v;            // store travel orders
    order++;                            // travel order ++
}

double GetTime()
{
    struct timeval tv;

    gettimeofday(&tv, NULL);
    return tv.tv_sec + 1e-6 * tv.tv_usec;       // sec + micro sec
}
