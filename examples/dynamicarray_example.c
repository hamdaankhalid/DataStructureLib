#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <dynamicarray.h>

// print utils
void printInt(void* element) {
    int* numPtr = (int*)element;
    printf("%d\n", *numPtr);
}

void printString(void* element) {
    char* str = (char*)element;
    printf("%s\n", str);
}

int main() {
    struct DynamicArray arr;
	
	int init = newArray(&arr, sizeof (int));
	if (init == -1) {
		return 1;
	}
    int num1 = 42;
    int num2 = 78;
    int num3 = 13;

    addElement(&arr, &num1); addElement(&arr, &num2); addElement(&arr, &num3);
    printData(&arr, printInt);

    // Free memory
    for (int i = 0; i < arr.occupied; i++) {
        free(arr.data[i]);
    }
    free(arr.data);

	// Now with strings
	char* test[] = {"abc", "def" , "jkl", "mno", "pqr", "stu", "vwx", "yz1", "234",
		"567", "890", "001", "002", "003", "004"};
	
    struct DynamicArray strArr;
	int initStrArr = newArray(&strArr, strlen(test[0]) + 1);
	if (initStrArr == -1) {
		return 1;
	}
	
	for (int i = 0; i < 15; i++) {
		addElement(&strArr, test[i]);
	}

    printData(&strArr, printString);
	
	// remove the 5th, 8th, 10th, 1st elements
	int removals[5] = {2, 1, 4, 6, 10};
	for (int i = 0; i < 5; i++) {
		removeElement(&strArr, removals[i]);
	}

	printData(&strArr, printString);

	// Free memory
    for (int i = 0; i < strArr.occupied; i++) {
        free(strArr.data[i]);
    }
    free(strArr.data);


    return 0;
}

