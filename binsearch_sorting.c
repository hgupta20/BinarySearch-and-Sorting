#include <stdio.h>
#include <stdlib.h> //to be used for malloc

// Prototype Functions
void arrayCopy(int fromArray[], int toArray[], int size);
void myFavorateSort(int arr[], int size);
int linSearch(int arr[], int size, int target, int* numComparisons);
int binSearch(int arr[], int size, int target, int* numComparisons);

//function to display array
void printArray(int arr[], int size){
    int i;
    for(i = 0; i < size; i++)
        printf("%d. %d\n", i, arr[i]);
    printf("\n");
}//end printArray()


int main(void){
    
    int userInput;          //for user input
    
    int size = 100;         //size to grow the array dynamically
    int count = 0;          //flag or counter

    int *dArray1 = (int *) malloc(sizeof(int) * size);    //dynamic array 1, using malloc to allocate memory

    //prompt for user input
    printf("Enter values into array. Enter \"-999\" when finished.\n");

    //while loop to add user input in dArr1
    while(userInput != -999){ //stops when user input is -999
        scanf("%d", &userInput); //reading user input from data files
        if(count >= size){ //checking if number of inputs is greater than the original size of array
            int i; //initializing variable for for-loop
            int *temp = (int *) malloc(sizeof(int) * size * 2);  //dynamic array temp, using malloc to allocate memory

            for(i = 0; i < size; i++) //Copying previous values to larger array 
                temp[i] = dArray1[i];

            free(dArray1); //free the space taken in memory

            dArray1 = temp; // now dArray1 will always point to temp array 
            size = size * 2; //changing the size to the larger array space
        }
        dArray1[count] = userInput; //adding value to array
        count++; //increase counter
    }

    int *dArray2 = (int *) malloc(sizeof(int) * size);    //dynamic array 2, using malloc to allocate memory

    //copying values from dArray1 to dArray2
    arrayCopy(dArray1, dArray2, count - 1);

    //sorting dArray1 with favorate sort
    myFavorateSort(dArray1, count - 1);

    printf("\nArray has been sorted and a new Array with the same elements has been made.\n");
    // To print the array uncomment the print statements
    //Sorted Array
    //printArray(dArray1, count - 1);
    //UnSorted Array
    //printArray(dArray2, count - 1);

    userInput = 0; //reset value for use with next loop

    //prompting for user input for values to search for
    printf("\nEnter values to search for in array. Enter \"-999\" when finished.");
    //While loop to use linear and Binary search
    while(userInput != -999){
        int positioninLin = 0, comparisonsinLin = 0;    //variables for linear search
        int positioninBin = 0, comparisonsinBin = 0;    //variables for binary search

        scanf("%d", &userInput);   //reading user input
        if(userInput == -999){  //check to see if user input is -999
            printf("Program Exiting\n\n");
            break;
        }

        positioninLin = linSearch(dArray2, count - 1, userInput, &comparisonsinLin); //searching for values using linear search
        positioninBin = binSearch(dArray1, count - 1, userInput, &comparisonsinBin); //searching for values using binary search

        if(positioninLin == -1 && positioninBin == -1){
            printf("\n%d has not been found in the array. The number of comparisons using Linear Search is %d\n", userInput, comparisonsinLin);
            printf("%d has not been found in the array. The number of comparisons using Binary Search is %d\n\n", userInput, comparisonsinBin);

            //reset values to 0 
            comparisonsinBin = 0;
            comparisonsinLin = 0;
            positioninLin = 0;
            positioninBin = 0;  
        }
        else{
            printf("\n%d has been found at index %d. The number of comparisons using Linear Search is %d\n", userInput, positioninLin, comparisonsinLin);
            printf("%d has been found at index %d. The number of comparisons using Binary Search is %d\n\n", userInput, positioninBin, comparisonsinBin);

            //reset values to 0
            comparisonsinBin = 0;
            comparisonsinLin = 0;
            positioninLin = 0;
            positioninBin = 0;  
        }
    }

    return 0;
}//end main()

//Defining Functions

//Copy values from one array to the another
void arrayCopy(int fromArray[], int toArray[], int size){
    int i;
    for(i = 0; i < size; i++)
        toArray[i] = fromArray[i];
}//end arrayCopy()

//Sorting array in ascending order using selection sort
void myFavorateSort(int arr[], int size){
    int i, j, position, swap;

    for(i = 0; i < (size - 1); i++){
        position = i;

        for(j = i + 1; j < size; j++){
           if(arr[position] > arr[j])
               position = j;
        }
        if(position != i){
            swap = arr[i];
            arr[i] = arr[position];
            arr[position] = swap;
        }
    }
}//end myFavorateSort()


//Binary Search function
int binSearch(int arr[], int size, int target, int* numComparisons){
    int low = 0;// low  
    int high = size - 1;// high   
    int mid = (low + high) / 2;   //mid

    while(low <= high){
        *numComparisons += 1;
        if(arr[mid] < target)
            low = mid + 1;
        else if(arr[mid] == target){
            return mid;
            break;
        }
        else
            high = mid - 1;

        mid = (low + high) / 2;
    }

    if(low > high)
        return -1;
}//end binSearch()

//Linear Search function
int linSearch(int arr[], int size, int target, int* numComparisons){
    int i;
    for(i = 0; i < size; i++){
        *numComparisons += 1;
        
        if(target == arr[i])
            break;
    }

    if(i == size)
        return -1;
    else
        return i;
}//end linSearch()

