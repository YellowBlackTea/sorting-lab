#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 100000

//function to print an array
void printTab(int tab[], int size){
    for(int i = 0; i<size-1; printf("%d ", tab[i]) , i++);
    printf("%d\n", tab[size-1]);
}

//bubble sorting without the flag
void bubbleSort(int tab[], int size){
    int temp;
    for(int i = 0; i<size; i++){
        //first loop to kinda re-creating a new array each time 
        for(int j = 0; j<size-1; j++){
            //comparing and then exchanging
            if(tab[j]>tab[j+1]){
                temp = tab[j];
                tab[j] = tab[j+1];
                tab[j+1] = temp;
            }
        }
    }
}

//bubble sorting with the flag
void bubbleSortFlag(int tab[], int size){
    int temp;
    int flag = 0;       // flag not sorted 
    int lenght = size - 1;
    while(!flag){
        flag = 1;
        //first loop for kinda re-creating a new array each time 
        for(int i=0; i<lenght; i++){
            //comparing and then exchanging
            if(tab[i]>tab[i+1]){
                temp = tab[i];
                tab[i] = tab[i+1];
                tab[i+1] = temp;
                flag = 0; // not sorted yet
            }

        }
        lenght-- ;
    }
}

void insertSort(int tab[], int size){
    int temp, key = 1;
    for(int i = 0; i<size; i++){
        if(tab[key]>=tab[i]){
            key++;
        }
        else{
            for(int j = i; j>=0; j--){
                if(tab[j]>tab[j+1]){
                    temp = tab[j];
                    tab[j] = tab[j+1];
                    tab[j+1] = temp;
                }
            }
            key++;
        }
    }
}

void selectionSort(int tab[], int size){
    int temp, min;
    for(int i = 0; i<size-1; i++){
        min = tab[i];
        for(int j = i+1; j<size; j++){
            if(min > tab[j]){
                min = tab[j];    //assign the new value of min

                //the actual swapping
                temp = tab[i];   
                tab[i] = min;;
                tab[j] = temp;
            }
        }
    }
}

// function that fills an array of a given length with random numbers in the range {0, . . . , 99}
void rand_fill(int *array, unsigned int lenght){
    time_t time_seed;
    srand((unsigned) time(&time_seed));
    for(int i = 0; i<lenght; i++){
        array[i] = rand()%100;
    }
}

// function reversing the order
void reverse(int *array, int size){
    int tab[size];
    int temp;
    for(int i = 0; i<size; i++){
        tab[i] = array[size-1-i]; 
    }
    for(int j = 0; j<size; array[j]=tab[j], j++);
}


int main(){

    int tab[SIZE];
    //int L[5] = {1e1, 1e1, 1e1, 1e1, 1e1};
    //int L[5] = {1e2, 1e2, 1e2, 1e2, 1e2};
    //int L[5] = {1e3, 1e3, 1e3, 1e3, 1e3};
    int L[5] = {1e4, 1e4, 1e4, 1e4, 1e4};
    //int L[5] = {1e5, 1e5, 1e5, 1e5, 1e5};

    long double elapsed_time1 = 0;
    long double elapsed_time2 = 0;
    long double elapsed_time3 = 0;
    long double elapsed_time4 = 0;

    // variable to store the elapsed time
    // start of the clock/time
    clock_t start, end;

    
    for(int i = 0; i<5; i++){
        rand_fill(tab, L[i]);
        //printTab(tab,L[i]);

        start = clock();
        bubbleSort(tab,L[i]);
        reverse(tab,L[i]);
        end = clock();

        elapsed_time1 += (long double)(end - start)/CLOCKS_PER_SEC;
    }
    for(int i = 0; i<5; i++){
        rand_fill(tab, L[i]);
        //printTab(tab,L[i]);

        start = clock();
        bubbleSortFlag(tab, L[i]);
        //reverse(tab,L[i]);
        end = clock();

        elapsed_time2 += (long double)(end - start)/CLOCKS_PER_SEC;
    }

    for(int i = 0; i<5; i++){
        rand_fill(tab, L[i]);
        //printTab(tab,L[i]);

        start = clock();
        insertSort(tab,L[i]);
        //reverse(tab,L[i]);
        end = clock();

        elapsed_time3 += (long double)(end - start)/CLOCKS_PER_SEC;
    }

    for(int i = 0; i<5; i++){
        rand_fill(tab, L[i]);
        //printTab(tab,L[i]);

        start = clock();
        selectionSort(tab,L[i]);
        //reverse(tab,L[i]);
        end = clock();

        elapsed_time4 += (long double)(end - start)/CLOCKS_PER_SEC;
    }

    // converting to ms
    elapsed_time1 *= 1e3;
    elapsed_time2 *= 1e3;
    elapsed_time3 *= 1e3;
    elapsed_time4 *= 1e3;

    // to get the avg of 5
    elapsed_time1 = (long double)elapsed_time1/5;
    elapsed_time2 = (long double)elapsed_time2/5;
    elapsed_time3 = (long double)elapsed_time3/5;
    elapsed_time4 = (long double)elapsed_time4/5;


    printf("-----------------------------------------\n");
    printf("Bubble Sort run: \t%LFms\n", elapsed_time1);
    printf("Bubble SortFlag run: \t%LFms\n", elapsed_time2);
    printf("Insert Sort run: \t%LFms\n", elapsed_time3);
    printf("Selection Sort run: \t%LFms\n", elapsed_time4);
    printf("-----------------------------------------\n");

    return 0;
}

