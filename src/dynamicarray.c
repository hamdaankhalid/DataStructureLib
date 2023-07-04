#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <dynamicarray.h>
#include <commontypes.h>

int dynamicArrayNew(struct DynamicArray* arr, unsigned int sizeOfElement) {
    arr->sizeOfElement = sizeOfElement;
    arr->occupied = 0;
    arr->capacity = 8;
    arr->data = malloc(arr->capacity * sizeof(void*));
	EXIT_IF_MALLOC_FAIL(arr->data);

	return 0;
}

int dynamicArrayAddElement(struct DynamicArray* arr, void* element) {
    if (arr->occupied == arr->capacity) {
        void** newData = realloc(arr->data, arr->capacity * 2 * sizeof(void*));
		EXIT_IF_MALLOC_FAIL(newData);

        arr->data = newData;
        arr->capacity *= 2;
    }

    arr->data[arr->occupied] = malloc(arr->sizeOfElement);
	EXIT_IF_MALLOC_FAIL(arr->data[arr->occupied]);

    memcpy(arr->data[arr->occupied], element, arr->sizeOfElement);

    arr->occupied++;

    return 0;
}


void dynamicArrayRemoveByIdx(struct DynamicArray* arr, int index) {
    if (index < 0 || index >= arr->occupied) {
        printf("Invalid index\n");
        return;
    }

    free(arr->data[index]);

    // Move elements after the removed element one box back
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

void dynamicArrayForEach(struct DynamicArray* arr, void (*func)(void*)) {
    for (int i = 0; i < arr->occupied; i++) {
        printf("Element %d: ", i);
        func(arr->data[i]);
    }
}

