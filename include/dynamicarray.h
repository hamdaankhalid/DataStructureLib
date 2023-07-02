#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H

struct DynamicArray {
    void** data; // TODO: Why am I holding an array of pointers?
				 // Was it because of type casting to void*
    int capacity; // metadata to work with data dynamically
    int occupied;
    unsigned int sizeOfElement;
};

// Initializer
int dynamicArrayNew(struct DynamicArray* arr, unsigned int sizeOfElement);

// copies data pointed to by element into the array. The invoker may choose to dispose off the element since the data has been copied over.
// If there is data being copied over that is a pointer, we copy over the address. So if you have a string as a part of your element, please dont remove it from heap otherwise the pointer will now be pointing to already freed memory, and accessing it will create U.B.
int dynamicArrayAddElement(struct DynamicArray* arr, void* element);

// Go to the index, delete the item, and accordingly move the elements leftwards as needed.
void dynamicArrayRemoveByIdx(struct DynamicArray* arr, int index);

// Perform a side effect user defined function on each of the elements
void dynamicArrayForEach(struct DynamicArray* arr, void (*func)(void*));

#endif 
