#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//function to print an array
void printTab(int tab[], int size){
    for(int i = 0; i<size-1; printf("%d ", tab[i]) , i++);
    printf("%d\n", tab[size-1]);
    printf("\n");
}

// function that fills an array of a given length with random numbers in the range {0, . . . , 99}
void rand_fill(int *array, unsigned int lenght){
    time_t time_seed;
    srand((unsigned) time(&time_seed));
    for(int i = 0; i<lenght; i++){
        array[i] = rand()%100;
    }
}

// swapping two numbers 
void swap(int *a, int *b){
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

// implementing a quicksort (pivot, sub-problem, borders, etc)
void Quicksort(int *array, int left, int right){
    // pivot arr=[m], will have to make a few more tests with different m to see if one of them is better
    int m = (left+right)/2;                         // choosing the middle
    //int m = left+rand()%(right-left);               // choosing a random number
    //int m = left;                               // choosing left
    //int m = right;                               // choosing right

    int i = left;
    int j = right;

    while(i<j){
        // loop: array[i] on its place
        while(array[i]<array[m]){
            //printf("boucle i<m: i=%d et arr[i]=%d.\n", i, array[i]);
            i++;
        }
        // loop: array[j] on its place
        while(array[j]>array[m]){
            //printf("boucle j>m: j=%d et arr[j]=%d.\n", j, array[j]);
            j--;
        }
        // the actual swapping
        if(i<=j){
            //printf("\n passe ici\n");
            swap(&array[i], &array[j]);
            i++;
            j--;
        }
    }
    // recursive for the first part of the array (subproblem 1)
    if(left<j){
        //printf("\n dans la première récurssion\n");
        Quicksort(array, left, j);
    }
    // recursive for the second part of the array (subproblem 2)
    if(i<right){
        //printf("\n dans la deuxième récurssion\n");
        Quicksort(array, i, right);
    }
}

// binary sort
// assuming non-negative elements
void binary_quicksort(int *array, int left, int right, int k){
    int i = left;
    int j = right;

    // condition to stop the sorting
    if(i>right || j<left || k<0){
        return;
    } 

    while(i<=j){
        while(!(array[i] & (1<<k)) && i<right){
            //printf("boucle des 0: i=%d et arr[i]=%d.\n", i, array[i]);
            i++;
        }
        while((array[j] & (1<<k)) && j>left){
            //printf("boucle des 1: j=%d et arr[j]=%d.\n", j, array[j]);
            j--;
        }
        if(i<=j){
            //printf("\n passe ici\n");
            swap(&array[i], &array[j]);
            //for(int cpt = 0; cpt<10; printf("%d ", array[cpt]), cpt++);
            //printf("\n");
            i++;
            j--;
        }
    }

    binary_quicksort(array, left, j, k-1);
    binary_quicksort(array, i, right, k-1);
}

// sift_down for array[i]
void sift_down(int *array, int size, int i){
    int j = 2*i + 1;    // for left child

    while(j<size){
        j = 2*i+1;
        // return if j exceeds the size of the array
        if(j>=size){
            return;
        }
        // if the next element is larger than the previous one
        // if j+1 child is larger than j child
        if((j+1 < size) && (array[j+1]>array[j])){
            j++;
        }
        // return if i is larger than j
        if(array[i]>=array[j]){
            return;
        }
        // as long as i is not the root
        swap(&array[i],&array[j]);
        i=j;
    }
}

//heap sort
void heap_sort(int *array, int size){
    /*
    long double elapsed_time = 0;
    clock_t start, end;
    */

    // building a heap
    for(int i = size/2 - 1; i>=0; i--){
        sift_down(array,size,i);
    }
    
    //start = clock();
    // sorting
    while(size>1){
        swap(&array[0],&array[size-1]);
        size--;
        sift_down(array,size,0);
    }
    //end = clock();
    /*
    elapsed_time += (long double)(end - start)/CLOCKS_PER_SEC;
    elapsed_time *= 1e3;
    printf("Building heap run: \t\t%LFms\n", elapsed_time);*/
}

// function reversing the order (from biggest to smallest)
void reverse(int *array, int size){
    int tab[size];
    int temp;
    Quicksort(array, 0, size-1);
    for(int i = 0; i<size; i++){
        tab[i] = array[size-1-i]; 
    }
    for(int j = 0; j<size; array[j]=tab[j], j++);
}

int main(){
    int k = 31;
    int left = 0;

    int L = 1e5;        // change value of L = 1e1, 1e2, 1e3, 1e4, 1e5
    int *tab;

    long double elapsed_time1 = 0;
    long double elapsed_time2 = 0;
    long double elapsed_time3 = 0;


    // variable to store the elapsed time
    // start of the clock/time
    clock_t start, end;


    for(int i = 0; i<5; i++){
        tab = (int *) malloc(sizeof(int)*L);
        rand_fill(tab, L);
        //reverse(tab,L);

        start = clock();
        Quicksort(tab, left, L-1);
        end = clock();

        elapsed_time1 += (long double)(end - start)/CLOCKS_PER_SEC;
        free(tab);
    }

    for(int i = 0; i<5; i++){
        tab = (int *) malloc(sizeof(int)*L);
        rand_fill(tab, L);
        //reverse(tab,L);

        start = clock();
        binary_quicksort(tab, left, L-1, k);
        end = clock();

        elapsed_time2 += (long double)(end - start)/CLOCKS_PER_SEC;
        free(tab);
    }

    for(int i = 0; i<5; i++){
        tab = (int *) malloc(sizeof(int)*L);
        rand_fill(tab, L);
        //reverse(tab,L);

        start = clock();
        heap_sort(tab,L);
        end = clock();

        elapsed_time3 += (long double)(end - start)/CLOCKS_PER_SEC;
        free(tab);
    }


    // converting to ms
    elapsed_time1 *= 1e3;
    elapsed_time2 *= 1e3;
    elapsed_time3 *= 1e3;

    // to get the avg of 5
    elapsed_time1 = (long double)elapsed_time1/5;
    elapsed_time2 = (long double)elapsed_time2/5;
    elapsed_time3 = (long double)elapsed_time3/5;


    printf("-----------------------------------------\n");
    printf("Quick Sort run: \t%LFms\n", elapsed_time1);
    printf("Binary Sort run: \t%LFms\n", elapsed_time2);
    printf("Heap Sort run: \t\t%LFms\n", elapsed_time3);
    printf("-----------------------------------------\n");

    return 0;
}