#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H

struct DynamicArray {
    void** data;
    int capacity;
    int occupied;
    unsigned int sizeOfElement;
};


int dynamicArrayNew(struct DynamicArray* arr, unsigned int sizeOfElement);

int dynamicArrayAddElement(struct DynamicArray* arr, void* element);

void dynamicArrayRemoveByIdx(struct DynamicArray* arr, int index);

void dynamicArrayForEach(struct DynamicArray* arr, void (*func)(void*));

#endif 
