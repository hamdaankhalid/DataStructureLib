#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H

struct DynamicArray {
    void** data;
    int capacity;
    int occupied;
    unsigned int sizeOfElement;
};


int newArray(struct DynamicArray* arr, unsigned int sizeOfElement);

int addElement(struct DynamicArray* arr, void* element);

void removeElement(struct DynamicArray* arr, int index);

void printData(struct DynamicArray* arr, void (*printElement)(void*));

#endif 
