// EE3980 HW01 Quardratic Sorts
// 106061225, 楊宇羲
// 2020/3/10

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>

double GetTime(void);								// get local time in seconds
void CopyArray(char **list, char** a, int n);		// copy array
void SelectionSort(char **list,int n);				// in-place selection sort
void InsertionSort(char **list,int n);				// in-place insertion sort
void BubbleSort(char **list,int n);					// in-place bubble sort
void OddEvenSort(char **list,int n);				// in-placr shaker sort

int main(){

	int R = 500;									// time of repetitions
	int n;											// size of the array
	int i;										// for loop counting
	double t, t0, t1;								// for CPU time counting
    
    scanf("%d", &n);                                // size of array

	char **a = (char**)malloc(n*sizeof(char*));		// the original array
	char **list = (char**)malloc(n*sizeof(char*));	// the array being sorted
	char buffer[512];								// buffer for storing
	

	for(i=0; i<n; i++){								// storing array to **a
		scanf("%s", buffer);
		a[i]=malloc(strlen(buffer+1));
		strcpy(a[i],buffer);
	}
	
	// selection sort
	
	t0 = GetTime();									// start counting time
	for(i=0; i<R; i++){								// repeat R times
		CopyArray(list,a,n);						// call copy function
		SelectionSort(list,n);						// start selection sort
	}
	t1 = GetTime();									// stop counting time

	t  = (t1-t0)/R;									// calculate CPU time
	printf("Selection Sort: N = %d CPU = %e seconds\n", n, t );

	// insertion sort

	t0 = GetTime();									// start counting time
	for(i=0; i<R; i++){								// repeat R times
		CopyArray(list,a,n);						// call copy function
		InsertionSort(list,n);						// start insertion sort
	}
	t1 = GetTime();									// stop counting time
	
	t  = (t1-t0)/R;									// calculate CPU time
	printf("Insertion Sort: N = %d CPU = %e seconds\n", n, t );
	
	// bubble sort

	t0 = GetTime();									// start counting time
	for(i=0; i<R; i++){								// repeat R times
		CopyArray(list,a,n);						// call copy function
		BubbleSort(list,n);							// start bubble sort
	}
	t1 = GetTime();									// stop counting time
	
	t  = (t1-t0)/R;									// calculate CPU time
	printf("Bubble Sort: N = %d CPU = %e seconds\n", n, t );

	// odd even sort
	
	t0 = GetTime();									// start counting time
	for(i=0; i<R; i++){								// repeat R times
		CopyArray(list,a,n);						// call copy function
		OddEvenSort(list,n);						// start odd even sort
	}
	t1 = GetTime();									// stop counting time

	t  = (t1-t0)/R;									// calculate CPU time
	printf("OddEven Sort: N = %d CPU = %e seconds\n", n, t );
	
	// print array
	
	for(i=0; i<n; i++){								// Display sorted array
		printf("%d %s\n", i+1, list[i]);
	}
	return 0;
}

void SelectionSort(char **list,int n){
	
	int i, j;								// for loop counting
	char *temp;								// for swapping

	for(i = 0; i < n; i++){					// list[i] is standard
		for(j = i+1; j < n; j++){			// looking for smaller element
			if(strcmp(list[i], list[j])>0){	// swap if latter index is smaller
				temp = list[i];
				list[i] = list[j];
				list[j] = temp;
			}
		}
	}
}

void InsertionSort(char **list,int n){
	
	int i;									// for loop counting
	char *temp;								// for swapping
	
	for(i = 1; i < n; i++){
		temp = list[i];						// move to proper place
		int j = i-1;
		while (strcmp(temp,list[j])<0 && j>0){	// find proper i
			list[j+1] = list[j];			// move to upper place
			j--;
		}
		list[j+1] = temp;					// replace temp
	}
}

void BubbleSort(char **list,int n){
	
	int i, j;
	char *temp;
	
	for(i = 0; i < n-1; i++){					
		for(j = 0; j < n-1-i; j++){				// sort from the last element
			if(strcmp(list[j], list[j+1])>0){	// compare to the right
				temp = list[j];
				list[j] = list[j+1];
				list[j+1] = temp;
			}
		}
	}
}

void OddEvenSort(char** list,int n){
	
	int sorted=0;
	int i;
	char *temp;
	
	while (!sorted){
		sorted=1;
		for(i = 1; i <= n-2; i=i+2){			// sort even element
			if(strcmp(list[i], list[i+1])>0){	// apply bubble sort
				temp = list[i];
				list[i] = list[i+1];
				list[i+1] = temp;
				sorted = 0;
			}
		}
		for(i = 0; i <= n-2; i=i+2){			// sort odd element
			if(strcmp(list[i], list[i+1])>0){	// apply bubble sort
				temp = list[i];
				list[i] = list[i+1];
				list[i+1] = temp;
				sorted = 0;
			}
		}
	}
}

void CopyArray(char** list, char** a, int n){
	
	int j;
	for(j = 0; j < n; j++){							
		list[j] = malloc(strlen(a[j]+1));	// dynamic storage
		strcpy(list[j], a[j]);				// use strcpy to copy
	}
}

double GetTime(){

	struct timeval tv;

	gettimeofday(&tv, NULL);
	return tv.tv_sec + 1e-6 * tv.tv_usec;	// sec + micro sec
}
