#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct DynamicArray {
    void** data;
    int capacity;
    int occupied;
    unsigned int sizeOfElement;
};

int newArray(struct DynamicArray* arr, unsigned int sizeOfElement) {
    if (!arr) {
        printf("Failed to allocate memory while creating the array\n");
        return -1;
    }

    arr->sizeOfElement = sizeOfElement;
    arr->occupied = 0;
    arr->capacity = 8;
    arr->data = malloc(arr->capacity * sizeof(void*));
    if (!arr->data) {
        printf("Failed to allocate memory for internal array\n");
        return -1;
    }

	return 0;
}

int addElement(struct DynamicArray* arr, void* element) {
    if (arr->occupied == arr->capacity) {
        void** newData = realloc(arr->data, arr->capacity * 2 * sizeof(void*));
        if (!newData) {
            printf("Failed to resize the array\n");
            return -1;
        }
        arr->data = newData;
        arr->capacity *= 2;
    }

    arr->data[arr->occupied] = malloc(arr->sizeOfElement);
    if (!arr->data[arr->occupied]) {
        printf("Failed to allocate memory for element\n");
        return -1;
    }

    memcpy(arr->data[arr->occupied], element, arr->sizeOfElement);

    arr->occupied++;

    return 0;
}


void removeElement(struct DynamicArray* arr, int index) {
    if (index < 0 || index >= arr->occupied) {
        printf("Invalid index\n");
        return;
    }

    free(arr->data[index]);

    // Move elements after the removed element
    for (int i = index; i < arr->occupied - 1; i++) {
        arr->data[i] = arr->data[i + 1];
    }

    arr->occupied--;

    // Check if capacity needs to be reduced
    if (arr->occupied <= arr->capacity / 4) {
        void** newData = realloc(arr->data, (arr->capacity / 2) * sizeof(void*));
        if (newData) {
            arr->data = newData;
            arr->capacity /= 2;
        }
    }
}

void printData(struct DynamicArray* arr, void (*printElement)(void*)) {
    for (int i = 0; i < arr->occupied; i++) {
        printf("Element %d: ", i);
        printElement(arr->data[i]);
    }
}

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

